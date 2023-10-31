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

cmd = ["cmake", "-G", "Xcode", "-DBUILD_TESTS=True", "-DXCODE=True", ".."]

with change_dir("xcodeProject"):
    call(cmd)
