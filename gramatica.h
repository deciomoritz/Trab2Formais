#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

#include<set>
using std::set;

typedef string NTerminal;
typedef string FormaSentencial;
typedef string Simbolo;
typedef std::pair<NTerminal, set<FormaSentencial>> Producao; //chamar de produção o lado esquerdo e TODO o lado direito

struct Regra{ //chamar de regra apenas o lado esquerdo e UMA produção do lado direito
    NTerminal ladoEsquerdo;
    FormaSentencial ladoDireito;

    Regra(NTerminal nTerminal, FormaSentencial fs){
        ladoEsquerdo = nTerminal;
        ladoDireito = fs;
    }
};

class Gramatica
{
    unordered_map<NTerminal, set<FormaSentencial>> _producoes;
    NTerminal _inicial;
    set<NTerminal> _NTerminais;

    void addProducao(Regra r);
    void addProducao(NTerminal nt, FormaSentencial fs);
    set<FormaSentencial> * getLadoDireito(NTerminal nt);

    set<Simbolo> first(FormaSentencial fs);
    set<Simbolo> follow(FormaSentencial fs);

public:
    Gramatica();

};

#endif // GRAMATICA_H
