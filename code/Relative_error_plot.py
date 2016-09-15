#from matplotlib.pyplot import plot, axis, show, xlabel, ylabel, title, loglog, subplot, figure, savefig, xticks
from matplotlib.pyplot import *
import math

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


loglog(h[:],error[:],basex = 10)
gca().invert_xaxis()
xlabel('step length')
ylabel('Relative error')
title('Fin Figur')


savefig("Relative_Error.pdf")
