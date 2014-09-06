#!/usr/bin/python
import socket, sys
import usb_commands

# AA7AS - SdrDx sample TCP client

host = "127.0.0.1"		# IP of server (very likely you need to change this)
port = 58085 			# Default port of SdrDx TCP server

# process() takes a single message, breaks it into cmd
# and data, then deals with the data as appropriate
# THIS is the ONLY routine you should modify; you can
# catch any message from SdrDx here and do whatever
# you like in response. The example catches the closing
# message, and has a commented-out section showing how
# to capture the centf message and pass it to an imaginary
# SDR tuning command. Catching any other message? Use
# those as models.
# ----------------------------------------------------
def process(content):
	cmd,data = m.split(':')
	if cmd=='ping':
		return 1

	sys.stdout.write(m+'\n') # log
	sys.stdout.flush() # force print

	if cmd == 'closing':          # catch closing
		return 0 # stop right now # respond with exit flag

	elif cmd == 'freq':          # catch change in center frequency
		freq = float(data)
		print "freq=", freq
		usb_commands.setFreq(freq*2)

	return 1 # keep going         # otherwise, don't exit

# parse() creates an array that contains from zero
# to n messages and returns that to the caller
# ------------------------------------------------
def parse(msg):
	try:
		msgs = msg.split('|')		# can be more than one message in packet
	except:							# failed to split
		msgs = []					# on the other hand, can just be one. :)
		msgs.append(msg)			# so build array with that one.
	# also possible messages separated by null:
	ms2 = []
	for m in msgs:
		try:
			ms = m.split(chr(0))
		except:
			ms2.append(m)
		else:
			for mm in ms:
				if mm != '':
					ms2.append(mm)
	return ms2						# hand back assembled list

# Create socket
# -------------
try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	sys.stderr.write("[ERROR] %s\n" % msg[1])
	sys.exit(1)

# Attempt to connect to SdrDx's TCP server
# ----------------------------------------
try:
	s.connect((host,port))
except socket.error, msg:
	sys.stderr.write("[ERROR] %s\n" % msg[1])
	sys.exit(2)

s.send("poll:0"+chr(0)) # ask SdrDx for freq, mode

# This is the main program loop, where we watch for messages
# from SdrDx, and optionally send commands to it (see s.send(),
# above for example of sending a command, it's very easy)
#
# see process(), at top, for example of catching messages
#
# The structure of the system requires that SdrDx be running
# before the client is, so that the TCP server will "be there"
# when the attempt to connect is made.
#
# You should not need to change the code below here
# ------------------------------------------------------------
if not usb_commands.findDevice():
    sys.exit(0)


data = ''
looping = 1
while looping:
	try:
		data = s.recv(4096)
	except KeyboardInterrupt: # you can safely stop with control-C
		s.send("close:0"+chr(0))
		print '\nclient aborted by user'
		looping = 0 # stop running
		data = '' # prevent any pending data from being handled
	except socket.error, msg: # something went wrong:
		sys.stderr.write("[ERROR] %s\n" % msg[1]) # say so
		looping = 0 # stop running
		data = '' # prevent any pending data from being handled
	ll = len(data) # how much data do we have?
	if ll > 0: # if we have any at all, then:
		msgs = parse(data) # break packets into a list of messages
		if len(msgs): # if we actually got some messages
			counter = 1
			for m in msgs:
				looping = process(m) # do whatever needs to be done
				counter += 1 # counter for log
s.close() # close the TCP socket, disconnect from server

sys.exit(0) # quit with no error
