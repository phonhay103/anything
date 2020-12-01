import numpy as np 
from PIL import Image

def stereo_matching_sad(left_img, right_img, kernel_size, disparity_range):
    left_img = Image.open(left_img).convert('L')
    left = np.asarray(left_img)

    right_img = Image.open(right_img).convert('L')
    right = np.asarray(right_img)

    height, width = left.shape
    depth = np.zeros((height, width), np.uint8)
    kernel_half = kernel_size//2
    print(kernel_half)
    scale = 255/disparity_range

    # Build sum-area table
    memory = np.ones((disparity_range, height, width))
    for j in range(disparity_range):
        data = np.ones((height, width))
        for y in range(kernel_half, height-kernel_half):
            for x in range(kernel_half, width-kernel_half):
                if x - j >=0:
                    data[y, x] = abs(int(left[y, x]) - int(right[y, x-j]))/255.0
        memory[j] = data.cumsum(axis=0).cumsum(axis=1)
    
    for y in range(kernel_half, height-kernel_half):
        for x in range(kernel_half, width-kernel_half):
            # Add constraint for x0=y0=0
            x0 = x - kernel_half
            x1 = x + kernel_half
            y0 = y - kernel_half
            y1 = y + kernel_half

            disparity = 0
            cost_min = 65534

            for j in range(disparity_range):
                a = memory[j, y0 - 1, x0 - 1]
                b = memory[j, y1, x0 - 1]
                c = memory[j, y0 - 1, x1]
                d = memory[j, y1, x1]
                sad = d - b - c + a

                if sad < cost_min:
                    cost_min = sad
                    disparity = j

            depth[y, x] = int(disparity * scale)
        
    Image.fromarray(depth).save('disparity_sum.png')

kernel_size = 9
stereo_matching_sad("left.png", "right.png", kernel_size, 16)