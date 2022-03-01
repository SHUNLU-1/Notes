import cv2
import numpy as np
import matplotlib.pyplot as plt
from skimage.feature import hog
from skimage import data, exposure

image = cv2.imread('/home/amber/code/Notes/machine_learning/SVM/image/2.png', 0)     
"""归一化"""
image = np.float32(image) / 255.0       

# cv2.imshow("normalization",image)
# cv2.waitKey()

"""multichannel=True是针对3通道彩色"""
fd, hog_image = hog(image,
                    orientations=8,
                    pixels_per_cell=(16, 16),
                    cells_per_block=(1, 1),
                    visualize=True,
                    multichannel=False) 
                    
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 6), sharex=True, sharey=True)
ax1.axis('off')
ax1.imshow(image, cmap=plt.cm.gray)
ax1.set_title('Input image')

""" Rescale histogram for better display"""
hog_image_rescaled = exposure.rescale_intensity(hog_image, in_range=(0, 10))
ax2.axis('off')
ax2.imshow(hog_image_rescaled, cmap=plt.cm.gray)
ax2.set_title('Histogram of Oriented Gradients')
plt.show()
