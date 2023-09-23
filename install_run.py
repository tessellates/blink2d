from subprocess import call
import argparse

# We add the option to create a clean build, -c. Running this script "python make_script.py -c" we will pass -c as true
parser = argparse.ArgumentParser()
# We add the option to create a debug build, -d. Default will then be a release build
parser.add_argument('-d', action='store_true')
parser.add_argument('-c', action='store_true')

cmd = ["python3", "make_script.py"]

if parser.parse_args().d:
    cmd.append("-d")
if parser.parse_args().c:
    cmd.append("-c")
call(cmd)
call(["python3", "driver.py"])
