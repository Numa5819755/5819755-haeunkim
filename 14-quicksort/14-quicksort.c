#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int comparisonCount = 0;
int moveCount = 0;
int rounds = 0;
int isFirst = 0;

//stack 구조체체
typedef struct {
    int top;
    int capacity;
    int* data;
} Stack;

// 스택 초기화
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->data = (int*)malloc(sizeof(int) * capacity);
    return stack;
}

// 스택 메모리 해제
void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// 스택이 비었는지 확인
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택에 값 추가
void push(Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->data[++stack->top] = value;
}

// 스택에서 값 꺼내기
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->data[stack->top--];
}
//배열 난수로 정의
void generateRandomArray(int* data) {
    for (int i = 0; i < SIZE; i++)
        data[i] = rand() % 1000;
}
//배열 출력
void printArray(int* data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}
//파티션 분할
int partition(int list[], int left, int right) {
    int pivot = list[left];
    int temp = 0;
    int low = left;
    int high = right + 1;

    do {
        do {
            low++;
            comparisonCount++;
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            comparisonCount++;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount += 3;
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);
    moveCount += 3;

    return high;
}
//퀵 정렬렬
void doQuickSort(int list[], int left, int right) {
    Stack* stack = createStack(SIZE);

    // 초기 범위를 스택에 푸시
    push(stack, left);
    push(stack, right);

    while (!isEmpty(stack)) {
        int right = pop(stack);
        int left = pop(stack);

        int pivot = partition(list, left, right);

        // 10번마다 40~60 위치 출력
        if (rounds % 10 == 0 && isFirst==0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", list[i]);
            }
            printf("\n\n");
        }
        rounds++;

        if (pivot - 1 > left) {
            push(stack, left);
            push(stack, pivot - 1);
        }

        if (pivot + 1 < right) {
            push(stack, pivot + 1);
            push(stack, right);
        }
    }

    freeStack(stack);
}

int main() {
    srand(time(NULL));
    int array[SIZE];
    int totalComparisons = 0;
    int totalMoveCount = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            // 정렬 결과 출력
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE-1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
