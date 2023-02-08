#include "stdio.h"
#include "stdbool.h"
#include "list.h"
#include "string.h"
#include "stdint.h"
#include "stdlib.h"

//Удаление элемента/элементов
void delete_some_values(listptr list, int min, int max){
    list_iter l = list_begin(list);
    list_iter r = list_end(list);

    bool between_values = false;

    for (l; !list_iter_is_equals(l, r);){
        int size = list_get_size(list);
        if (size == 1){
            if (!between_values){
                int tmp = list_iter_get_val(l);
                if (tmp >= min && tmp <= max){
                    list_iter_remove(&l);
                }
            }
            break;
        }
        int tmp = list_iter_get_val(l);
        if (tmp >= min && tmp <= max){
            list_iter_remove(&l);
        }
        else{
            between_values = true;
            list_iter_next(&l);
        }
    }
}

//Вывод списка
void print_list(listptr l){
    list_iter begin = list_begin(l);
    list_iter end = list_end(l);
    int val = 0;
    while (!list_iter_is_equals(begin, end)){
        val = list_iter_get_val(begin);
        printf("%d ", val);
        list_iter_next(&begin);
    }
    printf("\n");
}
//Вывод длины списка
void print_len_list(listptr l){
    printf("%ld\n", list_get_size(l));
}

listptr create_list(){
    listptr l;
    list_init(&l);
    return l;
}
//Вывод справки
void print_menu(){
    printf("Вывести список - 1\n");
    printf("Добавить новый элемент в список - 2\n");
    printf("Удалить элемент из списка - 3\n");
    printf("Переместиться к элементу - 4\n");
    printf("Вывести длину списка - 5\n");
    printf("Удалить элементы в числовом диапозоне - 6\n");
    printf("Вывести справку - 7\n");
    printf("Выйти - 8\n");
}
//Функция получени команды
void action(){
    listptr list = create_list();
    list_iter begin = list_begin(list);
    list_iter end = list_end(list);
    int variant = 0;
    while (variant != 8){
        if (scanf("%d", &variant) == EOF){
            break;
        }
        switch (variant){
        case 1:
            printf("Список:\n");
            print_list(list);
            break;
        case 2:
            printf("Введите значение\n");
            int val = 0;
            if (scanf("%d", &val) == 1){
                list_iter_insert_before(&begin, val);
            }
            else{
                printf("Некорректное значение\n");
            }
            break;
        case 3:
            list_iter_next(&begin);
            if (!list_iter_remove(&begin)){
                printf("Ошибка \n");
            }
            break;
        case 4:
            list_iter_next(&begin);
            if (!list_iter_remove(&begin)){
                printf("Ошибка\n");
            }
            break;
        case 5:
            printf("Длина списка:\n");
            print_len_list(list);
            break;
        case 6:
            printf("Введите значение\n");
            int min = 0;
            int max = 0;
            if (scanf("%d%d", &min, &max) == 2){
                delete_some_values(list, min, max);
                begin = list_begin(list);
                end = list_end(list);
            }
            else{
                printf("Некорректное значение\n");
            }
            break;
        case 7:
            print_menu();
            break;
        case 8:
            break;
        default:
            printf("Некорректный ключ\n");
            break;
        }
    }
}

int main(){
    print_menu();
    action();
}