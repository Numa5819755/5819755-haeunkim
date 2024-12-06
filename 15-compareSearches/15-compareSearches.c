#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 1000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int compareCount;
int left = 0;
int right = SIZE - 1;

//배열출력함수
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

// 랜덤 배열 생성
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
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

//순차 탐색
int seq_search(int list[], int target)
{
	int i;
	for (i = 0; i < SIZE; i++) {
		if (list[i] == target)
			return i+1; // 탐색 성공 | i가 0부터 시작so +1
	}
	return i+1;    	// 탐색 실패 가능성x
}

//순차탐색 평균횟수
float getAverageLinearSearchCompareCount(int array[]) {
	//횟수
	int r = 0;
	int count = 0;
	while (r < 100) {
		int target = array[rand() % SIZE];
		count += seq_search(array, target);//seq_serch에서 비교횟수를 받아 count에 중첩
		r += 1;
	}
	return (float)count / 100;//평균 비교횟수 반환
}

//파티션
int partition(int list[], int left, int right)
{
	int pivot = list[left];
	int temp = 0;
	int low = left;
	int high = right + 1;
	do {
		do {
			low++;
			compareCount++;
		} while (low <= right && list[low] < pivot);

		do {
			high--;
			compareCount++;
		} while (high >= left && list[high] > pivot);

		if (low < high) {
			SWAP(list[low], list[high], temp);
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void doQuickSort(int* data, int left, int right) {
	if (left < right) {
		int q = partition(data, left, right);
		doQuickSort(data, left, q - 1);
		doQuickSort(data, q + 1, right);
	}
}
//퀵 정렬
void getQuickSortCompareCount(int array[]) {
	if (left < right) {
		int q = partition(array, left, right);
		doQuickSort(array, left, q - 1);
		doQuickSort(array, q + 1, right);
	}
}

int search_binary(int* list[], int key, int low, int high)
{
	int count = 0;
	int middle;
	while (low <= high) { 				// 아직 숫자들이 남아 있으면
		middle = (low + high) / 2;
		if (key == list[middle]) {
			count++;//비교횟수 증가
			return count; 	// 탐색 성공
		}
		else if (key > list[middle]) {
			count++;//비교횟수 증가
			low = middle + 1; 	// 왼쪽 부분리스트 탐색
		}
		else {
			count++;
			high = middle - 1; 			// 오른쪽 부분리스트 탐색
		}
	}
	return count; 					// 탐색 실패
}

float getAverageBinarySearchCompareCount(int array[]) {
	//횟수
	int r = 0;
	int count = 0;
	while (r < 100) {
		int target = array[rand() % SIZE];
		count += search_binary(array, target, 0, SIZE-1);//search_binary에서 비교횟수를 반환받아 count에 중첩
		r += 1;
	}
	return (float)count / 100;//평균 비교횟수 반환
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	//평균값을 반환받기 위한 조치
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));
	//compareCount가 global variable이므로, 다음과 같이 구현
   //array에 대해서 직접 정렬하면 된다.
	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);
	//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array));
	printArray(array);
	return 0;
}