# coding=UTF-8
import usb
import time
import datetime
import os
import struct
import sys
import math

COMMAND_HELLO = 1
COMMAND_DDS_WORD = 2

dev = None
log_text_edit = None
CLKIN = 125e6 #125 MHz
FMUL = math.pow(2,32)/CLKIN

def log(text):
    global log_text_edit
    if log_text_edit:
        log_text_edit.append(text)
    else:
        print text
    pass


def findDevice():
    global dev
    dev = usb.core.find(idVendor=0x16C0, idProduct=0x05DC)

    if dev is None:
        log('Device not found')
        return False
    else:
        log("Device found")

    dev.set_configuration()
    dev.reset()
    return True

def dwrite(data):
    return dev.write(3, data, interface=1)

def readAll():
    time.sleep(0.1)
    while True:
        try:
            data = dev.read(129, 128, interface=1, timeout=50)
            if len(data)==0:
                break
            print "readb=", data
            #print "read=", data.tostring()
        except usb.core.USBError:
            break
    pass

def readOne():
    try:
        data = dev.read(129, 128, interface=1, timeout=50)
        if len(data)==0:
            print "Read empty"
        else:
            print "readb=", data
            #print "read=", data.tostring()
    except usb.core.USBError:
        print "Read USB error"
    pass

def readInt():
    data = dev.read(129, 128, interface=1, timeout=50)
    out = None
    if len(data)!=4:
        log("Fail read int len="+str(len(data)))
    else:
        out = data[0]+data[1]*0x100+data[2]*0x10000+data[3]*0x1000000
    return out

def printEndpoint(e):
    print "Endpoint:"
    print "bLength=", e.bLength
    print "bDescriptorType=", e.bDescriptorType
    print "bEndpointAddress=", e.bEndpointAddress
    print "bmAttributes=", e.bmAttributes
    print "wMaxPacketSize=", e.wMaxPacketSize
    print "bInterval=", e.bInterval
    print "bRefresh=", e.bRefresh
    print "bSynchAddress=", e.bSynchAddress
    pass

def uint32ToBytes(address):
    return [address%0x100, (address//0x100)%0x100, (address//0x10000)%0x100, (address//0x1000000)%0x100]

def hello():
    dev.write(3, [COMMAND_HELLO], interface=1)
    readOne()
    pass

def setFreq(f):
    if f>35e6:
        print "bad freq=", f
        return
    wrd = int(f*FMUL)
    print "wrd=", hex(wrd)
    dwrite(struct.pack("=BI", COMMAND_DDS_WORD, wrd))
    readOne()
    pass    

def main():
    if not findDevice():
        return

    hello()
    setFreq(2.2e6*2)


    log('Query complete.')

if __name__ == "__main__":
    main()

