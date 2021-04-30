#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX 200

int main(int argc, char* argv[])
{
        int e;
        //To ensure that the command follows the mv structure.
        if (argc !=3)  {
                write(2, "Usage: mv object_name new_location\n", strlen("Usage: mv$                      exit(1);
        }
       //To ensure that you are not trying to move the file to directory that it b$        if(strcmp(argv[2], ".")==0 && !strstr(argv[1],"/")){
        write(2,"You are trying to move the object to the location that it belongs$        exit(1);
}
        //To ensure that Jessica is not moved
        if (strcmp(argv[1], "Jessica")==0) {
                write(2, "Jessica can't be moved!\n", strlen("Jessica can't be mov$                exit(1);
        }
        //To ensure files from outside the current location are not moved
        if (strstr(argv[1],"/")) {
                write(2, "You can't move objects from outside your location\n", st$                exit(1);
        }
        //To ensure that secret files are not moved
        if (argv[1][0]=='.') {
                write(2, "Objects starting with . are secret, you can't move them,$                exit(1);
        }
		      

 //To ensure the destination directory is not outside the kitchen
        char wd[PATH_MAX];
        char *dirpath;
        getcwd(wd, sizeof(wd));
        dirpath = strrchr(wd, '/');
        if (strcmp(dirpath, "/kitchen")==0 && strstr(argv[2],"..") || strcmp(dirpa$                write(2, "You can't move objects outside the kitchen\n", strlen("Y$                exit(1);
        }

        char* path=argv[2];
        strcat(path,"/");
        strcat(path,argv[1]);
        e = link(argv[1], path);
        if (e==-1) {
                switch (errno) {
                        case ENOENT:
                                write(2, "That location doesn't exist\n", strlen("$                                break;
                        case ENOTDIR:
										  write(2, "That is not a location\n", strlen("That $                                break;
                        case EEXIST:
                                write(2,"There is already a file with the same nam$                                break;

                        default:
                                write(2, "An error has occurred\n", strlen("An err$                                break;
                }
                exit(1);
        }
        e=unlink(argv[1]);
        if (e==-1) {
          write(2, "An error has occurred\n",strlen("An error has occurred\n"));
          exit(1);
        }

}
