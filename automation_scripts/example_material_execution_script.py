from pathlib import Path
import os

mavor_exe = Path("..","build","mavor")
leapr_file = Path("..","build","test_files","simple_endf_library","tsl-HinH2O.leapr")
endf_file = Path("..","build","test_files","simple_endf_library","tsl-HinH2O.endf")

cmd = f"python process_single_material.py {str(mavor_exe)} {str(leapr_file)} {str(endf_file)}"

os.system(cmd)