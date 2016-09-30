#-*- coding: utf-8 -*-
import matplotlib as mpl

import matplotlib.pyplot as plt

text_file = open("RandMatData.txt","r")
n = []
itr = []

lines = text_file.readlines()

for line in lines:
	matrix_dim,iterations = line.split()
	n.append(matrix_dim)
	itr.append(iterations)


text_file.close()



plt.plot(n[:],itr[:],linestyle='None',marker ='x',markersize = 6);
plt.show()
