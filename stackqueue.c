#include <stdio.h>

#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10


// 현재 이렇게 하면 에러가 난다.

typedef struct _Stack {
    int value[MAX_STACK_SIZE];
    int p;  // point current position
} Stack;

typedef struct _Queue {
    int value[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

int stack_arr[MAX_STACK_SIZE];
int queue_arr[MAX_QUEUE_SIZE];

void init_stack(Stack s) {
    s.p = -1;
}
void init_queue(Queue q) {
    q.front = -1;
    q.rear = -1;
}

// 함수 파라미터 및 호출에서 포인터를 사용하지 않았기 때문에 에러가 난다.
bool push(Stack s, int value) {
    if (s.p > MAX_STACK_SIZE) { // is_stack_full
        return false;
    }

    s.p++;
    s.value[s.p] = value;
    return true;
}
bool pop() {
    return false;
}

bool push_arr() {
    return false;
}
bool pop_arr() {
    return false;
}

int main()
{
    // 스택과 큐가 포인터가 아니어서 에러가 난다.
    Stack stack;
    Queue queue;
    
    init_stack(stack);
    init_queue(queue);


    if (!push(stack, 100)) {
        printf("Fail to push %d\n", 100);
    }

    return 0;
}
