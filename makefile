run: shell ls date cat mkdir rm
	./shell

shell: ls date cat mkdir rm
	gcc-10 shell.c -o shell
ls: ls.c
	gcc-10 ls.c -o ls
date: date.c
	gcc-10 date.c -o date
cat: cat.c
	gcc-10 cat.c -o cat
mkdir: mkdir.c
	gcc-10 mkdir.c -o mkdir
rm: cat.c
	gcc-10 rm.c -o rm