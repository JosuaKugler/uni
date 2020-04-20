import requests
from requests_html import HTMLSession
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords

baseurl  = 'https://heibox.uni-heidelberg.de'
scrapeurl = 'https://heibox.uni-heidelberg.de/d/0583bd9e56af4b5ab9db/?p=%2F%C3%9Cbungsbl%C3%A4tter&mode=list'
url = 'https://heibox.uni-heidelberg.de/d/0583bd9e56af4b5ab9db/'
payload = passwords.heiboxpayload()

s = HTMLSession()

result = s.get(url)
tree = html.fromstring(result.text)
authenticity_token = list(set(tree.xpath("//input[@name='csrfmiddlewaretoken']/@value")))[0]
payload['csrfmiddlewaretoken'] = authenticity_token
result = s.post(
	url,
	data = payload, 
	headers = dict(referer=url)
)
r = s.post(url, data=payload)

r.html.render(send_cookies_session=True)

soup = BeautifulSoup(r.html.html, "html.parser")

content = soup.find("tbody")
alist = content.find_all("a")
useful = {}
for a in alist:
    if a["href"] != '#':
        useful[a.text] = a["href"]

zettel = s.get(url + useful["Übungsblätter"])
zettel.html.render(send_cookies_session=True)

zettelsoup = BeautifulSoup(zettel.html.html, "html.parser")
content = zettelsoup.find("tbody")
alist = content.find_all("a")

downloads = {}
for a in alist:
    try:
        if a["title"] == "Download":
            link = a["href"]
            numberstring = link.split("Blatt")[1][:2]
            downloads[int(numberstring)] = [numberstring, baseurl + link]
    except:
        pass

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