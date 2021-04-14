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
                        switch (errno) {
                                case EACCES:
                                        write(2, "You have not the permission to remove the file: ",strlen("The access to the directory containing "));
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, "\n", strlen("\n"));
                                        break;
                                case EBUSY:
                                        write(2, "The file ", strlen("The file "));
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, " can't be deleted because it is being used by another process\n", strlen(" can't be deleted because it is being used by another process\n"));
                                        break;
                                case EISDIR:
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, " is a directory, can't be deleted\n", strlen(" is a directory, can't be deleted\n"));
                                        break;
                                       
                                        
                               
                        }
                     write(2, "ERROR remove argument number ", 29);
                     write(2, &i, sizeof(i));
                     write(2, "\n",1);
                     
                }
        } 
}
