#include "terminal.h"

Terminal::Terminal()
{
}

Terminal::Terminal(string nome){
    _nome = nome;
}

Simbolos Terminal::first(Simbolos *X, Simbolos* Ne){
    _first.insert(this);
    return _first;
}

Simbolo * Terminal::contem(set<Terminal*> simbolos, Terminal s){
    for(auto A = simbolos.begin(); A != simbolos.end();A++){
        Terminal * s1 = *A;
        if(s1->nome().compare(s.nome()) == 0)
            return s1;
    }
    return NULL;
}
