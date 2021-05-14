#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
void grep(char *argv[])
{
    int fd,r,j=0, count=0;
    char temp,line[100000];
    memset(line, 0, sizeof(line));
	DIR *isdir = opendir(argv[2]);
	if (isdir!=NULL){
        write(2,"grep is not enabled for locations\n",strlen("grep is not enabled for locations\n"));
        exit(1);
}
    else if((fd=open(argv[2],O_RDONLY)) != -1)
    {
	int s=strlen(argv[1]);
	int check=0;
    int mustPrint=0;
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
                
		if(temp==argv[1][check]){
		    check++;
                    if(check==s){
                        mustPrint=1;
                        line[j-s+1]='[';
                        int h;
                        for(h=0;h<s;h++){
                            line[j-s+2+h]=argv[1][h];
                        }
                        j++;
                        j++;
                        line[j]=']';
                    }
			
		}else{
                    check=0;
			 if(temp==argv[1][check]){
			 	check++;
			 }	
                }
                j++;
            }
            else
            {   
                if(mustPrint==1){
                    strcat(line, "\n");
                	write(1, line, sizeof(line));
                }
                mustPrint=0;
                check=0;
                memset(line,0,sizeof(line));
                j=0;
            }

        }
    } else {
	    switch (errno) {
		   	case ENOENT:
			    	write(2, "Some locations in the path or the object specified doesn't exist\n", strlen("Some locations in the path or the object specified doesn't exist\n"));
				break;
			case ENOTDIR:
				 write(2, "A component of the path isn't a location\n", strlen("A component of the path isn't a location\n"));     
				break;
		    default:
				write(2, "An error has occurred\n", strlen("An error has occurred\n"));  
				break;
	    }
	    exit(1);
    }
    close(fd);
}

int main(int argc,char *argv[]){
        if (argc!=3) {
                write(2, "Usage: grep string_to_find object_name(if you want to find some consecutive words search them between \"\")\n", strlen("Usage: grep string_to_find object_name(if you want to find some consecutive words search them between \"\")\n"));
                exit(1);
        }
        grep(argv);
}

