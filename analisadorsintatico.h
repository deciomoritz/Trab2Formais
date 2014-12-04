#ifndef ANALISADORSINTATICO_H
#define ANALISADORSINTATICO_H

#include<stack>
using std::stack;

#include "leitorgramatica.h"

class AnalisadorSintatico
{
public:
    AnalisadorSintatico();

    static bool analisar(string sentenca, Gramatica g);
    static Sentenca lerSentenca(string s, Gramatica g);
};

#endif // ANALISADORSINTATICO_H
