# coding=UTF-8
import time
import serial

# ls /dev/cu.* <--- find device in Mac OS X

ser = None
lastData = ""

def connect():
	global ser
	ser = serial.Serial(
		#port='/dev/cu.usbmodem621', #left USB
		port='/dev/cu.usbmodem411', #right USB
		baudrate=115200,
		parity=serial.PARITY_ODD,
		stopbits=serial.STOPBITS_TWO,
		bytesize=serial.SEVENBITS
	)

	# ls /dev/cu.* <--- find device
	return ser.isOpen()

def close():
	ser.close()

def encode(data):
	ret = ""
	if data is None:
		return ret

	for c in data:
		oc = ord(c)
		if oc>=0xFE:
			ret += chr(0xFE)+chr(oc-0xFE)
		else:
			ret += c
	return ret

def decode(data):
	ret = ""
	last_is_FE = False
	for c in data:
		oc = ord(c)
		assert(oc!=0xFF)
		if oc==0xFE:
			last_is_FE = True
			continue

		if last_is_FE:
			if oc==0:
				c=chr(0xFE)
			elif oc==1:
				c=chr(0xFF)
			else:
				assert(0)
			last_is_FE = False
		ret += c

	return ret

def send(command, data=None):
	#в начало добавить command 
	#добавить data, преобразовать FE, FF как надо
	#в конец добавить FF
	assert(command>=0 and command<0xFF)
	full_data = chr(command) + encode(data) + chr(0xFF)
	#print "Send:"
	#printBin(full_data)
	ser.write(full_data)
	pass

def receive():
	global lastData
	time.sleep(0.01)
	command = None
	while ser.inWaiting() > 0:
		c = ser.read(1)
		if ord(c)==0xFF:
			command = decode(lastData)
			lastData = ""
			break
		else:
			lastData += c
	return command

def printBin(s):
	for c in s:
		print hex(ord(c)),
	print
	pass

def test():
	s = chr(0xFF)
	s += "abc"
	s += chr(0xFE)

	se = encode(s)
	printBin(se)
	s1 = decode(se)
	printBin(s1)
	pass
def test2():
	if not connect():
		print "Cannot connect device"
	send(2, "DDD")
	ret = receive()
	if ret:
		printBin(ret)

	send(3, "")
	ret = receive()
	if ret:
		printBin(ret)

	close()
	pass

#test2()
