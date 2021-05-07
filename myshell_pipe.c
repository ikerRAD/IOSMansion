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
#include<sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <termios.h>
#include <limits.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20
#define READ_END 0
#define WRITE_END 1

bool nowhere = true;

/// terminal configuration functions

void SetTermNoCanon ( struct termios *SavedTM) {
	struct termios tm;

	tcgetattr(0, &tm);	//read current properties
	tcgetattr(0, SavedTM);	//read current properties
	tm.c_lflag &= ~(ICANON|ECHO);
	tm.c_cc[VMIN]=1;
	tm.c_cc[VTIME]=0;
	tcsetattr(0, TCSANOW, &tm);	//change properties;
}

void Berreskuratu_tm(struct termios *tm) {
	tcsetattr(0, TCSANOW, tm);
}

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
	char setpass[PATH_MAX];

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
	strcpy(setpass, cwd);
	strcat(setpass, "setpass");

	if (strcmp(dirpath,"/basement")==0 || strcmp(dirpath,"/nowhere")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(grep, S_IRUSR|S_IRGRP|S_IROTH|S_IXUSR|S_IXGRP|S_IXOTH);
		chmod(man, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(help, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/stairs")==0 ||strcmp(dirpath,"/corridor")==0 || strcmp(dirpath,"/exitDoor")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/bedroom")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
	} else if (strcmp(dirpath,"/wardrobe")==0) {
		chmod(touch, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/library")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/kitchen")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath, "/oven")==0) {
		chmod(touch, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(mv, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(cp, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} else if (strcmp(dirpath,"/bath")==0) {
		chmod(touch, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(mv, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cp, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(man, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(help, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(rm, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(cook, S_IRUSR|S_IRGRP|S_IROTH);
		chmod(brush, S_IRUSR | S_IRGRP | S_IROTH| S_IXUSR |S_IXGRP  | S_IXOTH);
		chmod(setpass, S_IRUSR|S_IRGRP|S_IROTH);
	} 
}

/////////////////////////////////////////

int processPassword(char *pwdfile)
{
	//first store in a string the content of the file pwdfile
	//will ask for a password
	//if coincide return 1, if not 0 and print an error
	struct termios saved_tm;
	char pwd[20];
	char *input[40];
	char temp;
    //copying the content of the file to pwd
    int fd,i=0;
    if((fd=open(pwdfile,O_RDONLY)) != -1) {//making sure that there is not error but it is sure that there won´t be

        while (read(fd, &temp, sizeof(char)) != 0) {
            if(temp!=' ' && temp!='\n'){
              pwd[i]=temp;
              i++;
            }else{
                close(fd);
                break;
            }
        }	
	char paw[i];
	int j;
	for(j=0;j<i;j++){
		paw[j]=pwd[j];
	}	
	char r;
	char inp[40];
	int i=0;
	SetTermNoCanon(&saved_tm); //save current terminal properties
	//read password
	while (read(0,&r,1)>0) {
		if (r == '\n') {
			write(1, "\n", strlen("\n"));
			break;
		} else {
			inp[i]=r;
			i++;
			write(1, "*", strlen("*"));
		}
	}
	Berreskuratu_tm(&saved_tm); //restore terminal properties
	//look if entered password is correct
	if(strcmp(inp, paw)==0) {
               return 1;
        }else{
               write(2,"Password is not correct\n",strlen("Password is not correct\n"));
               return 0;
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
        char current_path[PATH_MAX];
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
	} 
	else if(strstr(argv[1],"/"))
	write(2,"Dont run too much\n",strlen("Dont run too much\n"));
	
else {
		int valid=0;
		int found=0;
		//search for .pass[location] file
		struct dirent *d;
 		struct stat fileStat;
		char path[10] = "./";
		strcat(path,argv[1]);  		

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
		    write(1,"introduce password:\n",strlen("introduce password:\n"));
			valid=processPassword(stri);
		}else valid=1;
		
		if(valid==1){
        		
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
					argv[2]=NULL;
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
 	   			if(execlp(cwd, "pwd", (char *)NULL)<0){
           				write(2, "An error has occurred\n", strlen("An error has occurred\n"));
           				return;
           			}
			} else if (proccess > 0)
           		 	wait(&status);
		}else{
			return;//PROVISIONAL IF PASSWORD FAILED
		}

	}
    } else {

	//pipe ls-f
	if(argc>1)
        if(strcmp(argv[0], "ls")==0 && strcmp(argv[1], "-f")==0){

            if(argc!=3){
                write(2,"the usage is ls -f [filter_name]\n",strlen("the usage is ls -f [filter_name]\n"));
                return;
            }
            char grep[20]="grep ";


            int STD_OUT = dup(1);
            int STD_IN =dup(0);

            int fd1[2];
            int pid;
            pipe(fd1);
            pid = fork();
            if(pid == 0){
                close(fd1[READ_END]);
                dup2(fd1[WRITE_END], STDOUT_FILENO);
                system("ls");
                exit(0);
            }
            else{

                //close(fd1[WRITE_END]);

                pid=fork();
                if(pid== 0){
                    close(fd1[WRITE_END]);
                    dup2(fd1[READ_END], STDIN_FILENO);
                    write(1,"\n",1);
                    strcat(grep,argv[2]);

                    system(grep);
                    exit(0);
                }
                //wait(&status);
			}
			wait(&status);


			dup2(STD_OUT, 1);
            close(STD_OUT);
            dup2(STD_IN, 0);
            close(STD_IN);

            return;
	}

            int proccess = fork();
            if (proccess == 0) {

                strcat(cwd, "/commands/");
                strcat(cwd, argv[0]);
                if (execvp(cwd, argv) < 0) {
                    switch (errno) {
                        case EACCES:
                            write(2, "That magical word can't be used in your current location\n",
                                  strlen("That magical word can't be used in your current location\n"));
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

   char * Prompt = "MansionShell> ";
   int eof= 0;
   int argc;
   char *args[MAXARGS];
   char cwd[PATH_MAX];
   getcwd(cwd, sizeof(cwd));
   char manual_path_original[PATH_MAX];
   getcwd(manual_path_original, sizeof(manual_path_original));
   strcat(manual_path_original,"/commands/manual/man");
   char manual_path[1000];
   
   //Change directory to starting point
   char start_path[PATH_MAX];
   getcwd(start_path, sizeof(start_path));
   strcat(start_path, "/IOSMansionGame/nowhere/basement");
   chdir(start_path);
   
   //Execute tutorial
   args[0] = "cat";
   args[1] = ".tutorial";
   args[2]=NULL;
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

