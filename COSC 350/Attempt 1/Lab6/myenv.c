/*
Write your own getenv() function called mygetenv() which has the same syntax and symantics.
Write a simple c program to show your mygetenv()
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *mygetenv(char *name){

	//For each string in environ
	int i = 0, nameSize = strlen(name);

	for(i = 0; environ[i] != '\0'; i++){

		//Find equals in environ.

		int j = 0;

		while(environ[i][j]!='\0'){
			//If environ variable name != name, break and move to next.
			if(j>nameSize){
				break;

			} else if(nameSize==j){
				//Check if we hit = sign in environ. If not, break.

				if(environ[i][j]=='='){
					return environ[i] + nameSize + 1;
				}

				else {
					break;
				}
			}

			else if(name[j]!=environ[i][j]){
				break;
			} else {
				j++;
			}
		}

	}

	return NULL;
}

int main(int argc, char *argv[]){

	if(argc!=2){
		printf("Please input an env variable name\n");
		return -1;
	}

	printf("calling getenv(%s)\n", argv[1]);
	char *env = mygetenv(argv[1]);

	if(env != NULL){
		printf("mygetenv returned: %s\n", env);

	} else {
		printf("mygetenv returned NULL\n");
	}

	env = getenv(argv[1]);
	if(env != NULL){

		printf("getenv returned: %s\n", env);
	} else {

		printf("getenv returned NULL\n");
	}

	return 0;
}
