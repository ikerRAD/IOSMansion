#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int fd;
    //To ensure command structure is correct
    if (argc !=3)  {
        write(2, "Usage: setpass object_name password\n", strlen("Usage: setpass object_name password\n"));
        exit(1);
    }
    if (strstr(argv[1], "/")) {
        write(2, "You set a password to objects from outside your location\n", strlen("You set a password to objects from outside your location\n"));
        exit(1);
    }

    int found=0;
    //search for .pass[location] file
    struct dirent *d;
    char path[10] = "./";
    strcat(path,argv[1]);

    DIR *direc=opendir(".");

    char *str;

    while((d=readdir(direc))!=NULL && found!=1){
        str=d->d_name;
        if(strcmp(str,argv[1])==0) found=1;
    }
    closedir(direc);

    if(found==0){
        write(2, "You must select an existing directory in this location\n", strlen("You must select an existing directory in this location\n"));
        exit(1);
    }

    if(strcmp(argv[1],"library")==0){
        write(2, "Do not set a password there!\n", strlen("Do not set a password there!\n"));
        exit(1);
    }

    int i;

    //Sees if there is any problem in the creation
    char file[20]=".pass";
    strcat(file,argv[1]);
    if ((fd = open(file, O_CREAT, 0666)) < 0) {
         switch (errno) {
             case ENOENT:
                 write(2, "Some locations in the path don't exist\n",strlen("Some locations in the path don't exist\n"));
                 break;
             case ENOTDIR:
                 write(2, "A component of the path isn't a location\n", strlen("A component of the path isn't a location\n"));
                 break;
             default:
                 write(2, "An error has occurred\n", strlen("An error has occurred\n"));
                 break;
         }
         exit(1);
    }

    write(fd,&argv[2],strlen(argv[2]));

    close(fd);

}

