#ifndef LEX_ANALISE_SYNTAX_H
#define LEX_ANALISE_SYNTAX_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "token.h"
#include "lex.h"
#include <fstream>
#include "variables.h"
#include "error.h"

bool_error is_block (string s);

token qur;
int next_index_in_main_vector;
int qur_line;

bool get_qur();

bool is_ident(){
    return letters.find(qur.value[0]) != letters.end();
}
void words_to_ident () {
    next_index_in_main_vector = 0;
    qur_line = 1;
    while (get_qur()) {
        if (qur.type == word and is_ident()) qur.type = identificator;
    }
}

void from_save_qur (int save_index, token save_qur, int save_line) {
    next_index_in_main_vector = save_index;
    qur_line = save_line;
    qur = save_qur;
}


bool_error is_F(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (!(qur.type==number ||
        qur.type==identificator ||
        qur.type==constant)){
        a.error.fill(expression_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(qur.value=="not"){
        if(!get_qur()) {
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if(qur.value=="(") {
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if(!get_qur()) {
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if(!is_F().val){
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if(!get_qur()) {
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if(qur.value==")") {
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
    }
    a.val=true;
    return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
}
bool_error is_T(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (!is_F().val){
        a.error.fill(expression_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    else{
        if (!get_qur()){
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if (qur.value=="*" ||
            qur.value=="%" ||
            qur.value=="/" ||
            qur.value=="and"){
            if (!get_qur()){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
            if (!is_F().val){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
        }
    }
    a.val=true;
    return a;
}
bool_error is_E1(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (!is_T().val){
        a.error.fill(expression_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    else{
        if (!get_qur()){
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if (qur.value=="+" ||
            qur.value=="-" ||
            qur.value=="or"){
            if (!get_qur()){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
            if (!is_T().val){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
        }
    }
    a.val=true;
    return a;
}
bool_error is_expression(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (!is_E1().val){
        a.error.fill(expression_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    else{
        if (!get_qur()){
            a.error.fill(expression_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        if (qur.value=="==" ||
            qur.value=="<" ||
            qur.value=="<=" ||
            qur.value==">" ||
            qur.value==">="){
            if (!get_qur()){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
            if (!is_E1().val){
                a.error.fill(expression_format_error, qur_line, qur);
                return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
            }
        }
    }
    a.val=true;
    return a;
}

bool_error is_for_nl(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if(qur.value==")"){
        a.val=true;
        return a;
    }
    if (qur.value!=",") {
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.type!=identificator){
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    else if (qur.type==identificator){
        if (!get_qur()){
            a.error.fill(list_format_error, qur_line, qur);
            return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
        }
        return is_for_nl();
    }
}
bool_error is_names_list(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=identificator){
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!is_for_nl().val){
        a.error.fill(list_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    a.val=true;
    return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
}
bool_error is_list(){
    bool_error a;
    a.val=false;
    a.error.fill();
//    if (!is_expression()){
//        a.error.fill(out_format_error, qur_line, qur);
//        return a;
//    }
    if (!get_qur()){
        a.error.fill(out_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!=","){
        a.val=true;
        return a;
    }
    else if (qur.value==",") {
        return is_list();
    }
}

bool_error is_op_do_while(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=res_word){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="do"){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
//    if (!is_operator()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.type!=res_word){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="while"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после while не должен быть конец кода
    if (qur.value!="("){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку тк после while необходима (
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после ( не должен быть конец кода
//    if (!is_expression()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }                 //после ( должно быть выражение
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //после выражения необходима )
    if (qur.value!=")"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //закрываем условную часть цикла
    a.val=true;
    return a;
}
bool_error is_op_while(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=res_word){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="while"){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после while не должен быть конец кода
    if (qur.value!="("){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку тк после while необходима (
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после ( не должен быть конец кода
//    if (!is_expression()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }                 //после ( должно быть выражение
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //после выражения необходима )
    if (qur.value!=")"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //закрываем условную часть цикла
//    if (!is_operator()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }                 //у нас тут операторы должны пойти как бы
    a.val=true;
    return a;
}
bool_error is_op_for(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=res_word){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="for"){
//        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if(!get_qur()) {
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после for не должен быть конец кода
    if (qur.value!="("){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку тк после for необходима (
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после ( не должен быть конец кода
//    if (!is_expression()) return 24228748; //после ( должно быть первое выражение
    if (qur.value!=";"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   // for (int i=0 ? i<32; ++i)
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //кинуть ошибку, потому что после первого оконченного выражения (;) не должен быть конец кода
//    if (!is_expression()) return 24228748; //после первого ; должно быть выражение
    if (qur.value!=";"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   // for (int i=0; i<32 ? ++i)
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //после первых двух выражений должно быть и третье обязательно
//    if (!is_expression()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }                 //после второго ; должно быть выражение
    if(!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //после трех полных выражений необходима )
    if (qur.value!=")"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }                   //закрываем условную часть цикла

//    if (!is_operator()){
//        a.error.fill(operator_format_error, qur_line, qur);
//        return a;
//    }                 //у нас тут операторы должны пойти как бы
    a.val=true;
    return a;
}

bool_error is_op_get(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=res_word) return a;
    if (qur.value!="get") return a;
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="("){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!is_names_list().val){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!=")"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    a.val=true;
    return a;
}
bool_error is_op_out(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.type!=res_word) return a;
    if (qur.value!="out") return a;
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!="("){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!is_list().val){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (!get_qur()){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    if (qur.value!=")"){
        a.error.fill(operator_format_error, qur_line, qur);
        return a;
    }
    a.val=true;
    return a;
}

// asror

bool_error is_op_if() {
    bool_error a;
    a.val=false;
    a.error.fill();
    if(qur.value!="if"){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(qur.value!="("){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!is_expression().val){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(qur.value!=")"){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(if_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
//    if(!is_block(????){
//        a.error.fill(if_format_error, qur_line, qur);
//        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
//    }
    a.val=true;
    return a;
}
bool_error is_for_cf(){
    bool_error a;
    a.val=false;
    a.error.fill();
    if(!(qur.type==number ||
         qur.type==identificator)){
        a.val=true;
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(qur.value!=":"){
        a.val=true;
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
//    if(!is_block(??????)){
//        a.error.fill(case_format_error, qur_line, qur);
//        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
//    }
    a=is_for_cf();
    return a;
}
bool_error is_op_case() {
    bool_error a;
    a.val=false;
    a.error.fill();
    if (qur.value!="case"){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.type!=identificator){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.value!="for"){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!(qur.type==number ||
          qur.type==identificator)){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(qur.value!=":"){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
//    if(!is_block(??????)){
//        a.error.fill(case_format_error, qur_line, qur);
//        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
//    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!is_for_cf().val){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
}

//ok
bool_error is_op_break() {
    bool_error a;
    a.error.fill();
    a.val = false;
    if (qur.type != res_word and qur.value != "break") return a;
    a.val = true;
    return a;
}

//ok
bool_error is_op_continue() {
    bool_error a;
    a.error.fill();
    a.val = false;
    if (qur.type != res_word and  qur.value != "continue") return a;
    a.val = true;
    return a;
}

//asror
bool_error is_function_call() {
    bool_error a;
    a.error.fill();
    a.val = false;
    if(qur.type!=identificator) return a;
    if(!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.value!="("){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!is_names_list().val){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.value!=")"){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    a.val=true;
    return a;
}

//asror
bool_error is_procedure_call() {
    bool_error a;
    a.error.fill();
    a.val = false;
    if(qur.type!=identificator) return a;
    if(!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.value!="("){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!is_names_list().val){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (!get_qur()){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if (qur.value!=")"){
        a.error.fill(syntax_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    a.val=true;
    return a;
}

//ok
bool is_an_array () {
    int s_i = next_index_in_main_vector;
    auto s_q = qur;
    int s_l = qur_line;
    while (qur.value == "[") {
        if (!get_qur()) return false;
        bool min_fl = false;
        if (qur.type == operation and qur.value == "-") min_fl = true;
        if (!get_qur()) return false;
        if (qur.type != int_type) { //first number
            from_save_qur(s_i, s_q, s_l);
            return false;
        }
        if (!get_qur()) return false;
        if (qur.type != punctuation and qur.value != "." and min_fl) { //min is ok only in [a...b] costruction
            from_save_qur(s_i, s_q, s_l);
            return false;
        }
        if (qur.type == punctuation and qur.value == ".") { //its [a...b] costruction
            for (int i = 0; i < 2; ++i) {
                if (!get_qur()) return false;
                if (qur.type != punctuation and qur.value != ".") {
                    from_save_qur(s_i, s_q, s_l);
                    return false;
                }
            }
            if (!get_qur()) return false;
            if (qur.type == operation and qur.value == "-") {
                if (min_fl) {
                    if (!get_qur()) {
                        from_save_qur(s_i, s_q, s_l);
                        return false;
                    }
                }
                else {
                    from_save_qur(s_i, s_q, s_l);
                    return false;
                }
            }
            if (qur.type != int_type) { //second number
                from_save_qur(s_i, s_q, s_l);
                return false;
            }
        }
        //its ] after [a or [a..b construction
        if (qur.type != punctuation and qur.value != "]") {
            from_save_qur(s_i, s_q, s_l);
            return false;
        }
        if (!get_qur()) return false;
    }
    return true;
}

//ok
bool_error is_variable_declaration() {
    bool_error a;
    a.error.fill();
    a.val = false;
    if (qur.type != res_word and types.find(qur.value) == types.end()) return a;
    get_qur();
    if (qur.type != identificator) return a;
    get_qur();
    if (qur.value == "[") { //this is an array
        int s_i = next_index_in_main_vector;
        auto s_q = qur;
        int s_l = qur_line;
        if (not is_an_array()) {
            from_save_qur(s_i, s_q, s_l);
        }
    }
    a.val = true;
    return a;
}

bool_error is_op_return(string s) {
    bool_error a;
    a.error.fill();
    a.val = false;
    if(qur.value!="return"){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!get_qur()){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    if(!is_expression().val){
        a.error.fill(case_format_error, qur_line, qur);
        return a;                      //САША СПАСИ И СОХРАНИ, ДА ХРАНИТ ТЕБЯ АЛЛАХ
    }
    a.val=true;
    return a;
}



//asror
bool_error is_function_header() {

}

bool_error is_pocedure_header () {

}

bool_error is_main_header() {

}

//

bool_error is_double(){
    bool_error a;
    a.val = false;
    a.error.fill(); //default
    if (qur.type != number) return a;
    if (qur.value.size() > 19) return a; //max size of double 19
    a.error.word.value = qur.value;
    if (!get_qur()) return a;
    if (qur.type != punctuation) return a;
    if (qur.value != ".") return a;
    a.error.word.value += qur.value;
    if (!get_qur()) {
        a.error.fill(double_format_error, qur_line, qur);
        return a;
    }
    if (qur.type != number) {
        a.error.fill(double_format_error, qur_line, qur);
        return a;
    }
    a.error.word.value += qur.value;
    a.val = true;
    return a;
}

bool_error is_float() {
    bool_error a;
    a.val = false;
    a.error.fill(); //default;
    if (qur.value[0] == '0' or qur.value.size() != 1) return a;
    a.error.word.value = qur.value;
    if (!get_qur()) return a;
    if (qur.type != punctuation) return a;
    if (qur.value != ".") return a;
    a.error.word.value += qur.value;
    if (!get_qur()) {
        a.error.fill(float_format_error, qur_line, qur);
        return a;
    }
    if (qur.type != word) return a;
    if (qur.value[qur.value.size() - 1] != 'e') return a;
    for (int i = 0; i < qur.value.size() - 1; ++i) {
        if (numbers.find(qur.value[i]) == numbers.end()) return a;
    }
    a.error.word.value += qur.value;
    if (!get_qur()) return a;
    if (qur.type != operation) {
        a.error.fill(float_format_error, qur_line, qur);
        return a;
    }
    if (not ((qur.value[0] == '+' or qur.value[0] == '-') and qur.value.size() == 1)) {
        a.error.fill(float_format_error, qur_line, qur);
        return a;
    }
    a.error.word.value += qur.value;
    if (!get_qur() or qur.type != number or qur.value[0] == '0') {
        a.error.fill(float_format_error, qur_line, qur);
        return a;
    }
    a.error.word.value += qur.value;
    a.val = true;
    return a;
}

error check_char_constants () {
    error a;
    next_index_in_main_vector = 0;
    qur_line = 1;
    while (get_qur()) {
        if (qur.type == char_constant and qur.value.size() > 1) {
            a.fill(char_format_error, qur_line, qur);
            return a;
        }
    }
    return a;
}

error numbers_to_types() {
    next_index_in_main_vector = 0;
    qur_line = 1;
    bool_error a;
    int i = 0, ii = 1;
    while (get_qur()) {
        if (qur.type == number) {
            i = next_index_in_main_vector - 1; //index of current token which is "number"
            ii = qur_line;
            auto save_qur = qur;
            a = is_float();
            if (a.error.type != none) return a.error;
            if (a.val) {
                main_vector[i].value = a.error.word.value;
                main_vector[i].type = float_type;
                main_vector.erase(main_vector.begin() + i + 1, main_vector.begin() + i + 5);
                next_index_in_main_vector -= 4;
            }
            else {
                next_index_in_main_vector = i + 1;
                qur = save_qur;
                qur_line = ii;
                a = is_double();
                if (a.error.type != none) return a.error;
                if (a.val) {
                    main_vector[i].value = a.error.word.value;
                    main_vector[i].type = double_type;
                    main_vector.erase(main_vector.begin() + i + 1, main_vector.begin() + i + 3);
                    next_index_in_main_vector -= 2;
                }
                else {
                    next_index_in_main_vector = i + 1;
                    qur = save_qur;
                    qur_line = ii;
                    main_vector[i].type = int_type;
                }
            }
        }
    }
    return a.error;
}

error pre_sintax () {
    error a;
    a = check_char_constants();
    if (a.type != none) return a;
    a = numbers_to_types();
    if (a.type != none) return a;
    words_to_ident();
}

bool get_qur() {
    if (next_index_in_main_vector >= main_vector.size()) return false;
    qur = main_vector[next_index_in_main_vector];
    if (qur.type == my_eof) return false;
    if (qur.type == my_endl) {
        next_index_in_main_vector++;
        qur_line++;
        return(get_qur());
    }
    next_index_in_main_vector++;
    return true;
}


bool_error is_block (string s) { // !!!!!   includes its '{'           !!!
    bool_error a;
    a.val = false;
    a.error.fill(); //default
    //string s is the type of the function this block belongs to
    if (qur.value != "{") {
        a.error.fill(unexpected_token_error, qur_line, qur);
        return a;
    }
    //else
    while (not (qur.value == "}" or qur.type == my_eof) ) {
        get_qur();
        //save qur not to spoil anything with analises;
        int s_i = next_index_in_main_vector;
        auto s_q = qur;
        int s_l = qur_line;
        a = is_expression();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        // cycles
        a = is_op_do_while();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_while();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_for();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //choise
        a = is_op_case();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_if();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //goto
        a = is_op_break();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_continue();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //call
        a = is_function_call();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_procedure_call();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //new
        a = is_variable_declaration(); //or an array
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //other
        a = is_op_get();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_out();
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_op_return(s);
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        a = is_block(s);
        if (not a.val) {
            if (a.error.type == none) from_save_qur(s_i, s_q, s_l);
            else return a;
        }
        //if it's not an operator;
        if(not a.val) break;
        else {
            if (qur.type != res_word and qur.value != ";") {
                a.error.fill(syntax_error, qur_line, qur);
                a.val = false;
                break;
            }
        }
    }
    if (qur.value == "}") {
        a.val = true;
        return a;
    }
    else {
        if (qur.type == my_eof) a.error.fill (broken_bracket_balance, qur_line, qur);
        else a.error.fill (unexpected_token_error, qur_line, qur);
        return a;
    }


}

error in_syntax_analise() {
    error a;
    bool_error b;
    a = pre_sintax ();
    if (a.type != none) return a;
    next_index_in_main_vector = 0;
    qur_line = 1;
    while (get_qur())
    {
        //header
        if (qur.value == "^_^") { //main
            b = is_main_header();
            if (not b.val) { //a error in main found
                a = b.error;
                return a;
            }
        }
        else if (qur.value == ">_<") { //procedure
            b = is_pocedure_header();
            if (not b.val) { //a error in procedure found
                a = b.error;
                return a;
            }
        }
        else if (types.find(qur.value) != types.end()) { //function
            b = is_function_header();
            if (not b.val) { //a error in function found
                a = b.error;
                return a;
            }
        }
        else {
            a.fill(unexpected_token_error, qur_line, qur);
            return a;
        }
        //function or prototype
        if (qur.value == ";") {
            //semantic thing mb
        }
        else if (qur.value == "{") { // block analise
            b = is_block(qur.value);
            if (! b.val) {
                a = b.error;
                return a;
            }
        }
        else {
            a.fill(unexpected_token_error, qur_line, qur);
            return a;
        }
    }
    return a;
}

#endif //LEX_ANALISE_SYNTAX_H
