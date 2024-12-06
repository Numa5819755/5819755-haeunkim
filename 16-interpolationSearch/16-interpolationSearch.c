#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

//배열 출력
void printArray(int* array) {
	printf("\nArray Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
}

//배열 랜덤 정의
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000; // 0 ~ 9999
	}
}

//quicksort 파티션
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}
//퀵정렬 구현
QuickSort(int array[], int left, int right) {
	if (left < right) {
		int q = partition(array, left, right);
		QuickSort(array, left, q - 1);
		QuickSort(array, q + 1, right);
	}
}

//이진탐색 1회 count반환 
int search_binary2(int list[], int key, int low, int high)
{
	int middle;
	int count = 0;
	while (low <= high) { 				// 아직 숫자들이 남아 있으면
		middle = (low + high) / 2;
		count++;
		if (key == list[middle]) {
			return count; 	// 탐색 성공
		}
		else {
			count++;
			if (key > list[middle]) low = middle + 1;// 왼쪽 부분리스트 탐색
			else high = middle - 1; 			// 오른쪽 부분리스트 탐색
		}
	}
	return -1; 					// 탐색 실패
}
//이진탐색 count 평균 반환
float getAverageBinarySearchCompareCount(int array[]) {
	int count = 0;
	int target;
	for (int i = 0; i < 1000; i++) {
		target = array[rand() % SIZE];
		count += search_binary2(array, target, 0, SIZE - 1);
	}
	return (float)count / 1000;
}
//보간탐색 1회 count 반환
int interpol_search(int list[], int key, int n)//보간탐색
{
	int count = 0;
	int low, high, j;

	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) {
			count++;//비교횟수 증가
			low = j + 1;
		}
		else if (key < list[j]) {
			count++;
			high = j - 1;
		}
		else{
			count++;
			low = j;
		}
	}
	count++;
	if (list[low] == key) return count;  // 탐색성공
	else return -1;  // 탐색실패
}
//보간탐색 평균 count 반환
float getAverageInterpolationSearchComparecount(int array[]) {
	int count = 0;
	int target;
	for (int i = 0; i < 1000; i++) {
		target = array[rand() % SIZE];
		count += interpol_search(array, target, SIZE);
	}
	return (float)count / 1000;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
		generateRandomArray(array);
		QuickSort(array, 0, SIZE - 1);
		printArray(array);
		printf("Average Compare Count of Binary Search: %.2f\n",
			getAverageBinarySearchCompareCount(array));
		printf("Average Compare Count of Interpolation Search: %.2f\n",
			getAverageInterpolationSearchComparecount(array));
	return 0;
}