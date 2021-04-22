#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char* argv[])
{
   int fd;
   const char* c;
   int length;
   int state;
   //Enable process abortion	   
   signal(2, SIG_DFL);
   //In case that the user doesn't give a file name to read, argc is going to be 1	
   if(argc == 1){
      //Whatever is written on the standar input is going to be printed on the standard output
      while (state = read(0, &c, 1) > 0) {
         write(1, &c, 1);
      } 
   } else if (argc == 2) {
      //fd will become -1 in case that the user gives a file name that doesn't exist 
      if ((fd = open(argv[1], O_RDONLY)) == -1) {
         switch (errno) {
               case 
         exit(1);
      }
      //The file will be printed completely in the standar output
      if(length=read(fd,&c, 1)>0){
         while (length > 0) {
            write(1,&c, length);
            length=read(fd, &c, 1);
         }
         write(1, "\n", strlen("\n"));
      }
      close(fd);
   } else {
      //Command structure is not correct
      write(2, "Usage: cat [file_name]\n", strlen("Usage: cat [file_name]\n"));
   }
   
}
