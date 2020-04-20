import requests
from pprint import pprint
from bs4 import BeautifulSoup
import sys

url = 'https://conan.iwr.uni-heidelberg.de/data/teaching/numerik0_ss2018/uebung'
# example: scrapeurl = 'https://conan.iwr.uni-heidelberg.de/data/teaching/numerik0_ss2018/uebung01.pdf'

def getZettel(number):
    if number < 10:
        numberstring = "0" + str(number)
    else:
        numberstring = str(number)
    scrapeurl = url + numberstring + ".pdf"
    response = requests.get(scrapeurl)
    soup = BeautifulSoup(response.text, "html.parser")
    if soup.title:
        print("not yet uploaded")
    else:
        basepath = "/home/josua/repos/uni/num/"
        filename = numberstring + "num.pdf"
        print(scrapeurl, " -> ", basepath + filename)
        with open(basepath + filename, "wb") as f:
            f.write(response.content)

getZettel(int(sys.argv[1]))