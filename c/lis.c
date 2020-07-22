#import <stdio.h>
#import <stdlib.h>
#import <dirent.h>
#include <time.h>
#include <sys/stat.h>

// use these 
// printf("\x1b[<color>m");
// fflush(stdout);/
enum Color {Black = 30,
            Red = 31,
            Green = 32,
            Yellow = 33,
            Blue = 34,
            Magenta = 35,
            Cyan = 36,
            White = 37};
// File Types
#define DT_UNKNOWN       0
#define DT_FIFO          1
#define DT_CHR           2
#define DT_DIR           4
#define DT_BLK           6
#define DT_REG           8
#define DT_LNK          10
#define DT_SOCK         12
#define DT_WHT          14

void print_entry(struct dirent * entry) {
    switch (entry -> d_type) {

    case  DT_DIR:
        printf("\x1b[%dm", Cyan);
        break;
    case  DT_REG:
        printf("\x1b[%dm", Yellow);
        break;
    default:
        printf("\x1b[%dm", White);
    }
    printf("%-30s", entry->d_name);
    struct stat buf;
    if (stat(entry->d_name, &buf)==0) {
        printf("\t ModAge: %10ld", time(NULL)-buf.st_mtime);
        printf("\t Mode: %o", buf.st_mode);
        printf("\t Size: %lld", buf.st_size);
        printf("\t Blocks: %lld", buf.st_blocks);
    }

    printf("\n\x1b[%dm", Yellow);
    fflush(stdout);

}

int main() {
    DIR * dir = opendir("/Users/ladyred/Code/Bradfield/csi/prep/c");
    struct dirent *entry;
    while((entry=readdir(dir))) {
        print_entry(entry);
        // printf("%s %d %d %d\n", entry->d_name, entry->d_reclen, entry->d_type, entry->d_namlen);
    }
    
    // for (char buf [100]; fgets(buf, 100, dir)!=NULL; printf("%s", buf));
    printf("hello_world!");
    printf("\x1b[%dm", White);

}