import json

with open("/home/josua/repos/uni/counters", "r") as f:
    counterdict = json.loads(f.read())

def write(counterdict):
    with open("/home/josua/repos/uni/counters", "w") as f:
        f.write(json.dumps(counterdict))

def getTheo():
    return counterdict["theo"]

def setTheo( newcount):
    counterdict["theo"] = newcount
    write(counterdict)

def increaseTheo():
    counterdict["theo"] += 1
    write(counterdict)

def getAna():
    return counterdict["ana"]

def setAna( newcount):
    counterdict["ana"] = newcount
    write(counterdict)

def increaseAna():
    counterdict["ana"] += 1
    write(counterdict)

def getLa():
    return counterdict["la"]

def setLa( newcount):
    counterdict["la"] = newcount
    write(counterdict)

def increaseLa():
    counterdict["la"] += 1
    write(counterdict)

def getNum():
    return counterdict["num"]

def setNum( newcount):
    counterdict["num"] = newcount
    write(counterdict)

def increaseNum():
    counterdict["num"] += 1
    write(counterdict)

def getFunktheo():
    return counterdict["funktheo"]

def setFunktheo( newcount):
    counterdict["funktheo"] = newcount
    write(counterdict)

def increaseFunktheo():
    counterdict["funktheo"] += 1
    write(counterdict)