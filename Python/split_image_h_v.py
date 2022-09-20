import shutil
from pathlib import Path
from PIL import Image
from tqdm import tqdm

path = Path.cwd()
h_path = path.joinpath('Horizontal')
h_path.mkdir(exist_ok=True)
v_path = path.joinpath('Vertical')
v_path.mkdir(exist_ok=True)

filetypes = ['jpg', 'png', 'jpeg']
filenames = sum([list(path.glob(f'*.{ext}')) for ext in filetypes], [])

for filename in tqdm(filenames):
    with Image.open(filename) as img:
        w, h = img.size
        if w > h:
            shutil.copy(filename, h_path.joinpath(filename.parts[-1]))
        else:
            shutil.copy(filename, v_path.joinpath(filename.parts[-1]))
    filename.unlink()