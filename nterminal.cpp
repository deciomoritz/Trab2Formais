#include "nterminal.h"

NTerminal::NTerminal()
{
}

NTerminal::NTerminal(string nome){
    _nome = nome;
}

void NTerminal::addProducao(FormaSentencial f){
    _producoes.insert(f);
}

set<FormaSentencial> * NTerminal::producoes(){
    return &_producoes;
}

void NTerminal::first_NT(Simbolos *Ne){
    Simbolos velho, novo;
    novo.insert(this);
    bool adicionou = false;
    do{
        velho = novo;
        for(auto it_firstNT = velho.begin(); it_firstNT != velho.end(); it_firstNT++){
            NTerminal *a = *it_firstNT;
            set<FormaSentencial> prod_a = a->_producoes;
            for(auto it_prod = prod_a.begin(); it_prod != prod_a.end(); it_prod++){
                FormaSentencial fs = *it_prod;
                for(auto it_simb = fs.begin(); it_simb != fs.end(); it_simb++){
                    Simbolo *x = *it_simb;
                    if(!ehNTerminal(*x))
                        break;
                    if(x == this)
                        adicionou = true;
                    novo.insert(x);
                    if(Ne->find(x)==Ne->end())
                        break;
                }
            }
        }

    }while(velho != novo);

    if(!adicionou)
        novo.erase(this);

    _first_NT.insert(novo.begin(), novo.end());
}

Simbolos NTerminal::get_first_NT(Simbolos *Ne){
    if(this->_first_NT.empty())
        this->first_NT(Ne);
    return this->_first_NT;
}

bool NTerminal::ehNTerminal(Simbolo a){
    string nome = a.nome();
    char * c = nome.c_str();
    return isupper(c[0]);
}

void NTerminal::first(){
    Simbolos first;

    for(auto A = _producoes.begin(); A != _producoes.end();A++){
        FormaSentencial fs = *A;
        int i =0;      //para iterar cada símbolo da produção
        bool e_found; //encontrou um & como first.
        Simbolos temp; //armazena o first intermediário para verificar se há & transição
        do{
            e_found = false;
            temp = fs.at(i)->get_first();  // calcule o first do primeiro símbolo.
            first.insert(temp.begin(), temp.end());//                first = first U temp;
            if(firstContemEpsilon(temp)){ //encontrou & transição;
                if(i != fs.size() - 1){ //se ainda não for o último símbolo da produção, não se pode concluir que & pertence a first ainda. Calcular first do próximo.
                    e_found = true; //avisa que & foi encontrado e
                    i++;//indice para calcular o first do próximo símbolo
                    removerEpsilon(&first); //& foi adicionado ao retorno por engano.
                }
            }
        }while(e_found);
    }
    this->_first.insert(first.begin(), first.end());
}

void NTerminal::follow(){
    Simbolos s;
    cout << "porra";
    this->_follow = s;
}
Simbolos NTerminal::get_follow(){
    if(this->_follow.empty())
        this->follow();
    return this->_follow;
}

bool NTerminal::firstContemEpsilon(Simbolos s){
    bool encontrou = false;
    for(auto A = s.begin(); A != s.end();A++){
        Simbolo * s1 = *A;
        encontrou = s1->nome().compare(string("&")) == 0;
    }
    return encontrou;
}

void NTerminal::removerEpsilon(Simbolos * s){
    for(auto A = s->begin(); A != s->end();A++){
        Simbolo * s1 = *A;
        if(s1->nome().compare(string("&")) == 0)
            s->erase(A);
    }
}

bool NTerminal::derivaEpsilonDiretamente(){

    for(auto A = _producoes.begin(); A != _producoes.end();A++){
        FormaSentencial fs = *A;

        if(fs.front()->nome().compare(string("&")) == 0)
            return true;

        if(NTerminal::somenteNTerminais(fs)){
            for (int i = 0; i < fs.size(); ++i) {
                Simbolo * s = fs.at(i);
                if(s->nome().compare(string("&")) == 0)
                    return true;
            }
        }
    }
    return false;
}

bool NTerminal::somenteTerminais(FormaSentencial fs){
    for (int i = 0; i < fs.size(); ++i) {
        Simbolo * s = fs.at(i);
        string tipo = typeid(*s).name();
        tipo.erase(tipo.begin());
        if(tipo.compare("NTerminal") == 0)
            return false;
    }
    return true;
}

bool NTerminal::somenteNTerminais(FormaSentencial fs){
    for (int i = 0; i < fs.size(); ++i) {
        Simbolo * s = fs.at(i);
        string tipo = typeid(*s).name();
        tipo.erase(tipo.begin());
        if(tipo.compare("Terminal") == 0)
            return false;
    }
    return true;
}

bool NTerminal::ehRE(Simbolos * Ne){
    Simbolos * firstNT = &get_first_NT(Ne);
    return firstNT->find(this) != firstNT->end();
}
