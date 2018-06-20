#include<iostream>
#include<sstream>
#include<fstream>
#include<string.h>
#include<vector>
#include<string>
#include <cstdlib> 

using namespace std;
std::string get_csv_column(ifstream & in);
class Record{
	public:
	Record(){};
	std::string color;
	std::string director_name;
	std::string num_critic_for_review;
	std::string duration;
	std::string director_facebook_likes;
	std::string actor_3_facebook_likes;
	std::string actor_2_name;
	std::string actor_1_facebook_likes;
	std::string gross;
	std::string genres;
	std::string actor_1_name;
	std::string movie_title;
	std::string num_voted_users;
	std::string cast_total_facebook_likes;
	std::string actor_3_name;
	std::string facenumber_in_poster;
	std::string plot_keywords;
	std::string movie_imdb_link;
	std::string num_user_for_reviews;
	std::string language;
	std::string country;
	std::string content_rating;
	std::string budget;
	std::string title_year;
	std::string actor_2_facebook_likes;
	std::string imdb_score;
	std::string aspect_ratio;
	std::string movie_facebook_likes;
	
	void populateMembers(ifstream & csv_row){
		/* tokenize the line */
		vector <string> tokens;
		for(int i = 0; i < 27; i++){
			string col = get_csv_column(csv_row);
			tokens.push_back(col); 
		}
		/* Populate the members of object */
		this->color = tokens[0];
		this->director_name = tokens[1];
		this->num_critic_for_review = tokens[2];
		this->duration = tokens[3];
		this->director_facebook_likes = tokens[4];
		this->actor_3_facebook_likes = tokens[5];
		this->actor_2_name = tokens[6];
		this->actor_1_facebook_likes = tokens[7];
		this->gross = tokens[8]; 
		this->genres = tokens[9];
		this->actor_1_name= tokens[10];
		this->movie_title = tokens[11];
		this->num_voted_users = tokens[12];
		this->cast_total_facebook_likes = tokens[13];
		this->actor_3_name = tokens[14];
		this->facenumber_in_poster = tokens[15];
		this->plot_keywords = tokens[16];
		this->movie_imdb_link = tokens[17];
		this->num_user_for_reviews = tokens[18];
		this->language = tokens[19];
		this->country = tokens[20];
		this->content_rating = tokens[21];
		this->budget = tokens[22];
		this->title_year = tokens[23];
		this->actor_2_facebook_likes = tokens[24];
		this->imdb_score = tokens[25];
		this->aspect_ratio = tokens[26];
		this->movie_facebook_likes = tokens[27];
		
	}
};
void merge(int low,int mid,int high, vector<Record>& objVect,string col);
void mergeSort(int low,int high,vector<Record> &objVect,string col);
	
int main(int argc, char *argv[]){

	if(argc != 4){ 
		cout<<"Must have 4 arguments, Structure: ./<executable filename + <-c> + <column name> + <input file>\n";
		return 0;  // must have 3 arguments
	}
	string csv_row;
	ifstream infile(argv[3]);
	
	Record tempObject;
	vector<Record> vectRecord; 
	
	
	while(getline(infile,csv_row)){
		tempObject.populateMembers(infile);
		vectRecord.push_back(tempObject);
	}
	
	string column = argv[2];
	int highIndex = static_cast<int>(vectRecord.size());
	mergeSort(0,highIndex,vectRecord,column);

}
std::string get_csv_column(ifstream & in){
    std::string col;
    unsigned quotes = 0;
    char prev = 0;
    bool finis = false;
    for (int ch; !finis && (ch = in.get()) != EOF; ) {
        switch(ch) {
        case '"':
            ++quotes;
            break;
        case ',':
            if (quotes == 0 || (prev == '"' && (quotes & 1) == 0)) {
                finis = true;
            }
            break;
        default:;
        }
        col += prev = ch;
    }
	string st = col.substr(0,col.size()-1);
    return st;
}
void merge(int low,int mid,int high, vector<Record> &objVect,string col){
	int h,i,j,k;
	vector<Record> temp;
	h = low;
	i = low;
	j = mid+1;
	
	while((h<=mid) && (j<=high)){
		if(col == "gross"){
			if(objVect[h].gross <= objVect[j].gross){
				temp.push_back(objVect[h]);
				h++;
			}
			else{
				temp.push_back(objVect[j]);
				j++;
			}
			i++;
		}
	}
	if(h<mid){
		for(k = j; k<= high;k++){
			temp.push_back(objVect[k]);
			i++;
		}
	}
	else{
		for(k = h; k <= mid; k++){
			temp.push_back(objVect[k]);
			i++;
		}
	}
	
	for(k = low; k <= high; k++){
		objVect[k] = temp[k];
	}
}
void mergeSort(int low,int high,vector<Record> &objVect,string col){
	if(low<high){
		int mid = low+(high-low)/2;
		mergeSort(low,mid,objVect,col);
		mergeSort(mid+1,high,objVect,col);
		merge(low,mid,high,objVect,col);
	}
}

