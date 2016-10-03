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
mpl.rcParams['axes.color_cycle'] = ['k', 'k', 'k', 'k', 'k' ,'k']
import matplotlib.pyplot as plt

text_file = open("data.dat","r")
n = []
itr = []
lwrx = []
lwry = []
uprx = []
upry = []
meanx = []
meany = []

def readfile(filename):
	text_file = open(filename,"r")
	x = []
	y = []

	lines = text_file.readlines()

	for line in lines:
	    x_i,y_i = line.split()
	    x.append(float(x_i))
	    y.append(float(y_i))
	text_file.close()
	return x, y


lines = text_file.readlines()
for line in lines:
	matrix_dim,iterations,a , b ,c, d, e = line.split()
	n.append(matrix_dim)
	itr.append(iterations)
text_file.close()

lwrx, lwry = readfile("lwr.txt")
uprx, upry = readfile("mean.txt")
meanx, meany = readfile("upr.txt")



plt.figure(figsize=(4*0.8,3*0.8))
plt.scatter(n[:],itr[:], facecolors='none', edgecolors='k',s = 7,linewidth=0.4)
plt.title(ur"Complexity, any matrix", fontsize=11)
plt.ylabel(r"Num iterations")
plt.xlabel(r"Matrix dimension, $n$")
plt.tight_layout(.5)
plt.xlim(0,160)
plt.ylim(0,5e4)
plt.hold("on")
plt.plot(meanx[:],meany[:],linestyle='--')
plt.hold("on")
plt.plot(lwrx[:],lwry[:],linestyle='--')
plt.hold("on")
plt.plot(uprx[:],upry[:])
plt.ticklabel_format(style="sci",axis= "y",scilimits = (-2,2))
plt.savefig("anyMatrix.png")
plt.savefig("anyMatrix.pgf")
