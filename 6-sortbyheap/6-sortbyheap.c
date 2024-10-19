#include <stdio.h>
#include <stdlib.h>

// 값을 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙을 재정렬하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i;        // 현재 노드를 가장 큰 노드로 가정
    int left = 2 * i + 1;   // 왼쪽 자식의 인덱스
    int right = 2 * i + 2;  // 오른쪽 자식의 인덱스

    // 왼쪽 자식>부모
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;  // 가장 큰 노드를 왼쪽 자식으로 갱신
    }

    // 오른쪽 자식>부모
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;  // 가장 큰 노드를 오른쪽 자식으로 갱신
    }

    // 큰 노드!=부모 --> swap, 재귀 호출로 힙을 재정렬
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);  // 부모 노드와 가장 큰 자식 노드의 값 교환
        resortHeap(inputData, n, largest);        // 힙 재정렬
    }
}

// 힙을 구성하는 함수
void BuildMaxHeap(int inputData[], int n) {
    // index의 크기를 늘려가며 힙을 재정렬
    for (int i = 1; i <= n; i++) {
        for (int j = i / 2 - 1; j >= 0; j--) {
            resortHeap(inputData, i, j);
        }
        // 현재 힙 상태를 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// 힙을 정렬하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);  // 최대 힙 생성

    // 힙의 최대값를 하나씩 제거하여 배열을 정렬
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);  // 최대값을 배열의 끝으로 이동
        resortHeap(inputData, i, 0);

        // 힙 재정렬 후 현재 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };  // 입력 데이터 배열
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);  // 최대 힙을 구성하고 정렬

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
