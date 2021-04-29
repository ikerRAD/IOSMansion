//looks if all the ingredients in the recipe are inside the oven. If so, it returns the password

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  if (argc!=1){
    write(2, "Usage: cook\n", 14);
    exit(1);
  }
  
  struct dirent *d;
  struct stat fileStat;
  
  DIR *direc=opendir("./oven");
  
  char *str;
  
  char recipe [6][20] = {"bakingPowder","cornFlour","eggs","milk","salt","sugar"};
  int goodIng=0;
  int numIng=0;
  int i;
  
  while((d=readdir(direc))!=NULL){
    str=d->d_name;
    if (str[0]!='.') {
      numIng++;
      for (i = 0; i < 6; i++) {
        if (strcmp(str, recipe[i]) == 0)
            goodIng++;
      }
    }
  }
  closedir(direc);
  
  if(numIng==6 && goodIng==6){
    write(1, "The password fragment of the kitchen is, take note please: \"alakamula\"\n", strlen("The password fragment of the kitchen is, take note please: \"alakamula\"\n"));
  } else if(numIng>6 && goodIng==6){
    write(2, "Some ingredients in the oven do not belong to the recipe!!!\n", strlen("Some ingredients in the oven do not belong to the recipe!!!\n"));
  } else {
    write(2,"Don't cook that!!! You haven't followed the recipe correctly!!!\n", strlen("Don't cook that!!! You haven't followed the recipe correctly!!!\n"));
  }
 
}
