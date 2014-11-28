#include "gramatica.h"

Gramatica::Gramatica()
{
}

void Gramatica::calculaNe(){

    for(auto B = _NTerminais.begin(); B != _NTerminais.end();B++){
        NTerminal * s = *B;
        if(s->derivaEpsilonDiretamente())
            _Ne.insert(s);
    }

    Simbolos novoNe;

    do{
        novoNe.insert(_Ne.begin(), _Ne.end());
        for(auto B = _NTerminais.begin(); B != _NTerminais.end();B++){
            NTerminal * nt = *B;
            for(auto A = nt->producoes()->begin(); A != nt->producoes()->end();A++){
                FormaSentencial fs = *A;

                bool derivaE = true;
                if(NTerminal::somenteNTerminais(fs)){
                    for (int i = 0; i < fs.size(); ++i) {
                        Simbolo * s = fs.at(i);
                        if(_Ne.find(s) == _Ne.end())
                            derivaE = false;
                    }
                    if(derivaE)
                        _Ne.insert(nt);
                }
            }
        }
    }while(_Ne != novoNe);
}

bool Gramatica::derivaEpsilon(NTerminal * nt){
    return _Ne.find(nt) != _Ne.end();
}

Simbolos * Gramatica::Ne(){
    return &_Ne;
}

void Gramatica::addNTerminal(NTerminal * nt){
    _NTerminais.insert(nt);
}

void Gramatica::eliminarInferteis(){
    set<NTerminal*> ferteis;
    set<NTerminal*> novoFerteis;

    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        bool fertil = false;
        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            if(NTerminal::somenteTerminais(fs))
                fertil = true;
        }
        if(fertil)
            ferteis.insert(nt);
    }

    do{
        novoFerteis = ferteis;
        for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
            NTerminal * nt = *A;

            bool fert = false;
            for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
                FormaSentencial fs = *B;

                if(fertil(fs, ferteis))
                    fert = true;
            }
            if(fert)
                ferteis.insert(nt);
        }
    }while(ferteis.size() != novoFerteis.size());

    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            if(!fertil(fs, ferteis))
                nt->producoes()->erase(B);
        }
    }

    _NTerminais.clear();
    _NTerminais.insert(ferteis.begin(),ferteis.end());
}

void Gramatica::eliminarInuteis(){
    this->eliminarInalcancaveis();
    this->eliminarInferteis();
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

        if(nt->nome().compare(_inicial->nome()) == 0)
            saida += nt->nome()+"(inicial)" + " -> ";
        else
            saida += nt->nome() + " -> ";
        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            for (int i = 0; i < fs.size(); ++i)
                saida += fs.at(i)->nome() + " ";

            saida += "| ";
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

bool Gramatica::fertil(FormaSentencial fs, set<NTerminal*> ferteis){
    set<NTerminal*> nTerminais;

    for (int i = 0; i < fs.size(); ++i) {
        Simbolo * s = fs.at(i);
        string tipo = typeid(*s).name();
        tipo.erase(tipo.begin());
        if(tipo.compare("NTerminal") == 0)
            nTerminais.insert(s);
    }
    for(auto A = nTerminais.begin(); A != nTerminais.end();A++){
        NTerminal * nt = *A;

        bool contido = false;
         for(auto B = ferteis.begin(); B != ferteis.end();B++){
            NTerminal * fert = *B;

            if(nt->nome().compare(fert->nome()) == 0)
                contido = true;
         }
         if(!contido)
             return false;
         contido = false;
    }
    return true;
}

unordered_map<Simbolo*,Simbolos> Gramatica::first_NT(){
    unordered_map<Simbolo*,Simbolos> retorno;
    for(auto it = _NTerminais.begin(); it!= _NTerminais.end(); it++){
        NTerminal *A = (*it);
        retorno.insert({A, A->get_first_NT(&_Ne)});
    }
    return retorno;
}

unordered_map<Simbolo*,Simbolos> Gramatica::first(){
    unordered_map<Simbolo*,Simbolos> retorno;
    for(auto it = _NTerminais.begin(); it!= _NTerminais.end(); it++){
        NTerminal *A = (*it);
        retorno.insert({A, A->get_first()});
    }
    return retorno;
}

unordered_map<Simbolo*,Simbolos> Gramatica::follow(){
    unordered_map<Simbolo*,Simbolos> retorno;
    for(auto it = _NTerminais.begin(); it!= _NTerminais.end(); it++){
        NTerminal *A = (*it);
        retorno.insert({A, A->get_follow()});
    }
    return retorno;
}

void Gramatica::calculaFirst(){

    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
            FormaSentencial fs = *B;

            for(auto C = fs.begin(); C != fs.end();C++){
                Simbolo * s = *C;

                if(!NTerminal::ehNTerminal(*s)){
                    nt->getFirst()->insert(s);
                }else{
                    NTerminal * nt2 = s;
                    if(nt2->ehRE(&_Ne))
                        break;
                    nt2->first();
                    nt->getFirst()->insert(nt2->getFirst()->begin(), nt2->getFirst()->end());
                    break;
                }
            }
        }
    }

    Simbolos newFirst;
    bool houveAlteracao = false;

    do{
        for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
            NTerminal * nt = *A;
            newFirst.insert(nt->getFirst()->begin(), nt->getFirst()->end());

            for(auto B = nt->producoes()->begin(); B != nt->producoes()->end();B++){
                FormaSentencial fs = *B;

                bool continuar = false;
                for(auto C = fs.begin(); C != fs.end();C++){
                    Simbolo * s = *C;
                    if(NTerminal::ehNTerminal(*s)){
                        NTerminal * nt2 = s;
                        if(!nt2->ehRE(&_Ne) && !continuar)
                            break;
                        continuar = false;
                        nt->getFirst()->insert(nt2->getFirst()->begin(),nt2->getFirst()->end());

                        houveAlteracao = false;
                        if(*nt->getFirst() != newFirst)
                            houveAlteracao = true;

                        if(derivaEpsilon(nt2))
                            continuar = true;
                    }else
                        break;
                }
            }
        }
    }while (houveAlteracao);

    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        if(!derivaEpsilon(nt))
            NTerminal::removerEpsilon(nt->getFirst());
    }
}
