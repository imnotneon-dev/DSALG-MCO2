#include "social-functions.c"


int main()
{
	socialGraph socialMedia;
	int choice = 0;

	loadGraph(&socialMedia);

//  just a debugger	DONT MIND HEHE
//	printf("Loaded %ld nodes and %ld edges\n", socialMedia.nodes, socialMedia.edges);
//
//	for (int i = 0; i < 10 && i < socialMedia.nodes; i++) { // show only first 10
//	    printf("ID: %08d, Name: %s %s, Friends: %d\n",
//	           socialMedia.userAccount[i].ID,
//	           socialMedia.userAccount[i].userName.fName,
//	           socialMedia.userAccount[i].userName.lName,
//	           socialMedia.userAccount[i].friendCount);
//	}

	do {
		mainMenu();
		printf("Enter Choice: ");
		(scanf("%d", &choice));

		switch (choice) {
			case 1:
				displayFriends(&socialMedia);
				break;
			case 2:
				displayConnections(&socialMedia);
				break;
			case 3:
				printf("Exiting program...\n");
				break;
			default:
				printf("Invalid choice.\n");
				while (getchar() != '\n');
		}
	} while (choice != 3);

	freeGraph(&socialMedia);

	return 0;
}