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

    using Simbolo::first;

public:
    NTerminal();
    NTerminal(string nome);

    void addProducao(FormaSentencial f);
    set<FormaSentencial> * producoes();

    Simbolos first() override;
    Simbolos follow() override;

    bool derivaEpsilonDiretamente();

    bool firstContemEpsilon(Simbolos s);
    void removerEpsilon(Simbolos s);

    static bool somenteTerminais(FormaSentencial fs);
    static bool somenteNTerminais(FormaSentencial fs);
};

#endif // NTERMINAL_H
