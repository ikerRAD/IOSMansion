// myShell0
//////////////////////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20
#define PATH_MAX 200

bool nowhere = true;
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
	char cook[PATH_MAX];
	char brush[PATH_MAX];

	if (getcwd(wd, sizeof(wd)) != NULL) {
		dirpath = strrchr(wd, '/'); //returns a pointer to last occurrence of '/'
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
	strcpy(cook, cwd);
	strcat(cook, "cook");
	strcpy(brush, cwd);
	strcat(brush, "brush");

	if (strcmp(dirpath,"/basement")==0 || strcmp(dirpath,"/nowhere")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(help, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/stairs")==0 ||strcmp(dirpath,"/corridor")==0 ||strcmp(dirpath,"/bedroom")==0 || strcmp(dirpath,"/exitDoor")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/wardrobe")==0) {
		chmod(touch, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/library")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/kitchen")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath, "/oven")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/bath")==0) {
		chmod(touch, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IXUSR |S_IXGRP  | S_IXOTH);
	} 
}

/////////////////////////////////////////

int processPassword(char *pwdfile)
{
	//first store in a string the content of the file pwdfile
	//will ask for a password
	//if coincide return 1, if not 0 and print an error
	char pwd[40];
	char input[40];
	char temp;
    //copying the content of the file to pwd
    int fd,i=0;
    if((fd=open(pwdfile,O_RDONLY)) != -1) {//making sure that there is not error but it is sure that there won´t be

        while (read(fd, &temp, 1) != 0) {
            if(temp!=' ' && temp!='\n'){
              pwd[i]=temp;
              i++;
            }else{
                close(fd);
                break;
            }
        }

        int argn,f=0;
        if (read_args(&argn, input, 40, &f) && argn > 0){//reading from console (we could also use write(0,...), stdin)
            if(argn>1){
                write(2,"you should just introduce the password\n",strlen("you should just introduce the password\n"));
            }else{
               if(strcmp(input[0], pwd)==0) {
                   return 1;
               }else{
                   write(2,"Password failed\n",strlen("Password failed\n"));
                   return 0;
               }
            }

        }

    }else{
        return 0;//will not happen
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
			write(2, "You can't go out of nowhere!\n", strlen("You can't go out of nowhere!\n"));
			return;
		}
	}
	if (argc!=2) {
		write(2, "Usage: cd new_location\n", strlen("Usage: cd new_location\n"));
	} else {
		int valid=0;
		int found=0;
		//search for .pass[location] file
		struct dirent *d;
 		struct stat fileStat;
  
  		DIR *direc=opendir(".");
  
  		char *str;
  		
		char stri[20]=".pass";
		strcat(stri,argv[1]);
  		while((d=readdir(direc))!=NULL && found!=1){
    			str=d->d_name;
    			if(strcmp(str,stri)==0) found=1;
  		}
  		closedir(direc);
		//process password if needed
		if(found==1){
			valid=processPassword(stri);
		}else valid=1;
		
		if(valid==1){
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
				return;		
			}
			else {
                     		getcwd(current_path, sizeof(current_path));
		      		if ((strcmp(strrchr(current_path, '/'), "/nowhere")==0) && nowhere){
		      			argv[0] = "cat";
                     			argv[1] = ".tutorial";
                      			nowhere = false;	
                     			execute(2, argv, cwd);
	       	       		}
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
           				return;
           			}
			} else if (proccess > 0)
           		 	wait(&status);
		}else{
			return;//PROVISIONAL IF PASSWORD FAILED
		}

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
   
   //Execute tutorial
   args[0] = "cat";
   args[1] = ".tutorial";
   execute(2,args, cwd);

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

