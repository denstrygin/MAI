#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

// Функция чтения строки и подсчёта её размера
int getStr(char **str){
    int size = 0;    // Счётчик размера строки
    char a = '\0';    // Временное хранилище символа
    int strSize = 10;     // Начальное простраство строки
    (*str) = malloc(sizeof(char) * strSize);
    if((*str) == NULL){     // Проверка на память
        write(STDERR_FILENO, "memory error\n", sizeof(char) * 14);
        exit(-1);
    }
    while(read(0, &a, 1) == 1){    // Делаем посимвольное прочтение со стандартного ввода
        if(a == '\n'){
            break;
        }
        (*str)[size] = a;    // Присвоеваем каждый символ ячейке массива
        size++;
        if(size == strSize){     // Увеличиваем область памяти для строки
            strSize = strSize * 3 / 2;
            (*str) = realloc((*str), sizeof(char) * strSize);
            if((*str) == NULL){
                write(STDERR_FILENO, "memeory error\n", sizeof(char) * 14);
                exit(-1);
            }
        }
    }
    if(size == 0){     // Проверка на ввод нуля элементов
        free((*str));
        (*str) = NULL;
        return -1;
    } else {
        (*str)[size] = '\0'; // Символ окончания строки
        (*str) = realloc((*str), sizeof(char) * (size + 1)); // Сокращаем область памяти до необходимой
        if((*str) == NULL){
            write(STDERR_FILENO, "memory error\n", sizeof(char) * 14);
            exit(-1);
        }
    }
    return size;
}

//родительский процесс
void parent(int *pipe1, int *pipe2, int fd){
    close(pipe1[0]);   // Закрываем лишние дискрипторы чтения-записи
    close(pipe2[1]);
    char *errorMess = "Error\n";
    while(1){    
        char *str;
        int size = getStr(&str);    // Получаем длину строки
        write(pipe1[1], &size, sizeof(int));    
        if(size < 0){    
            break;
        }
        if(size == 0){
            continue;
        }
        write(pipe1[1], str, sizeof(char) * size);    
        free(str);
        bool result;
        read(pipe2[0], &result, sizeof(bool));    
        if(!result){     
            write(fd, errorMess, sizeof(char) * 6);    
        }
    }
    wait(NULL);    
    close(fd);
    close(pipe1[1]);
    close(pipe2[0]);
}

//дочерний процесс
void child(int *pipe1, int *pipe2, int fd){
    close(pipe1[1]);
    close(pipe2[0]);
    while(1){     //
        int size;
        bool result;
        char *str;
        read(pipe1[0], &size, sizeof(int));   
        if(size < 0){     
            break;
        }
        str = malloc(sizeof(char) * size);
        read(pipe1[0], str, sizeof(char) * size);  
        
        if((str[size - 1] != ';' && str[size - 1] != '.') || size == 0){    
            result = false;
            write(pipe2[1], &result, sizeof(bool));
        } else {
            result = true;
            write(pipe2[1], &result, sizeof(bool));
            write(fd, str, sizeof(char) * size);
            write(fd, "\n", sizeof(char));
        }
        free(str);
    }
    close(fd);
    close(pipe1[0]);
    close(pipe2[1]);
}

int main(){
    int fd1[2], fd2[2]; // Файловые дискрипоры
    int pid, fd;    // pid переменная для проверки и работы с процессами
    char *filename = NULL;    // Указатель на область памяти файл
    while(!filename){     // Считываем в него строку(название)
        getStr(&filename);
    }
    fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, S_IWUSR | S_IRUSR); // Открываем файл
    if(pipe(fd1) == -1){    // Создаём каналы
        perror("pipe1 error");
    }
    if(pipe(fd2) == -1){
        perror("pipe2 error");
    }
    pid = fork();     // Создаём родительский и дочерний процессы
    if(pid == -1){
        perror("fork error");
    } else if(pid == 0){
        child(fd1, fd2, fd);
    } else {
        parent(fd1, fd2, fd);
    }
    free(filename);
    return 0;
}