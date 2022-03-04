#include <stdio.h>

#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10


// 이제 기능이 잘 동작하기 시작했다. 나머지 기능들도 마저 구현해야 한다.

typedef struct _Stack {
    int value[MAX_STACK_SIZE];
    int p;  // point current position
} Stack;

typedef struct _Queue {
    int value[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 포인터를 만드는 대신 전역 변수로 선언해주었다.
Stack stack;
Queue queue;


int stack_arr[MAX_STACK_SIZE];
int queue_arr[MAX_QUEUE_SIZE];

// 사실 전역변수 자료구조를 사용하면 함수의 매개변수는 필요없다.
void init_stack() {
    stack.p = -1;
}
void init_queue() {
    queue.front = -1;
    queue.rear = -1;
}

// 여기도 마찬가지로 전역변수 자료구조를 사용하므로 매개변수가 필요없다.
bool push(int value) {
    if (stack.p > MAX_STACK_SIZE) { // is_stack_full
        return false;
    }

    stack.p++;
    stack.value[stack.p] = value;

    // stack 값도 이제 잘 바뀐다.
    printf("%d ", stack.value[stack.p]);
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
    init_stack();
    init_queue();

    // 이제 전역변수의 값이 성공적으로 바뀌었다.
    printf("%d ", stack.p);
    printf("%d ", queue.front);
    printf("%d ", queue.rear);

    if (!push(100)) {
        printf("Fail to push %d\n", 100);
    }

    return 0;
}
