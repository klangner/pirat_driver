'''
Created on Jun 1, 2014

@author: Krzysztof Langner
'''

import bluetooth

target_name = "MyRover"
target_address = None

nearby_devices = bluetooth.discover_devices()

for bdaddr in nearby_devices:
    if target_name == bluetooth.lookup_name( bdaddr ):
        print "found %s device with address: %s " % (target_name, bdaddr)

print "Done"