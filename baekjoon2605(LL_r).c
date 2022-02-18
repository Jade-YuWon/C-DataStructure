#include <stdio.h>
#include <stdlib.h>

/* Referenced version completed
* Resource of reference :
* https://www.acmicpc.net/source/39137587
*/

typedef struct _node {
    int number;
    struct _node *prev;
    struct _node *next;
} Node;

typedef struct _list {
    Node *head;
    Node *tail;
    Node *cur;
} List;

void list_init(List *plist);
void list_insert(List *plist, int number, int move);

int main() {
    int num;
    int arr[100];
    List *list = (List*)malloc(sizeof(List));
    list_init(list);
    
    scanf("%d", &num);
    
    for (int i=0; i<num; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (int i=0; i<num; i++) {
        Node *new = (Node*)malloc(sizeof(Node));
        list_insert(list, i+1, arr[i]);
    }
    
    list->cur = list->head;
    while (list->cur != NULL) {
        printf("%d ", list->cur->number);
        list->cur = list->cur->next;
    }
    
    return 0;
}

void list_init(List *plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->cur = NULL;
}

void list_insert(List *plist, int number, int move) {
    Node *tmp;
    Node *new = (Node*)malloc(sizeof(Node));
    new->number = number;
    new->prev = NULL;
    
    if (plist->head == NULL && move == 0) {
        plist->head = new;
        plist->tail = new;
    }
    else if (plist->head != NULL && move == 0) {
        plist->tail->next = new;
        new->prev = plist->tail;
        plist->tail = new;
    }
    else if (plist->head != NULL && move > 0) {
        plist->cur = plist->tail;
        for (int i=0; i<move; i++) {
            plist->cur = plist->cur->prev;
        }
        
        if (plist->cur == NULL) {
            plist->head->prev = new;
            new->next = plist->head;
            plist->head = new;
        } else {
            new->next = plist->cur->next;
            plist->cur->next->prev = new;
            plist->cur->next = new;
            new->prev = plist->cur;
        }
    }
}
