#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>

char tuto[]="Hello player! Such a nice party you had last night! ;)\n"
            "As you can see, everything is dark...\n"
            "You may be wondering who am I. I'm Jessica, 3 years ago I woke up here and I couldn't get \n"
            "out because I ran out of oxygen, so now I'm a ghost that will help you escape not to end up like me.\n"
            "\n"
            "In order to move around this place and get out, you will need to use some magical words. \n"
            "For now, I will teach you this 4:\n"
            "\n"
            "pwd\n"
            "This will tell you where you are every time you say it.\n"
            "\n"
            "ls\n"
            "It is like a scanner of the room, it lists everything you are able to see, locations and objects.\n"
            "Nevertheless, it has an issue, locations and objects aren't distinguished.\n"
            "Adding a -l at the end (ls -l), some strange letters appear in the left of each name.\n"
            "Those are called permissions, they define the rules here!\n"
            "Apart from the permissions you should see a d in the leftmost part of some of the components. \n"
            "Those d's mean that the name related to it is a new location. \n"
            "If a name is missing that d, it means that it is an object.\n"
            "\n"
            "cat\n"
            "This magical word can do two different things:\n"
            "If you say \"cat\" without specifying any object, \n"
            "anything you write will be printed on the screen. If you want to stop it, press Ctrl+C.\n"
            "If you specify an object after cat (cat object_name), it will show you everything inside an object,\n"
            "just like reading a book!\n"
            "\n"
            "cd \n"
            "It enables you to move around. \n"
            "If you say cd followed by a location that appears in the ls list, you will enter on it. \n"
            "If you say cd .., you will go back to the previous location.\n"
            "\n"
            "I hope you haven't fallen asleep while reading the explanation.\n"
            "\n"
            "Well, you have to get out of here quickly! Scan the room. You should see a key.\n"
            "\n"
            "Try to read it with \"cat key\" and follow what it says.";

int main(int argc, char* argv[])
{
   int fd;
   const char* c;
   int length;
   int state;
   //Enable process abortion	   
   signal(2, SIG_DFL);
   //In case that the user doesn't give a file name to read, argc is going to be 1	
   if(argc == 1){
      //Whatever is written on the standard input is going to be printed on the standard output
      while (state = read(0, &c, 1) > 0) {
         write(1, &c, 1);
      } 
   } else if (argc == 2) {
       if(strcmp(".tutorial",argv[1])==0){
            write(1, tuto, strlen(tuto));
       }else {
           //to ensure the file name is not a directory
           DIR *isdir = opendir(argv[1]);
           if (isdir != NULL) {
               write(2, "cat is not enabled for locations\n", strlen("cat is not enabled for locations\n"));
               exit(1);
           } //fd will be -1 in case that the user gives a file name that doesn't exist
           else if ((fd = open(argv[1], O_RDONLY)) == -1) {
               switch (errno) {
                   case ENOENT:
                       write(2, "Some locations in the path or the object specified doesn't exist\n",
                             strlen("Some locations in the path or the object specified doesn't exist\n"));
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

           //The file will be printed completely on the standard output
           if (length = read(fd, &c, 1) > 0) {
               while (length > 0) {
                   write(1, &c, length);
                   length = read(fd, &c, 1);
               }
               write(1, "\n", strlen("\n"));
           }
           close(fd);
       }
   } else {
      //Command structure is not correct
      write(2, "Usage: cat [object_name]\n", strlen("Usage: cat [object_name]\n"));
   }
   
}
