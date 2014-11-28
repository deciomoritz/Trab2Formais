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
    Simbolos _Ne;

public:
    Gramatica();

    void addNTerminal(NTerminal * nt);

    void eliminarInferteis();
    void eliminarInalcancaveis();
    void eliminarInuteis();

    void setInicial(NTerminal * inicial);

    set<NTerminal*> * nTerminais();

    unordered_map<Simbolo*,Simbolos>  first_NT();
    unordered_map<Simbolo*,Simbolos>  first();
    unordered_map<Simbolo*,Simbolos> follow();

    Simbolo * contem(set<NTerminal*> simbolos, NTerminal s);

    bool fertil(FormaSentencial fs, set<NTerminal*> ferteis);

    void calculaNe();
    Simbolos * Ne();
    bool derivaEpsilon(NTerminal * nt);

    string print();
};

#endif // GRAMATICA_H
