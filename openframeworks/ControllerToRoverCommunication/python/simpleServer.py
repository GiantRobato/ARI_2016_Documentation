import SocketServer

class MyTCPHandler(SocketServer.BaseRequestHandler):
    """
    The request handler class for our server.
    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        while(1):
            # self.request is the TCP socket connected to the client
            self.data = self.request.recv(1024).strip()
            print "{} wrote:".format(self.client_address[0])
            print self.data
            # just send back the same data, but upper-cased
            #self.request.sendall("Hello\r\n")
            self.request.sendall(self.data.upper())
            print "Sent data"

if __name__ == "__main__":
    HOST, PORT = "192.168.112.101", 9999

    #reuse socket
    SocketServer.TCPServer.allow_reuse_address = True

    # Create the server, binding to localhost on port 9999
    server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()