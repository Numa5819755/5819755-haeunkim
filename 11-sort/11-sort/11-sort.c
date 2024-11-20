#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 100

void generateRandomData(int* data) {
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
		data[i] = rand() % 1000;
}

// 배열 출력
void printArray(int* data) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void doSelectionSort(int* data) {
    int data_sort[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data_sort[i] = data[i];
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (data_sort[j] < data_sort[minIndex]) {
                minIndex = j;
            }
        }
        int temp = data_sort[minIndex];
        data_sort[minIndex] = data_sort[i];
        data_sort[i] = temp;

        // 10부터 20 단위로 출력
        if ((i + 1) == 10 || ((i + 1) > 10 && ((i + 1) - 10) % 20 == 0) || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            printArray(data_sort);
            printf("\n");
        }
    }
}

void doInsertionSort(int* data) {
    int totalComparisons = 0;
    int data_sort[SIZE];

    for (int trial = 0; trial < 20; trial++) {
        // 배열 복사
        for (int i = 0; i < SIZE; i++) {
            data_sort[i] = data[i];
        }

        int comparisons = 0;
        // 삽입 정렬
        for (int i = 1; i < SIZE; i++) {
            int key = data_sort[i];
            int j = i - 1;
            while (j >= 0 && data_sort[j] > key) {
                data_sort[j + 1] = data_sort[j];
                j--;
                comparisons++;
            }
            data_sort[j + 1] = key;
            comparisons++; // 마지막 비교 포함
        }

        totalComparisons += comparisons;
    }

    // 평균 비교 횟수 출력
    printf("\nInsertion Sort Compare Average: %d\n", totalComparisons / 20);

    // 최종 정렬 결과 출력
    printf("Insertion Sort Result:\n");
    printArray(data_sort);
}

void doBubbleSort(int* data) {
    int totalMoves = 0;
    int data_sort[SIZE];

    for (int trial = 0; trial < 20; trial++) {
        for (int i = 0; i < SIZE; i++) {
            data_sort[i] = data[i];
        }

        int moves = 0;
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (data_sort[j] > data_sort[j + 1]) {
                    int temp = data_sort[j];
                    data_sort[j] = data_sort[j + 1];
                    data_sort[j + 1] = temp;
                    moves += 3; // 값 이동 3회로 계산
                }
            }
        }
        totalMoves += moves;
    }

    printf("\nBubble Sort Move Average: %d\n", totalMoves / 20);
    printf("Bubble Sort Result:\n");
    printArray(data_sort);
}

int main() {
	int randomData[SIZE];
	generateRandomData(randomData);
	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);
	return 0;
}
