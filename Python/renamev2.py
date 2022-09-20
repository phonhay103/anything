import os, sys
import glob
import math
import time

# V3.0
# 17-3-2020 8:42PM

class rename_all_file:
    def __init__(self, path = sys.argv[1], head = sys.argv[2]):
        self.path = path
        self.head = head
        self.start_time = time.time()
    
    def rename(self, start=1):
        # Lấy danh sách file
        filenames = glob.glob(self.path.replace('[', '[[]'))
        if not filenames:
            exit()

        # Bỏ qua thư mục và file chạy
        filenames = list(filter(lambda filename: os.path.isfile(filename), filenames))
        del filenames[(filenames.index('\\'.join(filenames[0].split('\\')[:-1]) + '\\' + 'renamev2.bat'))]

        # Đổi sang tên tạm thời (tránh trùng tên file)
        for i, filename in enumerate(filenames):
            temp = '\\'.join(filename.split('\\')[:-1]) + '\\' + 'nhay_' + filename.split('\\')[-1]
            os.rename(filename, temp)
            filenames[i] = temp

        # Đổi sang tên mới
        i = start # Vị trí bắt đầu đánh số
        total = int(math.log10(len(filenames))) + 1

        for filename in filenames:
            num = str(i)
            for _ in range(total - len(num)):
                num = '0' + num
            new = filename.replace(filename.split('.')[0].split('\\')[-1], self.head + num)
            if new.split('.')[-1] == 'jpg':
                new = new.replace('.jpg', '_1 copy.png')
            elif new.split('.')[-1] == 'png':
                new = new.replace('.png', '_1 copy.png')
            os.rename(filename, new)
            i = i + 1

    def show_time(self):
        print('Time:', time.time() - self.start_time)

rename = rename_all_file()
rename.rename()
rename.show_time()