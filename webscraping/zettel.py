#!/usr/bin/env python3
import counterwrapper
import sys
import os

lecture = sys.argv[1]
command = "xdg-open /home/josua/repos/uni/"

if lecture == "ana":
    number = counterwrapper.getAna()
elif lecture == "la":
    number = counterwrapper.getLa()
elif lecture == "num":
    number = counterwrapper.getNum()
elif lecture == "funktheo":
    number = counterwrapper.getFunktheo()
elif lecture == "theo":
    number = counterwrapper.getTheo()

if number < 10:
    numberstring = "0" + str(number)
else:
    numberstring = str(number)

command += lecture + "/" + numberstring + lecture + ".pdf"

os.system(command)