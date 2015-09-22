#include<stdio.h>
#include<stdlib.h>


void snake(int n) {
   // int **num = malloc(sizeof(int)*(n+1));
    int** num =(int **)malloc(sizeof(int *) * (n+1));
    for (int i = 0; i < n + 1; i++) {
        num[i] = (int*)malloc(sizeof(int) * (n+1));
    }
    int R = 1;
    int i = 1;
    while (i < n + 1 - i) {
        for (int j = i; j <= n + 1 - i; j++) {
            num[j][n+1-i] = R++;
        }
        for (int j = n - i; j >= i; j--) {
            num[n+1-i][j] = R++;
        }
        for (int j = n - i; j >= i; j--) {
            num[j][i] = R++;
        }
        for (int j = i + 1; j <= n - i; j++) {
            num[i][j] = R++;
        }
        i++;
    }
    if (i == n+1-i) {
        num[i][i] = R;
    }
    for (int y = 1; y < n+1; y++) {
        for (int j = 1; j <  n + 1; j++) {

            printf("%3d ", num[y][j]);
        }
        printf("\n");
    }
}

void snake2(int n) {
    printf("\n\n");
   // int **num = malloc(sizeof(int)*(n+1));
    int** num =(int **)malloc(sizeof(int *) * (n));
    for (int i = 0; i < n; i++) {
        num[i] = (int*)malloc(sizeof(int) * (n));
    }
    int R = 1;
    int i = 1;
    while (i < n - i + 1) {
        for (int j = i - 1; j <= n - i; j++) {
            num[j][n-i] = R++;
        }
        for (int j = n - i - 1; j >= i - 1; j--) {
            num[n-i][j] = R++;
        }
        for (int j = n - i - 1; j >= i - 1; j--) {
            num[j][i-1] = R++;
        }
        for (int j = i; j <= n - i - 1; j++) {
            num[i-1][j] = R++;
        }
        i++;
    }
    if (i == n+1-i) {
        num[i-1][i-1] = R;
    }
    for (int y = 0; y < n; y++) {
        for (int j = 0; j <  n + 0; j++) {

            printf("%3d ", num[y][j]);
        }
        printf("\n");
    }
}





int main() {
    int n;
    scanf("%d", &n);
    snake(n);
    snake2(n);
}
