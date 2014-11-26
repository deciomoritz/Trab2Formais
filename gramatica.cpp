#include "gramatica.h"

Gramatica::Gramatica()
{
}

void Gramatica::addNTerminal(NTerminal * nt){
    _NTerminais.insert(nt);
}
