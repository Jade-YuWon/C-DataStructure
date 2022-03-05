#include <stdio.h>

#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10


// 구조체 전역변수 자료구조, int 배열 전역변수 자료구조를 구현하였고, is~ 함수만 따로 선언해주면 된다.

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

// Version 2 (arr ver.)
int stack_arr[MAX_STACK_SIZE];
int p = -1;  // point current stack position
int queue_arr[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

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
    // 포지션 증가가 is_stack_full 이후에 일어나므로, 비교할 대상이 MAX - 1 이어야 한다.
    if (stack.p >= MAX_STACK_SIZE - 1) { // is_stack_full
        return false;
    }
    stack.p++;
    stack.value[stack.p] = value;

    // stack 값도 이제 잘 바뀐다.
    printf("%d ", stack.value[stack.p]);
    return true;
}
bool pop() {
    if (stack.p < 0) { // is_stack_empty
        return false;
    }

    printf("%d poped.. ", stack.value[stack.p]);
    stack.p--;
    
    return true;
}
bool enqueue(int value) {
    // Non-circular Queue
    if (queue.rear >= MAX_QUEUE_SIZE - 1) { // is_queue_full
        return false;
    }
    if (queue.front < 0) {
        queue.front = 0;
    }
    queue.rear++;
    queue.value[queue.rear] = value;
    printf("%d ", queue.value[queue.rear]);
    return true;
}
bool dequeue() {
    if (queue.front > queue.rear) { // is_queue_empty
        return false;
    }
    printf("%d dequeued.. ", queue.value[queue.front]);
    queue.front++;
    return true;
}

bool push_arr(int value) {
    if (p >= MAX_STACK_SIZE - 1) { // is_stack_arr_full
        return false;
    }
    p++;
    stack_arr[p] = value;

    printf("%d ", stack_arr[p]);
    return true;
}
bool pop_arr() {
    if (stack.p < 0) { // is_stack_empty
        return false;
    }
    printf("%d poped.. ", stack.value[stack.p]);
    stack.p--;
    return true;
}
bool enqueue_arr(int value) {
    // Non-circular Queue
    if (rear >= MAX_QUEUE_SIZE - 1) { // is_queue_arr_full
        return false;
    }
    if (front < 0) {
        front = 0;
    }
    rear++;
    queue_arr[rear] = value;
    printf("%d ", queue_arr[rear]);
    return true;
}
bool dequeue_arr() {
    if (front > rear) { // is_queue_arr_empty
        return false;
    }
    printf("%d dequeued.. ", queue_arr[front]);
    front++;
    return true;
}

int main()
{
    init_stack();
    init_queue();
    // 이제 전역변수의 값이 성공적으로 바뀌었다.
    printf("%d ", stack.p);
    printf("%d ", queue.front);
    printf("%d \n", queue.rear); 
    
    printf("%d ", p);
    printf("%d ", front);
    printf("%d \n", rear);

    // push 인덱스를 MAX와 같을 때까지 넣는다. 마지막에 같아질 때는 push에 실패한다.
    // (따라서 인덱스 0 시작을 기준으로 할 때는 i<MAX (같아지기 직전) 까지만 넣어야 한다.)
    for (int v = 0; v <= MAX_STACK_SIZE; v++) {
        if (!push(v * 100)) {
            printf("Fail to push %d\n", v * 100);
        }
    }
    while (1) {
        if (!pop()) {
            printf("Fail to pop\n");
            break;
        }
    }

    for (int v = 0; v <= MAX_STACK_SIZE; v++) {
        if (!enqueue(v * 100)) {
            printf("Fail to enqueue %d\n", v * 100);
        }
    }
    while (1) {
        if (!dequeue()) {
            printf("Fail to dequeue\n");
            break;
        }
    }

    for (int v = 0; v <= MAX_STACK_SIZE; v++) {
        if (!push_arr(v * 100)) {
            printf("Fail to push %d\n", v * 100);
        }
    }
    while (1) {
        if (!pop_arr()) {
            printf("Fail to pop\n");
            break;
        }
    }

    for (int v = 0; v <= MAX_STACK_SIZE; v++) {
        if (!enqueue_arr(v * 100)) {
            printf("Fail to enqueue %d\n", v * 100);
        }
    }
    while (1) {
        if (!dequeue_arr()) {
            printf("Fail to dequeue\n");
            break;
        }
    }


    return 0;
}
