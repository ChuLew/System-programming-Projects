#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sorter.h"
#include "mergeSort.c"

int overallcounter = 0;

record* SortedMerge(record *a, record *b, char* column);
void Split(record *source, record **frontRef, record **backRef);
void mergeSort(record **headRef, char* column);
void sorter(FILE* fPointer,char* filename, char* fieldname, char* outputdirectory);

char *strtok_new(char *comma, char *delims)
{
	static char *savecomma = NULL;
	char *p;
	int n;

	if(comma != NULL)				// checks if the input char* is empty or not, if not empty, variable savecomma will get the input char*
	{
		savecomma = comma;
	}
	if(savecomma == NULL || *savecomma == '\0')  //if input char* empty, return value will be NULL since an empty char* is being inputed
	{
		return(NULL);
	}
	n = strcspn(savecomma,delims);   // return the first location where the savecomma and delims are the same
	p = savecomma; 					// once found, assign it to the output variable p
	savecomma += n;					// move the pointer in savecomma by the location found from strcspn

	if(*savecomma != '\0')
	{
		*savecomma++ = '\0';
	}
	return(p);
}
void handleFile(char* filename,char *fieldname,char *outputdirectory)
{
	FILE *fp;
	fp=fopen(filename,"r");
	
	char buff[10000];//trying to determine if the csv file has a proper header line with 28 columns
	fgets(buff,10000,fp);
	int i, count=0; 
	for(i = 0; i < strlen(buff); i++){
		if(buff[i]==','){
		count++;
		}
	}
	if(count!=27){
		printf("Improper heading, file ignored\n");
		return;
	}
	else{
		sorter(fp, filename, fieldname,outputdirectory);	
	}
	return;
}

