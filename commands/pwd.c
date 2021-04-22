#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[])
{
   int fd;
   char c;
   int length;
   char cwd[PATH_MAX];
   char *path;
   
   //The command structure is incorrect
   if (argc!=1) {
      write(2, "Usage: pwd\n", strlen("Usage: pwd\n"));
      exit(1);
   }
   
   //get current working directory and print the path
   if (getcwd(cwd, sizeof(cwd)) != NULL) { //it is not expected that it will give any error
	path = strstr(cwd, "/nowhere");
        write(1,"Location: ", strlen("Location: "));
	write(1, path, strlen(path));
	write(1, "\n", strlen("\n"));
   }
   
   //fd will be -1 if the .description file doesn't exist
   if ((fd = open(".description", O_RDONLY)) == -1) { //it won't give any error, because .description is present in every location
      write(2, "An error has occurred\n", strlen("An error has occurred\n"));
      exit(1);
   }
	
   //print .description file at the standar output
   while (length=read(fd, &c, 1) > 0) {
      write(1,&c, length);
   }
   close(fd);
}
