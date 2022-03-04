#include <stdio.h>

#define MAX_STACK_SIZE 10
#define MAX_QUEUE_SIZE 10


// 현재 이렇게 하면 에러는 안나지만 기능이 제대로 동작하지 않는다.

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

// 잘 보면, 함수 내의 지역변수(멤버) 값만 바꾸고 있다. 전역변수값이 바뀌는게 아니다. 
void init_stack(Stack s) {
    s.p = -1;
}
void init_queue(Queue q) {
    q.front = -1;
    q.rear = -1;
}

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
    init_stack(stack);
    init_queue(queue);

    // 값이 제대로 바뀌어 출력되지 않는다. (쓰레기값이 아닌 0이 나오는 이유는 전역변수는 기본값으로 초기화되기때문)
    printf("%d ", stack.p);
    printf("%d ", queue.front);
    printf("%d ", queue.rear);

    if (!push(stack, 100)) {
        printf("Fail to push %d\n", 100);
    }

    return 0;
}
