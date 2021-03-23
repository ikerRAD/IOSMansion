#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
void _ls(const char *dir){
        struct dirent *d;
	//Open the the directory given
        DIR *directorio = opendir(dir);
	char *str;
	//See if the directory exists
        if(!directorio){
                write(2, "ERROR open\n", 11);
                exit(1);
        }
	  //Print at the standar output the entries from the directory that doesn't start with a dot.
          while((d = readdir(directorio)) != NULL) {
             if(d->d_name[0]=='.')
              continue;
	      str = d->d_name;
            write(1, str, strlen(str));
	    write(1, "\n", strlen("\n"));
           }
	   
}
//Call the program above with current directory
int main(int argc, const char *argv[]){
  _ls(".");
}
