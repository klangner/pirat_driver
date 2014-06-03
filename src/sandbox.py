'''
Created on Jun 1, 2014

@author: Krzysztof Langner
'''

import bluetooth
import time


ROVER_NAME = "MyRover"
ROVER_ADDRESS = "00:18:E4:0C:68:09"
PORT = 1

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((ROVER_ADDRESS, PORT))
print 'Connected'
sock.settimeout(1.0)
print "forward command"
sock.send("forward\n")
time.sleep(4)
print "stop command"
sock.send("stop\n")

sock.close()