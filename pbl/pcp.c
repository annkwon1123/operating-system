#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define MAX_RESOURCE_PRIORITY 10

pthread_mutex_t resource_mutex;
pthread_cond_t resource_cond;
int resource_owner;
int resource_priority[MAX_RESOURCE_PRIORITY];

void init_resource() {
    pthread_mutex_init(&resource_mutex, NULL);
    pthread_cond_init(&resource_cond, NULL);
    resource_owner = -1;
    for (int i = 0; i < MAX_RESOURCE_PRIORITY; i++) {
        resource_priority[i] = -1;
    }
}

void acquire_resource(int thread_id, int thread_priority) {
    pthread_mutex_lock(&resource_mutex);

    // 우선순위 상승
    for (int i = 0; i < thread_priority; i++) {
        if (resource_priority[i] != -1) {
            pthread_cond_wait(&resource_cond, &resource_mutex);
            i = -1; // 다시 처음부터 탐색
        }
    }

    // 우선순위 설정
    resource_priority[thread_priority] = thread_id;

    // 자원 소유
    if (resource_owner == -1) {
        resource_owner = thread_id;
    }

    pthread_mutex_unlock(&resource_mutex);
}

void release_resource(int thread_id, int thread_priority) {
    pthread_mutex_lock(&resource_mutex);

    // 자원 반환
    if (resource_owner == thread_id) {
        resource_owner = -1;
    }

    // 우선순위 해제
    resource_priority[thread_priority] = -1;

    // 다른 스레드에게 자원 양보
    for (int i = thread_priority + 1; i < MAX_RESOURCE_PRIORITY; i++) {
        if (resource_priority[i] != -1) {
            pthread_cond_signal(&resource_cond);
            break;
        }
    }

    pthread_mutex_unlock(&resource_mutex);
}

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    int thread_priority = rand() % MAX_RESOURCE_PRIORITY;

    acquire_resource(thread_id, thread_priority);
    printf("Thread %d acquired the resource.\n", thread_id);

    // 일부러 시간 지연
    int delay = rand() % 5;
    sleep(delay);

    release_resource(thread_id, thread_priority);
    printf("Thread %d released the resource.\n", thread_id);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    init_resource();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
