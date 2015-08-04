#include<string.h>
#include<stdio.h>

int main() {
    char a[] = "string[a]";
    char b[] = "string(b)";
    memccpy(a,b,'B',sizeof(b));
    printf("memccpy():%s\n",a);
    return 0;
}
