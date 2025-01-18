#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *array;
    int size;
    int capacity;
}Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (int*)malloc(sizeof(int) * capacity);

    return heap;
}

void swap(int*a, int*b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }

    if(right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }

    if(largest != i) {
        swap(&heap->array[i], &heap->array[largest]);
        heapify(heap, largest);
    }

}

void buildHeap(Heap* heap) {
    int n = heap->size;

    for(int i = (n-1)/2; i >= 0; i--) {
        heapify(heap, i);
    }
}

void insertHeap(Heap* heap, int value) {
    heap->size++;

    int i = heap->size-1;

    heap->array[i] = value;

    while(i != 0 && heap->array[(i-1)/2] < heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i-1)/2]);
        i = (i-1)/2;
    }

}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
