#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "sorter_server.h"
#include <pthread.h>
#include <unistd.h>
#include "mergeSort.c"
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *conhandle(void*sockfd);
void addelement(int count,char * buff, record* library);
char *strtok_new(char *c, char *d);
void addGlobal(record* internet, int hi);
void printGlobal(int hi);
globalNode* head;
globalNode* pointer;
char * col;
int sum = 0;

int main( int argc, char* argv[]) 
{
  int sockfd,portno=0,clilen,optval=1;

        int f = 0 ;
        while(f < argc-1){
          if(strcmp(argv[f],"-p")==0){
            portno = atoi(argv[f+1]);
          }
          if(f+2>argc){
            ////printf("no column heading was inputed after -p, arguments are inputted incorrectly, program terminated");
            exit(1);
          }
        f++;
        }
//hoprintf("portno %d\n",portno);
//char buffer[1000];
struct sockaddr_in serv_addr, cli_addr; //  sockaddr is a struct generic container that just allows os to read the first couple bytes that identify the adress family
  //address family detrmines what variant of the sockaddr struct to use that contains elements that make sense for that specific ommunication type
  // for ip newtowrking , we use struct sockaddr_in which has 
  /*struct sockaddr_in {
    _uint8_t sin_len;
    sa_family_t sin_family; //sin_family the adress family we use to set up socket in our case its AF_INET
    in_port_t sin_port;// sin_port is the portnumber 
    struct in_addr sin_addr;//sin_addr is adress for socket ( this is your machines ip adress) you can you INADDR_ANY to access this adress 
  char  sin_zero[8];
  }*/
//int k;
//for(k=0;k<10;k++){
//int*newspace=(int*)malloc(sizeof(int));
//memcpy(newspace,"hey",strlen("hey")+1);
//////printf("%s\n",newspace);
//////printf("%p\n",(void*)&newspace);
//}
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
//////printf("wKILL %d\n",KILL);

listen(sockfd,100);
clilen=sizeof(cli_addr);//size of client
pthread_t thread_id;
/* accept actual connection from the client*/
int newsockfd;
int *newspace=(int*)malloc(sizeof(int));
newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);

  socklen_t len;
  struct sockaddr_storage addr;
  char ipstr[INET6_ADDRSTRLEN];
  //int port;

  len = sizeof(addr);
  getpeername(newsockfd, (struct sockaddr*)&addr, &len);

  if(addr.ss_family == AF_INET){
    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    //port = ntohs(s->sin_port);
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
  }else{
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
    //port = ntohs(s->sin6_port);
    inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
  }

  printf("Received connections from: %s\n", ipstr);

*newspace=newsockfd;


//serv_addr.sin_family=AF_INET;//sin family is the adress family we use wehn we set up socket 
//serv_addr.sin_addr.s_addr=INADDR_ANY;//the adress of this socket, this is your machines ip adress. INADDR_ANY  or 0.0.0.0 is is your machines ip adress 0.0.0.00 allows any connection on any ip so to restrict use inet_addr("127.0.0.1")
////htonl(INADDR_LOOPBACK)//restricts ip to hostnetwork
//serv_addr.sin_port=htons(portno);// the port number (the transport adress) hosttonewtowrk (htons) a random portnumber would be htons(0)


////printf("address newsockfd: %p \n",newspace);
////printf("newsockfd: %d \n",newsockfd);

if(pthread_create(&thread_id,NULL,conhandle,(void*)newspace)<0)
{
  perror("could not create thread");
}
//////printf("afteconhandle\n");
//////printf("connection accepted\n");

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

////printf("here is the messsage: %s\n",buffer);
// write a response to a client  
n=write(newsockfd,"Message received!", 18);

if(n<0)
{
  perror("error reading form scoket");
  exit(1);

}*/

}
pthread_mutex_destroy(&mutex);
pthread_mutex_destroy(&mutex1);

