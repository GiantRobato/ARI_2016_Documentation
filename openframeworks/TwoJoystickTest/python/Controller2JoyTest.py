# Name: Controller2JoyTest.py
#
# Author: penguindustin
#
# Description: reads in two controller sticks and sends it
# appropriately to the arduino microcontroller
#

import SocketServer
import smbus
import time

bus = smbus.SMBus(1)
address = 0x04
retry = 0

def proMini(cmd,data):
	global retry
	try:
		#message = bus.read_byte_data(address,1);
		message = bus.write_byte_data(address,cmd,data);
	except IOError:
		retry = 1;
		return 0
	retry = 0
	return message

def sendToProMini(cmd,data):
	msg = proMini(cmd,data)
	if retry == 1:
		while retry == 1:
			msg = proMini(cmd,data)

class MyTCPHandler(SocketServer.BaseRequestHandler):
	def handle(self):
		while(1):
			self.data = self.request.recv(1024).strip();
			#print "GS sent: ", self.data
			self.data = self.data.replace("[/TCP]","")
			s = self.data.split()
			print "left stick: ", s[0] #for debug
			print "right stick: ", s[1] #for debug
			datToSend = int(s[0].strip('\0'))
			sendToProMini(0, datToSend)
			datToSend = int(s[1].strip('\0'))
			sendToProMini(1,datToSend)
			#send to arduino

if __name__ == "__main__":
	HOST, PORT = "192.168.112.101", 9999

	SocketServer.TCPServer.allow_reuse_address = True
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	server.serve_forever()	

time.sleep(2)
print "Starting program :)"
