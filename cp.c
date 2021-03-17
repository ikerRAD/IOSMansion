#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int e;
        
        if (argc !=3)  {
                write(2, "Usage: cp file_name copy_name\n", 24);
                      exit(1);
        }
        
        e = link(argv[1], argv[2]);
        if (e==-1) {
          write(2, "ERROR copy\n", 11);
        }
}
