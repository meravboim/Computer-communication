#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10 
#define PORT 1337 

void clean_up(int cond, int *sock)//close the socket
{ printf("Exiting now.\n");
  close(*sock); 
  exit(cond);
} 

int main(void)
{ 
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  socklen_t len; 
  int count;
  
  sock = socket(AF_INET, SOCK_STREAM, 0); //create the socket. for IPv4 protocol with UDP with the default for it. 
  if (sock < 0)//check if there is poblem, and clean the socket if there is
    { perror ("Error opening channel");
      clean_up(1, &sock);
    }
  
  memset((char *)&serv_name,0, sizeof(serv_name)); //put 0 in the sizeof(serv_name) first tavs. To delete unnecessary information.
  serv_name.sin_family = AF_INET; //Set the family as IPv4                                  
  serv_name.sin_port = htons(PORT); //Set port number by converting with htons function

  if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0)//check if there is poblem, and clean the socket if there is
    { perror ("Error naming channel");
      clean_up(1, &sock);
    }
      
  printf("Server is alive and waiting for socket connection from client.\n");
  listen(sock, 1); //listen to the client

  len = sizeof(serv_name);
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);

  for (count = 1; count <= SIM_LENGTH; count++)
    { 
	  write(connect_sock, &count, 4);//return the value to the client
      printf("Server has written %d to socket.\n", count);
    }

  close(connect_sock); 
  clean_up(0, &sock); //close the socket

}