import requests
from requests_html import HTMLSession
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords

baseurl = 'https://moodle.uni-heidelberg.de'
scrapeurl = 'https://moodle.uni-heidelberg.de/course/view.php?id=1948'
url = 'https://moodle.uni-heidelberg.de/login/index.php'

payload = passwords.funktheopayload()

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

def verify(result):
    if "athanael" in result.html.html:
        print("success") 

def write(result):
    with open("temp.html", "w") as f:
        f.write(result.html.html)

r = s.get(scrapeurl)
verify(r)
write(r)

soup = BeautifulSoup(r.html.html, "lxml")
alist = soup.find_all("a")

for a in alist:
    if "Skript" in a.text:
        skriptlink = a["href"]
        break

def getZettel(number):
    try:
        zettel = downloads[number]
        numberstring = zettel[0]
        zettelurl = zettel[1]
        basepath = "/home/josua/repos/uni/ana/"
        filename = numberstring + "ana.pdf"
        response = s.get(zettelurl)
        print(zettelurl, " -> ", basepath + filename)
        with open(basepath + filename, "wb") as f:
            f.write(response.content)
    except:
        print("not yet uploaded")

getZettel(int(sys.argv[1]))