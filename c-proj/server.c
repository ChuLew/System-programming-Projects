#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


void *conhandle(void*sockfd);

int main( int argc, char* argv[]) 
{
int sockfd,newsockfd,portno=5001,clilen,optval=1;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr; //  sockaddr is a struct generic container that just allows os to read the first couple bytes that identify the adress family
	//address family detrmines what variant of the sockaddr struct to use that contains elements that make sense for that specific ommunication type
	// for ip newtowrking , we use struct sockaddr_in which has 
	/*struct sockaddr_in {
		_uint8_t sin_len;
		sa_family_t sin_family; //sin_family the adress family we use to set up socket in our case its AF_INET
		in_port_t sin_port;//	sin_port is the portnumber 
		struct in_addr sin_addr;//sin_addr is adress for socket ( this is your machines ip adress) you can you INADDR_ANY to access this adress	
	char  sin_zero[8];
	}*/

int n;

//first call to socket() function
sockfd=socket(AF_INET, SOCK_STREAM,0);//initialize the socket socket name is sockfd 
//AF_INET (Internet protocol) identifies host connected to internet
//SOCK_STREAM (type of service) sockstream is a virtual circuit servicedelivery in a networked enviorment is guaranteed if u send abc you they will arrive in same order.
	if(sockfd<0)//sockfd is a socket descriptor returned by the socket function
	{
	perror("ERROR OPENING SOCKET");

	}

if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeof(int))<0){ //fixes already in  use part
perror("setsockopt(SO_REUSEADDR) failed");
}
/*initialize socket structure*/ 
bzero((char*)&serv_addr, sizeof(serv_addr)); //bzero(void *s, int nbytes); bzero function places nbytes null bytes in the string s, used to set all the socket structures with null values // serv_addr is a struct that contains destination IP adress and port portno=5001;

serv_addr.sin_family=AF_INET;//sin family is the adress family we use wehn we set up socket 
serv_addr.sin_addr.s_addr=INADDR_ANY;//the adress of this socket, this is your machines ip adress. INADDR_ANY  or 0.0.0.0 is is your machines ip adress 0.0.0.00 allows any connection on any ip so to restrict use inet_addr("127.0.0.1")
//htonl(INADDR_LOOPBACK)//restricts ip to hostnetwork
serv_addr.sin_port=htons(portno);// the port number (the transport adress) hosttonewtowrk (htons) a random portnumber would be htons(0)

/* now bind the host address using bind() call */
if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) 
// bind contains 3 agruments 1) socket, specifies the file descriptor of the socket to be bound 
//adress points to sockaddr structure contanining the adress to be bound to the socket
//adress len specifies the length of the sockaddr structure pointed to by the adress argument
{
 	perror("error on binding");
	exit(1);
}// upon completoin to bind a 0 shall be returned. if not it will return -1 and error messages displayed

//now start listening for the clients, here process will go in sleep mode and will wait for incoming connections
while(1){
listen(sockfd,100);
clilen=sizeof(cli_addr);//size of client
pthread_t thread_id;
/* accept actual connection from the client*/
newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
if(pthread_create(&thread_id,NULL,conhandle,(void*)&newsockfd)<0)
{
	perror("could not create thread");
}
//printf("connection accepted\n");

if(newsockfd<0)
{
	perror("error on accept");
	exit(1);
}

/* if connection is accepted than start communicating */
/*bzero(buffer,256);
n = read( newsockfd, buffer, 255);

if(n<0)
{
 	perror("error reading from scoket");
	exit(1);
}

printf("here is the messsage: %s\n",buffer);
// write a response to a client  
n=write(newsockfd,"Message received!", 18);

if(n<0)
{
	perror("error reading form scoket");
	exit(1);

}*/
}
return 0;
}
void *conhandle(void*sockfd)
{
	printf("connection accepted\n");
	int n;
	int sock = *(int*)sockfd;
	char buffer[256];
	
	/* if connection is accepted than start communicating */
bzero(buffer,256);
n = read( sock, buffer, 256);

if(n<0)
{
 	perror("error reading from socket");
	exit(1);
}

printf("here is the messsage: %s\n",buffer);
// write a response to a client  
n=write(sock,"Message received!", 18);

if(n<0)
{
	perror("error reading form scoket");
	exit(1);

}
	
}