////printf("server shutdown\n");
return 0;
}
void *conhandle(void*sockfd){ 

////printf("socket id %d\n",*((int*)sockfd));
  ////printf("connection accepted\n");

  int n;
  int sock = *(int*)sockfd;
  char buffer[1000];
bzero(buffer,1000); 

n = read( sock, buffer, 1000);
////printf("first read %s\n", buffer);

if(strcmp(buffer,"kill myself")==0){
bzero(buffer,1000);
////printf("destroy evidence\n");
////printf("destroy evidence\n");

record* final  = (record*)malloc(sizeof(record) * sum);

pointer=head;
int counter=0;
    
    ////printf("killer\n");
        while(pointer !=NULL){
            int k= pointer->size;
            ////printf("k %d\n",k);
            int i=0;
            while(i<k-1){
              final[counter] = pointer->library[i];

              counter++;
              i++;
            }
        pointer = pointer->next;
        }
           
pointer=head;
//////printf("final %s\n",final[9].movietitle);
int lo=0;
//////printf("sum %d\n",sum);
//printf("This is before mergeSort for final\n");

//printf("%d\n", sizeof(final));

mergeSort(final,col,lo,sum-1);
n=0;
sprintf(buffer,"next");
n = write( sock, buffer, 1000);
////printf("\n %d \n",n);
bzero(buffer,1000);
n=0;
n=read( sock, buffer, 1000);
while(1){
if(strcmp(buffer,"ready to receive")==0){
  break;
}
}
////printf("%s\n",buffer);
bzero(buffer,1000);



int tmep = 0;
 while(1){
 //FILL BUFFER
 if(tmep!=sum){
 
 sprintf(buffer,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
            final[tmep].color,
            final[tmep].director,  
            final[tmep].numCritic,
            final[tmep].duration,
            final[tmep].fbLikes,
            final[tmep].a3L,
            final[tmep].a2n,
            final[tmep].a1L,
            final[tmep].gross,
            final[tmep].genres,
            final[tmep].a1n,
            final[tmep].movietitle,
            final[tmep].numVote,
            final[tmep].castTotal,
            final[tmep].an3,
            final[tmep].fnInPic,
            final[tmep].plotWord,
            final[tmep].movieLink,
            final[tmep].numUserReview,
            final[tmep].language,
            final[tmep].country,
            final[tmep].rating,
            final[tmep].budget,
            final[tmep].titleYear,
            final[tmep].a2L,
            final[tmep].imdbScore,
            final[tmep].aspectRatio,
            final[tmep].MoviefbLikes);
            
            char * ret;
         ret=strchr(buffer,'\n');
         if(ret==NULL){
        sprintf(buffer,"%s\n",buffer);
        }
 }
 else{
 sprintf(buffer,"*");
 //break;
 }
 
 
 
 
 n=0;
 
 
 //
 //////printf("client buffer %s\n",buffer);
 while(n<1000){
   n += write(sock, buffer, 1000);
 }
 
   //////printf("b: %s\nn: %d\n",buffer);
   if(strcmp(buffer,"*")==0){
   //////printf("breaking\n");
   free(final);
   pointer=head;
   //int co=0;
   sum=0;
while(pointer!=NULL)
{  
  //////printf("\n%d\n",co);
  //pthread_join(ptr->peerTid,NULL);
  head=pointer->next;
 //////printf("\n%s\n",pointer->library[1].movietitle);
  free(pointer);
 //////printf("\n%s\n",pointer->library[1].movietitle);
  pointer=head;
 //co++;
}

   close(sock);
    return;
      //break;
    }
     //////printf("Stop\n");
   //////printf("Please enter the message: ");
  // sprintf(buffer,"File Send");
  
  //////printf("client buffer %s\n",buffer);
  n=0;
  bzero(buffer,1000);
  //////printf("Please enter the message: ");
    
   
  while(n<1000){
n += read( sock, buffer, 1000);
  //////printf("b: %s\nn: %d\n",buffer);
  //////printf("1wait\n");
    if(strcmp(buffer, "next")==0){
      break;
    }
  }
   //////printf("sb: %s\nn: %d\n",buffer,n);
   n=0;
  bzero(buffer,1000);
  //
  
  
tmep++;
}
//////printf("here");


//// I want to free global linked list here
//pointer=head;
//while(pointer!=NULL)
//{
//  //pthread_join(pointer->peerTid,NULL);
//  pointer=head;
//  head=pointer->next;
//  free(pointer);
//  
//}


////


}

char *token = strtok_new(buffer, ",");
int hi = atoi(strdup(token));
token = strtok_new(NULL, ",");
col = strdup(token); 
////printf("HIGHR %d, COLUMN %s\n",hi,col);
sum=sum+hi-1;
bzero(buffer,1000);





sprintf(buffer,"next");
n = write( sock, buffer, 1000);
bzero(buffer,1000);

record* library   = (record*)malloc(sizeof(record) * hi);
int count=0;


while(1){
read( sock, buffer, 1000);//read
//////printf("\n ELEMENT: %s\n",buffer);
if(strcmp(buffer,"")==0){
  break;
}
  /* if connection is accepted than start communicating */

//printf("server buffer %s\n",buffer);

addelement(count,buffer,library);

//printf("After addelement\n");
//////printf("test %s\n", library[count].numCritic);
count++;
bzero(buffer,1000);
sprintf(buffer,"next");
////printf("server buffer should be sending:%s\n",buffer);
n = write( sock, buffer, 1000);//write
////printf("return value of next write statement:%d\n",n);
////printf("%s\n",buffer);
bzero(buffer,1000);
}


int lo = 0;
//printf("before mergeSort\n");
//mergeSort(library, col, lo, hi-2);
////printf("beforeaddglobal\n");


addGlobal(library,hi);


////printf("beforeprintglobal\n");
printGlobal(hi);
//bzero(buffer, 1000);  
////printf("afterprintglobal\n");
//free(library);
//here is where i want to put the csv file into global
//int g=0;
//        while(g<(hi-1)){
//          ////printf("sorted %s\n", library[g].numCritic);
//          g++;
//        } 
//sort structure and put into global memory

close(sock);
}
void addelement(int count,char * buff, record* library){

      //pthread_mutex_lock(&mutex);
      //printf("Start of addelement\n");

        record curr;
        char *token = strtok_new(buff, ",");
      
          if(token[0] == ' ')
          {
            token++;
          }
          //////printf("%s", curr.director);
        curr.color = strdup(token);
      
        token = strtok_new(NULL, ","); 
        curr.director = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.numCritic = strdup(token);
      
        token = strtok_new(NULL , ",");
        curr.duration = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.fbLikes = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.a3L = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.a2n = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.a1L = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.gross = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.genres = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.a1n = strdup(token);
      
        token = strtok_new(NULL, ",");
          if (token[0]=='"'){
            strcat(token,strtok_new(NULL, "\""));
            token++;
            curr.movietitle = strdup(token);
            strtok_new(NULL, ",");
          }
          else
          {
            curr.movietitle = strdup(token);
          }
      
        token = strtok_new(NULL, ",");
        curr.numVote = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.castTotal = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.an3 = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.fnInPic = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.plotWord = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.movieLink = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.numUserReview = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.language = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.country = strdup(token);
      
        token = strtok_new(NULL, ",");
        curr.rating = strdup(token);
      
        token=strtok_new(NULL, ",");
        curr.budget = strdup(token);
      
        token=strtok_new(NULL, ",");
        curr.titleYear = strdup(token);
      
        token=strtok_new(NULL, ",");
        curr.a2L = strdup(token); 
      
        token=strtok_new(NULL, ",");
        curr.imdbScore = strdup(token);
      
        token=strtok_new(NULL, ",");
        curr.aspectRatio = strdup(token);
      
        token=strtok_new(NULL, ",");
        curr.MoviefbLikes = strdup(token);
          
        library[count]=curr;
        //////printf("%s \n",records[a].movietitle);

    
//int lo = 0;
    
          
       //////printf("TEST %s,%d,%d\n",col,lo,hi);
     //mergeSort(library, col, lo, hi-2);
       
//      ////printf("TEST\n");
//      int k=0;
//        while(k<(hi-1)){
//          ////printf("test %s\n", records[k].numCritic);
//          k++;
//        } 
     //pthread_mutex_lock(&mutex);
     //addgarr(records, hi-1);
     //pthread_mutex_unlock(&mutex);
        
         //add function
         //////printf("TEST\n");
        //free(records);
       
       //fcounter++;
        //pthread_mutex_unlock(&mutex);
      }

