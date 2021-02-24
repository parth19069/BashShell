#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<unistd.h>

extern int errno;

int main(int argc, char *argv[]){
	errno = 0;
	char *flag = argv[1], *args = argv[2];
	struct stat file_stat;
	if(strlen(args) == 0){
		printf("%s\n", "File name not given");
		return 0;
	}
	if(strlen(flag) == 0){
		int check = unlink(args);
		if(check == -1){
			perror("Error");
		}
	}
	else if(strlen(flag) == 1){
		if(flag[0] == 'd'){
			int check = remove(args);
			if(check == -1){
				perror("Error");
			}
		}
		else if(flag[0] == 'v'){
			int check = unlink(args);
			if(check == -1){
				perror("Error");
			}
			else{
				printf("Removed file %s\n", args);
			}
		}
		else{
			printf("Invalid flag\n");
		}
	}
	else{
		printf("%s\n", "Invalid flag");
	}
	return 0;
}

//end