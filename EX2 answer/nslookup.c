
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
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

  printf("Address for %s is %s\n", hostname, hostaddr);//printing the hostname and the addres
  exit(0);
}