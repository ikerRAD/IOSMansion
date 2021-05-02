#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <termios.h>

/// terminal configuration functions

void SetTermNoCanon ( struct termios *SavedTM) {
	struct termios tm;

	tcgetattr(0, &tm);	//read current properties
	tcgetattr(0, SavedTM);	//read current properties
	tm.c_lflag &= ~(ICANON|ECHO);
	tm.c_cc[VMIN]=1;
	tm.c_cc[VTIME]=0;
	tcsetattr(0, TCSANOW, &tm);	//change properties;
}

void Berreskuratu_tm(struct termios *tm) {
	tcsetattr(0, TCSANOW, tm);
}

//manual static link of processPassword method
int processPassword(char *pwdfile)
{
    //first store in a string the content of the file pwdfile
    //will ask for a password
    //if coincide return 1, if not 0 and print an error
    struct termios saved_tm;
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
        //copy pwd to paw to avoid bugs
        char paw[i];
        int j;
        for(j=0;j<i;j++){
            paw[j]=pwd[j];
        }

        //read password from input
        char r;
	    char inp[40];
	    int i=0;
	    SetTermNoCanon(&saved_tm); //save current terminal properties
	    //read password
	    while (read(0,&r,1)>0) {
		    if (r == '\n') {
		    	write(1, "\n", strlen("\n"));
		    	break;
		    } else {
		    	inp[i]=r;
		    	i++;
		    	write(1, "*", strlen("*"));
		    }
	    }
	    Berreskuratu_tm(&saved_tm); //restore terminal properties
	    //look if entered password is correct
	    if(strcmp(inp, paw)==0) {
               return 1;
        }else{
               write(2,"Password is not correct\n",strlen("Password is not correct\n"));
               return 0;
        }

    }else{
        return 0;//will not happen
    }

}

int main(int argc, char* argv[])
{
    int fd;
    //Error management
    if (argc !=3)  {
        write(2, "Usage: setpass location password\n", strlen("Usage: setpass location password\n"));
        exit(1);
    }
    if (strstr(argv[1], "/")||strstr(argv[1], "..")) {
        write(2, "You can only set a password to a directly reachable location\n", strlen("You can only set a password to a directly reachable location\n"));
        exit(1);
    }
    if(strcmp(argv[1],"library")==0){
        write(2, "Do not set a password there!\n", strlen("Do not set a password there!\n"));
        exit(1);
    }

    int found=0; //to ensure the location specified exists
    int valid; //to see if there is some password to access the location
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
        if(strcmp(str,argv[1])==0) found=1;  //checks if the directory exists
        if(strcmp(passn,str)==0) foundtwo=1; //checks if the directory already has a password
    }
    closedir(direc);

    if(found==0){//the location specified does not exist
        write(2, "You must select an existing directly reachable location\n", strlen("You must select an existing directly reachable location\nn"));
        exit(1);
    }

    if(foundtwo==1){//it needs to verify the last password before
        write(1,"This location already has a password\nIn order to change it, introduce the actual password:\n",strlen("This location already has a password\nIn order to change it, introduce the actual password:\n"));
        valid=processPassword(passn); //valid will be 1 if player puts the correct password
    }else{
        valid=1;
    }

    int i;
    if(valid==1) { //password is going to be changed (.passlocation file
        char file[20] = ".pass";
        strcat(file, argv[1]);
        if(foundtwo==1){//if the location already had a password, reset it
            unlink(file);//reset the file
        }
        fd = open(file, O_CREAT | O_WRONLY, 0666) //create .passlocation file
        write(fd, argv[2], strlen(argv[2])); //write the specified password on it
        close(fd);
    }
}

