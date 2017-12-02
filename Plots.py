import numpy as np
import matplotlib.pyplot as plt

data= np.genfromtxt('RadialVelocities.dat')
bb=0.2497
bd=5.16
ad=0.3105
ah=64.3

R=data[:,0]
y=data[:,1]


def likelihood(y_obs, y_model):
    chi_squared = (1.0/2.0)*sum((y_obs-y_model)**2)
    return (-chi_squared)

mod=[]
mb0=16.08
md0=6326.02
mh0=15008.30
i=0
mod=mb0**(1.0/2.0)*R/(R**2+bb**2)**(3.0/4.0)+md0**(1.0/2.0)*R/(R**2+(bd+ad)**2)**(3.0/4.0)+mh0**(1.0/2.0)/(R**2+ah**2)**(1.0/4.0)

plt.plot(R,y, label="Datos experimentales")
plt.plot(R,mod, label="Modelo")
plt.legend()
plt.xlabel("R")
plt.ylabel("Vcirc")
plt.savefig("Datosymodelo.jpg")

"res=likelihood(x,y)"

 

