#include "gramatica.h"

Gramatica::Gramatica()
{
}

Terminal _dollar("$");
Terminal _epsilon("&");

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
                if(s->ehNTerminal()){
                    NTerminal * aux = s;
                    if(!NTerminal::contem(alcancaveis, *aux))
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
        if(s->ehNTerminal())
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
        retorno.insert({A, A->get_first(&_Ne )});
    }
    return retorno;
}

void Gramatica::follow(){
    bool atualizou;
    _inicial->get_follow()->insert(&_dollar);
    do{
        atualizou = false;
        for(auto it_firstNT = _NTerminais.begin(); it_firstNT != _NTerminais.end(); it_firstNT++){
            NTerminal *A = *it_firstNT;
            set<FormaSentencial> *prod_A = A->producoes();
            for(auto it_prod = prod_A->begin(); it_prod != prod_A->end(); it_prod++){
                FormaSentencial fs = *it_prod;
                for(auto it_simb = fs.begin(); it_simb != fs.end(); it_simb++){
                    Simbolo *x = *it_simb;
                    if(!x->ehNTerminal()) // se é um símbolo Terminal, ler o próximo
                        continue;
                    NTerminal *nt = x;
                    Simbolos* nt_follow = nt->get_follow();
                    if(it_simb == --fs.end()){//ele é o último não terminal da sentença
                        Simbolos *s1 = A->get_follow();
                        int tamanho_velho = nt_follow->size();
                        nt_follow->insert(s1->begin(), s1->end()); // coloca o follow de A nele
                        int tamanho_novo = nt_follow->size();
                        if(!atualizou) atualizou = tamanho_velho!=tamanho_novo;//se o tamanho do velho for igual ao novo, foi adicionado algo ao follow
                        break;
                    }
                    Simbolos first;
                    get_first((++it_simb), (fs.end()), &first);
                    --it_simb;
                    int tamanho_velho = nt_follow->size();
                    if(NTerminal::firstContemEpsilon(first)){
                            NTerminal::removerEpsilon(&first);
                        nt_follow->insert(A->get_follow()->begin(), A->get_follow()->end());
                    }
                    nt_follow->insert(first.begin(), first.end());
                    int tamanho_novo = nt_follow->size();
                   if(!atualizou) atualizou = tamanho_velho!=tamanho_novo;//se o tamanho do velho for igual ao novo, foi adicionado algo ao follow
                }
            }
        }
    }while(atualizou);
}

void Gramatica::get_first(FormaSentencial::iterator it,FormaSentencial::iterator end, Simbolos * retorno){
    //retorna o first de uma forma sentencial. esses elementos serão o follow de outro símbolo que fez a chamada.
    if(it == end)
        return;

    Simbolo * aux = *it;
    Simbolos first = aux->get_first(&_Ne);

    if(NTerminal::firstContemEpsilon(first)){
        if(++it != end){
            NTerminal::removerEpsilon(&first);
            it--;
            get_first(++it, end, retorno);
        }
    }
    retorno->insert(first.begin(), first.end());
}

set<Terminal*> * Gramatica::alfabeto(){
    return &_alfabeto;
}

Terminal * Gramatica::getEpsilon(){
    return &_epsilon;
}

Terminal * Gramatica::getDollar(){
    return &_dollar;
}
