#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        int e;
        char str;
        
        //Avoid not having any file name
        if (argc <2)  {
                write(2, "Usage: rm file_name\n", 24);
                exit(1);
        }
        
        int i;
        //Delete all the files from the names given
        for (i=1; i<argc; i++) {
                //Remove the file
                e=unlink(argv[i]);
                //See if any error happened
                if (e==-1) {
                     write(2, "ERROR remove argument number ", 29);
                     write(2, &i, sizeof(i));
                     write(2, "\n",1);
                     
                }
        } 
}
