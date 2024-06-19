# EJERCICIO 3

import cv2
from matplotlib import pyplot as plt
from google.colab import drive
import os

drive.mount("/content/drive")
os.chdir("/content/drive/MyDrive/INF317")

imG1 = cv2.imread("IMG3.png")
imG2 = cv2.imread("IMG4.png")

adicion = cv2.addWeighted(imG1, 0.8, imG2, 0.1, 0)

resta = cv2.subtract(imG1, imG2)

plt.figure(figsize=(10, 5))

# Mostrar la imagen resultante de la adición
plt.subplot(1, 2, 1)
plt.title("SUMA")
plt.imshow(cv2.cvtColor(adicion, cv2.COLOR_BGR2RGB))

# Mostrar la imagen resultante de la sustracción
plt.subplot(1, 2, 2)
plt.title("RESTA")
plt.imshow(cv2.cvtColor(resta, cv2.COLOR_BGR2RGB))

# Mostrar la figura
plt.show()
