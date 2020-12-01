import numpy as np 
from PIL import Image

def stereo_matching(left_img, right_img, disparity_range):

    # Đọc ảnh trái và ảnh phải rồi chuyển sang ảnh greyscale
    left_img = Image.open(left_img).convert("L")
    left = np.asarray(left_img)
    
    right_img = Image.open(right_img).convert("L")
    right = np.asarray(right_img)

    # Cho trước chiều rộng, chiều cao của ảnh
    height, width = left.shape

    # Tạo disparity map
    depth = np.zeros((height, width), np.uint8)
    scale = 255 / disparity_range

    for y in range(height):
        for x in range(width):

            # Tìm j tại đó cost có giá trị min
            disparity = 0
            cost_min = 255**2
            for j in range(0, disparity_range):
                cost = 255**2 if (x - j) < 0 else (int(left[y, x]) - int(right[y, x - j]))**2

                if cost < cost_min:
                    cost_min = cost
                    disparity = j

            depth[y, x] = disparity * scale

    Image.fromarray(depth).save('disparity_map.png')
    
disparity_range = 16
stereo_matching("left.png", "right.png", disparity_range)