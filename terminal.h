#ifndef TERMINAL_H
#define TERMINAL_H

#include "simbolo.h"

#include <iostream>
using namespace::std;

class Terminal : public Simbolo{

public:
    Terminal();
    Terminal(string nome);
    using Simbolo::get_first;
    using Simbolo::ehNTerminal;
    Simbolos first(Simbolos *X, Simbolos* Ne) override;

    static Simbolo * contem(set<Terminal*> simbolos, Terminal s);
};

#endif // TERMINAL_H
