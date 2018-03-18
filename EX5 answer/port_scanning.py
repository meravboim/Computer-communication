import socket
import subprocess
import sys
from datetime import datetime
from distutils import text_file
from random import shuffle
from sqlite3 import collections
from array import array

class PortScanning(object):
 @classmethod
 def scan(self,ip):
  way_of_scan = input("Enter 0-to usual scan ,1- to random scan ,2-to efficiently scan: ")
  pace = input("Enter a pace of scan: ")
  remoteServer = ip
  remoteServerIP = socket.gethostbyname(remoteServer)


  if way_of_scan==0:
      try:
          file = open("port-scanning-usual.txt",'a')
          for port in range(0,1000):  
              sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
              socket.setdefaulttimeout(pace)
              result = sock.connect_ex((remoteServerIP, port))
              if result == 0:
                  print("Port  %d : Open" % port)
                  file.writelines("Port  %d : Open \n" % port)
                  sock.close()
              else:
                  print("Port  %d : Close" % port)
                  file.writelines("Port  %d : Close \n" % port)
                  sock.close()
      finally:
            file.close()
          
  if way_of_scan==1:
      try:
          file = open("port-scanning-random.txt",'a')
          x = list(range(1000))
          shuffle(x)
          for port in x:
              sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
              socket.setdefaulttimeout(pace)
              result = sock.connect_ex((remoteServerIP, port))
              if result == 0:
                  print("Port  %d : Open" % port)
                  file.writelines("Port  %d : Open \n" % port)
                  sock.close()
              else:
                  print("Port  %d : Close" % port)
                  file.writelines("Port  %d : Close \n" % port)
                  sock.close()
      finally:
            file.close()
          
  if way_of_scan==2:
      try:
          file = open("port-scanning-efficiently.txt",'a')
          y = [80,443,22,161,123,21,25,53,23,110,143,111,135,137,445,81,139,587,389,20,37,113,161,500,69]
          x = set(range(1000)) - set(y)
          for port in y:
              sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
              socket.setdefaulttimeout(pace)
              result = sock.connect_ex((remoteServerIP, port))
              if result == 0:
                  print("Port  %d : Open" % port)
                  file.writelines("Port  %d : Open \n" % port)
                  sock.close()
              else:
                  print("Port  %d : Close" % port)
                  file.writelines("Port  %d : Close \n" % port)
                  sock.close()
          for port in x:
              sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
              socket.setdefaulttimeout(pace)
              result = sock.connect_ex((remoteServerIP, port))
              if result == 0:
                  print("Port  %d : Open" % port)
                  file.writelines("Port  %d : Open \n" % port)
                  sock.close()
              else:
                  print("Port  %d : Close" % port)
                  file.writelines("Port  %d : Close \n" % port)
                  sock.close()
      finally:
            file.close()
          
          
