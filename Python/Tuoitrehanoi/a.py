import requests
from bs4 import BeautifulSoup
import os
import shutil

def cauhoi(): # Có thông tin name, value
    with open('Tuổi trẻ Hà Nội.html','r', encoding='utf-8') as f:
        html = f.read()
    soup = BeautifulSoup(html, 'html.parser')

    # Questions with #name
    temp = [i.string.replace('\n', ' ').strip('\t ') for i in soup.find_all('h4')] # Tag h4
    name_attr = list(dict.fromkeys( [i['name'] for i in soup('input')[1:]] )) # Tag input, attr='name'

    questions = []
    for question, name in zip(temp, name_attr[1:]):
        questions.append(name + '#' + ' '.join(question.split(' ')[2:]))

    # Answers with #value
    temp = [''.join([i.string for i in r.find_all('span')]) for r in soup.div.find_all(class_=["item-q css-left-side", "item-q css-right-side"])] # ????
    temp = [i.split(':')[1].strip(' ') for i in temp] # Tag div, class = ["item-q css-left-side", "item-q css-right-side"] ????
    value_attr = [i['value'] for i in soup('input')[1:]] # Tag input, attr='value'
    temp = [value + '#' + i for value, i in zip(value_attr[1:], temp)]
    temp = [i.replace('\n', ' ').strip(' ') for i in temp]

    answers = []
    i = 0
    while i < len(temp):
        answers.append('|'.join([temp[i], temp[i+1], temp[i+2], temp[i+3]]))
        i = i + 4

    # Ghi file lần đầu
    fff = 'CH.txt'
    if (not os.path.exists(fff)):
        with open(fff, 'w', encoding='utf-8') as f:
            for i in range(len(questions)):
                f.write('%s@%s\n' % (questions[i], answers[i]))
        exit()

    # Thêm câu hỏi mới vào file
    with open(fff, 'r', encoding='utf-8') as f:
        questions_old = f.readlines()
    questions_old = [i.strip('\n') for i in questions_old]
    questions_old = [i.split('@')[0] for i in questions_old]
    questions_old = [i.split('#')[0] for i in questions_old]

    with open(fff, 'a', encoding='utf-8') as f:
        for i in range(len(questions)):
            if (questions[i].split('#')[0] not in questions_old):
                print('NEW')
                f.write('%s@%s\n' % (questions[i], answers[i]))

def thi():
    with open('Tuổi trẻ Hà Nội.html','r', encoding='utf-8') as f:
        html = f.read()
    soup = BeautifulSoup(html, 'html.parser')

    questions_name = list(dict.fromkeys( [i['name'] for i in soup('input')[1:]] )) # Tag input, attr='name'

    valueToAnswers = {} # value : {A B C D}
    temp = [''.join([i.string for i in r.find_all('span')]) for r in soup.div.find_all(class_=["item-q css-left-side", "item-q css-right-side"])]
    temp = [i.split(':')[0] for i in temp]
    temp2 = [i['value'] for i in soup('input')[1:]] # Tag input, attr='value'
    for t1, t2 in zip(temp, temp2[1:]):
        valueToAnswers[t2] = t1

    nameToValue = {} # name : value
    with open('tuan5_DA_id.txt', 'r', encoding='utf-8') as f:
        data = f.readline()
    data = data.split('|')
    for i in data[:-1]:
        nameToValue[i.split('@')[0]] = i.split('@')[1]

    for i in questions_name[1:]:
        print(valueToAnswers[nameToValue[i]], end=' ')

def thiV2():
    with open('Tuổi trẻ Hà Nội.html','r', encoding='utf-8') as f:
        html = f.read()
    soup = BeautifulSoup(html, 'html.parser')

    questions_name = list(dict.fromkeys( [i['name'] for i in soup('input')[1:]] )) # Tag input, attr='name'

    nameToValue = {} # name : value
    with open('DA_id.txt', 'r', encoding='utf-8') as f:
        data = f.readline()
    data = data.split('|')
    for i in data[:-1]:
        nameToValue[i.split('@')[0]] = i.split('@')[1]
    
    send = [{'name': "txt_testid", 'value': "126-126"}]
    send.append({'name':'txttoken', 'value':soup.find_all('input')[1].attrs['value']})

    for q in questions_name[1:]:
        send.append({'name':q, 'value':nameToValue[q]})
    addToClipBoard("$.post('http://tuoitrehanoi.com/ajaxs/test/result.php',"+str(send)+", function(response_data){window.location='http://tuoitrehanoi.com/lam-bai/tuan-9-tim-hieu-lich-su-90-nam-dang-bo-thanh-pho/binh-chon.html';});")

def dapan_text():
    with open('DA.txt', 'r', encoding='utf-8') as f:
        data = f.readlines()
    data = [i.strip('\n').split('@') for i in data]
    with open('DA_text.txt', 'w', encoding='utf-8') as f:
        for x in range(len(data)):
            f.write('Câu ' + str(x+1) + ': ' + data[x][0].split('#')[1] + '\n' + '-> ' + data[x][1].split('#')[1] + '\n\n')    

def dapan_id():
    with open('DA.txt', 'r', encoding='utf-8') as f:
        data = f.readlines()
    with open('DA_id.txt', 'w', encoding='utf-8') as f:
        for x in data:
            f.write(x.split('#')[0] + '@' + x.split('@')[1].split('#')[0] + '|')

def addToClipBoard(text):
    command = 'echo ' + text.strip() + '| clip'
    os.system(command)

def check1():
    with open('Tuổi trẻ Hà Nội.html','r', encoding='utf-8') as f:
        soup = BeautifulSoup(f.read(), 'html.parser')
    name_attr = list(dict.fromkeys( [i['name'] for i in soup('input')[2:]] )) # Tag input, attr='name'
    with open('check.txt', 'w') as f:
        for i in name_attr:
            f.write('%s\n' % i)
def not_check():
    checked = open('check.txt', 'r', encoding='utf-8').readlines()
    checked = [i.split('#')[0] for i in checked]
    
    all = open('DA.txt', 'r', encoding='utf-8').readlines()
    all = [i.split('#')[0] for i in all]

    for i in all:
        if i not in checked:
            print(i, end=' ')

################################################################################################################
# cauhoi()
dapan_text()
# dapan_id()
# check1()
# thi()
# thiV2()