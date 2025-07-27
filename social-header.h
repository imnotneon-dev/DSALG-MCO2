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
} account;

typedef struct {
	account *userAccount;
	long int nodes;
	long int edges;
} socialGraph;

