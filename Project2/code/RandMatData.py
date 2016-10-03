#-*- coding: utf-8 -*-

import matplotlib as mpl
mpl.use("pgf")
pgf_with_pdflatex = {
    "pgf.texsystem": "pdflatex",
    "font.family": "serif",
    "font.serif": [],
    "font.size" : 11.0,
    "pgf.preamble": [
         r"\usepackage[utf8x]{inputenc}",
         r"\usepackage[T1]{fontenc}",
         r"\usepackage{cmbright}",
         r"\usepackage{newtxtext}"
         ]
}
mpl.rcParams.update(pgf_with_pdflatex)
mpl.rcParams['axes.color_cycle'] = ['k', 'k', '#009900', '#964B00', '#d30704' ,'#ff6100']


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


plt.figure(figsize=(4*0.8,3*0.8))
plt.scatter(r(n[:],itr[:],facecolors='none', edgecolors='k',s = 3,linewidth=0.4)
plt.title(ur"Complexity, any matrix", fontsize=11)
plt.ylabel(r"Num iterations")
plt.xlabel(r"Matrix dimension, $n$")
plt.tight_layout(.5)
plt.ticklabel_format(style="sci",axis= "y",scilimits = (-2,2))
plt.savefig("iterations_vs_matrix_dim_any_matrix.png")
plt.savefig("iterations_vs_matrix_dim_any_matrix.pgf")
