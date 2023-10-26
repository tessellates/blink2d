from subprocess import call
import argparse

import os
import contextlib
import subprocess

@contextlib.contextmanager
def change_dir(destination):
    """
    Temporarily change the working directory.
    """
    current_path = os.getcwd()
    try:
        os.chdir(destination)
        yield
    finally:
        os.chdir(current_path)

# We add the option to create a clean build, -c. Running this script "python make_script.py -c" we will pass -c as true
parser = argparse.ArgumentParser()
# We add the option to create a debug build, -d. Default will then be a release build
parser.add_argument('-d', action='store_true')
parser.add_argument('-c', action='store_true')

cmd = ["python3", "make_script.py"]

subprocess.run(["rm", "-rf", "build/tests"])

if parser.parse_args().d:
    cmd.append("-d")

cmd.append("-t")

call(cmd)

with change_dir("build"):
    subprocess.check_call(["ctest", "--verbose"])
