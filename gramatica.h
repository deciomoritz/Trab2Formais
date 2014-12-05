#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

#include<set>
using std::set;

#include "nterminal.h"

typedef vector<Terminal*> Sentenca;

class Gramatica
{
    NTerminal * _inicial;
    set<NTerminal*> _NTerminais;
    set<Terminal*> _alfabeto;
    Simbolos _Ne;
    unordered_map<FormaSentencial*, int> _FSparaInt;
    unordered_map<NTerminal*,unordered_map<Terminal*,FormaSentencial*>> _tabelaParse;

public:
    Gramatica();

    void addNTerminal(NTerminal * nt);

    void eliminarInferteis();
    void eliminarInalcancaveis();
    void eliminarInuteis();

    void construirTabelaParse();
    void calculaNe();
    void setInicial(NTerminal * inicial);
    void follow();

    void setFSParaInt( unordered_map<FormaSentencial*, int> fs){
        _FSparaInt = fs;
    }

    void get_first(FormaSentencial::iterator it,FormaSentencial::iterator end, Simbolos * s);

    unordered_map<Simbolo*,Simbolos>  first_NT();
    unordered_map<Simbolo*,Simbolos>  first();

    unordered_map<FormaSentencial*, int> * FSparaInt(){
        return &_FSparaInt;
    }

    set<NTerminal*> * nTerminais(){
        return &_NTerminais;
    }

    NTerminal * inicial(){
        return _inicial;
    }

    Simbolos * Gramatica::Ne(){
        return &_Ne;
    }

    set<Terminal*> * alfabeto(){
        return &_alfabeto;
    }

    unordered_map<NTerminal*,unordered_map<Terminal*,FormaSentencial*>> * tabelaParse(){
        return &_tabelaParse;
    }

    Terminal * getEpsilon();
    Terminal * getDollar();


    bool fertil(FormaSentencial fs, set<NTerminal*> ferteis);
    bool derivaEpsilon(NTerminal * nt);
    bool testaLL1();
    bool possuiRE();
    bool testaFatorada();
    bool testaFirstFollow();
    bool interseccaoVazia(vector<Simbolos> conj);

    string printaGramatica();
    string printaGramaticaNumerada();
    string printarTP();
    string printarTPParaDebug();

};

#endif // GRAMATICA_H
