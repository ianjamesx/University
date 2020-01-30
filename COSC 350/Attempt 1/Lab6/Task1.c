#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *mygetenv(char *name){
//For each string in environ
	int i=0;
	int name_length=strlen(name);
	int var_length=0;
	for(i=0; environ[i]!='\0'; i++){
		//Find equals in environ.
		int j=0;
		printf("Testing environ string %s\n", environ[i]);
		while(environ[i][j]!='\0'){
			//If environ variable name != name, break and move to next.
			printf("j %d\n",j);
			// if(j>=name_length){
			// 	printf("Skip 1");
			// 	break;
			// }
			if(j>name_length && environ[i][j]!='=' ){
				printf("Skipping\n");
				break;
			}
			else if(name_length==j && environ[i][j]=='='){
				//Found the result
				printf("Hello");
				printf("Found Env Variable: %s\n", environ[i][j]);
				return environ[i];
			}
			else if(name[j]!=environ[i][j]){
				printf("Skip 2\n");
				break;
			}
			else
				j++;
		}
	}
//strip var_name from variable data
//check if each index in var is = each index in var_name from environ.
//if they all match return pointer to this variable.
}

int main(int argc, char **argv){
	printf("%s",mygetenv("PATH"));
	return 0;
}
