# -*- coding: UTF-8 -*-
# balmer@inbox.ru 2015 SDR Mixer test

from math import *
import matplotlib.pyplot as plt

'''
Протестируем такое утверждение:
	Основное отличие во времени открытого состояния ключей смесителя со 
	всеми вытекающими последствиями. В Вашей схеме это четверть периода, 
	в тех на которые мной даны ссылки - половина периода.

Пусть будет такоая убогенькая вещь конструкция.
Есть тактовый генератор, который генерирует время. 
Есть синусоидальные генераторы.
Есть смесители (синусоидальный и ключевой).
Есть детектор амплитуды сигнала.
Есть штука, которая частоту считает.

phase меняется от 0 до 1
'''

class SinGen:
	def __init__(self, freq, phase=0):
		self.freq = freq
		self.phase = phase
		pass
	def go(self, time):
		return sin(2*pi*(self.freq*time+self.phase))

class SquareGen:
	'''
		Половина такта - единица
	'''
	def __init__(self, freq, phase=0, fill=0.5):
		self.freq = freq
		self.phase = phase
		self.empty = 1.0-fill
		pass
	def gof(self, time, phase):
		f = self.freq*time+self.phase+phase
		r = f % 1.0
		if r<self.empty:
			return 0
		return 1.0

	def go(self, time):
		return self.gof(time, 0)

class Mixer:
	def __init__(self, func):
		self.func = func
		pass
	def go(self, time, xin):
		return self.func.go(time)*xin

class Mixer2:
	def __init__(self, func):
		self.func = func
		pass
	def go(self, time, xin):
		return self.func.gof(time, 0)*xin-self.func.gof(time, 0.5)*xin

def iir(NewSample, x, y, ACoef, BCoef, NCoef):
	#shift the old samples
	for n in xrange(NCoef, 0, -1):
		x[n] = x[n-1]
		y[n] = y[n-1]

	#Calculate the new output
	x[0] = NewSample
	y[0] = ACoef[0] * x[0]
	for n in xrange(1, NCoef+1):
		y[0] += ACoef[n] * x[n] - BCoef[n] * y[n]

	return y[0]

class Filter5KHz:
	'''
	Filter type: Low Pass
	Filter model: Chebyshev
	Sampling Frequency: 100 KHz
	Cut Frequency: 5.000000 KHz
	Pass band Ripple: 1.000000 dB
	'''
	NCoef = 4
	ACoef = [
	0.00014578208376921133,
	0.00058312833507684532,
	0.00087469250261526803,
	0.00058312833507684532,
	0.00014578208376921133
	]

	BCoef = [
	1.00000000000000000000,
	-3.60789616912903900000,
	4.97947080375098670000,
	-3.11076368298272810000,
	0.74152014735579552000
	]

	def __init__(self):
		self.x = [0]*(self.NCoef+1)
		self.y = [0]*(self.NCoef+1)
		pass

	def iir(self, NewSample):
		return iir(NewSample, self.x, self.y, self.ACoef, self.BCoef, self.NCoef)

class Filter20KHz:
	'''
	Filter type: Low Pass
	Filter model: Butterworth
	Filter order: 2
	Sampling Frequency: 10 MHz
	Cut Frequency: 0.020000 MHz
	'''
	NCoef = 2
	ACoef = [
	0.00003865708800429753,
	0.00007731417600859505,
	0.00003865708800429753
	]

	BCoef = [
	1.00000000000000000000,
	-1.98222892979252820000,
	0.98238545061412497000
	]

	def __init__(self):
		self.x = [0]*(self.NCoef+1)
		self.y = [0]*(self.NCoef+1)
		pass

	def iir(self, NewSample):
		return iir(NewSample, self.x, self.y, self.ACoef, self.BCoef, self.NCoef)

def myplot(xdata, ydata):
	fig, ax = plt.subplots()
	ax.plot (xdata, ydata)
	plt.show()


def test0():
	sg = SinGen(1000)
	#mx = Mixer(SinGen(1100))
	mx = Mixer2(SquareGen(1100, fill=0.25))
	f5 = Filter5KHz()
	#sg = SquareGen(1, 0, 0.3)
	timedata = []
	ydata = []
	for itime in xrange(600):
		time = itime*1e-5
		xin = 1 #sg.go(time)
		y = mx.go(time, xin)
		#y = f5.iir(xin)

		timedata.append(time)
		ydata.append(y)

	myplot(timedata, ydata)

def test1():
	'''
	Изначально сигнал на 10 МГц
	Потом применяем к нему миксер, пропускаем через Filter20KHz
	Берем каждый сотый сэмпл. Получаем сигнал с квантизацией 100 КГц
	Его фильруем Filter5KHz
	'''
	freq = 250e3
	sg = SinGen(freq*5+1.2e3, phase=0.25)
	mx = Mixer(SinGen(freq))
	#mx = Mixer2(SquareGen(freq))
	#mx = Mixer2(SquareGen(freq, fill=0.25))
	
	dt = 1e-7 #10 MHz
	f20 = Filter20KHz()
	f5 = Filter5KHz()
	i100 = 0
	timedata = []
	ydata = []
	for itime in xrange(30*1000):
		time = itime*dt
		xin = sg.go(time)
		x1 = mx.go(time, xin)

		y = f20.iir(x1)

		i100 += 1
		if i100>=100:
			i100 = 0

			y = f5.iir(y)
			timedata.append(time)
			ydata.append(y)
		pass

	myplot(timedata, ydata)

test1()

