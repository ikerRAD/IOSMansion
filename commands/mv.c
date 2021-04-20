#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int e;
        
        //To ensure that the command follows the mv structure.
        if (argc !=3)  {
                write(2, "Usage: mv file_name new_location\n", 24);
                      exit(1);
        }
        //Copy the file.
        e = link(argv[1], argv[2]);
        if (e==-1) {
          write(2, "ERROR copy\n", 11);
          exit(1);
        }
        e=unlink(argv[1]);
        if (e==-1) {
          write(2, "ERROR unlink\n", 11);
          exit(1);
        }
  
}
