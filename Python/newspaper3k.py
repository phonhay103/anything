from newspaper import Article
url = 'https://vnexpress.net/ha-noi-cong-bo-diem-chuan-vao-lop-10-thpt-cong-lap-4300885.html'
article = Article(url)
article.download()
article.parse()

print(article.text)