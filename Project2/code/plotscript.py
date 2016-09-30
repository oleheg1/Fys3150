
from matplotlib.pyplot import plot, axis, show, xlabel, ylabel, title, loglog
import math

text_file = open("coulomb.txt","r")

N = int(text_file.readline())
a = []
b = []
c = []
rho = []

lines = text_file.readlines()

for line in lines:
    rho_i,ai,bi,ci = line.split()
    a.append(float(ai))
    b.append(float(bi))
    c.append(float(ci))
    rho.append(float(rho_i))
text_file.close()

plot(rho[:],a[:],"r",rho[:],b[:],"g",rho[:],c[:])
xlabel('rho')
ylabel('psi(rho)')
title('N = '+str(N))
show()


