#!/usr/bin/env python3
import requests
from requests_html import HTMLSession
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords
import counterwrapper

baseurl = 'https://moodle.uni-heidelberg.de'
scrapeurl = 'https://moodle.uni-heidelberg.de/course/view.php?id=1948'
url = 'https://moodle.uni-heidelberg.de/login/index.php'

payload = passwords.funktheopayload() #moodle login

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

def getZettel(number):
    global alist
    if number < 10:
        numberstring = "0" + str(number)
    else:
        numberstring = str(number)
    blattlink = ""

    for a in alist:
        if "Übungsblatt " + numberstring in a.text and "Lösungen" not in a.text:
            blattlink = a["href"]
    
    if blattlink != "":
        finalpage = s.get(blattlink)
        soup = BeautifulSoup(finalpage.html.html, "lxml")
        alist = soup.find_all("a")

        for a in alist:
            if "Blatt" + numberstring in a.text:
                zettelurl = a["href"]
        basepath = "/home/josua/repos/uni/ana/"
        filename = numberstring + "ana.pdf"
        response = s.get(zettelurl)
        print(zettelurl, " -> ", basepath + filename)
        with open(basepath + filename, "wb") as f:
            f.write(response.content)
            counterwrapper.increaseAna()
    else:
        print("ana {} not yet uploaded".format(number))

counter = counterwrapper.getAna()

getZettel(counter+1)