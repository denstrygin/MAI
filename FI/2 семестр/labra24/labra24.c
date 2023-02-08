#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "sorting_station.h"
#include "token_tree.h"

void check_const(treeptr *t){
    if ((*t)->val.constval > 0)
        return;

    treeptr minus = malloc(sizeof(tree));
    minus->val.type = TOK_OP;
    minus->val.op = '~';
    minus->l = NULL;
    minus->r = *t;

    (*t)->val.constval *= -1;
    *t= minus;
}

void multi_exp(treeptr *t, int k){
    if (*t == NULL){
        return;
    }

    if ((*t)->val.type == TOK_OP){
        if ((*t)->val.op == '/'){
            multi_exp(&(*t)->l, k);
        }
        else if ((*t)->val.op == '*'){
            multi_exp(&(*t)->r, k);
        }
        else if ((*t)->val.op == '^'){
            treeptr new_deg = malloc(sizeof(tree));
            new_deg->val.op = '^';
            new_deg->val.type = TOK_OP;
            new_deg->l = (*t)->l;
            new_deg->r = (*t)->r;

            treeptr multiplier = malloc(sizeof(tree));
            multiplier->val.type = TOK_CONST;
            multiplier->l = NULL;
            multiplier->r = NULL;
            multiplier->val.constval = k;

            (*t)->r = multiplier;
            (*t)->val.op = '*';
            (*t)->l = new_deg;

            check_const(&(*t)->r);
        }
        else if ((*t)->val.op == '+' || (*t)->val.op == '-'){
            multi_exp(&(*t)->l, k);
            multi_exp(&(*t)->r, k);
        }
        else{ //только ~
            if (k > 0){
                multi_exp(&(*t)->r, k);
            }
            else{
                *t = (*t)->r;
                multi_exp(t, (-1 * k));
            }
        }
    }//lets try
    else if ((*t)->val.type == TOK_CONST){
        (*t)->val.constval *= k;
        check_const(t);
    }
    else{ //только var
        if (k == 1){
            return;
        }
        else if (k == -1){
            treeptr new_var = malloc(sizeof(tree));
            new_var->val.type = TOK_VAR;
            strcpy(new_var->val.varname, (*t)->val.varname);
            new_var->l = (*t)->l;
            new_var->r = (*t)->r;

            (*t)->val.type = TOK_OP;
            (*t)->val.op = '~';
            (*t)->l = NULL;
            (*t)->r = new_var;
        }
        else{
            treeptr new_var = malloc(sizeof(tree));
            new_var->val.type = TOK_VAR;
            strcpy(new_var->val.varname, (*t)->val.varname);
            new_var->l = (*t)->l;
            new_var->r = (*t)->r;

            treeptr multiplier = malloc(sizeof(tree));
            multiplier->val.type = TOK_CONST;
            multiplier->val.constval = k;
            multiplier->l = NULL;
            multiplier->r = NULL;

            (*t)->val.type = TOK_OP;
            (*t)->val.op = '*';
            (*t)->l = new_var;
            (*t)->r = multiplier;

            check_const(&(*t)->r);
        }
    }   
}

