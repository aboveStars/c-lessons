#include "../include/min_heap.h"

// Helper function to get index of parent node
static size_t get_parent(size_t index) {
    return (index - 1) / 2;
}

// Helper function to get index of left child
static size_t get_left_child(size_t index) {
    return 2 * index + 1;
}

// Helper function to get index of right child
static size_t get_right_child(size_t index) {
    return 2 * index + 2;
}

// Helper function to swap two elements in the heap
static void swap_elements(MinHeap* heap, size_t i, size_t j) {
    char temp[heap->element_size];
    char* data = (char*)heap->data;

    memcpy(temp, data + i * heap->element_size, heap->element_size);
    memcpy(data + i * heap->element_size, data + j * heap->element_size, heap->element_size);
    memcpy(data + j * heap->element_size, temp, heap->element_size);
}

// Helper function to bubble up an element to maintain heap property
static void bubble_up(MinHeap* heap, size_t index) {
    char* data = (char*)heap->data;

    while (index > 0) {
        size_t parent = get_parent(index);
        if (heap->compare(data + index * heap->element_size,
                         data + parent * heap->element_size) < 0) {
            swap_elements(heap, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

// Helper function to bubble down an element to maintain heap property
static void bubble_down(MinHeap* heap, size_t index) {
    char* data = (char*)heap->data;
    size_t smallest = index;

    while (1) {
        size_t left = get_left_child(index);
        size_t right = get_right_child(index);

        if (left < heap->size &&
            heap->compare(data + left * heap->element_size,
                         data + smallest * heap->element_size) < 0) {
            smallest = left;
        }

        if (right < heap->size &&
            heap->compare(data + right * heap->element_size,
                         data + smallest * heap->element_size) < 0) {
            smallest = right;
        }

        if (smallest != index) {
            swap_elements(heap, index, smallest);
            index = smallest;
        } else {
            break;
        }
    }
}

MinHeap* heap_create(size_t capacity, size_t element_size,
                    int (*compare)(const void*, const void*)) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;

    heap->data = malloc(capacity * element_size);
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->element_size = element_size;
    heap->capacity = capacity;
    heap->size = 0;
    heap->compare = compare;

    return heap;
}

void heap_destroy(MinHeap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

int heap_insert(MinHeap* heap, const void* element) {
    if (heap->size == heap->capacity) {
        // Double the capacity
        size_t new_capacity = heap->capacity * 2;
        void* new_data = realloc(heap->data, new_capacity * heap->element_size);
        if (!new_data) return 0;

        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    // Add new element at the end
    char* data = (char*)heap->data;
    memcpy(data + heap->size * heap->element_size, element, heap->element_size);

    // Bubble up the new element
    bubble_up(heap, heap->size);
    heap->size++;

    return 1;
}

int heap_extract_min(MinHeap* heap, void* result) {
    if (heap->size == 0) return 0;

    // Copy root element to result
    memcpy(result, heap->data, heap->element_size);

    // Move last element to root and bubble down
    heap->size--;
    if (heap->size > 0) {
        memcpy(heap->data,
               (char*)heap->data + heap->size * heap->element_size,
               heap->element_size);
        bubble_down(heap, 0);
    }

    return 1;
}

int heap_peek(const MinHeap* heap, void* result) {
    if (heap->size == 0) return 0;

    memcpy(result, heap->data, heap->element_size);
    return 1;
}

size_t heap_size(const MinHeap* heap) {
    return heap->size;
}

int heap_merge(MinHeap* heap1, const MinHeap* heap2) {
    // Check if heaps are compatible
    if (heap1->element_size != heap2->element_size ||
        heap1->compare != heap2->compare) {
        return 0;
    }

    // Ensure heap1 has enough capacity
    size_t required_capacity = heap1->size + heap2->size;
    if (required_capacity > heap1->capacity) {
        size_t new_capacity = required_capacity * 2;
        void* new_data = realloc(heap1->data, new_capacity * heap1->element_size);
        if (!new_data) return 0;

        heap1->data = new_data;
        heap1->capacity = new_capacity;
    }

    // Copy all elements from heap2 to heap1
    char* data1 = (char*)heap1->data;
    char* data2 = (char*)heap2->data;

    for (size_t i = 0; i < heap2->size; i++) {
        memcpy(data1 + (heap1->size + i) * heap1->element_size,
               data2 + i * heap2->element_size,
               heap2->element_size);
    }

    // Rebuild heap1 to maintain heap property
    heap1->size += heap2->size;
    for (size_t i = heap1->size / 2; i > 0; i--) {
        bubble_down(heap1, i - 1);
    }

    return 1;
}