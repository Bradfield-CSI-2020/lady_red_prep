#import <dirent.h>
#import <stdio.h>
#import <stdlib.h>
#import <strings.h>
#import <sys/stat.h>
#import <time.h>
#import <unistd.h>


char *getcwd(char *buf, size_t size);

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
#define printcolor(c)   printf("\x1b[%dm", c)
#define dprintf   printf

void print_size(long long int size) {
    long long giga = 1000000000;
    long long mega =    1000000;
    long long kilo =       1000;
    if (size > giga) {
        printcolor(Red);
        printf("%lldG", size/giga);
        printcolor(White);
    }  else if (size > mega) {
        printcolor(Yellow);
        printf("%lldM", size/mega);
        printcolor(White);
    } else if (size > kilo) {
        printcolor(Green);
        printf("%lldK", size/kilo);
        printcolor(White);
    }
    else {
        printcolor(White);
        printf("%lld", size);
        printcolor(White);
    }
}

void print_entry(char* path, struct dirent * entry) {
    switch (entry -> d_type) {

    case  DT_DIR:
        printcolor(Cyan);
        break;
    case  DT_REG:
        printcolor(Yellow);
        break;
    default:
        printcolor(White);
    }
    printf("%-30s", entry->d_name);
    struct stat buf;
    char* filepath[1000];
    strcpy(filepath, path);
    strcat(filepath, "/");
    strcat(filepath, entry->d_name);
    if (stat(filepath, &buf)==0) {
        printf("\t ModAge: %10ld", time(NULL)-buf.st_mtime);
        printf("\t Mode: %o \t", buf.st_mode);
        print_size(buf.st_size);
        printf("\t Blocks: %lld \n", buf.st_blocks);
    } else {
        printf(" <bad info> \n");
    }

    printcolor(White);
    fflush(stdout);
}

int lsdir(char* path) {
    if(path[0] != '/') {
        char cwd[1000];
        getcwd(cwd, 1000);	
        strcat(cwd, "/");
        strcat(cwd, path);
        path = cwd;
    }

    dprintf("opening path: %s\n", path);
    DIR * dir = opendir(path);
    struct dirent *entry;
    while((entry=readdir(dir))) {
        print_entry(path, entry);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    printf("%d\n", argc);
    if( argc==1) {
	return lsdir("");
    }
    int ret = 0;
    for(;--argc>=1; ) {
        ret += lsdir(argv[argc]);
    }  
    return ret;

}
