#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 4

double modul(double a){
	if(a<0){
		a*=-1;
	}
	return a;
}

void usage(){
	fprintf(stderr,"Преминение: программа принимает на вход размер разреженной матрицы и саму матрицу и работает с ней.\n");
}

int main(){
	int *lambda; // указатель на матрицу-лямбда
	double *value; //указатель на матрицу значений
	int m,n,count=0,mas_index=0,zero=0;
	int mas_size=START_SIZE,v;
	double val,max=0;
	int lline,rline;

	//ввод матрицы
	scanf("%d %d",&m,&n);
	if(m<1 || n<1){
		fprintf(stderr,"Некорректный размер матрицы\n");
		usage();
		return 1;
	}
	value=(double *) malloc(sizeof(double)*mas_size);
	lambda=(int *) malloc(sizeof(int)*mas_size);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			scanf("%lf",&val);
			count++;
			if(val!=0){
				if(modul(max)<modul(val)){
					max=val;
				}
				//выделение памяти при переполнении
				if(mas_size==mas_index){
					mas_size=mas_size*3/2;
					value=(double *) realloc(value,mas_size*sizeof(double));
					lambda=(int *) realloc(lambda,mas_size*sizeof(int));
				}
				lambda[mas_index]=count;
				value[mas_index]=val;
				mas_index++;
			}
		}
	}

	//вывод векторов и максимального значения
	lambda[mas_index]=-1;
	printf("Векторы:\n");
	for(int i=0;i<=mas_index;i++){
		printf("%5d ",lambda[i]);
	}
	printf("\n");
	for(int i=0;i<mas_index;i++){
		printf("%5.2lf ",value[i]);
	}
	printf("\n\nМаксимальное значение по модулю: %lf\n",max);

	//преобразование матрицы
	for(int i=0;i<mas_index;i++){
		if(value[i]==max){
			//lline - левая граница строчки матрицы с максимальным элементом, rline - правая
			lline=(lambda[i]-1)/n*n+1;
			rline=lline+n-1;
			v=i-1;
			while(lambda[v]>=lline){
				value[v]/=max;
				v--;
			}
			v=i+1;
			while(lambda[v]<=rline){
				value[v]/=max;
				v++;
			}
			value[i]/=max;
			i=v-1;
		}
	}

        printf("\nИзменённый вектор значений:\n");
        for(int i=0;i<mas_index;i++){
                printf("%5.2lf ",value[i]);
        }

	//вывод изменённой матрицы
	printf("\n\n");
	count=1;
	v=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(count!=lambda[v]){
				printf("%5d ",zero);
			} else {
				printf("%5.2lf ",value[v]);
				v++;
			}
			count++;
		}
		printf("\n");
	}
	return 0;
}
