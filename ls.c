#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>

extern int errno;

int main(int argc, char *argv[]){
	struct dirent *entry;
	struct stat file_stat;
	char *flag = argv[1], *args = argv[2];
	DIR *dir;
	if(strlen(args) == 0) dir = opendir(".");
	else dir = opendir(args);
	if(dir == NULL){
		dir = opendir(".");
		while((entry = readdir(dir))){
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
			if(strcmp(entry->d_name, args) == 0){
				printf("%s\n", args);
				return 0;
			}
		}
		printf("%s\n", "No such directory");
		return 0;
	}
	if(strlen(flag) > 1){
		printf("%s\n", "Invalid flag");
		return 0;
	}
	if(strlen(flag) == 0){
		while((entry = readdir(dir))){
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
			printf("%s\n", entry->d_name);
		}
		printf("\n");
		return 0;
	}
	else{
		if(flag[0] == 'a'){
			while((entry = readdir(dir))){
				printf("%s\n", entry->d_name);
			}
			printf("\n");
		}
		else if(flag[0] == 'l'){
			while((entry = readdir(dir))){
				if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
				// printf("%d\n", entry->d_type);
				char * temp = (char*)malloc(200*sizeof(char));
				if(strlen(args) != 0)strcpy(temp, args);
				else strcpy(temp, ".");
				strcat(temp, "/");
				strcat(temp, entry->d_name);
				int check = stat(temp, &file_stat);
				if(check == -1){
					perror("Error");
					return 0;
				}
				printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
				printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
				printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
				printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
				printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
				printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
				printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
				printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
				printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
				printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
				printf(" ");
				printf(" %d ", file_stat.st_uid);
				printf(" %d ", file_stat.st_gid);
				printf(" %lld ", file_stat.st_size);
				char str[32];
				strftime(str, sizeof(str), "%c", localtime(&file_stat.st_atime));
				printf(" %s ", str);
				printf("%s\n", entry->d_name);
			}
		}
		else{
			printf("%s\n", "Invalid flag");
		}
		return 0;
	}

}

// end