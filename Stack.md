# Intro - Stack
- I'll overcome my DS-phobia in Winter Vacation __NO MATTER WHAT__ happens.
- The First step is STACK 🥞<br>
※ This document could be inaccurate because I'm beginner of learning CS. <br>
🙏 Please notify me of the error or edit this file if you discover. 

## Concept of Stack
- LIFO (Last In, First Out)
  - Pancakes🥞, Pringles, stack of books, boxes, plates, etc

## Application of STACK
- Memory stack
- Abstract Data structure STACK (in heap area)

## Create STACK
### Two Methods
1. Array (More Easy Way)
2. Linked List

### Operation
1. C
    1. Create Stack 
3. R
    1. Peek (Top)
    2. _Traverse_ - ???
5. U
    1. __Push__
    7. __Pop__ 
7. D
    1. Delete
4. Other
    1. Size (Calculate Size)

## 
``` C
int stack[STACK_SIZE];
int index = -1;

```

## Difficulties
### Array Linked List
1. string initializer
``` C
char str[6] = 0;  //Wrong ? <Web Compiler>
// Substitute
char str[6] = "";
```
2. Switch-case (Long time no see!): I forget to use only a constant or character value in 'case'. But I used a string value.
    - Solution
    1. Compare only first case of a string
        - Fail: 'P'ush and 'P'op crash 
    2. Delete Switch-case statement and use strcmp instead (#include <string.h> and #include <stdlib.h>)
        - Great, but I'd have __strcmp's return values__ more exactly
3. __strcmp(s1, s2) return values__: my if statements are malfunctioning becuase of the conditional statements.
    1. if s1 == s2: returns 0
    2. if s1 > s2: returns 1 (or >0)
    2. if s1 < s2: returns -1 (or <0)
    - C Language's Logical Value
        - 0 -> False
        - \>0 or <0 -> True
        - True -> 1
        - False -> 0 
 

```C
#include <stdio.h>

int main() {
    int num = strcmp("push", "push");
    
    printf("num = %d\n", num);
    printf("!num = %d\n\n", !num);

    num = 1;
    printf("num = %d\n", num);
    printf("!num = %d\n\n", !num);
    num = 2;
    printf("num = %d\n", num);
    printf("!num = %d\n\n", !num);

    num = -1;
    printf("num = %d\n", num);
    printf("!num = %d\n\n", !num);
    num = -2;
    printf("num = %d\n", num);
    printf("!num = %d\n\n", !num);

    return 0;
}
```

> num = 0 <br>
> !num = 1 <br>
> 
> num = 1 <br>
> !num = 0 <br>
> 
> num = 2 <br>
> !num = 0 <br>
> 
> num = -1 <br>
> !num = 0 <br>
> 
> num = -2 <br>
> !num = 0 <br>

