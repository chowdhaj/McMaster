#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
  
int isDirectory(const char *path);
void listDirectory(char *name1);

int main(void) { 

    struct dirent *de;
  
    DIR *dr = opendir("."); 

    char * name;
  
    if (dr == NULL) { 
        printf("Not A Directory" ); 
        return 0; 
    } 
  
    while ((de = readdir(dr)) != NULL) {
        
        name = de->d_name;

        if ( !(strcmp(name, ".")) || !(strcmp(name, ".."))  ) {
            
        } else {
            if (isDirectory(de->d_name)) {
                printf("[D] %s\n", name);
                listDirectory(name); // recursive call
            } else {
                printf("[F] %s\n", name); 
            }
        }   
    }

    closedir(dr);
    return 0; 
} 

void listDirectory(char *name1) {

    struct dirent *df;
    DIR *ds = opendir(name1);

    if (ds == NULL) {
        printf("No Dir");
        return;
    }

    while ((df = readdir(ds)) != NULL) {
        name1 = df->d_name;

        if ( !(strcmp(name1, ".")) || !(strcmp(name1, ".."))  ) {
        
        } else {

            if (isDirectory(df->d_name)) {
                printf("    [D] %s\n", name1);
            } else {
                printf("    [F] %s\n", name1); 
            }
        }
    }
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}


/*

                             Note

    This code is not mine. Most of it comes from the documentation here:
        http://pubs.opengroup.org/onlinepubs/009604599/functions/opendir.html
        http://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html

    And stack overflow:
        https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
        https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program

    After learning how to somewhat use opendir, readdir, closedir, etc., I was able to make this.
    None of this stuff is from the textbook.

    Also, this solution is poorly coded. It is not up to par. This code was created
    purely for heuristics. It's a POC (proof of concept). It hasn't even been extensively tested.

    Thank you!

 */