
V = 12.0
Rk = 33+100.0
#V = 5.0
#Rk = 33+33.0

Rbk = 330+3300.0
Rbe = 1000.0
Vb = 0.7
Hfe = 130.0
#Hfe = 80.0

Irbe = Vb/Rbe

Ik = (V-Vb-Irbe*Rbk-Irbe*Rk)/(Rbk/Hfe+(1+1/Hfe)*Rk)
#Ik = 25e-3

Ib= Ik/Hfe
Iksum = Ik+Ib+Irbe
Vk = V - Iksum * Rk
Ibsum = Ib + Irbe
Vk1 = Ibsum*Rbk+Vb

print "Irbe=", Irbe
print "Ik=", Ik
print "Iksum=", Iksum
print "Ib=", Ib
print "Vk=", Vk, Vk1
print "Iksum * Rk=", Iksum * Rk