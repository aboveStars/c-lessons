#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int* array;
    int size;
    int capacity;
}Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    heap->array= (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void swap(int*a, int*b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void insertHeap(Heap* heap, int value) {
    if(heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }

    heap->size++;

    int index = heap->size - 1;

    heap->array[index] = value;

    while(index != 0 && heap->array[index] > heap->array[(index-1)/2]) {
        // Swap
        swap(&heap->array[index], &heap->array[(index-1)/2]);
        // Re-Assign
        index = (index-1)/2;
    }
}

void printHeap(Heap* heap) {
    for(int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

void heapify(Heap* heap, int index) {

    if(!heap) return;

    int largest = index;
    int left = (index*2) + 1;
    int right = (index*2) + 2;

    if(left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }

    if(index != largest) {
        swap(&heap->array[index], &heap->array[largest]);
        heapify(heap, largest);
    }
}

void buildHeap(Heap* heap) {
    int size = heap->size;

    for(int i = (size-1)/2; i>=0; i++) {
        heapify(heap, i);
    }
}

void sortHeap(Heap* heap) {

    if(!heap) return;

    const int size = heap->size;

    for(int i=0; i < size; i++) {
        swap(&heap->array[0], &heap->array[heap->size-1]);
        heap->size--;
        heapify(heap, 0);
    }
}

void printArray(int* array, int capacity) {
    for(int i = 0; i < capacity; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int lesson_2_heapSort() {

    Heap* heap = createHeap(10);

    insertHeap(heap, 9);
    insertHeap(heap, 4);
    insertHeap(heap, 3);

    insertHeap(heap, 8);
    insertHeap(heap, 10);

    insertHeap(heap, 2);
    insertHeap(heap, 5);

    printHeap(heap);

    sortHeap(heap);

    printArray(heap->array, 7);

    free(heap);

    return 0;

}
