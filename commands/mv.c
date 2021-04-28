#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[])
{
        int e;
        //To ensure that the command follows the mv structure.
        if (argc !=3)  {
                write(2, "Usage: mv object_name new_location\n", 24);
                      exit(1);
	}
	if (strcmp(argv[1], "Jessica")==0) {
		write(2, "Jessica can't be moved!\n", strlen("Jessica can't be moved!\n"));
		exit(1);
	}
	if (argv[1][0]=='.') {
		write(2, "Objects starting with . are secret, you can't move them, you can't even see them\n", strlen("Objects starting with . are secret, you can't move them, you can't even see them\n"));
		exit(1);
	}
        char* path=argv[2];
        strcat(path,"/");
        strcat(path,argv[1]);
        e = link(argv[1], path);
        if (e==-1) {
		switch (errno) {
			case ENOENT:
				write(2, "That location doesn't exist\n", strlen("That location doesn't exist\n"));
				break;
			case ENOTDIR:
				write(2, "That is not a location\n", strlen("That is not a location\n"));
				break;
			default:
				write(2, "An error has occurred\n", strlen("An error has occurred\n"));
				break;
		}
		exit(1);
        }
        e=unlink(argv[1]);
        if (e==-1) {
          write(2, "An error has occurred\n",strlen("An error has occurred\n"));
          exit(1);
        }
  
}
