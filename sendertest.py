#! /usr/bin/python

import socket
import time

ip = "192.168.1.2"
port = 21567
  
print "Rover target IP:", ip
print "Rover target port:", port

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.sendto("MOVE_FORWARD", (ip, port))
time.sleep(2)

sock.sendto("STOP_MOVE", (ip, port))
time.sleep(4)

sock.sendto("MOVE_FORWARD", (ip, port))
time.sleep(2)

sock.sendto("STOP_MOVE", (ip, port))
