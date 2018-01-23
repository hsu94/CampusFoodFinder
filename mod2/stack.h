typedef struct
{
    float x[50];
    int top;
} Stack;

//initialize the stack
void init(Stack *S);
//push an element to the top of the stack
void push(Stack *S, int val);
//pop the element from the top of the stack
int pop(Stack *S);


