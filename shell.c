#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<fcntl.h>

#define si 300

char cur_dir[PATH_MAX];
char* history_dir;
char* ls_dir;
char* date_dir;
char* cat_dir;
char* mkdir_dir;
char* rm_dir;

extern int errno;

void get_everything(char* input_line, char* command, char* flag, char* args){
	int ptr = 0, ptr_command = 0, ptr_flag = 0, ptr_args = 0;
	if(strcmp(input_line, "") == 0){
		return;
	}
	while(input_line[ptr] != '\0' && input_line[ptr] == ' ') ptr++; // Remove leading spaces
	while(input_line[ptr] != '\0' && input_line[ptr] != ' '){ // Retrieve command
		command[ptr_command] = input_line[ptr];
		ptr++;
		ptr_command++;
	}
	command[ptr_command] = '\0';
	if(ptr_command > 0){
		if(command[ptr_command - 1] == '\n'){
			command[ptr_command - 1] = '\0';
		}
	}
	for(int i = 0; command[i] != '\0'; i++){
		command[i] = tolower(command[i]);
	}
	while(input_line[ptr] != '\0' && input_line[ptr] == ' ') ptr++; // Remove middle spaces
	if(input_line[ptr] == '\0'){
		return;
	}
	if(input_line[ptr] == '-'){
		ptr++;
		while(input_line[ptr] != '\0' && input_line[ptr] != ' '){ // Retrieve flag
			flag[ptr_flag] = input_line[ptr];
			ptr++;
			ptr_flag++;
		}
	}
	while(input_line[ptr] != '\0' && input_line[ptr] == ' ') ptr++; // Remove middle spaces
	while(input_line[ptr] != '\0'){ // Retrieve args
		args[ptr_args] = input_line[ptr];
		ptr++;
		ptr_args++;
	}
	if(ptr_args > 0){
		if(args[ptr_args - 1] == '\n'){
			args[ptr_args - 1] = '\0';
		}
	}
	if(ptr_flag > 0){
		if(flag[ptr_flag - 1] == '\n'){
			flag[ptr_flag - 1] = '\0';
		}
	}
}