void handy(char * dname,char *column,char *outputdirectory)
{
	DIR *dp=opendir(dname);  
	DIR *outExist=opendir(outputdirectory);
	if(outExist==NULL){
		if((outputdirectory = "")){
			
		}else{
			printf("The outputdirectory doesnt exist, program terminated\n");
			exit(1);
		}
	}

	struct dirent *entry;  // has two important members (d-type)-tells me if its a directory (d-name) tells me current file name
	if(dp==NULL){
		printf("directory doesnt exist: %s\n", dname);
		return;
	}
		int pidArray[255];
		int count = 0;

		while((entry=readdir(dp))!=NULL){
		if(strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".")==0){
		   continue;
		}
			if((entry->d_type==DT_DIR)){
				
				unsigned int const sz1 = strlen(dname);
				unsigned int const sz2 = strlen(entry->d_name);
			
				char *dnewname=(char *)malloc((sz1+sz2+2)*sizeof(char));
				
				memcpy(dnewname,dname,sz1);
				memcpy(dnewname+sz1,"/",sizeof(char));
				memcpy(dnewname+sz1+1,entry->d_name,sz2);
				//dnewname[strlen(dnewname)]='\0';

				pid_t pid = fork();
				count++;
				if(pid == 0){
					handy(dnewname,column,outputdirectory);
					exit(1);
				}
				if(pid > 0){
					pidArray[count - 1] = pid;
				//	printf("%d, ", pid);
				}
			}
		
		if((entry->d_type==DT_REG)){
			char *filename = entry->d_name;
			int len = strlen(filename);
			const char *last_four = &filename[len-4]; //need to account for if filename is less than 4 characters	
				if(strcmp(last_four,".csv")==0){
						
					 //here is where i call handle file and merge sort
					char *dnewname = (char*)malloc(sizeof(char)*(strlen(dname)+strlen(entry->d_name)+2));
					char *slash = (char*)malloc(sizeof(char));
					strcpy(dnewname, dname);
					strcpy(slash, "/");
					strcat(dnewname, slash);
					strcat(dnewname, entry->d_name);

					pid_t pid2 = fork();
					count++;
					if(pid2 == 0){
						handleFile(dnewname,column,outputdirectory);
						exit(1);
					}
					if(pid2 > 0){
						pidArray[count - 1] = pid2;
				//		printf("%d, ", pid2);
					}
				
				}
		}
	}
		int i, status;
		pid_t w;
		for(i = 0; i < 255; i++){
			w = waitpid(pidArray[i], &status, 0);
		//	printf("%d,", pidArray[i]);
		}
		for(i = 0; i < count; i++){
			printf("%d, ", pidArray[i]);
		}
}
void arghandle(int argc, char* argv[],char **column, char **directory, char **outputdirectory)
{
	if(argc<3)
	{
		printf("not enough input arguments\n");
		exit(1);
	}
	int countc=0;
	int countd=0;
	int counto=0;
	int i;
	for(i=1; i<argc; i++){
		if(strcmp(argv[i],"-c")==0){
			if(i+2>argc){
				printf("no column heading was inputed after -c, arguments are inputted incorrectly, program terminated");
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
				printf("Column heading spelled wrong, program terminated\n");
				exit(1);
			}
			*column = argv[i+1]; 
			countc++;
			if(countc != 1){
				printf("multiple -c inputs, program terminated\n");
				exit(1);
			}
		}
		if(strcmp(argv[i],"-d")==0){
			if(i+2>argc){
				printf("no column heading was inputed after -d, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			*directory=argv[i+1]; 
			countd++;
			}
		if(strcmp(argv[i],"-o")==0){
			if(i+2>argc){
				printf("no column heading was inputed after -o, arguments are inputted incorrectly, program terminated");
				exit(1);
			}
			*outputdirectory= argv[i+1];  
			counto++;
			}
		}
	if(countc<1||countc>1||countd>1||counto>1){
			printf("you have incorrectly formated your input argruments, program terminated\n");
			exit(1);
		}
	}
void sorter(FILE* fPointer,char* filename, char* fieldname,char* outputdirectory)
{	
	char *sortedname;

	if(strcmp(outputdirectory,"")==0){
		unsigned int const sz1 = strlen(filename)-4;
		unsigned int const szsorted = strlen("-sorted-");
		unsigned int const sz2 = strlen(fieldname);
		unsigned int const szcsv= strlen(".csv");

		int size = sz1 + szsorted + sz2 + szcsv;


		sortedname=(char *)malloc((size+1)*sizeof(char));
		memcpy(sortedname,filename,sz1);
		memcpy(sortedname+sz1,"-sorted-",szsorted);
		memcpy(sortedname+sz1+szsorted,fieldname,sz2);
		memcpy(sortedname+sz1+szsorted+sz2,".csv",szcsv);
		sortedname[strlen(sortedname)]='\0';
	}
	else{
		int starting_index, i;
		for(i = 0; i<strlen(filename);i++){
			if(filename[strlen(filename)-i]=='/'){
				starting_index=strlen(filename) - i + 1;
				break;
			}		
		}	
		unsigned int const sz1 = strlen(outputdirectory);
		unsigned int const szsl = strlen("/");
		unsigned int const sz2 = strlen(filename+starting_index)-4;
		unsigned int const szsorted = strlen("-sorted-");
		unsigned int const sz3 = strlen(fieldname);
		unsigned int const szcsv= strlen(".csv");
		
		sortedname=(char*)malloc((sz1+szsl+sz2+szsorted+sz3+szcsv+1)*sizeof(char));
		
		memcpy(sortedname, outputdirectory, sz1);
		memcpy(sortedname+sz1,"/", szsl);
		memcpy(sortedname+sz1+szsl,filename+starting_index,sz2);
		memcpy(sortedname+sz1+szsl+sz2,"-sorted-",szsorted);
		memcpy(sortedname+sz1+szsl+sz2+szsorted,fieldname,sz3);
		memcpy(sortedname+sz1+szsl+sz2+szsorted+sz3,".csv\0",szcsv+1);

		
		
		
	}
	
	
	
	char* ifalreadysorted = (char*)malloc(sizeof(char)*(strlen("-sorted-")+strlen(fieldname)));
	strcpy(ifalreadysorted, "-sorted-");
	strcat(ifalreadysorted, fieldname);

	if(strstr(filename, ifalreadysorted) != NULL){
		return;
	}

	//strcpy(sortedname, strcat(sortednamePart1,sortednamePart2));
	FILE *sorted;
	sorted = fopen(sortedname, "w");

	char buff[10000];
	//fgets(buff,10000,fPointer); //skips first line of csv file
	fgets(buff,10000,fPointer); //takes next line of csv file

	record *pFirstNode;
	record *pCurrent;

	pFirstNode = malloc(sizeof(record)); //allocate memory for the first node of the linked list
	pFirstNode->next = NULL;

	char *token = strtok_new(buff, ","); // from the first line, we assign all the members of the struct their appropriate char*
	pFirstNode->color = strdup(token);

	token = strtok_new(NULL, ","); // since we are still using the same line, we need to input NULL as the char* and do the same to create the first node in the linked list
	pFirstNode->director = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->numCritic = strdup(token);

	token = strtok_new(NULL , ",");
	pFirstNode->duration = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->fbLikes = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->a3L = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->a2n = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->a1L = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->gross = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->genres = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->a1n = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->movietitle = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->numVote = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->castTotal = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->an3 = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->fnInPic = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->plotWord = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->movieLink = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->numUserReview = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->language = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->country = strdup(token);

	token = strtok_new(NULL, ",");
	pFirstNode->rating = strdup(token);

	token=strtok_new(NULL, ",");
	pFirstNode->budget = strdup(token);

	token=strtok_new(NULL, ",");
	pFirstNode->titleYear = strdup(token);

	token=strtok_new(NULL, ",");
	pFirstNode->a2L = strdup(token);	

	token=strtok_new(NULL, ",");
	pFirstNode->imbdScore = strdup(token);

	token=strtok_new(NULL, ",");
	pFirstNode->aspectRatio = strdup(token);

	token=strtok_new(NULL, ",");
	pFirstNode->MoviefbLikes = strdup(token);

	pCurrent = pFirstNode; // the current pointer is assigned to the first node

	while(fgets(buff, 6000, fPointer))  // this while loop loops until is gets to the bottom of the input csv file
	{
		if(pCurrent != NULL) // if there is more than one node in the linked list, we need to get to the last node so we can add the new node
		{
			while(pCurrent->next != NULL)
			{
				pCurrent = pCurrent->next;
			}
		}

		pCurrent->next = malloc(sizeof(record)); // allocate memory for each new struct (new node in linked list)
		pCurrent = pCurrent->next; // this line connects the linked list
		pCurrent->next = NULL; // since this is the last node, the next node will be NULL

		token = strtok_new(buff, ","); // now this assigns the members of struct their appropriate char*
		if(token[0] == ' ')
		{
			token++;
		}
		pCurrent->color = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->director = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->numCritic = strdup(token);

		token = strtok_new(NULL , ",");
		pCurrent->duration = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->fbLikes = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->a3L = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->a2n = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->a1L = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->gross = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->genres = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->a1n = strdup(token);

		token = strtok_new(NULL, ",");
		if (token[0]=='"'){
			token++;
			
			char* comma = (char*)malloc(sizeof(char));
			char* quote = (char*)malloc(sizeof(char));
			strcpy(comma, ",");
			strcpy(quote, "\"");

			char* token1 = strtok_new(NULL, "\"");
			char* temptoken = (char*)malloc(sizeof(char)*(strlen(token)+strlen(token1)+3));

			strcpy(temptoken, token);
			strcat(temptoken, comma);
			strcat(temptoken, token1);
			strcat(temptoken, quote);
			pCurrent->movietitle = strdup(temptoken);
		token = strtok_new(NULL,",");
		}
		else
		{
			pCurrent->movietitle = strdup(token);
		}

		token = strtok_new(NULL, ",");
		pCurrent->numVote = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->castTotal = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->an3 = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->fnInPic = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->plotWord = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->movieLink = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->numUserReview = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->language = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->country = strdup(token);

		token = strtok_new(NULL, ",");
		pCurrent->rating = strdup(token);

		token=strtok_new(NULL, ",");
		pCurrent->budget = strdup(token);

		token=strtok_new(NULL, ",");
		pCurrent->titleYear = strdup(token);

		token=strtok_new(NULL, ",");
		pCurrent->a2L = strdup(token);

		token=strtok_new(NULL, ",");
		pCurrent->imbdScore = strdup(token);

		token=strtok_new(NULL, ",");
		pCurrent->aspectRatio = strdup(token);

		token=strtok_new(NULL, "\0");
		pCurrent->MoviefbLikes = strdup(token);
	}

	pCurrent = pFirstNode; // after the linked list is created, we can move the current pointer to the first node

	//strcpy(column,fieldname);
	if(strcmp(fieldname,"color") != 0 && 
		strcmp(fieldname,"director_name") != 0 &&
		strcmp(fieldname,"num_critic_for_reviews") != 0 &&
		strcmp(fieldname,"duration") != 0 &&
		strcmp(fieldname,"director_facebook_likes") != 0 &&
		strcmp(fieldname,"actor_3_facebook_likes") != 0 &&
		strcmp(fieldname,"actor_2_name") != 0 &&
		strcmp(fieldname,"actor_1_facebook_likes") != 0 &&
		strcmp(fieldname,"gross") != 0 &&
		strcmp(fieldname,"genres") != 0 &&
		strcmp(fieldname,"actor_1_name") != 0 &&
		strcmp(fieldname,"movie_title") != 0 &&
		strcmp(fieldname,"num_voted_users") != 0 &&
		strcmp(fieldname,"cast_total_facebook_likes") != 0 &&
		strcmp(fieldname,"actor_3_name") != 0 &&
		strcmp(fieldname,"facenumber_in_poster") != 0 &&
		strcmp(fieldname,"plot_keywords") != 0 &&
		strcmp(fieldname,"movie_imdb_link") != 0 &&
		strcmp(fieldname,"num_user_for_reviews") != 0 &&
		strcmp(fieldname,"language") != 0 &&
		strcmp(fieldname,"country") != 0 &&
		strcmp(fieldname,"content_rating") != 0 &&
		strcmp(fieldname,"budget") != 0 &&
		strcmp(fieldname,"title_year") != 0 &&
		strcmp(fieldname,"actor_2_facebook_likes") != 0 &&
		strcmp(fieldname,"imdb_score") != 0 &&
		strcmp(fieldname,"aspect_ratio") != 0 &&
		strcmp(fieldname,"movie_facebook_likes") != 0)
	{
		printf("%s\n", "Not a valid input");
		return;
	}

	mergeSort(&pCurrent, fieldname);  // applies the Merge Sort on the linked list

	fprintf(sorted, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
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
			"movie_facebook_likes"); // prints out the first line of the output csv with all the column heading
			
	 
	while(pCurrent != NULL)
	{
		fprintf(sorted, "%s,", pCurrent->color);
		fprintf(sorted, "%s,", pCurrent->director);
		fprintf(sorted, "%s,", pCurrent->numCritic);
		fprintf(sorted, "%s,", pCurrent->duration);
		fprintf(sorted, "%s,", pCurrent->fbLikes);
		fprintf(sorted, "%s,", pCurrent->a3L);
		fprintf(sorted, "%s,", pCurrent->a2n);
		fprintf(sorted, "%s,", pCurrent->a1L);
		fprintf(sorted, "%s,", pCurrent->gross);
		fprintf(sorted, "%s,", pCurrent->genres);
		fprintf(sorted, "%s,", pCurrent->a1n);

			char* title = (char*)malloc(sizeof(char)*500);
			strcpy(title, pCurrent->movietitle);
			char* quote = (char*)malloc(sizeof(char)*500);
			strcpy(quote, "\"");
			int i;
			for(i = 0; i < strlen(title); i++)
			{
				if(title[i] == ',')
				{
					strcat(quote, title);
					pCurrent->movietitle = strdup(quote);
					break;
				}
			}
		fprintf(sorted, "%s,", pCurrent->movietitle);
		fprintf(sorted, "%s,", pCurrent->numVote);
		fprintf(sorted, "%s,", pCurrent->castTotal);
		fprintf(sorted, "%s,", pCurrent->an3);
		fprintf(sorted, "%s,", pCurrent->fnInPic);
		fprintf(sorted, "%s,", pCurrent->plotWord);
		fprintf(sorted, "%s,", pCurrent->movieLink);
		fprintf(sorted, "%s,", pCurrent->numUserReview);
		fprintf(sorted, "%s,", pCurrent->language);
		fprintf(sorted, "%s,", pCurrent->country);
		fprintf(sorted, "%s,", pCurrent->rating);
		fprintf(sorted, "%s,", pCurrent->budget);
		fprintf(sorted, "%s,", pCurrent->titleYear);
		fprintf(sorted, "%s,", pCurrent->a2L);
		fprintf(sorted, "%s,", pCurrent->imbdScore);
		fprintf(sorted, "%s,", pCurrent->aspectRatio);
		fprintf(sorted, "%s",pCurrent->MoviefbLikes);

		pCurrent = pCurrent->next;
	}
		fclose(sorted);
}

int numberOfProcesses(char* directory){
	DIR *dp = opendir(directory);

	struct dirent *entry;
	if(dp == NULL){
		printf("Directory does not exist: %s\n", directory);
		return 0;
	}
	
	while((entry = readdir(dp)) != NULL){
	
		if(strcmp(entry->d_name,"..") == 0 || strcmp(entry->d_name,".") == 0){
			continue;
		}
	
		if((entry->d_type == DT_DIR)){
			int count = 0;
			unsigned int const sz1 = strlen(directory);
			unsigned int const sz2 = strlen(entry->d_name);
			
			char *dnewname=(char *)malloc((sz1+sz2+2)*sizeof(char));
			
			memcpy(dnewname,directory,sz1);
			memcpy(dnewname+sz1,"/",sizeof(char));				
			memcpy(dnewname+sz1+1,entry->d_name,sz2);
			count++;
			overallcounter += count;
			numberOfProcesses(dnewname);
		}

		if(entry->d_type == DT_REG){
			char *filename = entry->d_name;
			int len = strlen(filename);
			const char *last_four = &filename[len-4];	
			if(strcmp(last_four,".csv")==0){
				overallcounter++;
			}
		}
	}
	return overallcounter;
}

int main(int argc, char *argv[]){
	// I want to initialize the values of directory and outputdirectory to current director initially
	char* column;
	char* directory= ".";
	char* outputdirectory="";
	
	printf("Inital PID: %d\n", getpid());
	
	printf("PIDs of all child processes: ");
	fflush(stdout);
	
	arghandle(argc,argv,&column,&directory,&outputdirectory);
	int total_number_of_processes = numberOfProcesses(directory);
	
	handy(directory,column,outputdirectory);

	printf("\nTotal number of processes: %d\n", total_number_of_processes);

	return 0;
}
