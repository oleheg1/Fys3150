import matplotlib as mpl

mpl.use("pgf")
from matplotlib.pyplot import plot, axis, show, xlabel, ylabel, title, loglog, subplot, figure, savefig, tight_layout
import math
import sys



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

text_file = open(sys.argv[1],"r")

N = int(text_file.readline())
v = []
u = []
x = []

lines = text_file.readlines()

for line in lines:
    vi,ui,xi = line.split()
    v.append(float(vi))
    u.append(float(ui))
    x.append(float(xi))
  
text_file.close()

h = []
h.append(0)
for i in range(1,N+2):
    h.append(abs((v[i]-u[i])/u[i]))

figure(1)
subplot(2,1,1)
titlename = ur"N = " + str(N)
plot(x[:],v[:],"r",x[:],u[:],"g")
title(titlename, fontsize=11)
ylabel(r"f(x) $\quad[\;\cdot\;]$")
xlabel(r"x  $\quad [\;\cdot\;]$")
tight_layout(.5)


subplot(2,1,2)
loglog(x[:],h[:], basex = 10)
ylabel(r"eps = (vi-ui)/ui $\quad[\;\cdot\;]$")
xlabel(r"x  $\tilde{t} \quad [\;\cdot\;]$")
tight_layout(.5)
savefig(sys.argv[1][:-4] + ".png")
savefig(sys.argv[1][:-4] + ".pgf")

del h[-1]

if(int(sys.argv[2])):
	error_file = open("Relative_Error.txt", "w")
else:
	error_file = open("Relative_Error.txt", "a")
error_file.write("Maximum error for n = " + str(N) + " is " + str(max(h)))
error_file.write('\n')
error_file.close()


if(int(sys.argv[2])):
	error_data = open("Relative_Error_Data.txt", "w")
else:
	error_data = open("Relative_Error_Data.txt", "a")
error_data.write(str(N) + "   " + str(max(h)))
error_data.write('\n')
error_data.close()
