#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/sysinfo.h>

// internals

void (*__parallel_for_thread)(int* i) = NULL;
void* __parallel_for_ebp = NULL;
void* __parallel_for_esp = NULL;

struct Thread {
    int position;
    int limit;
    pthread_t ref;
}* threads = NULL;

void* __run_parallel_for_thread(void *data) {
    struct Thread* thread = data;
    for (; thread->position < thread->limit; ++thread->position) {
        __parallel_for_thread(&thread->position);
    }
    return NULL;
}

// http://bisqwit.iki.fi/story/howto/openmp/#LoopDirectiveFor
void __run_parallel_for(int start, int end) {
    printf("for from %d to %d\n", start, end);
    const int count = get_nprocs();
    const int length = end - start;
    struct Thread* threads = malloc(count * sizeof(struct Thread));
    int i;
    for (i = 0; i < count; ++i) {
        threads[i].position = start + i * length / count;
        threads[i].limit = start + (i + 1) * length / count;
        pthread_create(&threads[i].ref, NULL, __run_parallel_for_thread,
                &threads[i]);
    }
    for (i = 0; i < count; ++i)
        pthread_join(threads[i].ref, NULL);
    free(threads);
}
