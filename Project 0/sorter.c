#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorter.h"
#include "mergeSort.c"

record* SortedMerge(record *a, record *b, char* column);
void Split(record *source, record **frontRef, record **backRef);
void mergeSort(record **headRef, char* column);

char *strtok_new(char *comma, char *delims) // This method builds off the strtok() method, where it takes in a char* and outputs a char* before the first delimiter.
											// Since strtok does not account for the delimiters being consecutive, this method will take care of that and assign NULL to the field between the two delimiter.
											// EX) say the input string is "ab,c,,de" -> the 1st field will get "ab", the 2nd field will get "c", the 3rd field will get NULL, and the 4th field will get "de"

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

 int main(int argc, char* argv[]){

 	if(argc != 3){ 
		printf("Only 3 arguments should be inputed into command prompt");
		return 0;  // must have 3 arguments
	}

	char buff[10000];
	fgets(buff,10000,stdin); //skips first line of csv file
	fgets(buff,10000,stdin); //takes next line of stdin(csv file)

	record *pFirstNode;
	record *pCurrent;

	pFirstNode = malloc(sizeof(record)); //allocate memory for the first node of the linked list
	pFirstNode->next = NULL;

	char *token = strtok_new(buff, ","); // from the first line, we assign all the members of the struct their appropriate char*
	if(token[0] == ' ')
		{
			token++;
		}
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
	if (token[0]=='"')
	{
		char* comma = (char*)malloc(sizeof(char));
		char* quote = (char*)malloc(sizeof(char));
		strcpy(comma, ",");
		strcpy(quote, "\"");

		char* temptoken = (char*)malloc(sizeof(char)*300);
		strcpy(temptoken, token);
		char* token1 = (char*)malloc(sizeof(char)*300);
		strcpy(token1, strtok_new(NULL, "\""));

		strcat(temptoken, comma);
		strcat(temptoken, token1);
		strcat(temptoken, quote);
		pCurrent->movietitle = strdup(temptoken);
	}
	else
	{
		pCurrent->movietitle = strdup(token);
	}

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

	while(fgets(buff, 6000, stdin))  // this while loop loops until is gets to the bottom of the input csv file
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
			char* comma = (char*)malloc(sizeof(char));
			char* quote = (char*)malloc(sizeof(char));
			strcpy(comma, ",");
			strcpy(quote, "\"");

			char* temptoken = (char*)malloc(sizeof(char)*300);
			strcpy(temptoken, token);
			char* token1 = (char*)malloc(sizeof(char)*300);
			strcpy(token1, strtok_new(NULL, "\""));

			strcat(temptoken, comma);
			strcat(temptoken, token1);
			strcat(temptoken, quote);
			pCurrent->movietitle = strdup(temptoken);
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

	if(strcmp(argv[2],"color") != 0 && 
		strcmp(argv[2],"director_name") != 0 &&
		strcmp(argv[2],"num_critic_for_reviews") != 0 &&
		strcmp(argv[2],"duration") != 0 &&
		strcmp(argv[2],"director_facebook_likes") != 0 &&
		strcmp(argv[2],"actor_3_facebook_likes") != 0 &&
		strcmp(argv[2],"actor_2_name") != 0 &&
		strcmp(argv[2],"actor_1_facebook_likes") != 0 &&
		strcmp(argv[2],"gross") != 0 &&
		strcmp(argv[2],"genres") != 0 &&
		strcmp(argv[2],"actor_1_name") != 0 &&
		strcmp(argv[2],"movie_title") != 0 &&
		strcmp(argv[2],"num_voted_users") != 0 &&
		strcmp(argv[2],"cast_total_facebook_likes") != 0 &&
		strcmp(argv[2],"actor_3_name") != 0 &&
		strcmp(argv[2],"facenumber_in_poster") != 0 &&
		strcmp(argv[2],"plot_keywords") != 0 &&
		strcmp(argv[2],"movie_imdb_link") != 0 &&
		strcmp(argv[2],"num_user_for_reviews") != 0 &&
		strcmp(argv[2],"language") != 0 &&
		strcmp(argv[2],"country") != 0 &&
		strcmp(argv[2],"content_rating") != 0 &&
		strcmp(argv[2],"budget") != 0 &&
		strcmp(argv[2],"title_year") != 0 &&
		strcmp(argv[2],"actor_2_facebook_likes") != 0 &&
		strcmp(argv[2],"imdb_score") != 0 &&
		strcmp(argv[2],"aspect_ratio") != 0 &&
		strcmp(argv[2],"movie_facebook_likes") != 0)
	{
		printf("%s\n", "Not a valid input");
		return 0;
	}

	mergeSort(&pCurrent, argv[2]);  // applies the Merge Sort on the linked list based on the the user input(argv[2])
	
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
			"movie_facebook_likes"); // prints out the first line of the output csv with all the column heading
			
	 

	while(pCurrent != NULL) // prints out the output sorted csv
	{
		printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
			pCurrent->color,
			pCurrent->director,
			pCurrent->numCritic,
			pCurrent->duration,
			pCurrent->fbLikes,
			pCurrent->a3L,
			pCurrent->a2n,
			pCurrent->a1L,
			pCurrent->gross,
			pCurrent->genres,
			pCurrent->a1n,
			pCurrent->movietitle,
			pCurrent->numVote,
			pCurrent->castTotal,
			pCurrent->an3,
			pCurrent->fnInPic,
			pCurrent->plotWord,
			pCurrent->movieLink,
			pCurrent->numUserReview,
			pCurrent->language,
			pCurrent->country,
			pCurrent->rating,
			pCurrent->budget,
			pCurrent->titleYear,
			pCurrent->a2L,
			pCurrent->imbdScore,
			pCurrent->aspectRatio,
			pCurrent->MoviefbLikes);

		pCurrent = pCurrent->next;
	}

	return 0;
}
