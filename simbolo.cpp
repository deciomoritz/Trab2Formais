#include "simbolo.h"

Simbolo::Simbolo()
{
}

void Simbolo::first(){
    /*Simbolos s;
    return s;*/
}

string Simbolo::nome(){
    return _nome;
}

Simbolos Simbolo::get_first(){
    if(this->_first.empty())
        this->first();
    return this->_first;
}

