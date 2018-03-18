
pas = raw_input("Enter password: ")
user = raw_input("Enter user: ")

    
if user and pas:
    with open("passwords.txt", 'r') as infile:     #open the file
        for line in infile:
            password = line.strip('\r\n')
            print "Testing: " + str(password)
            if (password==pas):
                print 'Password Found: ' + password
                exit(0)
else:
    exit(0)
print 'password Not Found '

