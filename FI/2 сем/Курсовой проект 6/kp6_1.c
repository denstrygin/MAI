#include "stdio.h"
#include "locale.h"
#include "stdbool.h"
#include "string.h"
#include "table.h"

void usage(char prog[]){
		fprintf(stderr, "Применение: %s [FILE1] [FILE2]\n\n",prog);
		fprintf(stderr, "Описание: программа получает на вход названия двух файлов.\n");
	        fprintf(stderr, "FILE1 - файл с исходным текстом. FILE2 - бинарный выходной файл.\n");
        	fprintf(stderr, "Если FILE2 не существует, то он будет создан.\n");
}

int main(int argc, char *argv[]){
	if(argc!=3){
		fprintf(stderr, "%s: Неверное количество аргументов\n",argv[0]);
		usage(argv[0]);
		return 1;
	}
	FILE *input=fopen(argv[1],"r");
	FILE *output=fopen(argv[2],"wb");
	table fishing;
	if(input==NULL){
		fprintf(stderr, "%s: FILE1 пуст либо не существует\n",argv[0]);
                usage(argv[0]);
                return 2;
	}

	//чтение и запись
	while(!feof(input)){
		fscanf(input, "%s %s %s %lf %d\n", fishing.fname, fishing.sname, fishing.tname, &fishing.score, &fishing.number);
		fwrite(&fishing, sizeof(fishing), 1, output);
	}
	fclose(input);
	fclose(output);
	return 0;
}
