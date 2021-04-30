#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    int i;

    //Sees if there is any problem in the creation
    if ((fd = open(argv[1], O_CREAT, 0666)) < 0) {
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

    write(fd,argv[2],strlen(argv[2]));

    close(fd);

}

