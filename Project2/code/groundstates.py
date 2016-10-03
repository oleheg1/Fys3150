#-*- coding: utf-8 -*-

import matplotlib as mpl
mpl.use("pgf")
pgf_with_pdflatex = {
    "pgf.texsystem": "exlatex",
    "font.family": "serif",
    "font.serif": [],
    "font.size" : 11.0,
    "pgf.preamble": [
         #r"\usepackage[utf8x]{inputenc}",
         r"\usepackage[T1]{fontenc}",
         r"\usepackage{cmbright}",
         r"\usepackage{newtxtext}"
         ]
}
mpl.rcParams.update(pgf_with_pdflatex)
mpl.rcParams['axes.color_cycle'] = ['k', 'k', 'k', 'k', 'k' ,'k']
import matplotlib.pyplot as plt



import math

import numpy as np
from numpy import trapz


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


rho001, psi001  = 		np.array(readfile("SL_for_wr_0.01.txt"))
rho001withPOT, psi001withPOT  = np.array(readfile("SL_for_wr_0.01_coulomb.txt"))
rho05, psi05  = 		np.array(readfile("SL_for_wr_0.5.txt"))
rho05withPOT, psi05withPOT = 	np.array(readfile("SL_for_wr_0.5_coulomb.txt"))
rho1, psi1  = 			np.array(readfile("SL_for_wr_1.txt"))
rho1withPOT, psi1withPOT  = 	np.array(readfile("SL_for_wr_1_coulomb.txt"))
rho5, psi5  = 			np.array(readfile("SL_for_wr_5.txt"))
rho5withPOT, psi5withPOT  = 	np.array(readfile("SL_for_wr_5_coulomb.txt"))


psi001[:] = psi001[:]*rho001[:]/trapz(psi001[:]*rho001[:], rho001[:])
psi05[:] = psi05[:]*rho05[:]/trapz(psi05[:]*rho05[:], rho05[:])
psi1[:] = psi1[:]*rho1[:]/trapz(psi1[:]*rho1[:], rho1[:])
psi5[:] = psi5[:]*rho5[:]/trapz(psi5[:]*rho5[:], rho5[:])
psi001withPOT[:] = psi001withPOT[:]*rho001withPOT[:]/trapz(psi001withPOT[:]*rho001withPOT[:], rho001withPOT[:])
psi05withPOT[:] = psi05withPOT[:]*rho05withPOT[:]/trapz(psi05withPOT[:]*rho05withPOT[:], rho05withPOT[:])
psi1withPOT[:] = psi1withPOT[:]*rho1withPOT[:]/trapz(psi1withPOT[:]*rho1withPOT[:], rho1withPOT[:])
psi5withPOT[:] = psi5withPOT[:]*rho5withPOT[:]/trapz(psi5withPOT[:]*rho5withPOT[:], rho5withPOT[:])

plt.figure(figsize=(4*0.8,3*0.8))
plt.plot(rho001[:],psi001[:], linestyle='-',label=r"$\omega_r = 0.01$")
plt.plot(rho05[:],psi05[:], linestyle='--',label=r"$\omega_r = 0.5$",linewidth = 1.2)
plt.plot(rho1[:],psi1[:], linestyle='-.',label=r"$\omega_r = 1$",linewidth = 1.5)
plt.plot(rho5[:],psi5[:], linestyle=':',label=r"$\omega_r = 5$",linewidth = 2)
plt.ticklabel_format(style="sci",axis= "y",scilimits = (-2,2))
plt.title(ur"Eigenstates for $V(\rho) = 0$", fontsize=11)
plt.ylabel(r"$|\psi|^2 \rho/\alpha$ $\quad[ \ \cdot \ ]$")
plt.xlabel(r"$\rho$ $\quad[ \ \cdot \ ]$")
plt.legend()
plt.tight_layout(.5)
plt.savefig("psi_vs_rho.png")
plt.savefig("psi_vs_rho.pgf")
plt.figure(figsize=(4*0.8,3*0.8))
plt.plot(rho001withPOT[:],psi001withPOT[:], linestyle='-',label=r"$\omega_r = 0.01$")
plt.plot(rho05withPOT[:],psi05withPOT[:], linestyle='--',label=r"$\omega_r = 0.5$",linewidth = 1.2)
plt.plot(rho1withPOT[:],psi1withPOT[:], linestyle='-.',label=r"$\omega_r = 1$", linewidth =1.5)
plt.plot(rho5withPOT[:],psi5withPOT[:], linestyle=':',label=r"$\omega_r = 5$",linewidth = 2)
plt.ticklabel_format(style="sci",axis= "y",scilimits = (-2,2))
plt.title(ur"Eigenstates for $V(\rho) = 1/\rho$", fontsize=11)
plt.ylabel(r"$|\psi|^2\rho/\alpha$ $\quad[ \ \cdot \ ]$")
plt.xlabel(r"$\rho$ $\quad[ \ \cdot \ ]$")
plt.legend()
plt.tight_layout(.5)
plt.savefig("psi_vs_rho_with_interaction.png")
plt.savefig("psi_vs_rho_with_interaction.pgf")
