import os
import buildUtil as util

srcDir = './src'

env = Environment(CCFLAGS='-std=c++0x -g -p -Wall')

binTarget = list()
for fileName in os.listdir(srcDir):
    if fileName.endswith(".cpp"):
        target = env.Program(target = util.genOutName(fileName) + ".out",
            source = srcDir + os.path.sep + fileName)
        binTarget.append(target)

