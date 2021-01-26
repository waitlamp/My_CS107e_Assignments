// File: codegen.c
// ---------------
// C examples that demo some interesting properties/transformations
// when C compiler generates ARM instructions.

// Part (a): arithmetic
// Study each function and the translation to ARM assembly.
// negate(): ARM has no negate instruction -- what is used instead?
// bitwise(): Note how constant expression is precomputed ("constant folding")
//            Which ARM instruction is used for this bitwise operation?
// arithmetic(): The first statement generates 3 assembly instructions, yet
//               second more complex line is just one. How/why does that happen?
int negate(int arg)
{
    return -arg;
}

int bitwise(int arg)
{
    return arg & ~((1 << 8) - 1);
}

int arithmetic(int arg)
{
    int result = arg*22;
    result = arg - (result + 3*result);
    return result + 17;
}

// Part (b): if-else
// Branch instructions are used to make decisions about control flow.
// Look at the compiler's generated assembly for the code below.
// Which instruction evaluates the expression for the if?
// Which instruction set the condition codes? Which instruction reads
// the codes? How are branch instructions used to route execution?
int conditional(int arg)
{
    int result = arg;

    if (arg % 2 == 0) {
        result++;
    } else {
        result--;
    }
    return result;
}

// Part (c): loops
// This function is a C version of the delay loop we used in
// the blink program.  If set to optimize at level -Og, the compiler's
// generated assembly is a close match to our hand-written assembly.
// Change the level to -O2 (aggressive optimization) -- woah! what
// changed in the generated assembly? Why did that happen?
// Add volatile qualifier to the declaration of variable delay.
// How does the generated assembly change now?
// (Restore the optimization level to -Og for next exercise)
void loops(void)
{
    int delay = 0x3f00;
    while (--delay != 0) ;
}

// Part (d): pointers
// The function below accesses memory using pointer/array
// notation. The code is divided into pairs of statements
// which perform a similar operation, but have subtle differences
// (such as adding a typecast or operating on pointer of
// different pointee type). How do those differences affect
// the generated assembly?
int global;

void pointers(int n)
{
    int *ptr = &global;
    char *cptr = (char *)&global;

    *ptr = 107;      // compare to next line
    *(char *)ptr = 55;

    ptr[5] = 13;     // compare to next line
    cptr[5] = 13;

    global = *(ptr + n);  // compare to next line
    global = ptr[n];
}


void main(void)
{
}

