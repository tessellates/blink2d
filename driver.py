import os
import shutil
import subprocess
import sys

__NAME = "blink2d"

path = os.getcwd()

# For Windows the path to the executalbe will be:
if sys.platform == ("win32" or "win64"):
    maincmd = r"build\Release\building.exe"
    if os.path.exists(path + "\build\Debug"):
        maincmd = r"build\Debug\building.exe"
else:
    maincmd = "./build/{}".format("main")

myenv = dict(os.environ)
myenv["PATH"] = os.pathsep.join([path, myenv.get("PATH", "")])
myenv["SDL_VIDEO_DRIVER"] = "cocoa" # Change this to a different driver!

subprocess.Popen( maincmd, shell = True, env=myenv )
