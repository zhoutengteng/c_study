#include<stdio.h>

int xx(int x) {
    printf("ccccccccccccccccccccc\n");
    return 1;
}
void xxx(int (* function1) (int x) ) {
    printf("aaaaaaaaaaaaaaaaaaaaa\n");
    printf("%d\n", (*function1)(11));
    printf("bbbbbbbbbbbbbbbb\n");
}

int main() {
    printf("%d\n", xx(0));
    int (* x_point)() = xx; 
    printf("%d\n", (*x_point)(0));
    xxx(x_point);
    return 0;
}
