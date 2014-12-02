#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

#include<set>
using std::set;

#include "nterminal.h"

//Terminal * _epsilon;
//Terminal * _dollar;


class Gramatica
{
    NTerminal * _inicial;
    set<NTerminal*> _NTerminais;
    set<Terminal*> _alfabeto;
    Simbolos _Ne;

public:
    Gramatica();

    void addNTerminal(NTerminal * nt);

    void eliminarInferteis();
    void eliminarInalcancaveis();
    void eliminarInuteis();

    void setInicial(NTerminal * inicial);

    set<NTerminal*> * nTerminais();
    set<Terminal*> * alfabeto();

    unordered_map<Simbolo*,Simbolos>  first_NT();
    unordered_map<Simbolo*,Simbolos>  first();
    void follow();
    void get_first(FormaSentencial::iterator it,FormaSentencial::iterator end, Simbolos * s);

    bool fertil(FormaSentencial fs, set<NTerminal*> ferteis);

    void calculaNe();
    Simbolos * Ne();
    bool derivaEpsilon(NTerminal * nt);

    Terminal * getEpsilon();
    Terminal * getDollar();

    string print();
};

#endif // GRAMATICA_H
