/*BFS Oracle of Bacon
Make queue of movies to search
	implement linked list
For each movie look through each cast member
	if found
		print all previous movie/actor connections 

	if cast member not what we're looking for
		add movie struct with previous movie and connecting actor
			

*/
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

#define MAX 1000


typedef struct PathNode_s PathNode;
typedef struct Node_s Node;

struct PathNode_s
{
	PathNode *nextPath;
	char * movie;
	char * actor;
} ;

struct Node_s
{
	Node *nextNode;
	PathNode *value;
};

typedef struct
{
	int len; 
	char *items[MAX];
	
}strlist;

void printQueue(Node* head);

MYSQL *con;

void finish_with_error(MYSQL *d)
{
  fprintf(stderr, "%s\n", mysql_error(d));
  mysql_close(d);
  exit(1);        
}

void initMySQLdb(){
	con = mysql_init(NULL);

	if (con == NULL) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, "localhost", "root", "PASSWORD", 
	  "softsys", 0, NULL, 0) == NULL) 
	{
		finish_with_error(con);
	}

}

void getMovies(strlist **movielist, char* actor){

	char * query = malloc(sizeof(char)*128);
	memset(query, 0, sizeof(char) * 128);

	char * escape = malloc(sizeof(char)*64);
	memset(escape, 0, sizeof(char) * 64);

	mysql_real_escape_string(con,escape,actor,strlen(actor));

	sprintf(query,"SELECT movie_name FROM actor_tbl WHERE actor_name = '%s'",escape);
	//printf("%s\n",query);

	if (mysql_query(con, query)) 
	{
		finish_with_error(con);
	}
	free(escape);
	free(query);

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL) 
	{
		finish_with_error(con);
	}

	//int num_rows = mysql_num_rows(result);

	strlist *movies = malloc(sizeof(strlist));
	
	MYSQL_ROW row;

	int i = 0;
	while ((row = mysql_fetch_row(result))) 
	{ 
		movies->items[i]=malloc(sizeof(char)*65);
		memset(movies->items[i],0,sizeof(char)*65);
		strcpy(movies->items[i],row[0] ? row[0] : "NULL");
		printf("Movie Res:%i ,%s\n", i,movies->items[i]);

		i++;
		if(i>=MAX){
			break;
		}
	}
	printf("Done with Movies\n");
	movies->len = i;
	printf("Len %i\n",movies->len);
	mysql_free_result(result);
	printf("Freed result\n");

	if(*movielist){
		printf("Freeing movielist\n");
		free(*movielist);
		printf("Freed movielist\n");
	}

	*movielist = movies;
	printf("reassigned movielist\n");


	/*strlist movies;
	if(!strcmp(actor,"A")){
		movies.items[0] = "1";
		movies.items[1] = "3";
		movies.len = 2;
	}else if(!strcmp(actor,"B")){
		movies.items[0] = "1";
		movies.items[1] = "2";
		movies.len = 2;
	}else if(!strcmp(actor,"C")){
		movies.items[0] = "3";
		movies.items[1] = "4";
		movies.len = 2;
	}else if(!strcmp(actor,"D")){
		movies.items[0] = "2";
		movies.items[1] = "5";
		movies.len = 2;
	}else if(!strcmp(actor,"E")){
		movies.items[0] = "3";
		movies.items[1] = "4";
		movies.len = 2;
	}
	return movies;*/
}
void getActors(strlist **actorlist,char* movie){
	char * query = malloc(sizeof(char)*128);
	memset(query, 0, sizeof(char) * 128);

	char * escape = malloc(sizeof(char)*64);
	memset(escape, 0, sizeof(char) * 64);

	mysql_real_escape_string(con,escape,movie,strlen(movie));

	sprintf(query,"SELECT actor_name FROM actor_tbl WHERE movie_name = '%s'",escape);
	//printf("%s\n",query);

	

	if (mysql_query(con, query)) 
	{
		finish_with_error(con);
	}
	free(escape);
	free(query);

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL) 
	{
		finish_with_error(con);
	}

	//int num_rows = mysql_num_rows(result);

	strlist *actors = malloc(sizeof(strlist));
	

	MYSQL_ROW row;

	int i =0;
	while ((row = mysql_fetch_row(result))) 
	{ 
		actors->items[i]=malloc(sizeof(char)*65);
		memset(actors->items[i],0,sizeof(char)*65);
		strcpy(actors->items[i],row[0] ? row[0] : "NULL");
		printf("Actor Res:%i ,%s\n", i,actors->items[i]);

		i++;
		if(i>=MAX){
			break;
		}
	}

	actors->len = i;

	mysql_free_result(result);
	if(*actorlist){
		free(*actorlist);
	}

	*actorlist = actors;

	/*strlist actors;
	if(!strcmp(movie,"1")){
		actors.items[0]="A";
		actors.items[1]="B";
		actors.len = 2;
	}else if(!strcmp(movie,"2")){
		actors.items[0]="B";
		actors.items[1]="D";
		actors.len = 2;
	}else if(!strcmp(movie,"3")){
		actors.items[0]="A";
		actors.items[1]="C";
		actors.items[2]="E";
		actors.len = 3;
	}else if(!strcmp(movie,"4")){
		actors.items[0]="C";
		actors.items[1]="E";
		actors.len = 2;
	}else if(!strcmp(movie,"5")){
		actors.items[0]="D";
		actors.len = 1;
	}
	return actors;*/
}

