#include "simbolo.h"

Simbolo::Simbolo()
{
}

Simbolos Simbolo::first(Simbolos *X, Simbolos* Ne){
}

string Simbolo::nome(){
    return _nome;
}

Simbolos Simbolo::get_first(Simbolos* Ne){
    if(this->_first.empty()){
        Simbolos s;
        s.insert(this);
       this->_first = this->first(&s, Ne);
    }
    return this->_first;
}
bool Simbolo::ehNTerminal(){
    string nome = this->nome();
    char * c = nome.c_str();
    return isupper(c[0]);
}

