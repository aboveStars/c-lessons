#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Heap {
    int* array;
    int size;
    int capacity;
}Heap;


Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));

    heap->array = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void swap(int* a, int*b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void insertHeap(Heap* heap, int value) {
    if(heap->size == heap->capacity) {
        printf("Heap is full");
        return;
    }

    heap->size++;

    int index = heap->size-1;

    heap->array[index] = value;

    while(index != 0 && heap->array[index] > heap->array[(index-1)/2]) {
        swap(&heap->array[index], &heap->array[(index-1)/2]);
        index = (index-1)/2;
    }
}

// From top to bottom.
void heapify(Heap* heap, int index) {
    int largest = index;
    int left = (index*2)+1;
    int right = (index*2)+2;

    if(largest < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }

    if(largest < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }

    if(index != largest) {
        swap(&heap->array[index], &heap->array[largest]);
        heapify(heap, largest);
    }


}

void buildHeap(Heap *heap) {
    int n = heap->size;

    for(int i = (n-1)/2; i>=0; i--) {
        heapify(heap, i);
    }
}

void printHeap(Heap* heap) {
    for(int i=0; i< heap->size; i++) {
        printf("%d ", heap->array[i]);
    }

    printf("\n");
}

void increaseKey(Heap* heap, int key, int newValue) {
    if(key > heap->size-1) {
        printf("Key exceeded");
        return;
    }

    if(heap->array[key] >= newValue) {
        printf("New Value is not bigger.");
        return;
    }

    heap->array[key] = newValue;

    while(key != 0 && heap->array[key] > heap->array[(key-1)/2]) {
        swap(&heap->array[key], &heap->array[(key-1)/2]);
        key = (key-1)/2;
    }
}

int extractMax(Heap* heap) {
    if(heap->size == 0) {
        printf("Heap is empty");
        return INT_MIN;
    }

    if(heap->size == 1) {
        heap->size = 0;
        return INT_MIN;
    }

    int root = heap->array[0];

    heap->array[0] = heap->array[heap->size-1];
    heap->size--;

    heapify(heap, 0);

    return root;
}

void deleteElement(Heap* heap, int index) {
    if(heap->size >= index) {
        printf("Invalid index to delete.");
        return;
    }

    heap->array[index] = heap->array[heap->size-1];
    heap->size--;

    heapify(heap, index);

}

int lesson1_maxHeap() {
    Heap* heap = createHeap(10);
    insertHeap(heap, 3);
    insertHeap(heap, 2);
    insertHeap(heap, 15);
    insertHeap(heap, 5);
    insertHeap(heap, 4);
    insertHeap(heap, 45);

    printf("Max Heap array: ");
    printHeap(heap);

    printf("Extracted max value: %d\n",
           extractMax(heap));
    printf("Max Heap array after extraction: ");
    printHeap(heap);

    free(heap->array);
    free(heap);
    return 0;
}