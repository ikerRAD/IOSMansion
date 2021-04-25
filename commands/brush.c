//looks if newBrush and toothPaste have been created. If so, it returns the password

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  if (argc!=1){
    write(2, "Usage: brush\n", 14);
    exit(1);
  }
  
  struct dirent *d;
  struct stat fileStat;
  
  DIR *direc=opendir(".");
  
  char *str;
  
  int isB=0;
  int isT=0;
  
  while((d=readdir(direc))!=NULL && isT+isB!=2){
    str=d->d_name;
    if(strcmp(str,"newBrush")==0) isB=1;
    else if(strcmp(str,"toothPaste")==0) isT=1;
  }
  closedir(direc);
  if(isB+isT==2){
    write(1, "The password fragment of the bathroom is, take note please: \"streiso\"\n", strlen("The password fragment of the bathroom is, take note please: \"streiso\"\n"));
  } else if(isB==1){
    write(2, "There is no toothPaste!!!!!\n", strlen("There is no toothPaste!!!!!\n"));
  } else if(isT==1){
    write(2, "There is no newBrush!!!!!\n", strlen("There is no newBrush!!!!!\n"));
  } else {
    write(2,"WTF!!! You did nothing!!!\n", strlen("WTF!!! You did nothing!!!\n"));
  }
 
}

  
  
