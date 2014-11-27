#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

#include<set>
using std::set;

#include "nterminal.h"

class Gramatica
{
    NTerminal * _inicial;
    set<NTerminal*> _NTerminais;

public:
    Gramatica();

    void addNTerminal(NTerminal * nt);

    void eliminarInferteis();
    void eliminarInalcancaveis();

    void setInicial(NTerminal * inicial);

    set<NTerminal*> * nTerminais();

    Simbolos first();
    Simbolos follow();

    Simbolo * contem(set<NTerminal*> simbolos, NTerminal s);

    string print();
};

#endif // GRAMATICA_H
