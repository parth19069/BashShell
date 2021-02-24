#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>

#define si 200

int main(int argc, char *argv[]){
	char *flag = argv[1], *args = argv[2];
	if(strlen(args) == 0){
		if(strlen(flag) == 0){
			char *buffer = (char*)malloc(si*sizeof(char));
			while(strcmp(buffer, "quit\n") != 0){
				fgets(buffer, si, stdin);
				printf("%s", buffer);
			}
		}
		else if(strlen(flag) == 1){
			// TODO handle flags
			if(flag[0] == 'b'){
				int line_no = 1;
				char *buffer = (char*)malloc(si*sizeof(char));
				while(strcmp(buffer, "quit\n") != 0){
					fgets(buffer, si, stdin);
					if(strcmp(buffer, "\n") != 0){
						printf("     %d  %s", line_no, buffer);
						line_no++;
					}
					else{
						printf("\n");
					}
				}
			}
			else if(flag[0] == 'n'){
				int line_no = 1;
				char *buffer = (char*)malloc(si*sizeof(char));
				while(strcmp(buffer, "quit\n") != 0){
					fgets(buffer, si, stdin);
					printf("     %d  %s", line_no, buffer);
					line_no++;
				}
			}
		}
		else{
			printf("%s\n", "Invalid flag");
		}
	}
	else{
		FILE *file = fopen(args, "r");
		if(file == NULL){
			printf("%s\n", "No such file");
			return 0;
		}
		if(strlen(flag) == 0){
			char *buffer = (char*)malloc(si*sizeof(char));
			while(fgets(buffer, si, file)){
				printf("%s", buffer);
			}
		}
		else if(strlen(flag) == 1){
			if(flag[0] == 'b'){
				int line_no = 1;
				char *buffer = (char*)malloc(si*sizeof(char));
				while(fgets(buffer, si, file)){
					if(strcmp(buffer, "\n") != 0){
						printf("     %d  %s", line_no, buffer);
						line_no++;
					}
					else{
						printf("\n");
					}
				}
			}
			else if(flag[0] == 'n'){
				int line_no = 1;
				char *buffer = (char*)malloc(si*sizeof(char));
				while(fgets(buffer, si, file)){
					printf("     %d  %s", line_no, buffer);
					line_no++;
				}
			}
		}
		else{
			printf("%s\n", "Invalid flag");
		}
	}
	return 0;
}

//end