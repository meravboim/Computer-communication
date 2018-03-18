#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SIM_LENGTH 10 
#define PORT 80 
#define MAXBUF  1024

int main(int argc, char* argv[])
{ 
  struct sockaddr_in cli_name; 
  int sock, bytes_read,value,port;
  char hostname[100];
  char path[100];
  char* url;
  char* prefix="http://";
  struct addrinfo* res;
  struct sockaddr_in* saddr;
  char buffer[MAXBUF];
  
  if (argc != 2) {//print error if the user dont enter hostname
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  url = argv[1];//get the url from the user

  
  if (strncmp(url, prefix, 7) != 0) {// check if the url has a "http://" in the start
    printf("\nno http:// prefix found\n");
    exit(1);
  }

 
 sscanf(url, "http://%99[^/]/%99[^\n]", hostname, path); // cut the http:// 

  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {// check if the hostname is good
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  printf("Client is alive and establishing socket connection.\n");
  
  

  sock = socket(AF_INET, SOCK_STREAM, 0); //create the socket. for IPv4 protocol with TCP with the default for it.
  if (sock < 0)// check if the socket is OK
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }

  saddr = (struct sockaddr_in*)res->ai_addr;

  
  bzero(&cli_name, sizeof(cli_name)); // set all values in the buffer to zero
  cli_name.sin_family = AF_INET;//Set the family as IPv4 
  //cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
  cli_name.sin_addr.s_addr = inet_addr(inet_ntoa(saddr->sin_addr)); 
  cli_name.sin_port = htons(PORT);//set the port(80)

    
    if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)//check if there is a problem with the connection
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
    
    sprintf(buffer, "GET %s%s HTTP/1.0\n\n", hostname, path);
    send(sock, buffer, strlen(buffer), 0);

    do//read the data from the server
    {
        bzero(buffer, sizeof(buffer));
        bytes_read = recv(sock, buffer, sizeof(buffer), 0);
        if ( bytes_read > 0 )
            printf("%s", buffer);
    }
    while ( bytes_read > 0 );

  printf("Exiting now.\n");

  close(sock); 
  exit(0);

} 