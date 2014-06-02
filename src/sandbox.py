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
print 'Sent forward behavior'
sock.send("f")
time.sleep(4)
sock.send("s")

sock.close()