#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main( int argc, char* argv[]){
	int sockfd, portno , n;
	struct sockaddr_in serv_addr;
	struct hostent * server;
	// struct hostent in most cases you will know the name of the machine but not its ip adress. an easy way of getting
	// the ip adress is with the hostbyname library (lbc) function. gethostbyname accepts a host name as a parameter and returns a hostent structure;
	/*struct hostent {
		char *h_name;		//offcial name of host		
		char ** h_aliases;	//alias lsit
		int h_addrtype;		//host adress type
		int h_length;		//legth of adress
		char **h_addr_list;	// list of adress from name server
	}*/
	
	char buffer[256];
	if (argc<3){
	fprintf(stderr,"usage %s hostname port\n", argv[0]);
	exit(0);
	}
	
	portno = atoi(argv[2]);
	 /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
     server = gethostbyname(argv[1]); // gethostbyname accepts a host name as a parameter and returns a hostent structure;
	 if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
	 }
	   
	   bzero((char *) &serv_addr, sizeof(serv_addr));//  The bzero() function erases the data in the n bytes of the memory
       //starting at the location pointed to by s, by writing zeroes (bytes containing '\0') to that area
	  // void bzero(void *s, size_t n);
	  
	   /*struct sockaddr_in {
		_uint8_t sin_len;
		sa_family_t sin_family; //sin_family the adress family we use to set up socket in our case its AF_INET
		in_port_t sin_port;//	sin_port is the portnumber 
		struct in_addr sin_addr;//sin_addr is adress for socket ( this is your machines ip adress) you can you INADDR_ANY to access this adress	
	char  sin_zero[8];
	}*/
	   serv_addr.sin_family = AF_INET;
	   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);//  void bcopy(const void *src, void *dest, size_t n);
	   // The bcopy() function copies n bytes from src to dest.  The result correct, even when both areas overlap.
	   serv_addr.sin_port = htons(portno); // given in by user in cmmand line
	   
	     /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) { // if statement wil connect it
      perror("ERROR connecting");
      exit(1);
   }
     /* Now ask for a message from the user, this message
      * will be read by server
   */
	
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   /* Send message to the server */
   n = write(sockfd, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);
   return 0;
}
   
   
    
