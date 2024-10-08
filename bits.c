/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */

/*  Solving idea:
 *  a=x&y;
 *  b=(~x)&(~y);
 */
int bitXor(int x, int y) {
    return (~(x&y))&(~((~x)&(~y))); 
}
/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
/*  Solving idea:
 *  handle the zero’s condition
 *  (x!=0 && y!=0)|| (x==0 && y==0)——> !(^signbit)
 *  else ——> 0
 *  
 */
int samesign(int x, int y) {   
    if(x&&y)
        return !((x^y)>>31&1);
    else
        return !(x^y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
/*  Solving idea:
 *  the most left 1's bit stands for the result
 *  111 -> 100 -> 2
 *  100 -> 111 (v>0 so logical shift)-> 011 -> bitcount 
 *  0111 -> 0100 -> 0011 -> bitcount
 */
int logtwo(int v) {
    int a,b,c,d,e = 0;
    a=(v>0xFFFF)<<4;
    v=v>>a;
    b=(v>0xFF)<<3;
    v=v>>b;
    c=(v>0xF)<<2;
    v=v>>c;
    d=(v>0x3)<<1;
    v=v>>d;
    e= (v>0x1);
    v=v>>e;
    return a|b|c|d|e;
}
/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
/*  Solving idea:
 *  x=x^y;y=x^y;x=x^y;
 *  only copy nth and mth byte -> construct x^y -> x^（x^y）=y
 *  consider arithmatic right shift
 */
int byteSwap(int x, int n, int m) {
    int shift_n = n<<3;
    int shift_m = m<<3;
    int nbyte = (0xff<<shift_n)&x;
    int mbyte = (0xff<<shift_m)&x;
    int temp= ((nbyte>>shift_n)^(mbyte>>shift_m))&0xff;
    temp = (temp<<shift_n)|(temp<<shift_m);
    return x^temp;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
/*  Solving idea:
 *  one by one out ,one by one in
 */
unsigned reverse(unsigned v) {
    int count=0;
    unsigned bit,result=0;
    unsigned x=0xffffffff;
    while(x){
        result = result<<1;
        bit = v&(1<<count);
        result |= bit>>count;
        x=x>>1;
        count=count+1;
    }
    return result;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
/*  Solving idea：
 *  handle sign bit
 *  arithmatic shift -> mask 0x 0...0(n bit)1...1 ->0x7fffffff shift n-1 -> n-1 = -1+n (consider n=0)
 *  or (0x1<<(32-n))-1 (consider n=0,if left shift count >= width of type ,there is auto %)
 *  or 0..0(n bit)1..11 <- 1...1(n bit)0...0 -> 0x80000000>>n<<1
 */
int logicalShift(int x, int n) {
    int mask = ~(1<<31>>n<<1);
    return (x>>n) & mask; 
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
/*  Solving idea：
 *  construct a=leftmost(x) , eg. 0x 0...0111.111 -> construct b=leftmost( leftmost(x)^x ) -> bitcount(a^b)
 *  or bitcount(a)-bitcount(b)
 *  consider the condition —— left-hand (most) end of word 从最左端开始,要判断最左端是否为1
 */
int leftBitCount(int x) {
    //int a = x|(x>>1)|(x>>2)|(x>>4)|(x>>8)|(x>>16);
    int mask=x>>31;
    x=x&mask;
    int a = x|(x>>1);
    a |= a>>2;
    a |= a>>4;
    a |= a>>8;
    a |= a>>16;
    int b = a^x;
    //b = b|(b>>1)|(b>>2)|(b>>4)|(b>>8)|(b>>16);
    b |= b>>1;
    b |= b>>2;
    b |= b>>4;
    b |= b>>8;
    b |= b>>16;
    mask = 0x11111111;
    int temp = a^b;
    int s = temp & mask;
    s += (temp>>1) & mask;
    s += (temp>>2) & mask;
    s += (temp>>3) & mask;
    s += (s>>16);
    mask = 0x0f0f ;
    s = (s&mask)+(s>>4 & mask);
    return ((s+(s>>8)) & 0x3f);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
/*  Solving idea：
 *  
 */
unsigned float_i2f(int x) {
    return 2;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
/*  Solving idea：
 *  
 */
unsigned floatScale2(unsigned uf) {
    return 2;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
/*  Solving idea：
 *  
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
/*  Solving idea：
 *  
 */
unsigned floatPower2(int x) {
    return 2;
}
