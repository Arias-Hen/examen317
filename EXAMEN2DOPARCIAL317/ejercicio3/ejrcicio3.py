import cv2
import numpy as np
from matplotlib import pyplot as plt

img1 = cv2.imread("IM1.jpg");
img2 = cv2.imread("IM2.jpg");

plt.figure(figsize=(10, 10))

# Muestra la primera imagen
plt.subplot(1, 2, 1) # (filas, columnas, índice de la imagen)
plt.imshow(cv2.cvtColor(adicion, cv2.COLOR_BGR2RGB))
plt.title('Adición')

# Muestra la segunda imagen
plt.subplot(1, 2, 2) # (filas, columnas, índice de la imagen)
plt.imshow(cv2.cvtColor(resta, cv2.COLOR_BGR2RGB))
plt.title('Resta')

plt.show()