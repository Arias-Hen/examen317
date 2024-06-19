import cv2
import scipy.sparse as sp

drive.mount("/content/drive")
os.chdir("/content/drive/MyDrive/INF317")

img1 = cv2.imread("IM1.jpg");
img2 = cv2.imread("IM2.jpg");
m_sparse1 = sp.coo_matrix(img1[:,:,1])
m_sparse2 = sp.coo_matrix(img2[:,:,1])
print(m_sparse2)
