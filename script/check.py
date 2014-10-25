# coding=UTF-8
from math import *

def check_sin():
	#sin(a+b) = sin(a)*cos(b)+cos(a)*sin(b)
	count = 30
	b = 1.5
	for i in xrange(count):
		a = pi*2.0/count
		print sin(a+b)-(sin(a)*cos(b)+cos(a)*sin(b))

def check_cos():
	#cos(a+b) = cos(a)*cos(b)-sin(a)*sin(b)
	count = 20
	b = 4.4
	for i in xrange(count):
		a = pi*2.0/count
		print cos(a+b) - (cos(a)*cos(b)-sin(a)*sin(b))

def check_sc():
	#sin(a)*cos(b) = 0.5*(sin(a+b)+sin(a-b))
	count = 20
	b = -0.222334
	for i in xrange(count):
		a = pi*2.0/count
		print sin(a)*cos(b) - 0.5*(sin(a+b)+sin(a-b))


def round_f(fdisc, frun, qmax):
	'''
	Ищем по возможности круглое число
	fdisc - частота дискретизации
	qmax - максимальное количество сэмплов
	'''
	delta_min = 100
	imin = 1
	period_disc = 1.0/fdisc
	period_run = 1.0/frun
	for i in xrange(1, qmax):
		period_cur = period_disc*i
		cur_min = (period_cur%period_run)/period_run
		if cur_min<delta_min:
			delta_min = cur_min
			imin = i
			print "imin=", imin, "delta_min=",delta_min

	pass

#check_sc()
round_f(48000, 9800, 10000)
