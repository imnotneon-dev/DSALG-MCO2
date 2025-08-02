#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USER_FILE "user_accounts.txt"

typedef struct {
	char fName[20];
	char lName[20];
} name;

typedef struct {
	name userName;
	int ID;
	int node;
	int friendCount;
	int *friends;
} account;

typedef struct {
	account *userAccount;
	long int nodes;
	long int edges;
} socialGraph;

// Queue for BFS
typedef struct {
	int *items;		// array of node IDs
	int front, rear;
	int capacity;		// total capacity of the queue
} Queue;

void loadGraph(socialGraph *database);
void mainMenu();
void displayFriends(socialGraph *database);
void displayConnections(socialGraph *database);
void freeGraph(socialGraph *database);

// Queue functions
Queue *createQueue(int capacity);
void addToQueue(Queue *q, int value);
int removeFromQueue(Queue *q);
int isEmpty(Queue *q);
void freeQueue(Queue *q);