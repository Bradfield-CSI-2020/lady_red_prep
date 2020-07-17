#define ALLOCSIZE 1000000
// allocate string memory on a single ginormous array.
// important - you have to call afree in the reverse order you called alloc because we are very dumb
static char allocbuf[ALLOCSIZE];
static char *allocptr = allocbuf;   // next free position


char *alloc(int len) {
    if (allocptr + len < allocbuf + ALLOCSIZE) {
        allocptr += len;
        return allocptr - len;
    } else {
        return 0;
    }
}

void afree(char *p) {
    // Client is telling us everything after P is free
    if (allocbuf <= p && allocptr > p && allocbuf + ALLOCSIZE > p) {
        allocptr = p;
    }
}