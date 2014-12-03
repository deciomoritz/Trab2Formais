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
    using Simbolo::get_first;
    using Simbolo::ehNTerminal;

    NTerminal();
    NTerminal(string nome);

    void addProducao(FormaSentencial f);
    set<FormaSentencial> * producoes();
    void set_follow(Simbolos *S);
    Simbolos* get_follow();

    Simbolos first(Simbolos *X, Simbolos* Ne) override;

    void first_NT(Simbolos *Ne);
    bool ehNTerminal(Simbolo a);
    Simbolos get_first_NT(Simbolos *Ne);

    bool ehRE(Simbolos * Ne);
    
    bool derivaEpsilonDiretamente();
    static bool contemEpsilon(Simbolos s);
    static void removerEpsilon(Simbolos *s);

    static Simbolo * contem(set<NTerminal*> simbolos, NTerminal s);

    static bool somenteTerminais(FormaSentencial fs);
    static bool somenteNTerminais(FormaSentencial fs);
};

#endif // NTERMINAL_H
