#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 랜덤 배열 생성
void generateRandomNumbers(int array[]) {
    srand((unsigned int)time(0));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0 ~ 999
    }
}

// 배열 출력
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%03d ", list[i]);
    }
    printf("\n\n");
}

// 삽입 정렬 (단일 갭 사용)
void inc_insertion_sort(int list[], int first, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;
    for (i = first + gap; i < ARRAY_SIZE; i += gap) {
        key = list[i];
        (*moveCount)++; // key 값을 temp에 저장
        for (j = i - gap; j >= first; j -= gap) {
            (*comparisonCount)++; // 비교 수행
            if (list[j] > key) {
                list[j + gap] = list[j];
                (*moveCount)++; // 값 이동
            }
            else {
                break;
            }
        }
        list[j + gap] = key;
        (*moveCount)++; // key 값을 삽입
    }
}

// 쉘 정렬
void doShellSort(int array[], int gap_unit, int* comparisonCount, int* moveCount) {
    int gap = ARRAY_SIZE / gap_unit;

    *comparisonCount = 0;
    *moveCount = 0;
    
    //원본유지
    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) tempArray[i] = array[i];

    while (gap > 0) {
        printf("Sorting with gap = %d\n", gap);

        for (int i = 0; i < gap; i++) {
            inc_insertion_sort(tempArray, i, gap, comparisonCount, moveCount);
        }

        print_list(tempArray, 20); // 정렬 진행 상황 출력 (앞 20개)
        gap /= gap_unit;
    }
    printf("Sorted shellArray (gap = %d):\n",gap_unit);
    print_list(tempArray, ARRAY_SIZE);
}

// 삽입 정렬
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    *comparisonCount = 0;
    *moveCount = 0;
    //원본 유지
    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) tempArray[i] = array[i];

    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = tempArray[i];
        (*moveCount)++; // key 값을 temp에 저장
        int j = i - 1;

        while (j >= 0) {
            (*comparisonCount)++; // 비교 수행
            if (tempArray[j] > key) {
                tempArray[j + 1] = tempArray[j];
                (*moveCount)++; // 값 이동
                j--;
            }
            else {
                break;
            }
        }
        tempArray[j + 1] = key;
        (*moveCount)++; // key 값을 삽입
    }
    printf("Sorted insertionArray:\n");
    print_list(tempArray, ARRAY_SIZE);
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    // shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
