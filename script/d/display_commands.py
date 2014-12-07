import time
import serial_protocol
import struct
import math

from serial_protocol import receive

COMMAND_NONE = 0
COMMAND_PRINT_INT = 1
COMMAND_SEND_SPI = 2
COMMAND_SET_FREQ = 3
COMMAND_SIDE_BAND = 4

def connect():
	if not serial_protocol.connect():
		print "Cannot connect to device"
		return False
	return True

def close():
	serial_protocol.close()

def command(comd, data=None):
	serial_protocol.send(comd, data)

def command_none():
	command(COMMAND_NONE, "ABCDEF")
	data = receive()
	print "len(data)=", len(data)
	(cmd, value) = struct.unpack('=BI', data)
	print "cmd=", cmd, "value=", value
	#assert(cmd==COMMAND_GET_REF)
	return

def command_print_int(i,x,y):
	command(COMMAND_PRINT_INT, struct.pack("=III", i, x, y))
	return;

def command_spi_send(data):
	command(COMMAND_SEND_SPI, struct.pack("=H", data))
	return;

def command_freq(freq):
	command(COMMAND_SET_FREQ, struct.pack("=I", freq))
	return;

def command_side_band(upper_side_band):
	if upper_side_band:
		ub = 1
	else:
		ub = 0
	print "usb=", ub
	command(COMMAND_SIDE_BAND, struct.pack("=B", ub))
	return;


def main():
	if not connect():
		return

	#command_none()
	#command_print_int(123, 17, 38)
	#command_spi_send(1277)
	command_freq(123000)

	close()
	pass

if __name__ == "__main__":
	main()