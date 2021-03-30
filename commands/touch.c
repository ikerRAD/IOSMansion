#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
        int fd;
        //To avoid not having a file name
        if (argc <2)  {
                write(2, "Usage: touch file_name\n", strlen("Usage: touch file_name\n"));
                      exit(1);
        }

        int i;
        //Creates all the files with the names given
        for (i=1; i<argc; i++) {
                //Sees if there is any problem in the creation
                if ((fd = open(argv[i], O_CREAT, 0666)) < 0) {
                        switch (fd) {
                               case ENOENT:
                                        write(2, "Some directories in the path don't exist\n",strlen("Some directories in the path don't exist\n"));      
                                        break;
                                case EDQUOT:
                                        write(2, "You can't create the file, you have reached your quota of created files\n", strlen("You can't create the file, you have reached your quota of created files\n"));
                                        break;
                                case EINVAL:
                                        write(2, "Some characters in the file name are illegal\n", strlen("Some characters in the file name are illegal\n"));
                                        break;
                                case ENOTDIR:
                                        write(2, "A component of the file isn't a directory\n", strlen("A component of the file isn't a directory\n"));
                                        break;
                               default:
                                        write(2, "An error has occurred with the open system call\n", strlen("An error has occurred with the open system call\n"));
                                        break;
                        }
                      write(2, "ERROR open\n", 11);
                      exit(1);
                }
        }
        close(fd);
}
