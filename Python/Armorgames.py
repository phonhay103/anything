import urllib.request
import re
import sys
import os
import shutil

url = sys.argv[1]

if re.search("/\d+$", url):
    exit()
name = re.search("(?<=/)[\w-]+$", url).group()
id = re.search("(?<=/)\d+", url).group()
link = "https://cache.armorgames.com/files/games/%s-%s.swf"%(name, id)

dir = os.path.expanduser('~\\Downloads')+ f"\\{name}.swf"

# Download
urllib.request.urlretrieve(link, dir)
'''
# Other download

import requests

r = requests.get(url)

with open("castaway.swf", "wb") as code:
    code.write(r.content)
'''
