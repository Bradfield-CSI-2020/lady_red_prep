#define BUFSIZE 100

int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push a character back onto the input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}

int getword(char* buf){
    char* b=buf;
    int got;

    while ((got=getch()) == ' '   || got=='\n' || got=='\t');
    ungetch(got);

    while((got=getch()) != ' '  &&
           got != EOF &&
           got != '\0' &&
           got!= '\n'&&
           got!= '\t'){
        *b++ = got;
    } 
    
    *b='\0';
    return b-buf;
}