char *strtok_new(char *c, char *d) 
      {
        static char *sc = NULL;
        char *p;
        int n;
      
        if(c != NULL){
          sc = c;
        }
        if(sc == NULL || *sc == '\0')  {
          return(NULL);
        }
        n = strcspn(sc,d);   
        p = sc;           
        sc += n;          
      
        if(*sc != '\0'){
          *sc++ = '\0';
        }
        return(p);
      }
      void addGlobal(record* internet,int hi){
      pthread_mutex_lock(&mutex1);
          if(head==NULL){
            globalNode *newNode= (globalNode*)malloc(sizeof(internet)+sizeof(globalNode));
            newNode->next=NULL;
          
            head = newNode;
            head->library=internet;
            head->size=hi;
            pointer = head;
          }
          else{
            while(pointer->next!=NULL){
              pointer=pointer->next;
            }
            
            pointer->next = (globalNode*)malloc(sizeof(internet)+sizeof(globalNode));
            pointer = pointer->next;
            pointer->next = NULL;
            pointer->library=internet;
            pointer->size=hi;
          }
          ////printf("end add global\n");
          pthread_mutex_unlock(&mutex1);
      }
      void printGlobal(int hi){
      pointer=head;
      //////printf("level 1\n");
      int j= 0;
        while(pointer !=NULL){
        ////printf("loop %d\n",j);
        int k=0;
            while(k<hi-1){
            ////printf("level 3\n");
              ////printf("globalprint %d %s\n",k,pointer->library[k].movietitle);
              k++;
            }
          pointer = pointer->next;
          j++;
          }
          pointer=head;
      }