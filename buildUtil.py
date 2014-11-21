
def isCppFile(fileName):
    return fileName.endswith(".cpp")

def isTestFile(fileName):
    return fileName.startswith("_TEST__")

def isOutFile(fileName):
    return fileName.endswith(".out")

def genOutName(fileName):
    return fileName[0: fileName.index(".cpp")]
