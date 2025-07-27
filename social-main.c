#include "social-functions.c"


int main()
{
	socialGraph socialMedia;
	
	loadGraph(&socialMedia);
	
	initAccounts(&socialMedia);

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

	free(socialMedia.userAccount);
	
	return 0;
}