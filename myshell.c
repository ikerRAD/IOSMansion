// myShell0
//////////////////////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20
#define PATH_MAX 200

/////////// reading commands:

int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;
   i=0;
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;
      if (i>=MAXLINE) {
         ret=-2;        // line too long
         break;
      }
   }
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
              break;
     case 0 : *eofp = 1;        // end of file
              return 0;
              break;
     case -1 : *argcp = -1;     // reading failure
              fprintf(stderr,"Reading failure \n");
              return 0;
              break;
     case -2 : *argcp = -1;     // line too long
              fprintf(stderr,"Line too long -- removed command\n");
              return 0;
              break;
   }
   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }
   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   *argcp= i;
   return 1;
}

///function for permissions

void change_permissions (char *cwd) {
	char wd[PATH_MAX];
	char *dirpath;
	char touch[PATH_MAX];
	char mv[PATH_MAX];
	char cp[PATH_MAX];
	char grep[PATH_MAX];
	char man[PATH_MAX];
	char help[PATH_MAX];
	char rm[PATH_MAX];

	if (getcwd(wd, sizeof(wd)) != NULL) {
		dirpath = strrchr(cwd, '/'); //returns a pointer to last occurrence of '/'
	}

	strcat(cwd,"/commands/");
	strcpy(touch, cwd);
	strcat(touch, "touch");
	strcpy(mv, cwd);
	strcat(mv, "mv");
	strcpy(cp, cwd);
	strcat(cp, "cp");
	strcpy(grep, cwd);
	strcat(grep, "grep");
	strcpy(man, cwd);
	strcat(man, "man");
	strcpy(help, cwd);
	strcat(help, "help");
	strcpy(rm, cwd);
	strcat(rm, "rm");

	if (strcmp(dirpath,"/basement")==0 || strcmp(dirpath,"/nowhere")==0) {
		chmod(touch, S_IRUSR);
		chmod(mv, S_IRUSR);
		chmod(cp, S_IRUSR);
		chmod(grep, S_IRUSR);
		chmod(man, S_IRUSR);
		chmod(help, S_IRUSR);
		chmod(rm, S_IRUSR);

	} else if (strcmp(dirpath,"/stairs")==0 ||strcmp(dirpath,"/corridor")==0 ||strcmp(dirpath,"/bedroom")==0 || strcmp(dirpath,"/exitDoor")==0) {
		chmod(touch, S_IRUSR);
		chmod(mv, S_IRUSR);
		chmod(cp, S_IRUSR);
		chmod(grep, S_IRUSR);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR);

	} else if (strcmp(dirpath,"/wardrobe")==0) {
		chmod(touch, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR);
		chmod(cp, S_IRUSR);
		chmod(grep, S_IRUSR);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IXUSR |S_IXGRP  | S_IXOTH);

	} else if (strcmp(dirpath,"/library")==0) {
		chmod(touch, S_IRUSR);
		chmod(mv, S_IRUSR);
		chmod(cp, S_IRUSR);
		chmod(grep, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR);

	} else if (strcmp(dirpath,"/kitchen")==0 ||strcmp(dirpath, "/oven")==0) {
		chmod(touch, S_IRUSR);
		chmod(mv, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cp, S_IRUSR);
		chmod(grep, S_IRUSR);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR);

	} else if (strcmp(dirpath,"/bath")==0) {
		chmod(touch, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR);
		chmod(cp, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(grep, S_IRUSR);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR);
	} 
}


///////////////////////////////////////

int execute(int argc, char *argv[], char *cwd)
{
    char copycwd[100];
    int status;
    if (strcmp(argv[0],"cd")==0){
        char* current_path[PATH_MAX];
        getcwd(current_path, sizeof(current_path));
	char *dirfinal;
	dirfinal= strrchr(current_path, '/');
	if(strcmp(dirfinal, "/nowhere")==0){
		if(strcmp(argv[1], "..")==0){
			write(2, "You can't access this location", strlen("You can't access this location"));
			exit(1);
		}
	}
	if (argc!=2) {
		write(2, "Usage: cd new_location\n", strlen("Usage: cd new_location\n"));
	} else {
        	char path[10] = "./";
        	strcat(path, argv[1]);
        	if (chdir(path)==-1) {
			switch (errno) {
				case ENOENT:
					write(2, "The new location doesn't exist\n", strlen("The new location doesn't exist\n"));
					break;
				case ENOTDIR:
					write(2, "A component of the path isn't a location\n", strlen("A component of the path isn't a location\n"));
					break;
				default:
					write(2, "An error has occurred\n", strlen("An error has occurred\n"));
					break;
			}
			exit(1); //HAU KENDU????		
		}
		int proccess = fork();
        	if(proccess==0){
			strcpy(copycwd, cwd);
			change_permissions(copycwd);
           		strcat(cwd,"/commands/");
           		strcat(cwd, "pwd");
	   		int *p = &argv[1];
 	   		if(execvp(cwd, p)<0){
           			write(2, "hey\n", strlen("hey\n"));
           			exit(1);
           		}
		} else if (proccess > 0)
           		 wait(&status);
	}
    } else {
        int proccess = fork();
        if(proccess==0){
	   
	   strcat(cwd,"/commands/");
	   strcat(cwd, argv[0]);
           if(execvp(cwd, argv)<0){
		   switch(errno) {
			   case EACCES:
				   write(2, "That magical word can't be used in your current location\n", strlen("That magical word can't be used in your current location\n"));
				   break;
			   case ENOENT:
				   write(2, "That magical word doesn't exist\n", strlen("That magical word doesn't exist\n"));
				   break;
			   default:
				   write(2, "An error has occurred\n", strlen("An error has occurred\n"));
				   break;
		   }
           exit(1);
           }
        } else if (proccess > 0)
            wait(&status);
    }
}


main ()
{
   char * Prompt = "myShell0> ";
   int eof= 0;
   int argc;
   char *args[MAXARGS];
   char *cwd[PATH_MAX];
   getcwd(cwd, sizeof(cwd));
   char *manual_path_original[PATH_MAX];
   getcwd(manual_path_original, sizeof(manual_path_original));
   strcat(manual_path_original,"/commands/manual/man");
   char *manual_path[1000];
   
   //Change directory to starting point
   char *start_path[PATH_MAX];
   getcwd(start_path, sizeof(start_path));
   strcat(start_path, "/IOSMansionGame/nowhere/basement");
   chdir(start_path);

   while (1) {
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         signal(2,SIG_IGN);
	 if(strcmp(args[0], "man")==0){
		strcpy(manual_path, manual_path_original);
		strcat(manual_path, args[1]);
		strcpy(args[0], "cat");
		strcpy(args[1], manual_path);
	 }
         execute(argc, args, cwd);
         signal(2,SIG_DFL);
      }
      if (eof) exit(0);
   }
}

