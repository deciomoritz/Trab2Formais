#include "simbolo.h"

Simbolo::Simbolo()
{
}

Simbolos Simbolo::first(){
    Simbolos s;
    return s;
}

Simbolos Simbolo::follow(){

}

string Simbolo::nome(){
    return _nome;
}

Simbolos Simbolo::get_first(){
    if(this->_first.empty())
        this->first();
    return this->_first;
}
