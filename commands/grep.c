#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int grep(char *argv[], int c)
{
    int fd,r,j=0, count=0;
    char temp,line[100];
    memset(line, 0, sizeof(line));
    if((fd=open(argv[2],O_RDONLY)) != -1)
    {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
        {
            if(temp!='\n')
            {
                line[j]=temp;
                j++;
            }
            else
            {
                if(strstr(line,argv[1])!=NULL){
			//if (c==1){
			//	count++;	
			//} else {
			strcat(line, "\n");
                	write(1, line, sizeof(line));
			//}
		}   
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
	if(grep(argv, 1)>0){
		write(1,"The word appears", strlen("The word appears"));
	}
}
