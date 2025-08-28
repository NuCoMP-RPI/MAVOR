from pathlib import Path
import os

# mavor_exe = Path.home() / "School/My_Programs/Mavor_Support/external/Mavor/build/mavor"
# endf_loc = Path.home() / "School/My_Programs/Mavor_Support/Data/Libraries/ENDF_8_0"
# working_dir = Path.home() / "School/My_Programs/Mavor_Support/Data/Test_ENDF8_0"
# output_loc = Path.home() / "School/My_Programs/Mavor_Support/Data/Test_ENDF8_0_OTF_Files"

mavor_exe = Path("..","build","mavor")
endf_loc = Path("..","build","test_files","simple_endf_library")
working_dir = Path("working_dir")
output_loc = Path("otf_files")

cmd = f"python process_endf_library.py {str(mavor_exe)} {str(endf_loc)} -d {str(working_dir)} -o {str(output_loc)}"

os.system(cmd)