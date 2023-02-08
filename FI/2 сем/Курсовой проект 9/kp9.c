#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kp9.h"


int main(){
	const int N = 50;
	int i, cnt, action;
	char ch;
	Row data[N];
	Key key;
	//Открытие файла с данными
	FILE *file = fopen("input.txt", "r");
	if (file == NULL){
		printf("Ошибка при открытии файла\n");
		return 0;
	}
	i = 0;
	//Считывание данных
	while (i < N && fscanf(file, "%lld %lf", &data[i].key.a, &data[i].key.b) == 2){
		fscanf(file, "%c", &ch);
		getRow(file, data[i].val, sizeof(data[i].val));
		i++;
	}
	fclose(file);
	cnt = i;
	//Реализация итерактивной части программы
	do{
		printf("Меню\n");
		printf("1) Печать\n");
		printf("2) Двоичный поиск\n");
		printf("3) Сортировка\n");
		printf("4) Перемешивание\n");
		printf("5) Реверс\n");
		printf("6) Выход\n");
		printf("Выберите действие\n");
		scanf("%d", &action);

		switch (action){
			case 1:
				printTable(data, cnt);
				break;
			case 2:
				if (!isSorted(data, cnt))
					printf("Ошибка. Таблица не отсортирована\n");
				else{
					printf("Введите ключ: ");
					scanf("%lld %lf", &key.a, &key.b);
					i = binSearch(data, cnt, key);
					if (i > -1)
						printf("Найдена строка: %s\n", data[i].val);
					else
						printf("Строка с таким ключом не найдена\n");
				}
				break;
			case 3:
				shaker_sort(data, cnt);
				break;
			case 4:
				scramble(data, cnt);
				break;
			case 5:
				reverse(data, cnt);
				break;
			case 6: 
				break;
			default:
				printf("Ошибка. Такого пункта меню не существует\n");
				break;
		}
	}
	while (action != 6);

	return 0;
}

void printTable(const Row *rows, const int size){
	int i;

	printf("+---------+------------------------------------------------------------+\n");
	printf("|  Ключ   |                          Значение                          |\n");
	printf("+---------+------------------------------------------------------------+\n");

	for (i = 0; i < size; i++)
		printf("|%lld %lf|%60s|\n", rows[i].key.a, rows[i].key.b, rows[i].val);

	printf("+---------+------------------------------------------------------------+\n");
}
//Реализация бинарного поиска
int binSearch(const Row *rows, const int size, const Key key){
	int start = 0, end = size - 1, mid;
	if (size <= 0)
		return -1;

	while (start < end){
		mid = start + (end - start) / 2;
		if (comparator(rows[mid].key, key) == 0)
			return mid;
		else if (comparator(rows[mid].key, key) < 1)
			start = mid + 1;
		else
			end = mid;
	}

	if (comparator(rows[end].key, key) == 0)
		return end;

	return -1;
}
//Реализация шейкерной сортировки
void shaker_sort(Row* rows, const int size){
	int left = 0;
	int right = size - 1;
	int flag = 1;
	while((left<right) && flag > 0){
		flag = 0;
		for(int i = left; i<right; ++i){
			if(comparator(rows[i+1].key, rows[i].key) < 1){
				swapRows(rows, i, i+1);
				flag = 1;
			}
		}
		right--;
		for(int i = right; i>left; i--){
			if(comparator(rows[i].key, rows[i-1].key) < 1){
				swapRows(rows, i, i-1);
				flag = 1;
			}
		}
		left++;
	}
}
//Функции интерактива
void scramble(Row* rows, const int size){
	int i, j, z;
	srand((unsigned int)time(NULL));

	for (z = 0; z < size; z++){
		i = randomAB(0, size - 1);
		j = randomAB(0, size - 1);

		swapRows(rows, i, j);
	}
}

void reverse(Row *rows, const int size){
	int i, j;
	for (i = 0, j = size - 1; i < j; i++, j--)
		swapRows(rows, i, j);
}

void getRow(FILE *stream, char *str, const int size){
	int cnt = 0, ch;
	while ((ch = getc(stream)) != '\n' && cnt < size - 1)
		str[cnt++] = ch;
	str[cnt] = '\0';
}

void swapRows(Row *rows, const int a, const int b){
	Row tmp;
	tmp = rows[a];
	rows[a] = rows[b];
	rows[b] = tmp;
}

int comparator(const Key k1, const Key k2){
	if (k1.a > k2.a)
		return 1;
	if (k1.a < k2.a)
		return -1;
	if (k1.b > k2.b)
		return 1;
	if (k1.b < k2.b)
		return -1;
	return 0;
}

int randomAB(const int a, const int b){
	return a + rand() % (b - a + 1);
}

int isSorted(const Row *rows, const int size){
	int i;
	for (i = 0; i < size - 1; i++)
		if (comparator(rows[i].key, rows[i + 1].key) > 0)
			return 0;
	return 1;
}