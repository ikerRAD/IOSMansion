#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
        int fd;
        //To ensure command structure is correct
        if (argc <2)  {
                write(2, "Usage: touch object_name\n", strlen("Usage: touch object_name\n"));
                      exit(1);
        }

        int i;
        //Creates all the files with the names given
        for (i=1; i<argc; i++) {
                //Sees if there is any problem in the creation
                if ((fd = open(argv[i], O_CREAT, 0666)) < 0) {
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
        }
        close(fd);
}
