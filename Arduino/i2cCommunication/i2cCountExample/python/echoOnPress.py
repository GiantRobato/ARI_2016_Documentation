# Name: echoOnPress.py
#
# Author: penguindustin
#
# Description: reads an echo i2c device when 'enter' is pressed
#

import smbus
import time

bus = smbus.SMBus(1)
address = 0x04
retry = 0

def proMini():
	global retry
	try:
		message = bus.read_byte_data(address,1);
	except IOError:
		retry = 1;
		return 0
	retry = 0
	return message

time.sleep(2)
print "Starting program"

#main loop
while True:
	raw_input("Press enter to get message ");
	msg = proMini()
	if retry == 1:
		while retry == 1:
			msg = proMini()
			#the below is optional
			#time.sleep(.05)
	print msg
