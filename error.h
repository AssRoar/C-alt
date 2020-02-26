//
// Created by ALEXA on 04.02.2020.
//

#ifndef LEX_ANALISE_ERROR_H
#define LEX_ANALISE_ERROR_H

#include "token.h"

enum error_type {
    none,
    double_format_error,
    float_format_error,
    char_format_error,
    do_while_format_error,
    broken_bracket_balance,
    get_format_error,
    out_format_error,
    if_format_error,
    case_format_error,
    list_format_error,
    expression_format_error,
    operator_format_error,
    unexpected_token_error,
    syntax_error
};

class error {
public :
    error_type type;
    int line;
    token word;
    error(error_type t, int lin, token tok): type(t), line(lin), word(tok) {};
    error() {
        type = none;
        line = -1;
        token a;
        word = a;
    }
    void fill (token t) {
        word = t;
    }
    void fill (error_type t) {
        type = t;
    }
    void fill (int i) {
        line = i;
    }
    void fill () {
        type = none;
        line = -1;
        token a;
        word = a;
    }
    void fill (error_type t, int lin, token tok) {
        type = t;
        line = lin;
        word = tok;
    }
};

struct bool_error {
    error error;
    bool val;
};

#endif //LEX_ANALISE_ERROR_H
