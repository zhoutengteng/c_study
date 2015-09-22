#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void manipulation(char* str) {
    int* array = (int*)malloc(sizeof(int) * 26);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '?') {
            array[str[i]-'a']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        printf("%c的个数=%d\n", i+'a', array[i]);
    }

    free(array);


}


void createFile(char* st, int n) {

      FILE *fp =  fopen(st, "w");
      char ch;
      srand(time(0));
      for (int i = 0; i < n; i++) {
          ch = rand() % 26 + 'a';
          fputc(ch, fp);

      }
      fputc('?',fp);
      if(fp==NULL )   return;  
      fclose(fp);  

}

void readFile(char* st) {
    FILE *fp =  fopen(st, "r");
    if(fp==NULL )   return;  
    fseek(fp,0L,SEEK_END);/* 定位到文件末尾 */
    int n = ftell(fp);
    printf("字符串的长度为%d   \n",n-1);
    char* str = (char *)malloc(sizeof(char) * (n+1));
    fseek(fp,0L,SEEK_SET);
    fread(str,n,1,fp);
    str[n] = '\0';
    //printf("字符串的值为%s\n", str);
    int* array = (int*)malloc(sizeof(int) * 26);

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '?') {
            array[str[i]-'a']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        printf("%c的个数=%d\n", i+'a', array[i]);
    }
    printf("\n\n");
    free(array);
    free(str);
    fclose(fp);  



}

int main() {
    //char* str ="addfhsdfjslfkjsdlfkjlfjsdlf?"; 
    //manipulation(str);
    createFile("str_test1.txt", 10);
    readFile("str_test1.txt");
    createFile("str_test2.txt", 100);
    readFile("str_test2.txt");
    createFile("str_test3.txt", 1000);
    readFile("str_test3.txt");
    createFile("str_test4.txt", 10000);
    readFile("str_test4.txt");
    createFile("str_test5.txt", 100000);
    readFile("str_test5.txt");

}
