
void mergeSort(record **headRef, char* column)
{
	record *head = *headRef;
	record *a;
	record *b;

	if((head == NULL) || (head->next == NULL))
	{
		return;
	}

	Split(head, &a, &b);
	mergeSort(&a, column);
	mergeSort(&b, column);

	*headRef = SortedMerge(a, b, column);
}

record* SortedMerge(record *a, record *b, char* column)
{
	record *result = NULL;

	if(a == NULL)
	{
		return b;
	}else if(b == NULL){
		return a;
	}

	if((strcmp(column, "color")) == 0)
	{
		if(strcmp(a->color, b->color) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "director_name")) == 0)
	{
		if(strcmp(a->director, b->director) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "num_critic_for_reviews")) == 0)
	{ 
		if(atoi(a->numCritic) < atoi(b->numCritic)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "duration")) == 0)
	{ 
		if(atoi(a->duration) < atoi(b->duration)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "director_facebook_likes")) == 0)
	{ 
		if(atoi(a->fbLikes) < atoi(b->fbLikes)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}		
	}

	if((strcmp(column, "actor_3_facebook_likes")) == 0)
	{ 
		if(atoi(a->a3L) < atoi(b->a3L)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}
	
	if((strcmp(column, "actor_2_name")) == 0)
	{
		if(strcmp(a->a2n, b->a2n) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "actor_1_facebook_likes")) == 0)
	{ 
		if(atoi(a->a1L) < atoi(b->a1L)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "gross")) == 0)
	{ 
		if(atoi(a->gross) < atoi(b->gross)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "genres")) == 0)
	{
		if(strcmp(a->genres, b->genres) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}
	
	if((strcmp(column, "actor_1_name")) == 0)
	{
		if(strcmp(a->a1n, b->a1n) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "movie_title")) == 0)
	{
		if(strcmp(a->movietitle, b->movietitle) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "num_voted_users")) == 0)
	{ 
		if(atoi(a->numVote) < atoi(b->numVote)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "cast_total_facebook_likes")) == 0)
	{ 
		if(atoi(a->castTotal) < atoi(b->castTotal)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "actor_3_name")) == 0)
	{
		if(strcmp(a->an3, b->an3) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "facenumber_in_poster")) == 0)
	{ 
		if(atoi(a->fnInPic) < atoi(b->fnInPic)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}	
	}

	if((strcmp(column, "plot_keywords")) == 0)
	{
		if(strcmp(a->plotWord, b->plotWord) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "movie_imdb_link")) == 0)
	{
		if(strcmp(a->movieLink, b->movieLink) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "num_user_for_reviews")) == 0)
	{ 
		if(atoi(a->numUserReview) < atoi(b->numUserReview)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "language")) == 0)
	{
		if(strcmp(a->language, b->language) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "country")) == 0)
	{
		if(strcmp(a->country, b->country) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}	
	}

	if((strcmp(column, "content_rating")) == 0)
	{
		if(strcmp(a->rating, b->rating) < 0)
		{
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "budget")) == 0)
	{ 
		if(atoi(a->budget) < atoi(b->budget)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "title_year")) == 0)
	{ 
		if(atoi(a->titleYear) < atoi(b->titleYear)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "actor_2_facebook_likes")) == 0)
	{ 
		if(atoi(a->a2L) < atoi(b->a2L)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "imdb_score")) == 0)
	{ 
		if(atof(a->imbdScore) < atof(b->imbdScore)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	if((strcmp(column, "aspect_ratio")) == 0)
	{ 
		if(atof(a->aspectRatio) < atof(b->aspectRatio)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}	
	}

	if((strcmp(column, "movie_facebook_likes")) == 0)
	{ 
		if(atoi(a->MoviefbLikes) < atoi(b->MoviefbLikes)){
			result = a;
			result->next = SortedMerge(a->next, b, column);
		}
		else{
			result = b;
			result->next = SortedMerge(a, b->next, column);
		}
	}

	return result;
}	

void Split(record *source, record **frontRef, record **backRef)
{
	record* fast;
	record* slow;

	if(source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}else{
		slow = source;
		fast = source->next;
	}

	while(fast != NULL)
	{
		fast = fast->next;
		if(fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}
