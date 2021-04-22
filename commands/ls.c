#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void _ls(const char *dir, int l){
        struct dirent *d;
	//Open the the given directory
        DIR *directorio = opendir(dir);
	char *str;
        struct stat fileStat;
        char *per;
	//See if the directory exists
        if(!directorio){
                write(2, "An error has occurred when opening the current directory\n", strlen("An error has occurred when opening the current directory\n"));
                exit(1);
        }
	//Print at the standar output the entries from the directory that don't start with a dot.
        while((d = readdir(directorio)) != NULL) {
             	if(d->d_name[0]=='.')
        		continue;
	     	str = d->d_name;
	    	if(l==1){ //if -l is specified, print permissions
    			if(stat(str, &fileStat) < 0){
				write(2, "An error occurred when searching for permissions\n", strlen("An error occurred when searching for permissions\n"));
				exit(1);
			}
   			per=((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    			write(1, per, strlen(per));
    			per=((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    			write(1, per, strlen(per));
    			per=((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    			write(1, per, strlen(per));
    			per=((fileStat.st_mode & S_IXUSR) ? "x" : "-");
			write(1, per, strlen(per));
    			per = ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
   			write(1, per, strlen(per));
   			per = ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    			write(1, per, strlen(per));
    			per = ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    			write(1, per, strlen(per));
    			per = ((fileStat.st_mode & S_IROTH) ? "r" : "-");
    			write(1, per, strlen(per));
    			per = ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    			write(1, per, strlen(per));
    			per = ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    			write(1, per, strlen(per));	
			write(1, " ", strlen(" "));
	   	}
		//print component's name
            	write(1, str, strlen(str));
	   	write(1, "\n", strlen("\n"));	
	}   
}

//Call the program above with current directory
int main(int argc, const char *argv[]){
	int l = 0;
	//See if command's structure is correct
	if(argc == 2){
		if(strcmp(argv[1], "-l")==0){
			l = 1;	
		} else {
			write(2, "Usage: ls [-l]\n", strlen("Usage: ls [-l]\n"));
			exit(1);
		}
	}
	if(argc > 2){
		write(2, "Usage: ls [-l]\n", strlen("Usage: ls [-l]\n"));
		exit(1);
	} 
	//The structure is correct, call the program
	_ls(".",l);
}
