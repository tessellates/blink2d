from subprocess import call
import argparse

import os
import contextlib
import subprocess

import argparse


# We add the option to create a clean build, -c. Running this script "python make_script.py -c" we will pass -c as true
parser = argparse.ArgumentParser()
parser.add_argument('-r', action='store_true')
release = parser.parse_args().r



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

cmd = ["cmake", "-G", "Xcode", "-DBUILD_TESTS=True", "-DXCODE=True", ".."]

if (release):
    cmd.append("-DCMAKE_BUILD_TYPE=Release")


with change_dir("xcodeProject"):
    call(cmd)
