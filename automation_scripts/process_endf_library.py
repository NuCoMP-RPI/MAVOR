import argparse
import os
import shutil
import time
from pathlib import Path


# Global variables
mavor_exe: Path | None = None
endf_lib: Path | None = None

output_dir: Path | None = None
working_directory: Path | None = None
delete_working_directory: bool = False

def parse_cli_args() -> None:
    """Parses command-line arguments and updates global variables."""
    global mavor_exe, endf_lib
    global output_dir, working_directory, delete_working_directory

    parser = argparse.ArgumentParser(description = "This script collects LEAPR and ENDF files from an ENDF thermal scattering library and makes a series of calls to an automation script to generate OTF files for the entire ENDF library.")
    parser.add_argument("mavor_exe", type=Path, help="Path to the MAVOR executable built on your system.")
    parser.add_argument("endf_lib", type=Path, help="Path to the ENDF library of interest. Must contain the LEAPR and ENDF files and the names of corresponding files must match. Eg. 'tsl-HinH2O.leapr' and 'tsl-HinH2O.endf")

    parser.add_argument("-d", "--working_dir", type=Path, help="Sets a location for MAVOR-related files. If not set, a directory will be created at the script location.")
    parser.add_argument("-o", "--output", type=Path, help="Sets the location of the generated OTF files.")
    parser.add_argument("-c", "--clean", action="store_true", help="Delete the working directory after the script calls are completed.")

    args = parser.parse_args()

    mavor_exe = args.mavor_exe
    endf_lib = args.endf_lib

    working_directory = args.working_dir if args.working_dir else Path(f"{endf_lib.name}_working_dir").resolve()
    working_directory.mkdir(exist_ok=True, parents=True)
    output_dir = args.output if args.output else Path("OTF_Files").resolve()
    output_dir.mkdir(exist_ok=True, parents=True)
    delete_working_directory = args.clean

    if delete_working_directory and output_dir.resolve().is_relative_to(working_directory.resolve()):
        raise ValueError(f"Output directory '{output_dir}' is inside the working directory '{working_directory}', preventing deletion.")

def get_materials() -> list[float]:
    endf_files = [file.stem for file in Path(endf_lib).glob('*.endf') if file.is_file()]
    leapr_files = [file.stem for file in Path(endf_lib).glob('*.leapr') if file.is_file()]
    materials = list(set(endf_files) & set(leapr_files))
    if materials == []:
        raise RuntimeWarning(f"No materials were found to have match LEAPR and ENDF file names.")
    return materials

def process_material(mat_name: str):
    leapr_file = Path(endf_lib, f"{mat_name}.leapr")
    endf_file = Path(endf_lib, f"{mat_name}.endf")
    output_file = Path(output_dir, f"{mat_name}_OTF.h5")
    command = f"python process_single_material.py {mavor_exe} {leapr_file} {endf_file} -n {mat_name} -o {output_file} -d {working_directory}"
    if delete_working_directory:
        command += " -c"
    os.system(command)

if __name__ == "__main__":
    start_time = time.perf_counter()

    parse_cli_args()
    print(f"Processing {endf_lib.name}")
    print()
    lib_mats = get_materials()
    for mat in lib_mats:
        process_material(mat)
        print()

    if delete_working_directory:
        shutil.rmtree(working_directory)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print(f"Time to process library: {elapsed_time:.6f} seconds")
