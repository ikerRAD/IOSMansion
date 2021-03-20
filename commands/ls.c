#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
void _ls(const char *dir){
        struct dirent *d;
        DIR *directorio = opendir(dir);
	char *str;
        if(!directorio){
                write(2, "ERROR open\n", 11);
                exit(1);
        }
          while((d = readdir(directorio)) != NULL) {
             if(d->d_name[0]=='.')
              continue;
	      str = d->d_name;
            write(1, str, strlen(str));
	    write(1, "\n", strlen("\n"));
           }
	   
}
int main(int argc, const char *argv[]){
  _ls(".");
}
