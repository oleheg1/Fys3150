
from matplotlib.pyplot import plot, axis, show, xlabel, ylabel, title, loglog, subplot, figure, savefig
import math
import sys



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
plot(x[:],v[:],"r",x[:],u[:],"g")
xlabel('x')
ylabel('f(x)')
title('N = '+str(N))

subplot(2,1,2)
loglog(x[:],h[:], basex = 10)
xlabel('x')
ylabel('eps = (vi-ui)/ui')
savefig(sys.argv[1][:-4] + ".pdf")

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
