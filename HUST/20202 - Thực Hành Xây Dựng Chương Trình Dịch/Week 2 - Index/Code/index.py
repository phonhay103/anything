def load_stopw():
    with open('data/stopw.txt', 'r') as f:
        data = f.readlines()
        data = [word[:-1] for word in data]
    return data

def load_text():
    with open('data/vanban2.txt', 'r') as f:
        data = f.readlines()
        data = [word[:-1] for word in data]
    return data

def insert_to_dict(dict: dict, word: str, num_line:int, num_column: int):
    if word not in dict.keys():
        dict[word] = '1,(%s.%s)' % (num_line, num_column)
    else:
        list_index = dict[word]
        list_index = list_index.split(',')

        list_index[0] = str(int(list_index[0])+1)
        list_index.append('(%d.%d)' % (num_line, num_column))
        list_index = ','.join(list_index)

        dict[word] = list_index

def remove_dot_after(word):
    return word[:-1] if word[-1] == '.' else word

dict = {}
prev = None
delim = "\n\t\r!#$%%&'()*+,/:;<=>?@[]^_`{|}~0123456789"
num_line = 1
stopw = load_stopw()
lines = load_text()
for line in lines:
    line = line.translate({ord(ch): '' for ch in delim})
    line = ' '.join(line.split())
    line = line.split()
    
    num_column = 1
    for token in line:
        if token != '.' and token != '-' and token not in stopw:
            if (prev is None or prev[-1] == '.'):
                insert_to_dict(dict, remove_dot_after(token.lower()), num_line, num_column)
            else:
                insert_to_dict(dict, remove_dot_after(token), num_line, num_column)
        prev = token
        num_column += 1
    num_line += 1

for k, v in dict.items():
    print(k, v)