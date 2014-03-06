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

strlist * getMovies(char* actor){

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

	return movies;
}
strlist * getActors(char* movie){
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

	return actors;
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

	strlist * allMovies = getMovies(start);

	printf("Got Movies\n");

	int i;
	int j;

	for(i = 0; i< allMovies->len; i++){
		char * movie = allMovies->items[i];

		printf("Checking movie: #%i %s\n",i, movie);

		strlist* allActors = getActors(movie);

		printf("Got Actors\n");

		for(j = 0; j< allActors->len ; j++){

			char * actor = allActors->items[j];

			if(strcmp(start,actor)){
				printf("Checking actor: #%i %s\n",j, actor);
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

		strlist *allMovies = getMovies(prevActor);

		for(i = 0; i< allMovies->len; i++){
			char * movie = allMovies->items[i];

			printf("Checking movie: #%i %s\n",i, movie);

			strlist * allActors = getActors(movie);
			printf("Actors Len: %i\n",allActors->len);

			for(j = 0; j< allActors->len; j++){

				char * actor = allActors->items[j];
				printf("Checking actor: #%i %s\n",j, actor);

				if(actor){
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