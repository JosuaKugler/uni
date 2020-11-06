import json

with open("/home/josua/repos/uni/webscraping/counters", "r") as f:
    counterdict = json.loads(f.read())

def write(counterdict):
    with open("/home/josua/repos/uni/webscraping/counters", "w") as f:
        f.write(json.dumps(counterdict))

def get(vlname):
    return counterdict[vlname]

def setnewcount(vlname, newcount):
    counterdict[vlname] = newcount
    write(counterdict)

def increase(vlname):
    counterdict[vlname] +=1
    write(counterdict)