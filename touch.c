//touch


//https://www.geeksforgeeks.org/touch-command-in-linux-with-examples/ 




#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
        if (argc <2)  {
                write(2, "Usage: touch file_name\n", 24);
                      exit(1);
        }


        if ((fd = open(argv[1], O_CREAT, 0666)) == -1) {
                      write(2, "ERROR open\n", 11);
                      exit(1);
          }
        close(fd);
}