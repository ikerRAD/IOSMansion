#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
        int e;
        
        //To ensure that the command follows the cp structure.
        if (argc !=3)  {
                write(2, "Usage: cp object_name copy_name\n", strlen("Usage: cp object_name copy_name\n"));
                      exit(1);
        }
        //Copy the file.
        e = link(argv[1], argv[2]);
        if (e==-1) {
                switch (errno) {
                        case EEXIST:
                             write(2, "There's already an object with that name in the location\n",strlen("There's already an object with that name in the location\n"));      
                             break;         
                        case ENOENT:
                             write(2, "Some locations in the path or the specified object doesn't exist\n",strlen("Some locations in the path or the specified object doesn't exist\n"));      
                             break;
                        default:
                             write(2, "An error has occurred\n", strlen("An error has occurred\n"));
                             break;
                }
                exit(1);
        }
}
