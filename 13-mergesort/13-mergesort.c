#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100
int isFirst = 0;
int comparisonCount = 0;
int moveCount = 0;
int sorted[SIZE]; // 추가 공간이 필요
int round = 0;

//배열 난수로 채우기
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000; // 0 ~ 999
	}
}

//출력
void printArray(int array[], int start, int end) {
	for (int i = start; i <= end; i++) {
		if (i >= 0 && i < SIZE) { 
			printf("%d ", array[i]);
		}
	}
	printf("\n");
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		comparisonCount++;
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else {
			sorted[k++] = list[j++];
		}
		moveCount++; // 이동 발생
	}

	// 남아 있는 레코드의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			moveCount++; // 이동 발생
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			moveCount++; // 이동 발생
		}
	}

	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		moveCount++; // 이동 발생
	}

	round++;
	// 10번에 한 번씩 출력
	if (round % 10 == 0 && isFirst == 0) {

		// 배열 처음부터 10개 출력
		for (int i = 0; i < 10; i++) {
			printf("%3d ", list[i]);
		}
		printf("| ");

		// 중앙 - 1부터 중앙 + 10까지 출력
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
			if (i >= 0 && i < SIZE) { // 배열 범위 체크
				printf("%d ", list[i]);
			}
		}
		printf("\n\n");
	}
}

void doMargeSort(int list[], int left, int right) {
	int width, i, mid, right_end;
	int rounds = 0; // 과정 출력 카운터

	// 너비 1부터 시작해 배열 전체 길이까지 반복
	for (width = 1; width < SIZE; width *= 2) {

		// 현재 너비만큼 왼쪽에서 오른쪽으로 이동하며 병합
		for (i = 0; i < SIZE; i += 2 * width) {
			// 왼쪽, 중간, 오른쪽 끝 계산
			mid = i + width - 1;
			right_end = i + 2 * width - 1;

			// 경계 조건 처리
			if (mid >= SIZE) break; // 중간이 배열 범위를 벗어나면 종료
			if (right_end >= SIZE) right_end = SIZE - 1; // 오른쪽 끝 조정

			merge(list, i, mid, right_end); // 병합 수행
		}
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	int totalComparisons = 0;
	int totalMoveCount = 0;
	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Merge Sort Run\n");
			doMargeSort(array, 0, SIZE - 1);
			printf("Result\n");
			printArray(array, 0, SIZE - 1);
			isFirst++;
		}
		else {
			doMargeSort(array, 0, SIZE - 1);
		}
		totalComparisons += comparisonCount;
		totalMoveCount += moveCount;
	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
	return 0;
}
