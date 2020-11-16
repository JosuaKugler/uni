#!/usr/bin/env python3
import requests
from pprint import pprint
from bs4 import BeautifulSoup
from passwords import theopayload
import counterwrapper

baseurl = 'https://uebungen.physik.uni-heidelberg.de/'
url = 'https://uebungen.physik.uni-heidelberg.de/uebungen/login.php'
payload = theopayload()

scrapeurl = 'https://uebungen.physik.uni-heidelberg.de/vorlesung/20201/ptp2'
#scrapeurl = 'https://uebungen.physik.uni-heidelberg.de/vorlesung/20192/1058'
s = requests.Session()
#if cookie is expired:

r = s.post(url, data=payload)
cookie = {'PHPSESSID': requests.utils.dict_from_cookiejar(s.cookies)['PHPSESSID']}

#else use this cookie:
#cookie = {'PHPSESSID': 'vqlb7608ubtl16pugalc210827'}
print(cookie)

theo1 = s.get(scrapeurl, cookies = cookie)
soup = BeautifulSoup(theo1.text, "html.parser")
alist = soup.find_all("a")

downloads = []

for a in alist:
    try:
        if "pdflink" in a["class"]:
            downloads.append({"name":a.text, "href":a["href"]})
    except:
        pass

def getZettel(number):
    exists = False
    for download in downloads:
        if "Blatt" + str(number) + ".pdf" in download['name']:
            if number < 10:
                numberstring = "0" + str(number)
            else:
                numberstring = str(number)
            exists = True
            zettelurl = baseurl + download['href']
            basepath = "/home/josua/repos/uni/theo/"
            filename = numberstring + "theo.pdf"
            response = s.get(zettelurl, cookies=cookie)
            print(zettelurl, " -> ", basepath + filename)
            with open(basepath + filename, "wb") as f:
                f.write(response.content)
            counterwrapper.increaseTheo()
    if not exists:
        print("not yet uploaded") 

counter = counterwrapper.getTheo()

getZettel(counter + 1)