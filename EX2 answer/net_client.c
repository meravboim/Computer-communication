
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#define SIM_LENGTH 10 
//#define IP_ADDRESS "10.9.3.64" 
#define PORT 1337 

int main(int argc, char* argv[])
{ 
  
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 


  printf("Client is alive and establishing socket connection.\n");
  struct addrinfo* res;
  char* hostname;//the hostname that recieved from the user
  char* hostaddr;//the addres that match to the hostname
  struct sockaddr_in* saddr;
  
  if (argc != 2) {//print error if the user dont enter hostname
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1];//define the hostname as what the user input
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);//find the ip addres 
    
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);//find the ip addres 
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)//check if there is poblem, and exit if there is
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      

  memset((char *)&cli_name,0, sizeof(cli_name)); //put 0 in the sizeof(cli_name) first tavs. To delete unnecessary information.
  cli_name.sin_family = AF_INET; //Set the family as IPv4
  cli_name.sin_addr.s_addr = inet_addr(hostaddr); 
  cli_name.sin_port = htons(PORT);//Set port number by converting with htons function


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)//check if there is poblem, and exit if there is
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);//recieve the value from the server
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 