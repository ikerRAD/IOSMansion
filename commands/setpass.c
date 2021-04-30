#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

//manual static link of processPassword method and readargs method
int processPassword(char *pwdfile)
{
    //first store in a string the content of the file pwdfile
    //will ask for a password
    //if coincide return 1, if not 0 and print an error

    char pwd[20];
    char *input[40];
    char temp;
    //copying the content of the file to pwd
    int fd,i=0;
    if((fd=open(pwdfile,O_RDONLY)) != -1) {//making sure that there is not error but it is sure that there won´t be

        while (read(fd, &temp, sizeof(char)) != 0) {
            if(temp!=' ' && temp!='\n'){
                pwd[i]=temp;
                i++;
            }else{
                close(fd);
                break;
            }
        }

        char paw[i];
        int j;
        for(j=0;j<i;j++){
            paw[j]=pwd[j];
        }

        int argn,f=0;
        if (read_args(&argn, input, 40, &f) && argn > 0){//reading from console (we could also use write(0,...), stdin)
            if(argn>1){
                write(2,"you should just introduce the password\n",strlen("you should just introduce the password\n"));
            }else{
                if(strcmp(input[0], paw)==0) {
                    return 1;
                }else{
                    write(2,"Password failed\n",strlen("Password failed\n"));
                    return 0;
                }
            }

        }

    }else{
        return 0;//will not happen
    }

}


int read_args(int* argcp, char* args[], int max, int* eofp)
{
    static char cmd[MAXLINE];
    char* cmdp;
    int ret,i;

    *argcp = 0;
    *eofp = 0;
    i=0;
    while ((ret=read(0,cmd+i,1)) == 1) {
        if (cmd[i]=='\n') break;  // correct line
        i++;
        if (i>=MAXLINE) {
            ret=-2;        // line too long
            break;
        }
    }
    switch (ret)
    {
        case 1 : cmd[i+1]='\0';    // correct reading
            break;
        case 0 : *eofp = 1;        // end of file
            return 0;
            break;
        case -1 : *argcp = -1;     // reading failure
            fprintf(stderr,"Reading failure \n");
            return 0;
            break;
        case -2 : *argcp = -1;     // line too long
            fprintf(stderr,"Line too long -- removed command\n");
            return 0;
            break;
    }
    // Analyzing the line
    cmdp= cmd;
    for (i=0; i<max; i++) {  /* to show every argument */
        if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
        cmdp= NULL;
    }
    if (i >= max) {
        fprintf(stderr,"Too many arguments -- removed command\n");
        return 0;
    }
    *argcp= i;
    return 1;
}


int main(int argc, char* argv[])
{
    int fd;
    //To ensure command structure is correct
    if (argc !=3)  {
        write(2, "Usage: setpass object_name password\n", strlen("Usage: setpass object_name password\n"));
        exit(1);
    }
    if (strstr(argv[1], "/")) {
        write(2, "You set a password to objects from outside your location\n", strlen("You set a password to objects from outside your location\n"));
        exit(1);
    }

    int found=0;
    int valid;
    int foundtwo=0;
    //search for .pass[location] file
    struct dirent *d;
    char path[10] = "./";
    strcat(path,argv[1]);

    DIR *direc=opendir(".");

    char *str;
    char passn[20]=".pass";
    strcat(passn,argv[1]);

    while((d=readdir(direc))!=NULL && (found!=1 || foundtwo!=1)){
        str=d->d_name;
        if(strcmp(str,argv[1])==0) found=1;
        if(strcmp(passn,str)==0) foundtwo=1; //checks if the directory already has a password
    }
    closedir(direc);

    if(found==0){
        write(2, "You must select an existing directory in this location\n", strlen("You must select an existing directory in this location\n"));
        exit(1);
    }

    if(strcmp(argv[1],"library")==0){
        write(2, "Do not set a password there!\n", strlen("Do not set a password there!\n"));
        exit(1);
    }

    if(foundtwo==1){//it needs to verify the last password before
        write(1,"introduce password:\n",strlen("introduce password:\n"));
        valid=processPassword(passn);
    }else{
        valid=1;
    }


    int i;
    if(valid==1) {
        //Sees if there is any problem in the creation
        char file[20] = ".pass";
        strcat(file, argv[1]);
        if ((fd = open(file, O_CREAT | O_WRONLY, 0666)) < 0) {
            switch (errno) {
                case ENOENT:
                    write(2, "Some locations in the path don't exist\n",
                          strlen("Some locations in the path don't exist\n"));
                    break;
                case ENOTDIR:
                    write(2, "A component of the path isn't a location\n",
                          strlen("A component of the path isn't a location\n"));
                    break;
                default:
                    write(2, "An error has occurred\n", strlen("An error has occurred\n"));
                    break;
            }
            exit(1);
        }

        write(fd, argv[2], strlen(argv[2]));

        close(fd);
    }
}

