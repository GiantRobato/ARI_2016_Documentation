# Name: sendToArd.py
#
# Author: penguindustin
#
# Description: sends data over i2c to arduino pro mini. To properly implement this,
# You would send data in bytes over the the arduino in a specific order using just
# the `send` command.
# 

import smbus
import time

bus = smbus.SMBus(1)
address = 0x04
retry = 0

def sendToMini(data):
    global retry
    try:
        bus.write_byte(address,data)
    except IOError:
        retry = 1
    retry = 0

#helper function to make code cleaner
def send(data):
    sendToMini(data)
    if(retry == 1):
        while(retry == 1):
            sendToMini(data)

#the below is optional
time.sleep(2)
print "Starting program"
n = 0

#main loop
while True:
    raw_input("Press enter to get message ");
    send(n)
    n = n + 1

