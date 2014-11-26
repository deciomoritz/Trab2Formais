#ifndef TERMINAL_H
#define TERMINAL_H

#include "simbolo.h"

#include <iostream>
using namespace::std;

class Terminal : public Simbolo{

    string _nome;

public:
    Terminal();
    Terminal(string nome);

    Simbolos first() override;
    Simbolos follow() override;

};

#endif // TERMINAL_H