Node* dequeue(Node **head, Node **tail){
	Node *toReturn = *head;
	*head = (*head)->nextNode;
	return toReturn;
}
void enqueue(Node **head, Node **tail, Node **node){
	if(*tail){
		(*tail)->nextNode = *node;
		*tail = *node;
	}else{
		*tail = *node;
		*head = *node;
	}
}
PathNode* BFS(char * start,char * target){
	printf("Start:%s Target:%s \n",start,target);

	Node* head = NULL;
	Node* tail = NULL;

	strlist *allMovies = NULL;
	getMovies(&allMovies,start);

	printf("Got Movies\n");

	int i;
	int j;
	char * movie;
	char * actor;
	strlist *allActors = NULL;

	for(i = 0; i< allMovies->len; i++){
		movie = allMovies->items[i];

		printf("Checking movie: %s\n", movie);

		getActors(&allActors,movie);

		printf("Got Actors\n");

		for(j = 0; j< allActors->len; j++){

			actor = allActors->items[j];

			if(strcmp(start,actor)){
				printf("Checking actor: %s\n", actor);
				PathNode *toAdd = malloc(sizeof(PathNode));
				memset(toAdd, 0, sizeof(PathNode));

				toAdd->movie = malloc(sizeof(char)*65);
				memset(toAdd->movie, 0, sizeof(char)*65);
				strcpy(toAdd->movie,movie);

				toAdd->actor = malloc(sizeof(char)*65);
				memset(toAdd->actor, 0, sizeof(char)*65);
				strcpy(toAdd->actor,actor);
				toAdd->nextPath = NULL;

				if (!strcmp(target,actor)){
					return toAdd; 
				}else{
					Node *newNode = malloc(sizeof(Node));
					newNode->value = toAdd;
					newNode->nextNode = NULL;
					enqueue(&head,&tail,&newNode);
					//printQueue(head);
				}
			}
		}
	}
	puts("Using queue");
	while(1){
		Node *toCheck = dequeue(&head,&tail);
		PathNode *path = toCheck->value;
		char * prevActor = path->actor;

		getMovies(&allMovies,prevActor);

		for(i = 0; i< allMovies->len; i++){
			movie = allMovies->items[i];

			printf("Checking movie: %s\n", movie);
			getActors(&allActors, movie);

			for(j = 0; j< allActors->len; j++){
				actor = allActors->items[i];

				if(strcmp(prevActor,actor)){

					printf("Checking actor: %s\n", actor);

					PathNode *toAdd = malloc(sizeof(PathNode));
					memset(toAdd, 0, sizeof(PathNode));

					toAdd->movie = malloc(sizeof(char)*65);
					memset(toAdd->movie, 0, sizeof(char)*65);
					strcpy(toAdd->movie,movie);

					toAdd->actor = malloc(sizeof(char)*65);
					memset(toAdd->actor, 0, sizeof(char)*65);
					strcpy(toAdd->actor,actor);

					toAdd->nextPath = path;

					if (!strcmp(target,actor)){
						return toAdd; 
					}else{
						Node *newNode = malloc(sizeof(Node));
						newNode->value = toAdd;
						newNode->nextNode = NULL;
						enqueue(&head,&tail,&newNode);
						//printQueue(head);
					}
				}
			}
		}
		free(toCheck);
	}
}

void printPath(PathNode * path){
	PathNode *curr = path;
	while(curr != NULL){
		printf("%s-%s ===> ",curr->movie,curr->actor);
		curr = curr->nextPath;
	}
}
void printQueue(Node* head){
	Node *curr = head;
	printf("Queue Start ");
	while(curr != NULL){
		printPath(curr->value);
		curr = curr->nextNode;
		printf("|||");
	}
	printf("Queue End \n");
}



int main(){
	initMySQLdb();
	PathNode *answer = BFS("50 Cent","3Oh!3");
	printPath(answer);
	return 0;
}