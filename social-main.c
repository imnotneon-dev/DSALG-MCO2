#include "social-functions.c"


int main()
{
	socialGraph socialMedia;
	int choice = 0;

	loadGraph(&socialMedia);

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