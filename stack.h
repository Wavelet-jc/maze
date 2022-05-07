#pragma once
#define Maxsize 100

typedef struct 
{
    Point data[Maxsize];
    int top;
}Stack;


int EmptyStack(const Stack *S);

//��ʼ��ջ
void InitStack(Stack *S)
{
    S->top = -1;
}

//Ԫ�ؽ�ջ
int Push(Stack *S, Point item)
{
    if (S->top == Maxsize - 1)   //ջ��
        return 0;
    S->data[++S->top] = item;
    return 1;
}

//ɾ��ջ��Ԫ��
int Pop(Stack *S)
{
    if (EmptyStack(S))   // ջ��
        return 0;
    S->top--;
    return 1;
}

//����ջ��Ԫ��
Point GetTop(const Stack *S)
{
    return S->data[S->top];
}

//�ж�ջ�Ƿ�Ϊ��
int EmptyStack(const Stack *S)
{
    return S->top == -1 ? 1 : 0;
}
//���ջ
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