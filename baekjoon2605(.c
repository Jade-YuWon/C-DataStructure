#include <stdio.h>

int main()
{
    int student_n;
    int line[100];
    int move[100];
    
    scanf("%d", &student_n);
    for (int i=0; i<student_n; i++) {
        line[i] = i+1;
        scanf("%d", move+i);
    }
    
    // test code
    /*
    printf("array before ordering:\n");
    for (int i=0; i<student_n; i++) {
        printf("%d ", line[i]);
    }
    */
    
    for (int i=0; i<student_n; i++) {
        if (move[i]==0) {
            continue;
        }
        int m = move[i];
      
        int tmp = line[i];
        for (int j=i; j>=i-m; j--) {
            line[j] = line[j-1];
        }
        line[i-m] = tmp;
    }
  
    /*
    printf("\n\nAnswer(array after ordering):\n");
    */
    for (int i=0; i<student_n; i++) {
        printf("%d ", line[i]);
    }
    
    return 0;
}
