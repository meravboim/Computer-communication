from ftplib import FTP
import os
import fileinput

ftp = FTP('')
ftp.connect('localhost',1026)
ftp.login()
ftp.cwd('Desktop') #replace with your directory - The destination place, the root is the server place!
ftp.retrlines('LIST')

def uploadFile():
 filename = '/home/merav/Desktop/send.txt' #replace with your file in your home folder - The source file
 ftp.storbinary('STOR '+ os.path.basename(filename), open(filename, 'rb'))
 ftp.quit()

def downloadFile():
 filename = 'send1.txt' #replace with your file in the directory ('directory_name')
 localfile = open(filename, 'wb')
 ftp.retrbinary('RETR ' + filename, localfile.write, 1024)
 ftp.quit()
 localfile.close()

uploadFile()
#downloadFile()
