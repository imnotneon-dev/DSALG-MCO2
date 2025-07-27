#include "social-header.h"

void loadGraph (socialGraph *database) 
{
    char graph[50];
    long int i;
    int id1, id2;
    FILE *fp = NULL;

    printf("Welcome to the Social Graph!\n");
    printf("Please load your graph (.txt): ");

    while (fp == NULL) {
        scanf("%s", graph);
        fp = fopen(graph, "r");
        if (fp == NULL) {
            printf("Error: Could not open file '%s'. Try again: ", graph);
        }
    }
	
    printf("File '%s' loaded successfully!\n", graph);

    fscanf(fp, "%ld %ld", &database->nodes, &database->edges);

    database->userAccount = malloc(sizeof(account) * database->nodes);
    

    for (i = 0; i < database->nodes; i++) {
        database->userAccount[i].ID = i;
        database->userAccount[i].friendCount = 0;
    }

    for (i = 0; i < database->edges; i++) {
        fscanf(fp, "%d %d", &id1, &id2);
        (database->userAccount[id1].friendCount)++;
        (database->userAccount[id2].friendCount)++;
    }
	
    fclose(fp);
}

int initAccounts(socialGraph *database) {
    long int i = 0;
    int id;
    FILE *fp = fopen(USER_FILE, "r");
    if (fp == NULL) {
        printf("Error: Could not open %s\n", USER_FILE);
        return 1; 
    }

	while (i < database->nodes && fscanf(fp, "%d %s %s", &id, database->userAccount[i].userName.fName, database->userAccount[i].userName.lName) == 3)
	{
	    database->userAccount[i].ID = id;
	    i++;
	}

    fclose(fp);
    return 0; 
}