void print_init(){
	char dir[PATH_MAX];
	getcwd(dir, sizeof(dir));
	printf("%s >>> ", dir);
}
void set_paths(){
	history_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/history.txt";
	ls_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/ls";
	date_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/date";
	cat_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/cat";
	mkdir_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/mkdir";
	rm_dir = "/Users/parth_mac/Desktop/parth_19069/OS_2/rm";
}
void external_commands(char* command, char* flag, char* args){
	int child_id;
	if((child_id = fork()) == 0){
		// Child process: handle all external commands here
		if(strcmp(command, "ls") == 0){
			execl(ls_dir, command, flag, args, NULL);
		}
		else if(strcmp(command, "date") == 0){
			execl(date_dir, command, flag, args, NULL);
		}
		else if(strcmp(command, "cat") == 0){
			execl(cat_dir, command, flag, args, NULL);
		}
		else if(strcmp(command, "mkdir") == 0){
			execl(mkdir_dir, command, flag, args, NULL);
		}
		else if(strcmp(command, "rm") == 0){
			execl(rm_dir, command, flag, args, NULL);
		}
		else{
			printf("Invalid command\n");
		}
		exit(0);
	}
	else{
		// Parent process
		int status;
		waitpid(child_id, &status, 0);
	}
}
int main(){
	set_paths();
	while(1){
		print_init();
		char *input_line = (char*)malloc(si*sizeof(char));
		fgets(input_line, si, stdin);
		char *command, *flag, *args;
		command = (char*)malloc(si*sizeof(char));
		flag = (char*)malloc(si*sizeof(char));
		args = (char*)malloc(si*sizeof(char));
		get_everything(input_line, command, flag, args);
		FILE *history = fopen(history_dir, "a+");
		if(history == NULL){
			printf("%s\n", "Error: Couldn't load history.");
		}
		else{
			fprintf(history, "%s", input_line);
			fclose(history);
		}
		// printf("%s %s %s\n", command, flag, args);
		if(strcmp(command, "cd") == 0){ // cd command
			if(strlen(flag) > 1){
				printf("Invalid flags\n");
				continue;
			}
			if(strlen(flag) == 0){
				int check;
				if(strlen(args) == 0) {
					chdir("/Users/parth_mac");
					check = 0;
				}
				else check = chdir(args);
				if(check == -1){
					perror("Error");
				}
				continue;
			}
			else if(strlen(flag) == 1){
				if(flag[0] == 'h'){
					FILE *help = fopen("/Users/parth_mac/desktop/parth_19069/OS_2/cd_help.txt", "r");
					if(help == NULL){
						printf("No help file found\n");
						continue;
					}
					char *buf = (char*)calloc(500, sizeof(char));
					while(fgets(buf, 500, help)){
						printf("%s", buf);
					}
					printf("\n");
					fclose(help);
				}
				else if(flag[0] == 'P'){
					int check;
					if(strlen(args) == 0) {
						chdir("/Users/parth_mac");
						check = 0;
					}
					else check = chdir(args);
					if(check == -1){
						perror("Error");
					}
					continue;
				}
				else{
					printf("Invalid flag\n");
				}
			}
		}
		if(strcmp(command, "pwd") == 0){ // pwd command
			if(strlen(args) != 0){
				printf("pwd has no arguments\n");
				continue;
			}
			if(strlen(flag) > 1){
				printf("%s\n", "Error: Invalid flag");
			}
			else if(strlen(flag) == 1){
				if(flag[0] == 'P'){
					char dir[PATH_MAX];
					if(getcwd(dir, sizeof(dir)) == NULL){
						perror("Error");
					}
					else printf("%s\n", dir);
				}
				else if(flag[0] == 'h'){
					FILE *pwd = fopen("/Users/parth_mac/Desktop/parth_19069/OS_2/pwd_help.txt", "r");
					if(pwd == NULL){
						printf("No help file found\n");
						continue;
					}
					char *buf = (char*)calloc(500, sizeof(char));
					while(fgets(buf, 500, pwd)){
						printf("%s", buf);
					}
					printf("\n");
					fclose(pwd);
				}
				else{
					printf("Invalid flag\n");
				}
			}
			else{
				char dir[PATH_MAX];
				if(getcwd(dir, sizeof(dir)) == NULL){
					perror("Error");
				}
				else printf("%s\n", dir);
			}
			continue;
		}
		if(strcmp(command, "echo") == 0){ // echo command
			int len = 0;
			for(int i = 0; args[i] != '\0'; i++){
				len++;
			}
			len--;
			while(len >= 0 && args[len] == ' '){
				args[len] = '\0';
				len--;
			}
			if(strlen(flag) == 0){
				for(int i = 0; args[i] != '\0'; i++){
					if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) continue;
					printf("%c", args[i]);
				}
				printf("\n");
			}
			else if(strlen(flag) == 1){ // flag -n
				if(flag[0] == 'n'){
					for(int i = 0; args[i] != '\0'; i++){
						if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) continue;
						printf("%c", args[i]);
					}
				}
				else if(flag[0] == 'e'){ // flag -e
					char *targs = (char*)malloc(si*sizeof(char));
					int ptr = 0;
					for(int i = 0; args[i] != '\0'; i++){
						if((i == 0 && args[i] == '"') || (args[i + 1] == '\0' && args[i] == '"')) continue;
						if(args[i] == '\\' && args[i + 1] == 'n'){
							targs[ptr] = '\n';
							i++;
						}
						else targs[ptr] = args[i];
						ptr++;
					}
					printf("%s\n", targs);
				}
				else{
					printf("%s\n", "Error: Invalid flag");
				}
			}
			else{
				printf("%s\n", "Error: Invalid flag");
			}
			continue;
		}
		if(strcmp(command, "history") == 0){ // History command
			if(strlen(flag) == 0){ // Display history
				if(strlen(args) != 0){
					printf("%s\n", "Error: Invalid command");
					continue;
				}
				FILE *history = fopen(history_dir, "r");
				if(history == NULL){
					printf("%s\n", "Error: Couldn't load history.");
					continue;
				}
				char *data = (char*)malloc(si*sizeof(char));
				while(fgets(data, si, history) != NULL){
					printf("%s", data);
				}
				fclose(history);
			}
			else if(strlen(flag) == 1){ // Clear history
				if(flag[0] == 'c'){
					if(strlen(args) != 0){
						printf("%s\n", "Error: Invalid command");
						continue;
					}
					FILE *history = fopen(history_dir, "w");
					if(history == NULL){
						printf("%s\n", "Error: Couldn't load history.");
						continue;
					}
					char *data = (char*)malloc(si*sizeof(char));
					fprintf(history, "");
					fclose(history);
				}
				else if(flag[0] == 's'){
					FILE *history = fopen(history_dir, "a+");
					if(history == NULL){
						printf("%s\n", "Error: Couldn't load history.");
						continue;
					}
					char *add = (char*)malloc(si*sizeof(char));
					int ptr = 0;
					for(int i = 0; args[i] != '\0'; i++){
						if(args[i] == '"') continue;
						add[ptr] = args[i];
						ptr++;
					}
					add[ptr] = '\n';
					fprintf(history, "%s", add);
					fclose(history);

				}
			}
			continue;
		}
		if(strcmp(command, "exit") == 0){
			if(strlen(args) != 0 || strlen(flag) != 0){
				printf("%s\n", "Error: Invalid command");
				continue;
			}
			break;

		}
		else{
			external_commands(command, flag, args);
		}

	}
}

//end