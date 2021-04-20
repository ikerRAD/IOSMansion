#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int grep(char *argv[], int c)
{
    int fd,r,j=0, count=0;
    char temp,line[100000];
    memset(line, 0, sizeof(line));
    if((fd=open(argv[2],O_RDONLY)) != -1)
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
    }
   // if (c==1){
   //    return c;
   // } 
   // return -1;           
}

int main(int argc,char *argv[]){
        if (argc!=3) {
                write(2, "Usage: grep string_to_find file_name\n", strlen("Usage: grep string_to_find"));
                exit(1);
        }
        if(grep(argv, 1)>0){
                write(1,"The word appears", strlen("The word appears"));
        }
}

