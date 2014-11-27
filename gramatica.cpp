#include "gramatica.h"

Gramatica::Gramatica()
{
}

void Gramatica::addNTerminal(NTerminal * nt){
    _NTerminais.insert(nt);
}

void Gramatica::eliminarInferteis(){

}

void Gramatica::eliminarInalcancaveis(){

    set<NTerminal*> alcancaveis;
    alcancaveis.insert(_inicial);
    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            for (int i = 0; i < fs.size(); ++i){
                Simbolo * s = fs.at(i);
                string tipo = typeid(*s).name();
                tipo.erase(tipo.begin());
                if(tipo.compare("NTerminal") == 0){
                    NTerminal * aux = s;
                    if(!contem(alcancaveis, *aux))
                        alcancaveis.insert(s);
                }
            }
        }
    }
    _NTerminais.clear();
    _NTerminais.insert(alcancaveis.begin(),alcancaveis.end());
}

string Gramatica::print(){
    string saida = "";
    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        saida += nt->nome() + " -> ";
        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            for (int i = 0; i < fs.size(); ++i)
                saida += fs.at(i)->nome();

            saida += " | ";
        }
        saida.pop_back();
        saida.pop_back();
        saida += "\n";
    }
    return saida;
}

Simbolo * Gramatica::contem(set<NTerminal*> simbolos, NTerminal s){
    for(auto A = simbolos.begin(); A != simbolos.end();A++){
        NTerminal * s1 = *A;
        if(s1->nome().compare(s.nome()) == 0)
            return s1;
    }
    return NULL;
}

void Gramatica::setInicial(NTerminal * inicial){
    _inicial = inicial;
}

set<NTerminal*> * Gramatica::nTerminais(){
    return &_NTerminais;
}
