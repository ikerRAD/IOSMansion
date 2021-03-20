#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
   int fd;
   char c;
   int length;

   if ((fd = open(".description", O_RDONLY)) == -1) {
      write(2, "ERROR open\n", 11);
      exit(1);
   }
   while (length=read(fd, &c, 1) > 0) {
      write(1,&c, length);
   }
   close(fd);
}
