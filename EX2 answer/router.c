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
#include <stdlib.h>


int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize,dd;
  struct sockaddr_in  s_in, from,dest;
  //struct hostent *hostptr;

 char clientmsg[100];
 char servermsg[100];

socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//create the socket. for IPv4 protocol with UDP with the default for it.
 
  memset((char *) &s_in,0, sizeof(s_in));   /* They say you must do this    *///put 0 in the sizeof(s_in) first tavs. To delete unnecessary information.
 memset((char *) &dest,0, sizeof(dest));/* They say you must do this */ //put 0 in the sizeof(dest) first tavs. To delete unnecessary information.
  
 s_in.sin_family = (short)AF_INET;//Set the family as IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */// set Internet address 
  s_in.sin_port = htons((u_short)0x3333);//Set port number by converting with htons function
  
  //hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  
  dest.sin_family = (short) AF_INET;//Set the family as IPv4
  //memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);// copy the name of the host
  dest.sin_port = htons((u_short)0x4444);//Set port number by converting with htons function

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//conect between the port to the socket
  bind(socket_fd, (struct sockaddr *)&dest, sizeof(dest)); 
  double x;
  while(1) {//allways listening
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&clientmsg,100,0,(struct sockaddr *)&from,&fsize);//get the data (UDP)
    //send the server response
    srand(time(NULL));
    double random=(double)rand()/(double)RAND_MAX ;
    printf("enter double number\n");
     scanf("%lf",&x);
   
   
    if(random>x){
    sendto(socket_fd,&clientmsg,100,0,(struct sockaddr *)&dest,sizeof(dest));
    int dsize = sizeof(dest);
   dd = recvfrom(socket_fd,&servermsg,100,0,(struct sockaddr *)&dest,&dsize);//get the data (UDP)
    sendto(socket_fd,&servermsg,100,0,(struct sockaddr *)&from,sizeof(from));
  }
else{
    char msg[]="Continuing the conversation";
   sendto(socket_fd,&msg,100,0,(struct sockaddr *)&from,sizeof(from));
  }
    fflush(stdout);//clean the memory
  }
  return 0;
}
 



 
  
  