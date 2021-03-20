#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[])
{
   int fd;
   const char* c;
   int length;
   int state;
	   
   signal(2, SIG_DFL);

   if(argc == 1){
      while (state = read(0, &c, 1) > 0) {
	 if(strcmp(c, "")==0){
            //write(1, "Empty", strlen("Empty"));
            //exit(1);
         }
         write(1, &c, 1);
      } 

   } else {
      if ((fd = open(argv[1], O_RDONLY)) == -1) {
         write(2, "ERROR open\n", 11);
         exit(1);
      }

      if(length=read(fd,&c, 1)>0){
         while (length > 0) {
            write(1,&c, length);
            length=read(fd, &c, 1);
         }
         write(1, "\n", strlen("\n"));
      }
   }
   close(fd);
}
