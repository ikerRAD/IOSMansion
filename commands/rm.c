#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int e;
        char str;
        
        if (argc <2)  {
                write(2, "Usage: rm file_name\n", 24);
                exit(1);
        }
        
        int i;
        for (i=1; i<argc; i++) {
                e=unlink(argv[i]);
                if (e==-1) {
                     write(2, "ERROR remove argument number ", 29);
                     write(2, &i, sizeof(i));
                     write(2, "\n",1);
                     
                }
        } 
}
