#include "sorting_station.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

bool is_num(char c){
    return '0' <= c && c <= '9';
}

bool is_letter(char c){
    return ('a' <= c  && c <= 'z') ||  ('A' <= c  && c <= 'Z');
}

read_token_res read_token(token* tok, token_type prev_type){
    int c = getchar();
    if (c == EOF){
        tok->type = TOK_NONE;
        return RTR_EOF;
    }
    if(is_letter(c) || c == '_'){
        tok->type = TOK_VAR;
        ungetc(c, stdin);
        char var[32];
        scanf("%[_A-Za-z0-9]", var);
        strcpy(tok->varname, var);
        return RTR_OK;
    }
    else if (is_num(c)){
        tok->type = TOK_CONST;
        ungetc(c, stdin);
        double value;
        scanf("%lf", &value);
        tok->constval = value;
        return RTR_OK;
    }
    else if (c == '-'){
        tok->type = TOK_OP;
        if (prev_type == TOK_OP || prev_type == TOK_LBR || prev_type == TOK_NONE){
            tok->op = '~';
        }
        else{
            tok->op = c;
        }
        return RTR_OK;
    }
    else if (!isspace(c)){
        if (c == '('){
            tok->type = TOK_LBR;
            tok->op = c;
            return RTR_OK;
        }
        else if (c == ')'){
            tok->type = TOK_RBR;
            tok->op = c;
            return RTR_OK;
        }
        else if (c == '+' || c == '*' || c == '/' || c == '^'){
            tok->type = TOK_OP;
            tok->op = c;
            return RTR_OK;
        }
        else{
            return RTR_ERROR;
        }
    }
    else{
        tok->type = TOK_NONE;
        if (c == '\n'){
            return RTR_EOE;
        }
        else{
            return RTR_OK;
        }
    }
}

read_exp_res read_expression(queue *q){
    token tok;
    token_type prev_type = TOK_NONE;
    read_token_res rtr;
    while ((rtr = read_token(&tok, prev_type)) == RTR_OK){
        if(tok.type == TOK_NONE)
            continue;

        prev_type = tok.type;
        q_push(q, tok);
    }
    switch (rtr){
        case RTR_ERROR: return RER_ERROR;
        case RTR_EOE: return RER_OK;
        case RTR_EOF: return RER_EOF;
        default: return RER_ERROR;
    }
}

bool should_pop_out(char new_op, char stack_op){
    if (new_op == '~' || new_op == '^'){
        if (new_op == '^' && stack_op == '~'){
            return true;
        }
        return false;
    }
    else{
        if (new_op == '+' || new_op == '-'){
            return true;
        }
        else{
            if (stack_op != '+' && stack_op != '-'){
                return true;
            }
            return false;
        }
    }
}

ss_result sorting_station(queue  *src, queue  *dest){
    token_stack s;
    token_s_init(&s);
    while (!q_is_empty(src)){
        token t = q_pop(src);
        if (t.type == TOK_VAR || t.type == TOK_CONST){
            q_push(dest, t);
        }
        else if (t.type == TOK_LBR){
            token_s_push(&s, t);
        }
        else if (t.type == TOK_RBR){
            token curr_tok;
            curr_tok.type = TOK_NONE;
            while (!token_s_is_empty(&s) && (curr_tok = token_s_pop(&s)).type != TOK_LBR){
                q_push(dest, curr_tok);
            }
            if (curr_tok.type != TOK_LBR){
                token_s_destroy(&s);
                return SSR_ERR_BRACKET_BALANCE;
            }
        }
        else{
            token curr_tok;
            curr_tok.type = TOK_NONE;
            while (!token_s_is_empty(&s)){
                if ((curr_tok = token_s_pop(&s)).type == TOK_OP && should_pop_out(t.op, curr_tok.op)){
                    q_push(dest, curr_tok);
                }
                else{
                    token_s_push(&s, curr_tok);
                    break;
                }
            }
            token_s_push(&s, t);
        }
    }
    while (!token_s_is_empty(&s)){
        token curr_tok = token_s_pop(&s);
        if (curr_tok.type == TOK_LBR){
            token_s_destroy(&s);
            return SSR_ERR_BRACKET_BALANCE;
        }
        q_push(dest, curr_tok);
    }
    token_s_destroy(&s);
    return SSR_OK;
}

build_tree_res build_tree(queue *polish, treeptr *tree){
    if (q_is_empty(polish)){
        *tree = NULL;
        return BTR_OK;
    }
    treeptr_stack s;
    treeptr_s_init(&s);

    while (!q_is_empty(polish)){
        token t = q_pop(polish);
        treeptr l , r;
        if (t.type == TOK_VAR || t.type == TOK_CONST){
            l = NULL;
            r = NULL;
        }
        else if (t.op == '~'){
            l = NULL;
            if (treeptr_s_is_empty(&s)){
                treeptr_s_destroy(&s);
                return BTR_ERROR;
            }
            r = treeptr_s_pop(&s);
        }
        else{
            if (treeptr_s_is_empty(&s)){
                treeptr_s_destroy(&s);
                return BTR_ERROR;
            }
            r = treeptr_s_pop(&s);
            if (treeptr_s_is_empty(&s)){
                treeptr_s_destroy(&s);
                return BTR_ERROR;
            }
            l = treeptr_s_pop(&s);
        }
        treeptr new_e = malloc(sizeof(struct tree));
        if (new_e == NULL)
            return BTR_ERROR;
        new_e->val = t;
        new_e->l = l;
        new_e->r = r;
        treeptr_s_push(&s, new_e);
    }
    treeptr res = treeptr_s_pop(&s);
    if (!treeptr_s_is_empty(&s)){
        delete_tree(&res);
        while (!treeptr_s_is_empty(&s)){
            treeptr to_del = treeptr_s_pop(&s);
            remove_node(&to_del);
        }
        treeptr_s_destroy(&s);
        return BTR_ERROR;
    }
    else{
        *tree = res;
        treeptr_s_destroy(&s);
        return BTR_OK;
    }
    return BTR_OK;
}