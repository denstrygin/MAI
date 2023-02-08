#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include "sys/time.h"
#include "batcher.h"
#include "table.h"

#define MYMAX 1000

//глобальные переменные
int bar_count = 0;
int n = 0;
int maxthread_count = 0;

int *list1 = NULL; 
int *l_a = NULL;

pthread_t* thread_handles = NULL;    // Массив указателей на поток

//функция вычисления текущего времени
long long current_timestamp() {
   struct timeval te;
   if(gettimeofday(&te, NULL) != 0) {
      fprintf(stderr, "GETTIME ERROR\n");
      exit(-1);
   }

   long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
   return milliseconds;
}

//функция справки использования программы
void usage(char* prog_name) {
   fprintf(stderr, "usage: %s <thread count> <n> [g] [o]\n", prog_name);
   fprintf(stderr, "'values[0]': кол-во потоков\n");
   fprintf(stderr, "values[0] не должно быть равно 0\n");
   fprintf(stderr, "оперция log2(values[0]) должна возвращать целое число\n");
   fprintf(stderr, "'n': кол-во элементов в массиве\n");
   fprintf(stderr, "n должно делиться на кол-во потоков\n");
   fprintf(stderr, "values[0] не может быть больше, чем n/2\n");
   fprintf(stderr, "'g':  генерирует числа\n");
   fprintf(stderr, "'o':  программа выведет и входные данные\n");
   exit(-1);
}

// Работа с ключами
void get_args(int argc, char *argv[], int* gen_list_p, int* output_list_p, int values [], int nvalue) {
   int values[0] = 0, n = 0;
   if (argc < 3 || argc > 5)
      usage(argv[0]);

   //Количество потоков и количество чисел в массиве
   if((values[0] = strtol(argv[1], NULL, 10)) == LONG_MIN || values[0] == LONG_MAX) {
      fprintf(stderr, "STRTOL ERROR\n");
      exit(-1);  
   }
   if((n = strtol(argv[2], NULL, 10)) == LONG_MIN || n == LONG_MAX) {
      fprintf(stderr, "STRTOL ERROR\n");
      exit(-1);
   }

   //Проверка на корректность кол-ва потоков
   if(values[0] == 0) 
      usage(argv[0]);
   if (n % values[0] != 0) 
      usage(argv[0]);
   if ((values[0] & (values[0]-1)) != 0) 
      usage(argv[0]);
   if (values[0] > (n / 2))
         usage(argv[0]);
   // Указатели на массивы ввода-вывода
   *gen_list_p = 0;
   *output_list_p = 0;

   // Проверка корректности 2х последних ключей
   if (argc == 4) {
      char c1 = argv[3][0];
      if (c1 == 'g') 
         *gen_list_p = 1;
      if (c1 == 'o')
         *output_list_p = 1;
      else {
         printf(stderr, "Ошибка ввода ключей\n");
         exit(-1);
      }
   } 
   else if (argc == 5) {
      char c1 = argv[3][0];
      char c2 = argv[4][0];
      if ((c1 == 'g') && (c2 == 'o')) {
         *gen_list_p = 1;
         *output_list_p = 1;
      }
      else {
         printf(stderr, "Ошибка ввода ключей\n");
         exit(-1);
      }
   }
   values[0] = values[0];
   values[1] = n;
}

//функция генерации массива
void gen_list(int list[], int n) {
   srand(time(NULL));
   for (int i = 0; i < n; ++i) { list[i] = 1 + rand()%MYMAX; }
}

//функция чтения массива
void read_list(char prompt[], int list[], int n) {
   printf("%s\n", prompt);
   for (int i = 0; i < n; ++i) { scanf("%d", &list[i]); }
}

//функция печати на экран массива
void print_list(char title[], int list[], int n) {
   printf("%s:\n", title);
   for (int i = 0; i < n; ++i) { printf("%d\n", list[i]); }
}


int main(int argc, char* argv[]) {    
   int g_list = 0, output_list = 0, nvalue = 2;
   long long start = 0, finish = 0;
   int values[2];
   get_args(argc, argv, &g_list, &output_list, values, nvalue);
   if((thread_handles = malloc(values[0]*sizeof(pthread_t))) == NULL) {
      fprintf(stderr, "MALLOC ERROR\n");
      exit(-1);
   }
   if((list1 = malloc(values[1]*sizeof(int))) == NULL) {
      fprintf(stderr, "MALLOC ERROR\n");
      exit(-1);  
   }
   if (g_list) 
      gen_list(list1, values[1]); 
   else  
      read_list("Enter the list", list1, values[1]);
   
   if (output_list) 
      print_list("The input list is", list1, values[1]);
   
   args_t argss = {list1, 0, n - 1};
   // Начало отсчёта времени
   start = current_timestamp();
   // Сортировка
   batcher_mergesort(&argss);
   // Конец отсчёта времени
   finish = current_timestamp();

   if (output_list) 
      print_list("The sorted list is", l_a, values[1]);

   printf("Elapsed time = %lld milliseconds\n", finish - start);

   free(list1);
   free(l_a);
   free(thread_handles);
   return 0;
}