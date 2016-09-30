
from matplotlib.pyplot import plot, axis, show, xlabel, ylabel, title, loglog, figure
import math
from numpy.linalg import norm
from numpy import trapz, array



def readfile(filename):
	text_file = open(filename,"r")
	psi = []
	rho = []

	lines = text_file.readlines()

	for line in lines:
	    rho_i,psi_i = line.split()
	    rho.append(float(rho_i))
	    psi.append(float(psi_i))
	text_file.close()
	for i in range(len(psi)):
		psi[i] = psi[i]*psi[i]
	return rho, psi


rho001, psi001  = 		array(readfile("SL_for_wr_0.01.txt"))
rho001withPOT, psi001withPOT  = array(readfile("SL_for_wr_0.01_coulomb.txt"))
rho05, psi05  = 		array(readfile("SL_for_wr_0.5.txt"))
rho05withPOT, psi05withPOT = 	array(readfile("SL_for_wr_0.5_coulomb.txt"))
rho1, psi1  = 			array(readfile("SL_for_wr_1.txt"))
rho1withPOT, psi1withPOT  = 	array(readfile("SL_for_wr_1_coulomb.txt"))
rho5, psi5  = 			array(readfile("SL_for_wr_5.txt"))
rho5withPOT, psi5withPOT  = 	array(readfile("SL_for_wr_1_coulomb.txt"))


psi001[:]  = psi001[:]/trapz(psi001[:]/rho001[:],rho001)
psi05[:] = psi05[:]/trapz(psi05[:]/rho05[:],rho05)
psi1[:] = psi1[:]/trapz(psi1[:]/rho1[:],rho1)
psi5[:] = psi5[:]/trapz(psi5[:]/rho5[:],rho5)
psi001withPOT[:]  = psi001withPOT[:]/trapz(psi001withPOT[:]/rho001withPOT[:],rho001withPOT)
psi05withPOT[:] = psi05withPOT[:]/trapz(psi05withPOT[:]/rho05withPOT[:],rho05withPOT)
psi1withPOT[:] = psi1withPOT[:]/trapz(psi1withPOT[:]/rho1withPOT[:],rho1withPOT)
psi5withPOT[:] = psi5withPOT[:]/trapz(psi5withPOT[:]/rho5withPOT[:],rho5withPOT)

figure(1)
plot(rho001[:],psi001[:],rho05[:],psi05[:],rho1[:],psi1[:],rho5[:],psi5[:])
xlabel('rho')
ylabel('psi(rho)^2')
show()
figure(2)
#plot(rho001withPOT[:],psi001withPOT[:],rho05withPOT[:],psi05withPOT[:],rho1withPOT[:],psi1withPOT[:],rho5withPOT[:],psi5withPOT[:])
plot(rho001withPOT[:],psi001withPOT[:])
figure(3)
plot(rho05withPOT[:],psi05withPOT[:])
figure(4)
plot(rho1withPOT[:],psi1withPOT[:])
figure(5)
plot(rho5withPOT[:],psi5withPOT[:])
show()

