#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "sorter_client.h"
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mergeSort.c"
void *handy(void *arguments);
void arghandle(int argc, char* argv[],char **column, char **directory, char **outputdirectory, char **hostname, char **portnumber);
void *searchRequest(void *arguments);
char *strtok_new(char *c, char *d); 
void *dumpRequest(void *arguments);
 
int main( int argc, char* argv[]){
	char* column;
	char* directory= ".";
	char* outputdirectory=".";
	char* hostname;
	char* portnumber;
	
	arghandle(argc,argv,&column,&directory,&outputdirectory,&hostname,&portnumber);
	handarg *arguments;
	arguments = malloc(sizeof(handarg));
	arguments->directory=directory;
	arguments->column=column;
	arguments->outputdirectory=outputdirectory;
	arguments->hostname=hostname;
	arguments->portnumber=portnumber;
 	handy(arguments);
  //dump request
  dumpRequest(arguments);
}
void *dumpRequest(void *arguments){
  
  handarg *cow=(handarg*)arguments;
  int sockfd, portno , n;
	struct sockaddr_in serv_addr;
	struct hostent * server;

	portno = atoi(cow->portnumber);
	char buffer[1000];
	
	
	 /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
     server = gethostbyname(cow->hostname); // gethostbyname accepts a host name as a parameter and returns a hostent structure;
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
  // printf("end of dump request\n");
   sprintf(buffer,"kill myself");
   n = write(sockfd, buffer, strlen(buffer));
   //n=0;
   bzero(buffer,1000);
   
    n = read( sockfd, buffer, 1000);
  while(1){
  //printf("bwait\n");
    if(strcmp(buffer, "next")==0){
      break;
    }
  }
//while(n<1000){
//n+=read( sockfd, buffer, 1000);
//printf("bwait\n");
//    if(strcmp(buffer, "next")==0){
//      break;
//    }
//}
//n=0;
  sprintf(buffer,"ready to receive");
   n = write(sockfd, buffer, strlen(buffer));
   //n=0;
   bzero(buffer,1000);
   
   //while
   //read wait
   //
 char entry[300];
      
      snprintf(entry,300,"AllFiles-sorted-%s.csv", cow->column);
      //getcwd(name,sizeof(name));
      //printf("name %s\n%s",name);
      //printf("entry %s\n%s",entry);
      chdir(cow->outputdirectory);
      freopen(entry, "w", stdout);
      printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
      			"color",
      			"director_name",
      			"num_critic_for_reviews",
      			"duration",
      			"director_facebook_likes",
      			"actor_3_facebook_likes",
      			"actor_2_name",
      			"actor_1_facebook_likes",
      			"gross",
      			"genres",
      			"actor_1_name",
      			"movie_title",
      			"num_voted_users",
      			"cast_total_facebook_likes",
      			"actor_3_name",
      			"facenumber_in_poster",
      			"plot_keywords",
      			"movie_imdb_link",
      			"num_user_for_reviews",
      			"language",
      			"country",
      			"content_rating",
            "budget",
      			"title_year",
      			"actor_2_facebook_likes",
      			"imdb_score",
      			"aspect_ratio",
      			"movie_facebook_likes");   
