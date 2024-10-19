#include <stdio.h>
#include <stdlib.h>
#define MAX 200
// 트리의 노드
typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 배열 구조체
typedef struct {
    TreeNode* data; 
    char ch;
    int key;
} element;

// Heap
typedef struct {
    element heap[MAX]; 
    int heap_size;
} HeapType;

// 힙 동적할당
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙 크기 초기화
void init(HeapType* h) {
    h->heap_size = 0; 
}

// 최소 힙에 삽입하는 함수
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size); 
    while (i != 1 && item.key < h->heap[i / 2].key) { 
        h->heap[i] = h->heap[i / 2]; 
        i /= 2; 
    }
    h->heap[i] = item; 
}

// 트리 삭제하는 함수
element delete_min_heap(HeapType* h) {
    element item = h->heap[1]; // 루트 임시 저장
    element temp = h->heap[(h->heap_size)--]; 
    int parent = 1, child = 2; 

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) {
            child++; 
        }
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 두 노드를 더한 값을 저장할 노드 생성
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 트리 삭제
void destroy_tree(TreeNode* root)
{
    if (root == NULL) return;
    destroy_tree(root->left); 
    destroy_tree(root->right); 
    free(root); 
}

// 단일 노드인지 확인하는 함수
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right); 
}

// 허프만 코드 출력
void printCodes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; 
        printCodes(root->left, codes, top + 1); 
    }
    if (root->right) {
        codes[top] = 0; 
        printCodes(root->right, codes, top + 1); 
    }
    if (is_leaf(root)) { 
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) 
            printf("%d", codes[i]);
        printf("\n");
    }
}

// 과정 출력
void print_process(HeapType* heap) {
    for (int i = 1; i <= heap->heap_size; i++) {
        printf("%d ", heap->heap[i].key); 
    }
    printf("\n");
}

// 허프만 트리 설정
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    TreeNode* node, * x; 
    HeapType* heap = create(); 
    init(heap); 
    element e, e1, e2;

    for (int i = 0; i < size; i++) {
        node = (TreeNode*)malloc(sizeof(TreeNode)); 
        node->ch = characters[i]; 
        node->weight = frequencies[i]; 
        node->left = node->right = NULL; 
        e.ch = node->ch;
        e.key = node->weight; 
        e.data = node; 
        insert_min_heap(heap, e); 
        print_process(heap); 
    }
    for (int i = 1; i < size; i++) {
        e1 = delete_min_heap(heap); 
        e2 = delete_min_heap(heap); 

        x = make_tree(e1.data, e2.data); 
        e.key = x->weight = e1.key + e2.key; 
        e.data = x;

        printf("/// %d + %d -> %d\n", e1.key, e2.key, e.key); 

        insert_min_heap(heap, e);
        print_process(heap); 
    }
    e = delete_min_heap(heap);
    return e.data;
}

// 허프만 코드를 만들고 출력
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(sizeof(int) * size); 
    int top = 0; 
    printCodes(root, arr, top); 
    destroy_tree(root);
}

main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' }; 
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 }; 
    int size = sizeof(characters) / sizeof(characters[0]); 

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
