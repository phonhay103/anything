import urllib.request
import re
import os
from tqdm import tqdm

url = input("Link truyenfull: ")

# Tên truyện, tác giả
with urllib.request.urlopen(url) as data:
    contents = data.read().decode("utf8")
    lst = re.findall(r'<meta property="book\:tag" content=".+?">', contents)
    name = lst[0].split('"')[-2]
    author = lst[2].split('"')[-2]

# Nhập chương
start, end = input('Nhập start-end: ').split('-')
start = int(start)-1
end = int(end)

# Tạo thư mục chứa truyện
dir = f"{name} - {author}"
if not os.path.isdir(dir):
    os.makedirs(dir)

if(url[-1] != '/'):
        url += '/'

# Load các chương
for i in tqdm(range(start, end)):
    with urllib.request.urlopen(url + f"chuong-{i+1}") as data:
        contents = data.read().decode("utf8")

        # Lấy tên chương
        name = re.findall(r"<title>.+?-\s(.+)</title>", contents)[0]

        # Xử lý nội dung chương
        contents = re.findall(r'-c">(.+)</div><div class="hidden-x', contents)[0]
        contents = re.sub(r"<br />", "\n", contents)

    # Ghi vào file
    with open(dir + f"/Chương {i+1}.txt", "w", encoding="utf8") as f:
        f.write(name + '\n\n')
        f.write(contents)