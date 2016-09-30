import matplotlib as mpl
from matplotlib.pyplot import *
import math
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
mpl.rcParams['axes.color_cycle'] = ['b', '#800080', '#009900', '#964B00', '#d30704' ,'#ff6100']
text_file = open("Relative_Error_Data.txt","r")

n = []
error = []

lines = text_file.readlines()

for line in lines:
    ni,ei = line.split()
    n.append(float(ni))
    error.append(float(ei))
  
text_file.close()

h = []
for i in range(len(n)):
	h.append(1./(n[i]-1.))

figure(figsize=(4,3))
loglog(h[:],error[:],basex = 10)
gca().invert_xaxis()
figure(figsize=(4,3))
title(ur"Tittel $\tilde{t}$", fontsize=11)
ylabel(r"Relative error $\quad[\;\cdot\;]$")
xlabel(r"step length $\quad [\;\cdot\;]$")
tight_layout(.5)
savefig("Relative_Error.png")
savefig("Relative_Error.pgf")

