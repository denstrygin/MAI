#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include "sys/time.h"
#include "batcher.h"

// Текущее кол-во потоков
int curthread_count = 0;
extern int maxthread_count;
extern int n;
extern pthread_t* thread_handles;

// Функция сортировки Бэтчера распоточевается рекурсивно
void* batcher_mergesort() {

   if (r == (l + 1))
      compexch(list, l, r);
   if (r < (l + 2))
      return;
   unsuflle(list, l, r);
   if (curthread_count != maxthread_count) {
      if(pthread_create(&thread_handles[curthread_count - 1], NULL, batcher_mergesort, (void*)(list, l, (l + r - 1) / 2)) != 0) {
         fprintf(stderr, "PTHREAD CREATE ERROR\n");
         exit(-1);
      }
      else
         curthread_count++;
      if(pthread_create(&thread_handles[curthread_count], NULL, batcher_mergesort, (void*)(list, (l + r + 1) / 2, r)) != 0) {
         fprintf(stderr, "PTHREAD CREATE ERROR\n");
         exit(-1);
      }
      else
         curthread_count++;
      if(pthread_join(thread_handles[curthread_count - 1], NULL) != 0) {
         fprintf(stderr, "PTHREAD JOIN ERROR\n");
         exit(-1);
      }
      if(pthread_join(thread_handles[curthread_count], NULL) != 0) {
         fprintf(stderr, "PTHREAD JOIN ERROR\n");
         exit(-1);
      }
   }
   else {
      batcher_mergesort(list, l, (l + r - 1) / 2);
      batcher_mergesort(list, (l + r + 1) / 2, r);
   }
   suffle(list, l, r);
   for (int i = l + 1; i < r; i += 2)
      compexch(list, i, i + 1);
}

// Вспомогательные ф-ии для сортировки
void shuffle(int list [], int l, int r) {
   int i, j, m = (l + r + 1) / 2; 
   int buf[2 * m];
   for (i = l, j = 0; i <= r; i += 2, j++) {
      buf[i] = list[l + j];
      buf[i + 1] = list[m + j];
   }
   for (i = l; i <= r; i++)
      list[i] = buf[i];
}

void unsuflle(int list [], int l, int r) {
   int i, j, m = (l + r + 1) / 2;
   int buf[2 * m];
   for (i = l, j = 0; i <= r; i += 2, j++) {
      buf[l + j] = list[i];
      buf[m + j] = list[i + 1];
   }
   for (i = l; i <= r; i++)
      list[i] = buf[i];
}

void compexch(int list [], int l, int r) {
   int buf;
   if (list[l] > list[r])
      buf = list[r];
      list[r] = list[l];
      list[l] = buf;
}