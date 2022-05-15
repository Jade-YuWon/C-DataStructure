# Dynamic Memory Allocation
### Malloc()
- Reservers the number of bytes requested by the argument passed to the function.
  - Malloc() 함수에 인수로 전달된 수 만큼의 바이트들을 reserve한다.
- Returns the address of the first reserved location, as an address of a void data type.
  - Malloc() 함수의 반환값은 reserve된 위치의 첫 주소이고, void 타입의 주소이다.
- Otherwise, returns NULL if sufficient memory is not available.
  - 또는 충분한 메모리를 reserve할 수 없을 때는 NULL을 반환한다.
### free()
- Release a block of bytes previously reserved.
- The address of the first reserved location is passed as an argument to the function.

------------
- malloc(), calloc() 모두 실무에서 자주 번갈아 사용하지만 malloc()이 좀 더 일반적 목적으로 사용됨.
- malloc 시 필요한 저장 공간의 수량을 나타내줘야 함 (수 또는 공간의 크기sizeof()로)
- 배열과 구조체의 동적 할당은 더욱 유용하게 사용됨
- malloc() 인자(argument)로 변수(variable)나 상수(constant), symbolic constant도 사용할 수 있음
- malloc으로 할당된 공간은 컴퓨터의 'free storage area, 즉 **heap**'으로 불리는 곳으로부터 온다.
- 그렇게 할당된 모든 메모리들은 heap으로 return되는데, 명시적으로 free() 함수를 사용하여 return할 수 있다. 자동으로 return되는 경우는 (다른) 추가적 메모리를 필요로 하고 있던 프로그램이 실행을 종료했을 때이다.
- 배열식으로 malloc했을 때 배열식 인덱싱이 가능하다. (중요)

``` C
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numgrades = 123;
    int i;
    int *grades;
    
    grades = (int*)malloc(numgrades*sizeof(int));
    
    if (grades==(int*)NULL) {
        printf("\nFailed to allocate grades array\n");
        exit(1);
    }
    
    for (i = 0; i<numgrades; i++) {
        grades[i]
    }
    free(grades);
    return 0;
}
```
