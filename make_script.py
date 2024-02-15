# Building C++ projects is different for every OS

import os
import shutil
import subprocess
import sys
import argparse

__NAME = "blink2d"

isWin = sys.platform == ("win32" or "win64")
isDar = sys.platform == "darwin"

# We add the option to create a clean build, -c. Running this script "python make_script.py -c" we will pass -c as true
parser = argparse.ArgumentParser()
parser.add_argument('-c', action='store_true')
# We add the option to create a debug build, -d. Default will then be a release build
parser.add_argument('-d', action='store_true')
parser.add_argument('-t', action='store_true')
clean = parser.parse_args().c
debug = parser.parse_args().d
tests = parser.parse_args().t

# Get the current working directory
path = os.getcwd()

# The path in which we need to invoke the cmake command is in the build folder
buildPath = os.path.join(path, "build")

# For a clean build we remove all traces of the previous build and remake the build folder
if clean:
    subprocess.run(["rm", "-rf", "build"])
    subprocess.run(["mkdir", "build"])


cmakeBin = "cmake" # we use the default cmake


cmakeCommands = [cmakeBin, ".."]
if not debug:
    cmakeCommands.append("-DCMAKE_BUILD_TYPE=Release")
    config = "Release"
else:
    cmakeCommands.append("-DCMAKE_BUILD_TYPE=Debug")
    config = "Debug"

if tests:
    cmakeCommands.append("-DBUILD_TESTS=True")

cmakeCommands.append("-DCMAKE_VERBOSE_MAKEFILE=ON")

# We run cmake with working directory in the build folder
subprocess.run(cmakeCommands, cwd=buildPath)

# Then we build! here with "cmake --build {BUILD_DIR_PATH} --target ALL_BUILD --config {BUILD_TYPE}". Note that we do not need to invoke "make" commands, modern cmake can do this for us.
# Here we specify --config, this works for the MSBuild or multi-configuration tools, however for others we will need "-DCMAKE_BUILD_TYPE".
if isWin:
    subprocess.run([cmakeBin, "--build",  "build", "--config", config])
else:
    subprocess.run([cmakeBin, "--build", "build", "--", "-j8"])

# Without running cmake --build we instead would run something like the following:
if 0:
    if isWin:
        subprocess.run("msbuild build\{__NAME}.sln")