while(1){
//
n=0;
while(n<1000){
n+=read( sockfd, buffer, 1000);
}
//printf("cb: %s\nn: %d\n",buffer,n);
if(strcmp(buffer,"*")==0){
//printf("breaking\n");
  break;
}
//printf("server buffer %s\n",buffer);
printf("%s",buffer);
//printf("Stop\n");
//DO SOME WORK
n=0;
bzero(buffer,1000);
sprintf(buffer,"next");
//printf("%s",buffer);

  while(n<1000){
  n += write( sockfd, buffer, 1000);
    //printf("next write %s\n ret value: %d\n",buffer, n);

  }
  n=0;
bzero(buffer,1000);
//
}
   fclose(stdout);
   
   
  close(sockfd);
}
void arghandle(int argc, char* argv[],char **column, char **directory, char **outputdirectory, char **hostname, char **portnumber){
	if(argc<7)
	{
		//printf("not enough input arguments\n");
		exit(1);
	}
	int countc=0;
	int countd=0;
	int counto=0;
  int counth=0;
  int countp=0;
	int i;
	for(i=1; i<argc; i++){
		if(strcmp(argv[i],"-c")==0){
			if(i+2>argc){
				//printf("no column heading was inputed after -c, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			if(strcmp(argv[i+1],"color") != 0 && 
				strcmp(argv[i+1],"director_name") != 0 &&
				strcmp(argv[i+1],"num_critic_for_reviews") != 0 &&
				strcmp(argv[i+1],"duration") != 0 &&
				strcmp(argv[i+1],"director_facebook_likes") != 0 &&
				strcmp(argv[i+1],"actor_3_facebook_likes") != 0 &&
				strcmp(argv[i+1],"actor_2_name") != 0 &&
				strcmp(argv[i+1],"actor_1_facebook_likes") != 0 &&
				strcmp(argv[i+1],"gross") != 0 &&
				strcmp(argv[i+1],"genres") != 0 &&
				strcmp(argv[i+1],"actor_1_name") != 0 &&
				strcmp(argv[i+1],"movie_title") != 0 &&
				strcmp(argv[i+1],"num_voted_users") != 0 &&
				strcmp(argv[i+1],"cast_total_facebook_likes") != 0 &&
				strcmp(argv[i+1],"actor_3_name") != 0 &&
				strcmp(argv[i+1],"facenumber_in_poster") != 0 &&
				strcmp(argv[i+1],"plot_keywords") != 0 &&
				strcmp(argv[i+1],"movie_imdb_link") != 0 &&
				strcmp(argv[i+1],"num_user_for_reviews") != 0 &&
				strcmp(argv[i+1],"language") != 0 &&
				strcmp(argv[i+1],"country") != 0 &&
				strcmp(argv[i+1],"content_rating") != 0 &&
				strcmp(argv[i+1],"budget") != 0 &&
				strcmp(argv[i+1],"title_year") != 0 &&
				strcmp(argv[i+1],"actor_2_facebook_likes") != 0 &&
				strcmp(argv[i+1],"imdb_score") != 0 &&
				strcmp(argv[i+1],"aspect_ratio") != 0 &&
				strcmp(argv[i+1],"movie_facebook_likes") != 0)
			{
				//printf("Column heading spelled wrong, program terminated\n");
				exit(1);
			}
			*column = argv[i+1]; 
			countc++;
			if(countc != 1){
				//printf("multiple -c inputs, program terminated\n");
				exit(1);
			}
		}
		if(strcmp(argv[i],"-d")==0){
			if(i+2>argc){
				//printf("no column heading was inputed after -d, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			*directory=argv[i+1]; 
			countd++;
			}
		if(strcmp(argv[i],"-o")==0){
			if(i+2>argc){
				//printf("no column heading was inputed after -o, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			*outputdirectory= argv[i+1];  
			counto++;
			}
      if(strcmp(argv[i],"-h")==0){
			if(i+2>argc){
				//printf("no column heading was inputed after -h, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			*hostname=argv[i+1]; 
			counth++;
			}
      if(strcmp(argv[i],"-p")==0){
			if(i+2>argc){
				//printf("no column heading was inputed after -p, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
      
			*portnumber=argv[i+1]; 
			countp++;
			}
		}
   
	if(countc<1||countc>1||countd>1||counto>1||counth>1||countp>1){
			//printf("you have incorrectly formated your input argruments, program terminated\n");
			exit(1);
		}
	}
 void *handy(void *arguments)
{	
  handarg *thestruct=(handarg*)arguments; 
	static pthread_t threadA;
	threadA=pthread_self();
	DIR *dp=opendir(thestruct->directory);  
	DIR *outExist=opendir(thestruct->outputdirectory);
	if(outExist==NULL){
		if((thestruct->outputdirectory = "")){
			
		}else{
			//printf("The outputdirectory doesnt exist, program terminated\n");
			exit(1);
		}
	}

	struct dirent *entry;  // has two important members (d-type)-tells me if its a directory (d-name) tells me current file name
	if(dp==NULL){
		//printf("directory doesnt exist: %s\n", thestruct->directory);
		exit(1);
	}
		NODE *head=(NODE*)malloc(sizeof(NODE)); //linked list
		NODE *ptr=(NODE*)malloc(sizeof(NODE));//node POINTER
		head=NULL;
		//int count = 0;

		while((entry=readdir(dp))!=NULL){
		if(strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".")==0){
		   continue;
		}
			if((entry->d_type==DT_DIR)){
				
				unsigned int const sz1 = strlen(thestruct->directory);
				unsigned int const sz2 = strlen(entry->d_name);
			
				char *dnewname=(char *)malloc((sz1+sz2+2)*sizeof(char));
				
				memcpy(dnewname,thestruct->directory,sz1);
				memcpy(dnewname+sz1,"/",sizeof(char));
				memcpy(dnewname+sz1+1,entry->d_name,sz2);
				dnewname[strlen(dnewname)]='\0';

			
				pthread_t tid;
				handarg *current=(handarg*)malloc(sizeof(handarg));//malloc
				current->directory=dnewname;
				current->outputdirectory=thestruct->outputdirectory;
				current->column=thestruct->column;
				current->portnumber=thestruct->portnumber;
				current->hostname=thestruct->hostname;
				pthread_create(&tid,NULL,&handy,current);
				static pthread_t threadA;
				threadA=pthread_self();
				NODE *newNode=(NODE*)malloc(sizeof(NODE));
					newNode->peerTid=tid;
					if(head==NULL)
					{
						head=newNode;
						ptr=newNode;
					}
					else
					{
						ptr->next=newNode;
						ptr=newNode;
						
					}
		
			}
		
		if((entry->d_type==DT_REG)){
			char *filename = entry->d_name;
			int len = strlen(filename);
			const char *last_four = &filename[len-4]; //need to account for if filename is less than 4 characters	
				if(strcmp(last_four,".csv")==0){
						
					 //here is where i call handle file and merge sort
					char *dnewname = (char*)malloc(sizeof(char)*(strlen(thestruct->directory)+strlen(entry->d_name)+2));
					char *slash = (char*)malloc(sizeof(char));
					strcpy(dnewname, thestruct->directory);
					strcpy(slash, "/");
					strcat(dnewname, slash);
					strcat(dnewname, entry->d_name);
					pthread_t tid;

					char* ifalreadysorted = (char*)malloc(sizeof(char)*(strlen("-sorted-")+strlen(thestruct->column)));
					strcpy(ifalreadysorted, "-sorted-");
					strcat(ifalreadysorted, thestruct->column);

					if(strstr(dnewname, ifalreadysorted) != NULL){
						
					}else{

					handarg *current=(handarg*)malloc(sizeof(handarg));
					current->directory=dnewname;
					current->outputdirectory=thestruct->outputdirectory;
					current->column=thestruct->column;
					current->portnumber=thestruct->portnumber;
					current->hostname=thestruct->hostname;
					pthread_create(&tid,NULL,&searchRequest,current);
					threadA=pthread_self();
					//printf("The Filepath is: %s, The Parent TID = %ld, THE peer TID = %ld\n",dnewname, threadA, tid);
					NODE *newNode=(NODE*)malloc(sizeof(NODE));
					newNode->peerTid=tid;
					if(head==NULL)
					{
						head=newNode;
						ptr=newNode;
					}
					else
					{
						ptr->next=newNode;
						ptr=newNode;
						
					}
					}
					}
			
				
				}
		}
		
			ptr = head;
			while(ptr!=NULL)
			{
				pthread_join(ptr->peerTid,NULL);
				//printf("%ld,",ptr->peerTid);
				ptr=ptr->next;
				//overallcounter++;
			}
		
		
}
void *searchRequest(void *arguments){

	handarg *cow=(handarg*)arguments;
  int sockfd, portno , n;
	struct sockaddr_in serv_addr;
	struct hostent * server;

	portno = atoi(cow->portnumber);
	char buffer[1000];
	
	
	 /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
     server = gethostbyname(cow->hostname); // gethostbyname accepts a host name as a parameter and returns a hostent structure;
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
   int hi=0;
   int size;
   FILE * fc;
   FILE * fp;
   FILE * fe;
   fe = fopen(cow->directory,"r");
   fc = fopen(cow->directory,"r");
   fp = fopen(cow->directory,"r");
         //printf("TEST\n");
        if (NULL != fe) {
          fseek (fe, 0, SEEK_END);
          size = ftell(fe);
        
          if (0 == size) {
              //printf("file is empty\n");
              return;
          }
        }
   fclose(fe);
   
   
   bzero(buffer,1000);
   
   record first;
  	 while(NULL != fgets(buffer,1000,fc)){
    if(hi==0){
    char *token = strtok_new(buffer, ",");
        
      		if(token[0] == ' ')
      		{
      			token++;
      		}
      		
      	first.color = strdup(token);
      
      	token = strtok_new(NULL, ","); 
      	first.director = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.numCritic = strdup(token);
      
      	token = strtok_new(NULL , ",");
      	first.duration = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.fbLikes = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.a3L = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.a2n = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.a1L = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.gross = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.genres = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.a1n = strdup(token);
      
      	token = strtok_new(NULL, ",");
      		if (token[0]=='"'){
      			strcat(token,strtok_new(NULL, "\""));
      			token++;
      			first.movietitle = strdup(token);
      			strtok_new(NULL, ",");
      		}
      		else
      		{
      			first.movietitle = strdup(token);
      		}
      
      	token = strtok_new(NULL, ",");
      	first.numVote = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.castTotal = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.an3 = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.fnInPic = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.plotWord = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.movieLink = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.numUserReview = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.language = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.country = strdup(token);
      
      	token = strtok_new(NULL, ",");
      	first.rating = strdup(token);
      
      	token=strtok_new(NULL, ",");
      	first.budget = strdup(token);
      
      	token=strtok_new(NULL, ",");
      	first.titleYear = strdup(token);
      
      	token=strtok_new(NULL, ",");
      	first.a2L = strdup(token);	
      
      	token=strtok_new(NULL, ",");
      	first.imdbScore = strdup(token);
      
      	token=strtok_new(NULL, ",");
      	first.aspectRatio = strdup(token);
      
      	token=strtok_new(NULL, ",");
      	first.MoviefbLikes = strdup(token);
      	
      	}
      	 
      	if( strcmp(first.color,"color") != 0 && 
      		strcmp(first.director,"director_name") != 0 &&
      		strcmp(first.numCritic,"num_critic_for_reviews") != 0 &&
      		strcmp(first.duration,"duration") != 0 &&
      		strcmp(first.fbLikes,"director_facebook_likes") != 0 &&
      		strcmp(first.a3L,"actor_3_facebook_likes") != 0 &&
      		strcmp(first.a2n,"actor_2_name") != 0 &&
      		strcmp(first.a1L,"actor_1_facebook_likes") != 0 &&
      		strcmp(first.gross,"gross") != 0 &&
      		strcmp(first.genres,"genres") != 0 &&
      		strcmp(first.a1n,"actor_1_name") != 0 &&
      		strcmp(first.movietitle,"movie_title") != 0 &&
      		strcmp(first.numVote,"num_voted_users") != 0 &&
      		strcmp(first.castTotal,"cast_total_facebook_likes") != 0 &&
      		strcmp(first.an3,"actor_3_name") != 0 &&
      		strcmp(first.fnInPic,"facenumber_in_poster") != 0 &&
      		strcmp(first.plotWord,"plot_keywords") != 0 &&
      		strcmp(first.movieLink,"movie_imdb_link") != 0 &&
      		strcmp(first.numUserReview,"num_user_for_reviews") != 0 &&
      		strcmp(first.language,"language") != 0 &&
      		strcmp(first.country,"country") != 0 &&
      		strcmp(first.rating,"content_rating") != 0 &&
      		strcmp(first.budget,"budget") != 0 &&
      		strcmp(first.titleYear,"title_year") != 0 &&
      		strcmp(first.a2L,"actor_2_facebook_likes") != 0 &&
      		strcmp(first.imdbScore,"imdb_score") != 0 &&
      		strcmp(first.aspectRatio,"aspect_ratio") != 0 &&
      		strcmp(first.MoviefbLikes,"movie_facebook_likes") != 0)
      	{//do nothing
      //printf("Invalid csv\n");
      		return;
      	}
       
      	hi++;
    }
  fclose(fc); 
 // printf("%d,%s\n",hi,cow->column);     	
  sprintf(buffer,"%d,%s",hi,cow->column);
  n = write(sockfd, buffer, strlen(buffer));
  bzero(buffer,1000);
 //printf("TEST %s\n",buffer);
 
 
  n = read( sockfd, buffer, 1000);
  //printf("first readback %s\n",buffer);
  while(1){
  //printf("First Read Wait\n");
    if(strcmp(buffer, "next")==0){
      break;
    }
  }
  //printf("passed first read stage\n");
 fgets(buffer,1000, fp); //skip first line
 bzero(buffer,1000);
 
 
 
 
 
 
 while(1){
 fgets(buffer,1000, fp);
   n = write(sockfd, buffer, strlen(buffer));//write
   if(strcmp(buffer,"")==0){
      break;
    }
   //printf("Please enter the message: ");
  // sprintf(buffer,"File Send");
  
  //printf("client buffer %s\n",buffer);
 // printf("client buffer before clear: %s\n",buffer);
  bzero(buffer,1000);
  //printf("client buffer should be next: %s\n",buffer);
  //printf("return value of next read statement:%d\n",n);
int bytesRead=0;
while(bytesRead<1000){
bytesRead+=read(sockfd,buffer,1000); //read
if(strcmp(buffer, "next")==0){
      break;
    }
} 
//printf("kamakazi: %s\n",buffer);
  bzero(buffer,1000);
}








sprintf(buffer,"%d",hi);
//printf("%s\n",buffer);
fclose(fp);
 close(sockfd);
 //close connection

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