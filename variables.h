//
// Created by Alex on 29.01.2020.
//

#ifndef LEX_ANALISE_VARIABLES_H
#define LEX_ANALISE_VARIABLES_H
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "token.h"
#include <fstream>
using namespace std;

// LEX VARIABLES

ifstream file;
vector <token> main_vector;
set <string> r_words = { "^_^", ">_<", "case", "of", "do", "break", "continue", "if", "then", "else", "return", "while", "for", "and", "or", "null", "get", "out", "float", "bool", "true", "false", "string", "int", "double", "char", "pi", "exp"};
set <string> types = {"float", "bool", "string", "int", "double", "char"};
set <char> r_punctiation = { ',' , ';' , ':' , '.' , '(' , ')' , '[' , ']' , '{' , '}' , '\"', '\''};
set <string> operators_single{ "+", "-", "*", "/", "=", "<", ">", "^"};
set <string> operators_many { "or", "and", ">=", "<=", "==", "!=", "mod", "div", "not", "++", "--", "+=", "-=", "*=", "/=", "%=", "^="};
set <string> constants { "true", "false", "pi", "exp"};
set <char> numbers;
set <char> letters;


// SINTAX VARIABLES

#endif //LEX_ANALISE_VARIABLES_H