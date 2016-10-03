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
mpl.rcParams['axes.color_cycle'] = ['k', '#800080', '#009900', '#964B00', '#d30704' ,'#ff6100']
import matplotlib.pyplot as plt

text_file = open("iterations_vs_matrix_dim.txt","r")
n = []
itr = []

lines = text_file.readlines()

for line in lines:
	matrix_dim,iterations = line.split()
	n.append(matrix_dim)
	itr.append(iterations)


text_file.close()



plt.figure(figsize=(4*0.8,3*0.8))
plt.plot(n[:],itr[:])
plt.title(ur"Complexity, Schrödinger equation", fontsize=11)
plt.ylabel(r"Num iterations")
plt.xlabel(r"Matrix dimension, $n$")
plt.ylim(0,5e4)
plt.tight_layout(.5)
plt.ticklabel_format(style="sci",axis= "y",scilimits = (-2,2))
plt.savefig("Niterations_vs_matrix_dim.png")
plt.savefig("Niterations_vs_matrix_dim.pgf")
