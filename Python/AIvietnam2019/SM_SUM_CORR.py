import numpy as np
from PIL import Image
import math

def stereo_matching_corr(left_img, right_img, kernel_size, disparity_range):
   
    # đọc ảnh trái và ảnh phải, rồi chuyển sang ảnh grayscale
    left_img  = Image.open(left_img).convert('L')
    left      = np.asarray(left_img)
    
    right_img = Image.open(right_img).convert('L')
    right     = np.asarray(right_img)
       
    # cho trước chiều rộng và chiều cao của ảnh
    height, width = left.shape
    
    # tạo disparity map
    depth = np.zeros((height, width), np.uint8)   
    
    # số lượng pixel trong một window
    n = kernel_size*kernel_size
    
    # kernel_half để bỏ rìa (viền) xung quanh
    kernel_half = kernel_size//2  
    
    # giá trị scale chỉ có tác dụng để làm disparity map nhìn rõ ràng hơn.
    scale = 255 / disparity_range
    
    # lưu tất cả các giá trị corr cho mỗi pixep p bên ảnh trái và D (disaprity range) pixel q bên ảnh phải
    corr_space = np.ones((disparity_range, height, width))
    
    memory_sum_x  = np.ones((height, width))
    memory_sum_y  = np.ones((height, width))
    memory_sum_xy = np.ones((height, width))
    memory_sum_x2 = np.ones((height, width))
    memory_sum_y2 = np.ones((height, width))
    
    for j in range(disparity_range):
        data_sum_x  = np.ones((height, width))
        data_sum_y  = np.ones((height, width))
        data_sum_xy = np.ones((height, width))
        data_sum_x2 = np.ones((height, width))
        data_sum_y2 = np.ones((height, width))

        for y in range(kernel_half, height-kernel_half):
            for x in range(kernel_half, width-kernel_half):
                if x - j >= 0:
                    data_sum_x[y, x]  = int(left[y, x])
                    data_sum_y[y, x]  = int(right[y, x - j])
                    data_sum_xy[y, x] = int(left[y, x])*int(right[y, x - j])
                    data_sum_x2[y, x] = int(left[y, x])**2
                    data_sum_y2[y, x] = int(right[y, x - j])**2

        memory_sum_x = data_sum_x.cumsum(axis=0).cumsum(axis=1)
        memory_sum_y = data_sum_y.cumsum(axis=0).cumsum(axis=1)
        memory_sum_xy = data_sum_xy.cumsum(axis=0).cumsum(axis=1)
        memory_sum_x2 = data_sum_x2.cumsum(axis=0).cumsum(axis=1)
        memory_sum_y2 = data_sum_y2.cumsum(axis=0).cumsum(axis=1)
                    
        for y in range(kernel_half, height-kernel_half):
            for x in range(kernel_half, width-kernel_half):  
                # xác định window để tính sum
                x0 = x - kernel_half
                x1 = x + kernel_half                
                y0 = y - kernel_half
                y1 = y + kernel_half
                
                # chỗ này cần thêm ràng buộc khi x0,y0=0
                
                sum_x = memory_sum_x[y1, x1] - memory_sum_x[y1, x0 - 1] - \
                        memory_sum_x[y0 - 1, x1] + memory_sum_x[y0 - 1, x0 - 1]
                
                sum_y = memory_sum_y[y1, x1] - memory_sum_y[y1, x0 - 1] - \
                        memory_sum_y[y0 - 1, x1] + memory_sum_y[y0 - 1, x0 - 1]
                
                sum_xy = memory_sum_xy[y1, x1] - memory_sum_xy[y1, x0 - 1] - \
                         memory_sum_xy[y0 - 1, x1] + memory_sum_xy[y0 - 1, x0 - 1]
                
                sum_x2 = memory_sum_x2[y1, x1] - memory_sum_x2[y1, x0 - 1] - \
                         memory_sum_x2[y0 - 1, x1] + memory_sum_x2[y0 - 1, x0 - 1]
                
                sum_y2 = memory_sum_y2[y1, x1] - memory_sum_y2[y1, x0 - 1] - \
                         memory_sum_y2[y0 - 1, x1] + memory_sum_y2[y0 - 1, x0 - 1]

                if (n*sum_x2 - sum_x**2) * (n*sum_y2 - sum_y**2) == 0:
                    corr = 0
                else:              
                    corr = (n*sum_xy - sum_x*sum_y) / \
                        np.sqrt((n*sum_x2 - sum_x**2) * (n*sum_y2 - sum_y**2))
                
                # có corr càng lớn càng tốt và -1 <= corr < = 1
                # Do đó, chúng ta cần chuyển corr thành dạng loss (hay error)
                corr_space[j, y, x] = 1.0 - corr
    
    # Tìm j, tại đó cost có giá trị min. Nói cách khác, trong D giá trị cost, trình vị trí disparity có cost nhỏ nhất
    for y in range(kernel_half, height-kernel_half):        
        for x in range(kernel_half, width-kernel_half):
            disparity = 0
            cost_min  = 1.0 # a large number            
            for j in range(disparity_range):
                cost = corr_space[j, y, x]                                
                if cost < cost_min:
                    cost_min = cost
                    disparity = j                  
            
            # gán j cho cost_min vào disaprity map
            depth[y, x] = int(disparity * scale)
                                
    # chuyển dữ liệu từ ndarray sang kiểu Image và lưu xuống file
    Image.fromarray(depth).save('disparity_map_corr.png')
 

disparity_range = 64
kernel_size = 11
stereo_matching_corr("Aloe_left_1.png", "Aloe_right_2.png", kernel_size, disparity_range)