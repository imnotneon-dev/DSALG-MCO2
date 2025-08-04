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
	printf("Person ID: ");
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
		printf("Person ID not found.\n");
}

void displayConnections(socialGraph *database)  // using BFS
{
    int i;
    int id1, id2;
    int curr;
    int friend;
    int found = 0;
    int len, current;
    int from;
    int to;
    int *visited = calloc(database->nodes, sizeof(int));    // 0 = unvisited, 1 = visited
    int *parent = malloc(database->nodes * sizeof(int));    // used to reconstruct path
    int *path = malloc(database->nodes * sizeof(int));  // stores the reconstructed path

    Queue *q = createQueue(database->nodes);
    account acc;

    printf("First Person ID: ");
    scanf("%d", &id1);
    printf("Second Person ID: ");
    scanf("%d", &id2);

    if(id1 < 0 || id1 >= database->nodes || id2 < 0 || id2 >= database->nodes)
    {
        printf("One or both person IDs cannot be found.\n");
        return;
    }

    for(i = 0; i < database->nodes; i++)
        parent[i] = -1;

    addToQueue(q, id1);
    visited[id1] = 1;

    while(!isEmpty(q))
    {
        curr = removeFromQueue(q);  // current node
        acc = database->userAccount[curr];

        // visit each friend
        for(i = 0; i < acc.friendCount; i++)
        {
            friend = acc.friends[i];

            if(!visited[friend])
            {
                visited[friend] = 1;
                parent[friend] = curr;
                addToQueue(q, friend);

                if(friend == id2)
                {
                    found = 1;
                    break;
                }
            }
        }

        if(found)
            break;
    }

    if(!found)
        printf("No connection found between %d and %d\n", id1, id2);
    else
    {
        len = 0;
        current = id2;

        while(current != -1)
        {
            path[len++] = current;
            current = parent[current];
        }

        printf("\nThere is a connection from %d to %d!\n", id1, id2);

        for(i = len - 1; i > 0; i--)
        {
            from = path[i];
            to = path[i - 1];

            printf("%d is friends with %d\n", from, to);
        }

        free(path);
    }

    free(visited);
    free(parent);
    freeQueue(q);
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

/* Queue functions */

Queue *createQueue(int capacity)
{
    Queue *q = malloc(sizeof(Queue));

    q->items = malloc(sizeof(int) * capacity);
    q->front = q->back = -1;
    q->capacity = capacity;

    return q;
}

void addToQueue(Queue *q, int value)
{
    if(q->back == q->capacity - 1)
        return;

    if(q->front == -1)
        q->front = 0;

    q->items[++q->back] = value;
}

int removeFromQueue(Queue *q)   // remove and return the front value of the queue
{
    if(q->front == -1 || q->front > q->back)
        return -1;

    return q->items[q->front++];
}

int isEmpty(Queue *q)
{
    return q->front == -1 || q->front > q->back;
}

void freeQueue(Queue *q)
{
    free(q->items);
    free(q);
}