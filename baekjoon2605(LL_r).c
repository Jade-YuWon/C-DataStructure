#include <stdio.h>
#include <stdlib.h>

/* Referenced(Clone coding) version - In progress 
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
void list_insert(List *plist, int number, int pick);
int list_get_first_data(List *plist, int *pdata);
int list_get_next_data(List *plist, int *pdata);
int list_get_data(List *plist);

int main()
{
    int num;
    int arr[100];
    
    scanf("%d", &num);
    
    for (int i=0; i<num; i++) {
        scanf("%d", &arr[i]);
    }
    
    List *list = (List*)malloc(sizeof(List));
    list_init(list);
    
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

void list_insert(List *plist, int number, int pick) {
    Node *tmp;
    Node *new = (Node*)malloc(sizeof(Node));
    new->number = number;
    new->prev = NULL;
    
    if (plist->head == NULL && pick == 0) {
        
    }
    else if (plist->head != NULL && pick == 0) {
    
    }
    else if (plist->head != NULL && pick > 0) {
    
    }
}

int list_get_first_data(List *plist, int *pdata) {
    
}

int list_get_next_data(List *plist, int *pdata) {
    
}

int list_get_data(List *plist) {
    
}
