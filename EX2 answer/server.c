#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void printsin(struct sockaddr_in *sin, char *pname, char *msg){
char *ip= inet_ntoa(sin->sin_addr); // https://linux.die.net/man/3/inet_ntoa
puts(pname); 
printf("%s",msg);
printf(" ip= %s  port= %d\n",ip,sin->sin_port);
}

int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
 char msg[100];
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//create the socket. for IPv4 protocol with UDP with the default for it.

  memset((char *) &s_in,0, sizeof(s_in));   /* They say you must do this    *///put 0 in the sizeof(s_in) first tavs. To delete unnecessary information.

  s_in.sin_family = (short)AF_INET;//Set the family as IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */// set Internet address 
  s_in.sin_port = htons((u_short)0x4444);//Set port number by converting with htons function

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);//clean the memory

bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//conect between the port to the socket
int ifexit=1;
  char exit[5];
  while(ifexit){//allways listening
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&from,&fsize);//get the data (UDP)
    printsin( &from, "recv_udp: ", "Packet from:");
    printf(" Got data ::%s\n",msg);
    //send the server response
    char msback[]="server get the massage";
    sendto(socket_fd,&msback,100,0,(struct sockaddr *)&from,sizeof(from));
       printf("enter exit if you want to exit,other write somthig else\n");
    scanf("%s",&exit);
    if (strcmp(exit, "exit")==0)
    ifexit=0;
    fflush(stdout);//clean the memory
  }
  return 0;
}