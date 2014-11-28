#ifndef NTERMINAL_H
#define NTERMINAL_H

#include "simbolo.h"

#include "terminal.h"

#include <vector>
using std::vector;

#include <algorithm>

#include <set>
using std::set;

typedef vector<Simbolo*> FormaSentencial;

class NTerminal : public Simbolo{
    set<FormaSentencial> _producoes;
    Simbolos _first_NT, _follow;
    using Simbolo::first;

public:
    NTerminal();
    NTerminal(string nome);

    void addProducao(FormaSentencial f);
    set<FormaSentencial> * producoes();

    void first() override;
    void follow();
    using Simbolo::get_first;
    void first_NT(Simbolos *Ne);
    static bool ehNTerminal(Simbolo a);
    Simbolos get_first_NT(Simbolos *Ne);
    Simbolos get_follow();

    bool ehRE(Simbolos * Ne);
    
    bool derivaEpsilonDiretamente();
    bool firstContemEpsilon(Simbolos s);
    static void removerEpsilon(Simbolos * s);

    static bool somenteTerminais(FormaSentencial fs);
    static bool somenteNTerminais(FormaSentencial fs);
};

#endif // NTERMINAL_H
