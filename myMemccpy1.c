#include<string.h>
#include<stdio.h>
int main()
    {
            char* s="GoldenGlobalView";
            char d[20];
            memcpy(d,s+12,4);//从第13个字符(V)开始复制，连续复制4个字符(View)
            d[4]='\0';//memcpy(d,s+12*sizeof(char),4*sizeof(char));也可
            printf("%s",d);
           getchar();
           return 0;
    }

