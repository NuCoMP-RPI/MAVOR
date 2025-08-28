import argparse
import multiprocessing as mp
import os
import shutil
import time
from functools import reduce
from pathlib import Path

import h5py as h5
import numpy as np

# Global variables
mavor_exe: Path | None = None
leapr_file: Path | None = None
endf_file: Path | None = None

mat_name: str | None = None
output_file: Path | None = None
working_directory: Path | None = None
delete_working_directory: bool = False

fit = 0
num = 15
njoy_results_loc_subpath = Path("Processed_NJOY_Results")
sab_results_loc_subpath = Path("SAB_Results")
non_unioned_sab_results_loc_subpath = Path(sab_results_loc_subpath, "non_unioned")
unioned_energy_grid_file_subpath_name = Path(sab_results_loc_subpath, "unioned_energy_grid.txt")
unioned_sab_results_loc_subpath = Path(sab_results_loc_subpath, "unioned")

def parse_cli_args() -> None:
    """Parses command-line arguments and updates global variables."""
    global mavor_exe, leapr_file, endf_file
    global mat_name, output_file, working_directory, delete_working_directory

    parser = argparse.ArgumentParser(
        description = "This script completes a series of calls to MAVOR to generate an OTF scattering file given LEAPR and ENDF files."
    )
    parser.add_argument("mavor_exe", type=Path, help="Path to the MAVOR executable built on your system.")
    parser.add_argument("leapr_file", type=Path, help="Path to the LEAPR file of interest.")
    parser.add_argument("endf_file", type=Path, help="Path to the ENDF file of interest.")

    parser.add_argument("-n", "--material_name", type=str, help="Sets the name of the material.  Will be used in creating directories and files.")
    parser.add_argument("-o", "--output", type=Path, help="Sets the location and name of the generated OTF file.")
    parser.add_argument("-d", "--working_dir", type=Path, help="Sets a location for MAVOR-related files. If not set, a directory will be created at the script location.")
    parser.add_argument("-c", "--clean", action="store_true", help="Delete the working directory after the MAVOR calls are completed.")

    args = parser.parse_args()

    # Assign parsed arguments to global variables given defaults if options aren't passed
    mavor_exe = args.mavor_exe
    leapr_file = args.leapr_file
    endf_file = args.endf_file

    mat_name = args.material_name if args.material_name else leapr_file.stem
    output_file = args.output if args.output else Path(f"{mat_name}_OTF.h5").resolve()
    working_directory = args.working_dir if args.working_dir else Path(f"{mat_name}_working_dir").resolve()
    delete_working_directory = args.clean

    if delete_working_directory and output_file.resolve().is_relative_to(working_directory.resolve()):
        raise ValueError(f"Output file '{output_file}' is inside the working directory '{working_directory}', preventing deletion.")

def run_mavor(args_string = ""):
    os.system(f"{mavor_exe} " + args_string)

def run_all_mavor(args_string_list):
    for args_string in args_string_list:
        run_mavor(args_string)

def run_all_mavor_threaded(args_string_list):
    cores = mp.cpu_count()
    thread_data = np.array_split(args_string_list, cores)
    p = mp.Pool(processes=cores)
    p.map(run_all_mavor, thread_data)

def print_time(t0):
    print(f"--Completed in {time.perf_counter() - t0:.2f} seconds")

def gen_njoy_results():
    t0 = time.perf_counter()
    print("-Creating Leapr files and running NJOY.")
    results_loc = Path(working_directory, mat_name, njoy_results_loc_subpath)
    results_loc.mkdir(exist_ok=True, parents=True)
    command_args = f" -s tsl -f -i {leapr_file} -o {results_loc} -d 5"
    run_mavor(command_args)
    print_time(t0)

def gen_non_unioned_sab_results():
    t0 = time.perf_counter()
    print("-Generating Direct SAB sampling distributions while linearizing the incident energy grid.")
    njoy_results_loc = Path(working_directory, mat_name, njoy_results_loc_subpath)
    njoy_results_files = [file for file in Path(njoy_results_loc).glob('*') if file.is_file()]
    sab_results_loc = Path(working_directory, mat_name, non_unioned_sab_results_loc_subpath)
    sab_results_loc.mkdir(exist_ok=True, parents=True)
    run_args_list = []
    for file in njoy_results_files:
        results_file = Path(sab_results_loc, file.stem.split("njoy")[0] + "sab.h5")
        run_args_list.append(f" -s sab -i {file} -o {results_file} --sigmoid")
    run_all_mavor_threaded(run_args_list)
    print_time(t0)

