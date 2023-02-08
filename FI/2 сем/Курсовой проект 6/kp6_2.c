#include <stdio.h>
#include <string.h>
#include "table.h"

void usage(char prog[]){
	fprintf(stderr, "Преминение: %s [FILE1]\n\n",prog);
	fprintf(stderr, "Описание: программа принимает на вход бинарный НЕПУСТОЙ файл и работает с ним.\n");
}

int main(int argc, char *argv[]){
	if(argc!=2){
		fprintf(stderr, "%s: Неверное количество аргументов\n",argv[0]);
		usage(argv[0]);
		return 1;
	}
	table fishing;
	double mscore=0; //средний балл
	int count=0;
	FILE *input=fopen(argv[1],"rb");
	if(input==NULL){
		fprintf(stderr, "%s: FILE1 не существует.\n",argv[0]);
		usage(argv[0]);
		return 2;
	}

	//чтение таблицы и вычисление среднего балла
	while(fread(&fishing, sizeof(fishing), 1, input)){
		mscore+=fishing.score;
		count++;
	}
	if(count==0){
		fprintf(stderr, "%s: FILE1 пуст.\n",argv[0]);
                usage(argv[0]);
                return 3;
	}
	mscore=mscore/count;

	//повторное чтение и вывод проходящих первый этап рыбаков
	printf("Средний балл: %.2lf\n",mscore);
	rewind(input); //ставим указатель в начало файлика
	printf("Лидеры по улову рыбы:\n");
	while(fread(&fishing, sizeof(fishing), 1, input)){
		if(fishing.score>=mscore){
                	printf("%s %s %s %.1lf %d\n",fishing.fname,fishing.sname,fishing.tname,fishing.score,fishing.number);
        	}
	}
	fclose(input);
	return 0;
}
