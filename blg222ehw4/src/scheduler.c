#include "../include/scheduler.h"

// Comparison function for processes based on virtual runtime
static int compare_processes(const void* a, const void* b) {
    const Process* p1 = (const Process*)a;
    const Process* p2 = (const Process*)b;

    // Compare virtual runtimes
    if (p1->vruntime < p2->vruntime) return -1;
    if (p1->vruntime > p2->vruntime) return 1;

    // If virtual runtimes are equal, use PID as tiebreaker
    return p1->pid - p2->pid;
}

Scheduler* create_scheduler(int capacity) {
    if (capacity <= 0) return NULL;

    Scheduler* scheduler = (Scheduler*)malloc(sizeof(Scheduler));
    if (!scheduler) return NULL;

    // Initialize min heap for process queue
    scheduler->process_queue = heap_create(capacity, sizeof(Process), compare_processes);
    if (!scheduler->process_queue) {
        free(scheduler);
        return NULL;
    }

    scheduler->current_process = NULL;
    scheduler->time_slice = 100; // Default time slice of 100ms

    return scheduler;
}

void destroy_scheduler(Scheduler* scheduler) {
    if (!scheduler) return;

    // Free the process queue
    if (scheduler->process_queue) {
        heap_destroy(scheduler->process_queue);
    }

    // Free current process if exists
    if (scheduler->current_process) {
        free(scheduler->current_process);
    }

    // Free scheduler structure
    free(scheduler);
}

void schedule_process(Scheduler* scheduler, Process process) {
    if (!scheduler) return;

    // Insert the process into the queue
    heap_insert(scheduler->process_queue, &process);
}

Process* get_next_process(Scheduler* scheduler) {
    if (!scheduler || heap_size(scheduler->process_queue) == 0) {
        return NULL;
    }

    // If there's a current process, put it back in the queue
    if (scheduler->current_process) {
        Process current = *scheduler->current_process;
        heap_insert(scheduler->process_queue, &current);
        free(scheduler->current_process);
        scheduler->current_process = NULL;
    }

    // Get process with minimum virtual runtime
    Process* next_process = (Process*)malloc(sizeof(Process));
    if (!next_process) return NULL;

    if (heap_extract_min(scheduler->process_queue, next_process)) {
        scheduler->current_process = next_process;
        return next_process;
    } else {
        free(next_process);
        return NULL;
    }
}

void tick(Scheduler* scheduler) {
    if (!scheduler || !scheduler->current_process) return;

    // Update virtual runtime of current process using the time slice as execution time
    update_vruntime(scheduler->current_process, scheduler->time_slice);
}