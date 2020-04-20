import requests
from lxml import html
from pprint import pprint
from bs4 import BeautifulSoup
import sys
import passwords

url = 'https://muesli.mathi.uni-heidelberg.de/user/login'
payload = passwords.mueslipayload()

scrapeurl = 'https://mampf.mathi.uni-heidelberg.de/courses/2/food?lecture_id=2&page=1&per=48&project=nuesse&reverse=false'


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
