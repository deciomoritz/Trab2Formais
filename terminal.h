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
    void first() override;
};

#endif // TERMINAL_H
