#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h>

extern int errno;

int main(int argc, char *argv[]){
	errno = 0;
	char *flag = argv[1], *args = argv[2];
	if(strlen(args) == 0){
		printf("%s\n", "File name not given");
		return 0;
	}
	if(strlen(flag) == 0){
		int check = mkdir(args, 0);
		if(check == -1){
			perror("Error");
		}
		else{
			chmod(args, 0777);
		}
	}
	else if(strlen(flag) == 1){
		if(flag[0] == 'v'){
			int check = mkdir(args, 0);
			if(check == -1){
				perror("Error");
			}
			else{
				chmod(args, 0777);
				printf("Created directory \"%s\"\n", args);
			}		
		}
		else if(flag[0] == 'm'){
			int ptr = 0, ptr_mode;
			char *mode = (char*)malloc(100*sizeof(char));
			for(int i = 0; args[i] != '\0' && args[i] != ' '; i++){
				mode[i] = args[i];
				if(isdigit(mode[i]) == 0){
					printf("Invalid flag value\n");
					return 0;
				}
				ptr++;
				mode[i + 1] = '\0';
			}
			int len = (int) strlen(mode);
			mode_t sum = 0;
			for(int i = 0; i < len; i++){
				int p = 1;
				for(int j = 0; j < len - i - 1; j++){
					p *= 8;
				}
				sum += p*(mode[i] - '0');
			}
			char *filename = (char*)malloc(100*sizeof(char));
			while(args[ptr] != '\0' && args[ptr] == ' ') ptr++;
			int ptr2 = 0;
			for(int i = ptr; args[i] != '\0'; i++){
				filename[ptr2] = args[i];
				ptr2++;
			}
			sum = strtol(mode, NULL, 8);
			int check = mkdir(filename, 0);
			if(check == -1){
				perror("Error");
			}
			else{
				chmod(filename, sum);
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