#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
        int fd;
        //To avoid not having a file name
        if (argc <2)  {
                write(2, "Usage: touch file_name\n", 24);
                      exit(1);
        }

        int i;
        //Creates all the files with the names given
        for (i=1; i<argc; i++) {
                //Sees if there is any problem in the creation
                if ((fd = open(argv[i], O_CREAT, 0666)) == -1) {
                      write(2, "ERROR open\n", 11);
                      exit(1);
                }
        }
        close(fd);
}
