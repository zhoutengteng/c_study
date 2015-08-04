#define abs(x) (x > 0 ? x : -x)
#define f(x) x
#define f1(x) (x+1)
//　简化理解：#是“字符串化”的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串
#define ERROR_LOG(module)   fprintf(stderr,"error: "#module"\n")
// “##”是一种分隔连接方式，它的作用是先分隔，然后进行强制连接
#define TYPE2(type,name)   type name##_##type##_type

#define switch(x,y) {int tmp; tmp=x;x=y;y=tmp;}

#define switch1(x,y) do {int tmp; tmp=x; x=y; y=tmp;} while(0)

#include<stdio.h>
#include<execinfo.h>

void xx() {
    // 返回当前复函数的地址
    int x= 1;
    printf("Call frame: %p\n", __builtin_frame_address(1));
    printf("Call stack: %p\n", __builtin_return_address(0));
    printf("Call frame: %p\n", __builtin_frame_address(1));
    int y = 2;
    printf("Call frame: %p\n\n", __builtin_frame_address(1));
    void *array[20];
    char** string;
    size_t size =backtrace(array,20);
    printf("size_t 为%d\n",(int)size);
    string =  backtrace_symbols (array, size); 
    for (size_t i = 0; i < size; i++) {
        printf("%s\n",string[i]);

    }
    printf("\n\n\n");
}

int main() {
    printf("%d\n", abs(-5));
    printf("%d\n", f(6));
    printf("%d\n", f1(6));
    ERROR_LOG("add");
    printf("Call stack: %p\n", __builtin_return_address(0));
    printf("Call frame: %p\n", __builtin_frame_address(1));
    TYPE2(int, tengteng);
    printf("%d\n",tengteng_int_type);
    int x = 7;
    int y = 8;
    switch(x,y);
    printf("Call stack: %p\n", __builtin_return_address(0));
    printf("Call frame: %p\n", __builtin_frame_address(1));
    printf("%d %d\n",x , y);
    switch1(x,y);
    printf("Call stack: %p\n", __builtin_return_address(0));
    printf("Call frame: %p\n", __builtin_frame_address(1));
    printf("%d %d\n",x , y);
    xx();
    void *array[20];
    char** string;
    size_t size =backtrace(array,20);
    string =  backtrace_symbols (array, size); 
    for (size_t i = 0; i < size; i++) {
        printf("%s\n",string[i]);

    }
    return 0;
}
