// myShell0
//////////////////////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

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

///////////////////////////////////////

int execute(int argc, char *argv[], char *cwd)
{
    int status;
    if (strcmp(argv[0],"cd")==0){
        char path[10] = "./";
        strcat(path, argv[1]);
        chdir(path);
    } else {
        int proccess = fork();
        if(proccess==0){
	   strcat(cwd,"/commands/");
	   strcat(cwd, argv[0]);
	   if(system("grep -c pwd .help")==0){
           	write(2, "You can't use that command now\n", strlen("You can't use that command now\n"));
		exit(1);
	   }
           if(execvp(cwd, argv)<0){
           write(2, "Unknown command\n", strlen("Unknown command\n"));
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
   while (1) {
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         signal(2,SIG_IGN);
         execute(argc, args, cwd);
         signal(2,SIG_DFL);
      }
      if (eof) exit(0);
   }
}
