#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

int main(int argc, char *argv[]){
	char *flag = argv[1], *args = argv[2];
	if(strlen(args) != 0){
		printf("%s\n", "Error: Date has no arguments");
		return 0;
	}
	if(strlen(flag) == 0){
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		char s[100];
		strftime(s, sizeof(s), "%a %b %d %T %Z %Y", tm);
		printf("%s\n", s);
	}
	else if(strlen(flag) == 1){
		if(flag[0] == 'u'){
			time_t t = time(NULL);
			struct tm *tm = gmtime(&t);
			char s[100];
			strftime(s, sizeof(s), "%a %b %d %T %Z %Y", tm);
			printf("%s\n", s);
		}
		else if(flag[0] == 'R'){
			time_t t = time(NULL);
			struct tm *tm = gmtime(&t);
			char s[100];
			strftime(s, sizeof(s), "%a, %d %b %Y %T %z", tm);
			printf("%s (UTC)\n", s);	
		}
		else{
			printf("Invalid flag\n");
		}
	}
	return 0;
}

//end