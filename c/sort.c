#include <stdio.h>
#include <strings.h>

#include "alloc.c"
// sort input lines
# define MAXLINELEN 1000
# define MAXLINES 1000

char *all_lines[MAXLINES]; 
char *alloc(int);

int read_line(char s[], int lim);
int read_lines(char *lines[], int max);
void copy_line(char *from, char *to);
void print_lines(char **lines, int num);
void sort(char *lines[], int num);
void swap(char **a, char **b);

int main(){
    int num = read_lines(all_lines, MAXLINES);
    sort(all_lines, num);
    print_lines(all_lines, num);
    return 0;
}

void print_lines(char **lines, int num) {
    for(int i=0; i< num; i++) {
        printf("%s\n", *lines++);
    }
}

void sort(char *lines[], int num) {
    // in-place quicksort num lines
    // go from left to right over array, having beginning and end ptr
    // if current place is less than pivot,  advance left ptr
    // if current place is more than pivot, swap it to end, decrement end ptr
    // if end ptr and left ptr collide, swap pivot there!
    // recursively sort both sides, from pivot +1 - end and from 0-pivot -1 
    // (pivot is perfectly placed)
    if (num <=1) 
        return;
    char **pivot = lines;
    char **left = pivot + 1;
    char **right = pivot + num-1;
    // printf("Starting Sort - p:%s l:%s r:%s \n", *pivot, *left, *right);
    while (left <= right ) {
        if (strcmp(*pivot, *left) > 0) 
            left++;
        else {
            swap(left, right);
            right--;
        }
    }
    // done - left and right collide
    swap(pivot, left-1);
    // recurse
    sort(lines, left-lines);
    sort(left,  num - (left - lines));


}
void swap(char **a, char **b) {
    char *tmp = *a;
    *a=*b;
    *b=tmp;
}



int read_lines(char *lines[], int max) {
    char line[MAXLINELEN];
    int whichline = 0;    
    int len=0;
    for(; (len=read_line(line, MAXLINELEN)) != -1 ; ){
        if( whichline > max || (all_lines[whichline] = alloc(len)) == NULL)
            return -1;
        copy_line(line, all_lines[whichline++]);
    }
    return whichline;
}

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

void copy_line(char *from, char *to) {
    while ((*to++ = *from++))
        ;
}