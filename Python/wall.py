import requests
import os

auth = 'ab08198aeab1d67104e1899cfbd24288' # 20/4
dir = 'D:/Pictures/wall.alphacoders.com/'

# get_by_category = {'auth':auth, 'method':'category', 'id':id, 'page':1}
# wallpaper_count = {'auth':auth, 'method':'wallpaper_count'} # data['count']

def download(id, method, first=1, last=1, auth=auth, info_level=1):
    parameters = {'auth':auth, 'method':method, 'id':id, 'page':first, 'info_level':info_level}

    with open(dir+'downloaded_original.txt', 'r') as f:
        images_id = [i.strip('\n') for i in f.readlines()]
    f = open(dir+'downloaded_original.txt', 'a')

    for page in range(first, last+1):
        parameters['page'] = page
        response = requests.get('https://wall.alphacoders.com/api2.0/get.php', params=parameters)
        data = response.json()

        if (data['success']):
            i = 0
            for img in data['wallpapers']:
                i += 1
                print('{}-{}'.format(page, i))
                if img['id'] not in images_id:
                    print(img['id'])
                    # f.write(img['id']+'\n') # new id
                    # img_dir = dir + img['id'] + '.' + img['file_type']
                    # img_data = requests.get(img['url_image'])
                    # open(img_dir, 'wb').write(img_data.content)
        else:
            print('Page {}: {}'.format(page, data['error']))
    f.close()

download(3, 'sub_category', int(os.sys.argv[1]), int(os.sys.argv[2]))
