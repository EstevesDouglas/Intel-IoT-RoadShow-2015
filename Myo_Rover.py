#! /usr/bin/python
import time, sys, signal, atexit
import pyupm_l298 as upmL298
import socket

Motor01 = upmL298.L298(3, 4, 8)
Motor02 = upmL298.L298(5, 6, 7)
UDPSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

listen_addr = ("",21567)
UDPSock.bind(listen_addr)

def SIGINTHandler (signum, frame):
        raise SystemExit

def exitHandler():
        print "Existing"
        sys.exit(0)

atexit.register(exitHandler)
signal.signal(signal.SIGINT, SIGINTHandler)

print "Ligado Rover 5"
def frente():                                            
        Motor01.setSpeed(25)                             
        Motor01.setDirection(upmL298.L298.DIR_CW)        
        Motor01.enable(True)                             
        Motor02.setSpeed(25)                             
        Motor02.setDirection(upmL298.L298.DIR_CW)        
        Motor02.enable(True)                     
def direita ():                                  
        Motor01.setSpeed(5)                      
        Motor01.setDirection(upmL298.L298.DIR_CW)
        Motor01.enable(True)                     
        Motor02.setSpeed(50)                     
        Motor02.setDirection(upmL298.L298.DIR_CW)
        Motor02.enable(True)
def esquerda():                                          
        Motor01.setSpeed(50)                             
        Motor01.setDirection(upmL298.L298.DIR_CW)        
        Motor01.enable(True)                             
        Motor02.setSpeed(5)                              
        Motor02.setDirection(upmL298.L298.DIR_CW)        
        Motor02.enable(True)                     
                                                 
def stop ():                                     
        Motor01.setSpeed(0)                      
        Motor01.setDirection(upmL298.L298.DIR_CCW)
        Motor01.enable(True)                      
        Motor02.setSpeed(0)                       
        Motor02.setDirection(upmL298.L298.DIR_CCW)
        Motor02.enable(True) 
while True:                                              
        data,addr = UDPSock.recvfrom(1024)               
        command = data.strip()                           
        if command == 'MOVE_FORWARD':                    
                print "Call Frente"                      
                frente()                                 
        elif command == 'STOP_MOVE':              
                print "Call Parar"                
                stop()                            
        elif command == 'RIGHT_MOVE':             
                print "Call Direita"                 
                direita()                            
        elif command == 'LEFT_MOVE':                 
                print "Call Esquedar"                
                esquerda()                           
        else:                                        
                print "Comando nao reconhecido"      
                                     

                                 
        
