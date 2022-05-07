#pragma once
#define Maxsize 100

typedef struct 
{
    Point data[Maxsize];
    int top;
}Stack;


int EmptyStack(const Stack *S);

//³õÊ¼»¯Õ»
void InitStack(Stack *S)
{
    S->top = -1;
}

//ÔªËØ½øÕ»
int Push(Stack *S, Point item)
{
    if (S->top == Maxsize - 1)   //Õ»Âú
        return 0;
    S->data[++S->top] = item;
    return 1;
}

//É¾³ýÕ»¶¥ÔªËØ
int Pop(Stack *S)
{
    if (EmptyStack(S))   // Õ»¿Õ
        return 0;
    S->top--;
    return 1;
}

//·µ»ØÕ»¶¥ÔªËØ
Point GetTop(const Stack *S)
{
    return S->data[S->top];
}

//ÅÐ¶ÏÕ»ÊÇ·ñÎª¿Õ
int EmptyStack(const Stack *S)
{
    return S->top == -1 ? 1 : 0;
}
//Çå¿ÕÕ»
void Clear(Stack *S)
{
    for (int i = 0; i <= S->top; ++i)
    {
        Pop(S);
    }
}

int StackLength(const Stack* S)
{
    return S->top+1;
}

void PrintStack(const Stack* S)
{
    for (int i = 0; i <= S->top; i++) {
        printf(" <%d,%d> ", S->data[i].x, S->data[i].y);
    }
}