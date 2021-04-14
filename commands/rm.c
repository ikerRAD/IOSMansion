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
                                case EISDIR:
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, " is a directory, can't be deleted\n", strlen(" is a directory, can't be deleted\n"));
                                        break;
                                case ENOENT:
                                        write(2, "Some directories in the path: ",strlen("Some directories in the path: "));      
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, " don't exist\n",strlen(" don't exist\n")); 
                                        break;
                                case ENOTDIR:
                                        write(2, "A component of the path: ", strlen("A component of the path: "));
                                        write(2, &argv[i], sizeof(argv[i]));
                                        write(2, " isn't a directory\n",strlen(" isn't a directory\n")); 
                                        break;
                               default:
                                        write(2, "An error has occurred with the unlink system call\n", strlen("An error has occurred with the unlink system call\n"));
                                        break;       
                                        
                               
                        }
                     write(2, "ERROR remove argument number ", 29);
                     write(2, &i, sizeof(i));
                     write(2, "\n",1);
                     
                }
        } 
}
