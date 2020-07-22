#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINELEN 100

// TODO this does not handle long lines very well. it can't track and erase them 
int read_line(char s[], int lim) {
    int i=0;
    int buf=0;
    for(i=0; i < lim && (buf = getchar()) !=EOF  && buf != '\n'; s[i++]=buf)
        ;
    if (i==0 && buf == EOF)
        return -1;
    s[i++] = '\0';       // end the line there
    return i;
}

void parseargs(int argc, char* argv[], int* buflen, char* filename) {
    int i=0;
    while (++i < argc) {
        if (strcmp(argv[i], "-n")==0){
            if(sscanf( argv[++i], "%d", buflen) !=1) {
               fprintf(stderr, "Argument error processing -n %s\n", argv[i]);
                exit(1);
            }
            continue;
         }
        if (sscanf( argv[i], "%s", filename)==1) continue;
        fprintf(stderr, "Argument error processing %s\n", argv[i]);
        exit(1);
    }
    // printf("got: %d %s \n", *buflen, filename);
}
int read_to_tail(FILE * f, char buf[][LINELEN], int buflen, int tailptr) {
    clearerr(f); // Clear eof if it is there (useful if file has changed under us)
    for(; fgets(buf[tailptr++], LINELEN, f)!= NULL; tailptr %= buflen);

    return --tailptr;
}
void print_tail(int tailptr,char buf[][LINELEN], int buflen) {
    for(int i=0; i < buflen; i++){
        printf("%s", buf[(tailptr + i) % buflen]);
    }
}
void erase_lines(int buflen){
    printf("\x1b[1000D");
    printf("\x1b[0K");
    fflush(stdout);
    for(;buflen--> 0; printf("\x1b[1000D\x1b[0K\x1b[1A\x1b[0K")) {
        fflush(stdout);
    }   
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("minitail: Give a file to tail, will display a rolling in-place buffer of the tail\n");
        printf("\t -n <lines>, number of lines in rolling buffer, default 10\n");
        exit(1);
    }
    int buflen = 10;
    char filename[LINELEN] = "";
    parseargs(argc, argv, &buflen, filename);

    // TODO handle filename not existing - use stdin
    
    FILE * f = fopen(filename, "r");
    char buf[buflen][LINELEN];
    for(int i =0; i < buflen; i++) buf[i][0]='\0';

    int tailptr = read_to_tail(f, buf, buflen, 0);
    print_tail(tailptr, buf, buflen);
    while(1) {
        usleep(100);
        int old_tail = tailptr;
        tailptr = read_to_tail(f, buf, buflen, tailptr);
        if(old_tail!=tailptr) {
            erase_lines(buflen);
            print_tail(tailptr, buf, buflen);
        }
    }

}