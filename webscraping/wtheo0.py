#!/usr/bin/env python3
import requests
from requests_html import HTMLSession
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords
import newcounterwrapper

baseurl = 'https://moodle.uni-heidelberg.de'
scrapeurl = 'https://moodle.uni-heidelberg.de/course/view.php?id=4797'
url = 'https://moodle.uni-heidelberg.de/login/index.php'

payload = passwords.moodlepayload()

s = HTMLSession()

result = s.get(url)
tree = html.fromstring(result.text)
authenticity_token = list(set(tree.xpath("//input[@name='logintoken']/@value")))[0]
payload['logintoken'] = authenticity_token
result = s.post(
	url,
	data = payload, 
	headers = dict(referer=url)
)

r = s.get(scrapeurl)

soup = BeautifulSoup(r.html.html, "lxml")
alist = soup.find_all("a")

vlname = "wtheo0"


def getZettel(number):
    global alist
    if number < 10:
        numberstring = "0" + str(number)
    else:
        numberstring = str(number)
    blattlink = ""

    for a in alist:
        if "Übungsblatt - " + numberstring in a.text and "Lösungen" not in a.text:
            blattlink = a["href"]
    
    if blattlink != "":
        basepath = "/home/josua/repos/uni/" + vlname + "/"
        filename = numberstring + vlname + ".pdf"
        response = s.get(blattlink)
        print(blattlink, " -> ", basepath + filename)
        with open(basepath + filename, "wb") as f:
            f.write(response.content)
            newcounterwrapper.increase(vlname)
    else:
        print(vlname + " {} not yet uploaded".format(number))

counter = newcounterwrapper.get(vlname)
getZettel(counter+1)