def remove_duplicates(values: np.ndarray, fmt: str) -> np.ndarray[str]:
    """
    Remove duplicates after formatting numbers to strings.
    Keeps the first occurrence and preserves order.
    """
    unique = []
    seen = set()
    for val in values:
        sval = f"{val:{fmt}}"
        if sval not in seen:
            seen.add(sval)
            unique.append(sval)
    return np.array(unique, dtype=str)

def gen_unioned_energy_grid():
    t0 = time.perf_counter()
    print("-Determining linearized, unioned incident energy grid.")
    sab_results_loc = Path(working_directory, mat_name, non_unioned_sab_results_loc_subpath)
    file_paths = [file for file in Path(sab_results_loc).glob('*') if file.is_file()]
    energy_grid = reduce(np.union1d, (h5.File(file, 'r')['XS/ENERGY_GRID'][:] for file in file_paths))
    energy_file = Path(working_directory, mat_name, unioned_energy_grid_file_subpath_name)
    str_vals = remove_duplicates(energy_grid, "1.4e") # Delete any duplicate energies after formatting
    np.savetxt(energy_file, str_vals, fmt="%s")
    print_time(t0)

def gen_unioned_sab_results():
    t0 = time.perf_counter()
    print("-Generating Direct SAB sampling distributions with linearized, unioned incident energy grid.")
    njoy_results_loc = Path(working_directory, mat_name, njoy_results_loc_subpath)
    njoy_results_files = [file for file in Path(njoy_results_loc).glob('*') if file.is_file()]
    sab_results_loc = Path(working_directory, mat_name, unioned_sab_results_loc_subpath)
    sab_results_loc.mkdir(exist_ok=True, parents=True)
    energy_grid_file = Path(working_directory, mat_name, unioned_energy_grid_file_subpath_name)
    run_args_list = []
    for file in njoy_results_files:
        results_file = Path(sab_results_loc, file.stem.split("njoy")[0] + "sab.h5")
        run_args_list.append(f" -s sab -i {file} -o {results_file} -u {energy_grid_file} --sigmoid")
    run_all_mavor_threaded(run_args_list)
    print_time(t0)

def gen_coefficients():
    t0 = time.perf_counter()
    print("-Generating coefficients.")
    sab_files_loc = Path(working_directory, mat_name, unioned_sab_results_loc_subpath)
    results_loc = Path(working_directory, mat_name)
    results_loc.mkdir(exist_ok=True, parents=True)
    results_file = Path(results_loc, f"{mat_name}_coeffs.h5")
    command_args = f" -s otf -i {sab_files_loc} -o {results_file} --b_xs --p_xs {fit} --p_xs_num {num} --b_beta --p_beta {fit} --p_beta_num {num} --b_alpha --p_alpha {fit} --p_alpha_num {num}"
    run_mavor(command_args)
    print_time(t0)

def gen_otf_file():
    t0 = time.perf_counter()
    print("-Adding elastic scattering parameters for full OTF treatment.")
    coeff_file = Path(working_directory, mat_name, f"{mat_name}_coeffs.h5" )
    command_args = f" -s elastic -i {coeff_file} -e {endf_file} -o {output_file}"
    run_mavor(command_args)
    print_time(t0)

def full_run():
    gen_njoy_results()
    gen_non_unioned_sab_results()
    gen_unioned_energy_grid()
    gen_unioned_sab_results()
    gen_coefficients()
    gen_otf_file()

if __name__ == "__main__":
    start_time = time.perf_counter()

    parse_cli_args()
    print(f"Processing {mat_name}.")
    full_run()
    if delete_working_directory:
        shutil.rmtree(working_directory)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print(f"Time to generate OTF file for {mat_name}: {elapsed_time:.6f} seconds.")
