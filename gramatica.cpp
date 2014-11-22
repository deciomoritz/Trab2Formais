#include "gramatica.h"

Gramatica::Gramatica()
{
}

void Gramatica::addProducao(Regra r){
    set<FormaSentencial> s;
    s.insert(r.ladoEsquerdo);
    Producao p = make_pair(r.ladoEsquerdo,s);
    _producoes.insert(p);
    _NTerminais.insert(r.ladoEsquerdo);
}

void Gramatica::addProducao(NTerminal nt, FormaSentencial fs){
    addProducao(Regra(nt, fs));
}

set<FormaSentencial> * Gramatica::getLadoDireito(NTerminal nt){
//    std::unordered_map<NTerminal, set<FormaSentencial>>::iterator got = _producoes.find(nt);
//    return &got->second;
    return &_producoes.find(nt)->second;
}

set<Simbolo> Gramatica::first(FormaSentencial fs){

}

set<Simbolo> Gramatica::follow(FormaSentencial fs){

}
