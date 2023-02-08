#ifndef types_h
#define types_h

typedef enum {
    TOK_NONE,
    TOK_CONST,
    TOK_VAR,
    TOK_OP,
    TOK_LBR,
    TOK_RBR
} token_type;

typedef struct{
    token_type type;
    char varname[32];
    double constval;
    char op;
} token;

typedef enum {
    RTR_OK,
    RTR_ERROR = -3,
    RTR_EOE = -2,
    RTR_EOF = -1
} read_token_res;

typedef enum {
    RER_OK = 0,
    RER_ERROR = -2,
    RER_EOF = -1
} read_exp_res;

typedef enum {
    SSR_OK,
    SSR_ERR_BRACKET_BALANCE
} ss_result;

typedef enum {
    BTR_OK,
    BTR_ERROR
} build_tree_res;

#endif