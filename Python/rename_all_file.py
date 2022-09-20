# Rename images (jpg, png): '00..1' --> '99..9'
# V4
# 3-6-2022

import sys
import math
import time

from pathlib import Path

path = Path(sys.argv[1])
start_time = time.time()

filenames = []
for ext in ['jpg', 'png']:
    filenames.extend(path.glob(f'*.{ext}'))

len_ = int(math.log10(len(filenames))) + 1

for i, filename in enumerate(filenames):
    num = str(i+1).zfill(len_)
    new_path = Path(filename.parent, num + filename.suffix)
    filename.rename(new_path)

print('Time:', time.time() - start_time)