#include <stdio.h>
#include <stdlib.h>

typedef struct record
{
	char *color;
	char *director;
	char *numCritic;
	char *duration;
	char *fbLikes;
	char *a3L;
	char *a2n;
	char *a1L;
	char *gross;
	char *genres;
	char *a1n;
	char *movietitle;
	char *numVote;
	char *castTotal;
	char *an3;
	char *fnInPic;
	char *plotWord;
	char *movieLink;
	char *numUserReview;
	char *language;
	char *country;
	char *rating;
	char *budget;
	char *titleYear;
	char *a2L;
	char *imbdScore;
	char *aspectRatio;
	char *MoviefbLikes;

	struct record *next;
} record;
typedef struct handarg
{
	char* directory;
	char* column;
	char* outputdirectory;
}handarg;

record* SortedMerge(record *a, record *b, char* column);
void Split(record *source, record **frontRef, record **backRef);
void mergeSort(record **headRef, char* column);