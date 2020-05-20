#!/usr/bin/env python3
import requests
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords
import os


url = 'https://mampf.mathi.uni-heidelberg.de/users/sign_in?locale=de'
payload = passwords.mampfpayload()

scrapeurl = 'https://mampf.mathi.uni-heidelberg.de/courses/26/food?lecture_id=30&page=1&per=48&project=kaviar&reverse=false'


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


def getskript():
    i = 0
    for download in downloads:
        if ".pdf" in download['name']:
            i += 1
            if i < 10:
                numberstring = "0" + str(i)
            else:
                numberstring = str(i)
            zettelurl = download['href']
            basepath = "/home/josua/repos/uni/num/"
            filename =  "partskript" + numberstring + ".pdf"
            response = s.get(zettelurl)
            print(zettelurl, " -> ", basepath + filename)
            with open(basepath + filename, "wb") as f:
                f.write(response.content)
    os.system("pdfunite partskript* newskript.pdf")
    for f in os.listdir(basepath):
        if "partskript" in f:
            os.remove(os.path.join(basepath, f))

getskript()