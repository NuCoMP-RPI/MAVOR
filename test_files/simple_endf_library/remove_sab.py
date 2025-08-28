# Simple script to remove the inelastic component of thermal scattering data in ENDF files.
# Takes all file in directory that end with ".endf", opens them with ENDFtk, removes file 7, mt 4, and then writes the file back out

import ENDFtk

from pathlib import Path

endf_files = [file for file in Path(".").glob("*.endf") if file.is_file()]

for file in endf_files:
    tape = ENDFtk.tree.Tape.from_file(str(file))
    tape.materials.front().remove(7,4)
    tape.update_directory()
    tape.to_file(str(file))