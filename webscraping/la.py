#!/usr/bin/env python3
import requests
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords
import counterwrapper


url = 'https://mampf.mathi.uni-heidelberg.de/users/sign_in?locale=de'
payload = passwords.mampfpayload()

scrapeurl = 'https://mampf.mathi.uni-heidelberg.de/courses/2/food?lecture_id=28&page=1&per=48&project=nuesse&reverse=false'


s = requests.session()
result = s.get(url)
tree = html.fromstring(result.text)
authenticity_token = list(set(tree.xpath("//input[@name='authenticity_token']/@value")))[0]
payload['authenticity_token'] = authenticity_token
result = s.post(
	url,
	data = payload, 
	headers = dict(referer=url)
)

result = s.get(
    scrapeurl,
    headers = dict(referer = scrapeurl)
)

soup = BeautifulSoup(result.text, "html.parser")


alist = soup.find_all('a')
downloads = []
for a in alist:
    try:
        if "triggerDownload" in a["class"]:
            downloads.append({"name" : a["download"], "href" : a["href"]})
    except:
        pass


def getZettel(number):
    exists = False
    for download in downloads:
        if number < 10:
                numberstring = "0" + str(number)
        else:
            numberstring = str(number)
        if "Blatt" + numberstring + ".pdf" in download['name']:
            exists = True
            zettelurl = download['href']
            basepath = "/home/josua/repos/uni/la/"
            filename = numberstring + "la.pdf"
            response = s.get(zettelurl)
            print(zettelurl, " -> ", basepath + filename)
            with open(basepath + filename, "wb") as f:
                f.write(response.content)
            counterwrapper.increaseLa()
    if not exists:
        print("la {} not yet uploaded".format(number)) 
         
counter = counterwrapper.getLa()

getZettel(counter + 1)