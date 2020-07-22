#include <stdio.h>

int main() {
    float test = 1.0 * 16100000;
    char count = 1;
    for( ; ; ) {
        test += 1.0;
        if (count ++ % 10==0) {
        printf("%f\n", test);
        }
    }

}