#include "social-header.h"

void loadGraph(socialGraph *database) {
    char graph[50];
    long int i;
    int id1, id2;
    FILE *fp;

    printf("Welcome to the Social Graph!\n");
    printf("Please load your graph (.txt): ");

    do {
        scanf("%s", graph);
        fp = fopen(graph, "r");
        if (fp == NULL) {
            printf("Error: Could not open file '%s'. Try again: ", graph);
        }
    } while (fp == NULL);

    printf("File '%s' loaded successfully!\n", graph);

    fscanf(fp, "%ld %ld", &database->nodes, &database->edges);

    database->userAccount = malloc(sizeof(account) * database->nodes);

    for (i = 0; i < database->nodes; i++) {
        database->userAccount[i].ID = i;
        database->userAccount[i].friendCount = 0;
        database->userAccount[i].friends = NULL;
    }

    for (i = 0; i < database->edges; i++) {
        if (fscanf(fp, "%d %d", &id1, &id2) == 2) {
            database->userAccount[id1].friends = realloc(
                database->userAccount[id1].friends,
                (database->userAccount[id1].friendCount + 1) * sizeof(int));
            database->userAccount[id1].friends[database->userAccount[id1].friendCount++] = id2;

            database->userAccount[id2].friends = realloc(
                database->userAccount[id2].friends,
                (database->userAccount[id2].friendCount + 1) * sizeof(int));
            database->userAccount[id2].friends[database->userAccount[id2].friendCount++] = id1;
        }
    }

    fclose(fp);
}

void mainMenu()
{
	printf("\n====MAIN MENU====\n");
	printf("(1) Display Friend List\n");
	printf("(2) Display Connections\n");
	printf("(3) Exit Program\n");
}

void displayFriends(socialGraph *database)
{
	long int i;
	int input = 0, node = -1, friendNode;
	printf("Account ID: ");
	scanf("%d", &input);
	
	for (i = 0; i < database->nodes; i++)
	{
		if (input == database->userAccount[i].ID)
			node = i;
	}
	
	if (node != -1)
	{
        printf("Person %d has %d friends!\n", node, database->userAccount[node].friendCount);

		printf("List of friends: ");
		for (i = 0; i < database->userAccount[node].friendCount; i++) {
		    friendNode = database->userAccount[node].friends[i];
		    printf("%d ", friendNode);
		}
		printf("\n");
	}
	else
		printf("Account ID not found.\n");
	

}

void freeGraph(socialGraph *database)
{
    long int i;
    if (database && database->userAccount) {
        for (i = 0; i < database->nodes; i++) {
            free(database->userAccount[i].friends);
        }

        free(database->userAccount);
        database->userAccount = NULL;
    }
}