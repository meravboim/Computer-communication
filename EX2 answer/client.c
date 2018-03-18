#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int socket_fd, dd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
char msgbuf[100];

  socket_fd = socket(AF_INET, SOCK_DGRAM, 0); //create the socket. for IPv4 protocol with UDP with the default for it.
  memset((char *) &dest,0, sizeof(dest));/* They say you must do this */ //put 0 in the sizeof(dest) first tavs. To delete unnecessary information.
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  dest.sin_family = (short) AF_INET;//Set the family as IPv4
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);// copy the name of the host
  dest.sin_port = htons((u_short)0x3333);//Set port number by converting with htons function
  int ifexit=1;
  char exit[5];
  while(ifexit){
    printf("enter massage to the server(instead of space write '-')\n");
    scanf("%s",&msgbuf);
  sendto(socket_fd,&msgbuf,100,0,(struct sockaddr *)&dest,sizeof(dest));//send the data (UDP)
  //receive the server response
  char msgback[100];
  int fsize = sizeof(dest);
  dd = recvfrom(socket_fd,&msgback,100,0,(struct sockaddr *)&dest,&fsize);
  printf(" Got data ::%s\n",msgback); 
   printf("enter exit if you want to exit,other write somthig else\n");
    scanf("%s",&exit);
    if (strcmp(exit, "exit")==0)
    ifexit=0;
  }
  return 0;

}