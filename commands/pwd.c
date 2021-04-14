#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
   int fd;
   char c;
   int length;
   //The command structure is incorret
   if (argc!=1) {
      write(2, "Usage: pwd\n", strlen("Usage: pwd\n"));
      exit(1);
   }
   //fd will be -1 if the .description file doesn't exist
   if ((fd = open(".description", O_RDONLY)) == -1) {
      write(2, "An error has occurred with the open system call\n", strlen("An error has occurred with the open system call\n"));
      exit(1);
   }
   //print .description file at the standar output
   while (length=read(fd, &c, 1) > 0) {
      write(1,&c, length);
   }
   close(fd);
}