void div_exp(treeptr *t, int k){
    if (*t == NULL){
        return;
    }

    if ((*t)->val.type == TOK_OP){
        if ((*t)->val.op == '/'){
            multi_exp(&(*t)->r, k);
        }
        else if ((*t)->val.op == '*'){
            div_exp(&(*t)->r, k);
        }
        else if ((*t)->val.op == '^'){
            treeptr new_deg = malloc(sizeof(tree));
            new_deg->val.op = '^';
            new_deg->val.type = TOK_OP;
            new_deg->l = (*t)->l;
            new_deg->r = (*t)->r;

            treeptr divisor = malloc(sizeof(tree));
            divisor->val.type = TOK_CONST;
            divisor->val.constval = k;
            divisor->l = NULL;
            divisor->r = NULL;

            (*t)->val.op = '/';
            (*t)->l = new_deg;
            (*t)->r = divisor;

            check_const(&(*t)->r);
        }
        else if ((*t)->val.op == '+' || (*t)->val.op == '-'){
            div_exp(&(*t)->l, k);
            div_exp(&(*t)->r, k);
        }
        else{ //только ~
            if (k > 0){
                div_exp(&(*t)->r, k);
            }
            else{
                *t = (*t)->r;
                div_exp(t, (-1 * k));
            }
        }
    }//lets try
    else if ((*t)->val.type == TOK_CONST){
        (*t)->val.constval /= k;
        check_const(t);
    }
    else{ //only var
        if (k == 1){
            return;
        }
        else if (k == -1){
            multi_exp(t, k);
        }
        else{
            treeptr new_var = malloc(sizeof(tree));
            new_var->val.type = TOK_VAR;
            strcpy(new_var->val.varname, (*t)->val.varname);
            new_var->l = (*t)->l;
            new_var->r = (*t)->r;

            treeptr divisor = malloc(sizeof(tree));
            divisor->val.type = TOK_CONST;
            divisor->val.constval = k;
            divisor->l = NULL;
            divisor->r = NULL;

            (*t)->val.type = TOK_OP;
            (*t)->val.op = '/';
            (*t)->l = new_var;
            (*t)->r = divisor;

            check_const(&(*t)->r);
        }
    }   
}

bool q_get_number(queue *q, double *k){
    if (q->first->val.type == TOK_OP && q->first->val.op == '~'){
        if (q->first->next != NULL){
            if (q->first->next->next == NULL && q->first->next->val.type == TOK_CONST){
                *k = -1 * q->first->next->val.constval;
                return true;
            }
            return false;
        }
        else{
            return false;
        }
    }
    else if(q->first->val.type == TOK_CONST && q->first->next == NULL){
        *k = q->first->val.constval;
        return true;
    }
    else{
        return false;
    }
}

void clear_line(){
    int c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

int main(int argc, char const *argv[]){
	queue input;
    q_init(&input);
    read_exp_res rer = RER_OK;

    while (rer != RER_EOF){
        printf("Введите выражение:\n");
        rer = read_expression(&input);
        if (rer == RER_EOF)
            continue;

        if (rer == RER_ERROR){
            printf("Ошибка чтения выражения\n\n\n");
            q_destroy(&input);
            clear_line();
            continue;
        }

        queue polish;
        q_init(&polish);
        ss_result ssr = sorting_station(&input, &polish);
        if (ssr == SSR_ERR_BRACKET_BALANCE){
            printf("Ошибка в кол-ве скобок\n");
            continue;  
        }

        treeptr root = NULL;
        printf("ПОЛЬСКАЯ ЗАПИСЬ:\n");
        q_print(&polish);
        printf("\n");

        build_tree_res btr = build_tree(&polish, &root);
        if (btr == BTR_ERROR){
            printf("Ошибка построения дерева\n");
            continue;
        }
        q_destroy(&polish);

        printf("ДЕРЕВО:\n");
        print_tree(root, 0);
        printf("\n");

        printf("ИНФИКСНАЯ ФОРМА (из дерева):\n");
        if (root != NULL){
            print_infix_form(root);
        }
        else{
            printf("Пустое выражение");
        }
        printf("\n\n");


        printf("ДЕЛЕНИЕ НА k:\n");
        printf("Введите k: ");
        rer = read_expression(&input);
        if (rer == RER_EOF){
            printf("\n");
            continue;
        }
        double k;
        if (!q_get_number(&input, &k)){
            printf("Введен некорректный аргумент\n");
        }
        else{
            div_exp(&root, k);
            if (root != NULL){
               print_infix_form(root);
            }
            else{
               printf("Пустое выражение");
            }
            printf("\n");

            printf("ДЕРЕВО:\n");
            print_tree(root, 0);
            printf("\n");
        }

        printf("\n----------\n\n");
        q_destroy(&input);
        delete_tree(&root);
    }
    q_destroy(&input);
    return 0;
}