#include<stdio.h>
int leftBitCount(int);

int main(){
    printf("%d\n",leftBitCount(-1));
    return 0;
}

int leftBitCount(int x) {
    int mask=x>>31;
    x=x&mask;
    int a = x|(x>>1);
    a |= a>>2;
    a |= a>>4;
    a |= a>>8;
    a |= a>>16;
    printf("%x\n",a);
    int b = a^x;
    b |= b>>1;
    b |= b>>2;
    b |= b>>4;
    b |= b>>8;
    b |= b>>16;
    printf("%x\n",b);
    mask = 0x11111111;
    int temp = a^b;
    int s = temp & mask;
    s += (temp>>1) & mask;
    s += (temp>>2) & mask;
    s += (temp>>3) & mask;
    s += (s>>16);
    mask = 0x0f0f ;
    s = (s&mask)+(s>>4 & mask);
    printf("%x\n",(x>>31)&1);
    return ((s+(s>>8)) & 0x3f);
}