import numpy as np 
from PIL import Image

def stereo_matching_ssd(left_img, right_img, kernel_size, disparity_range):

    # Đọc ảnh trái và ảnh phải rồi chuyển sang ảnh greyscale
    left_img = Image.open(left_img).convert("L")
    left = np.asarray(left_img)

    right_img = Image.open(right_img).convert("L")
    right = np.asarray(right_img)

    # Cho trước chiều rộng, chiều cao của ảnh
    height, width = left.shape

    # Tạo disparity map
    depth = np.zeros((height, width), np.uint8)

    kernel_half = kernel_size//2
    scale = 255/disparity_range

    for y in range(kernel_half, height - kernel_half):
        for x in range(kernel_half, width - kernel_half):
            
            disparity = 0
            cost_min = 255**2

            for j in range(disparity_range):
                ssd = 0
                ssd_temp = 0

                for v in range(-kernel_half, kernel_half):
                    for u in range(-kernel_half, kernel_half):
                        ssd_temp = 255**2
                        if (x+u-j) >= 0:
                            ssd_temp = (int(left[y+v, x+u]) - int(right[y+v, x-j+u]))**2
                        ssd += ssd_temp
                
                if ssd < cost_min:
                    cost_min = ssd
                    disparity = j
                
            depth[y, x] = disparity * scale

    # Chuyển dữ liệu từ ndarray sang kiểu Image và lưu xuống file
    Image.fromarray(depth).save('disparity_map_ssd.png')

disparity_range = 16
kernel_size = 5
stereo_matching_ssd("left.png", "right.png", kernel_size, disparity_range)