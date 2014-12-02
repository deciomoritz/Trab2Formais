#include "nterminal.h"

NTerminal::NTerminal()
{
}

extern Terminal _dollar;
extern Terminal _epsilon;

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
                    if(!x->ehNTerminal())
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
    if(!adicionou){
        novo.erase(this);
    }
    _first_NT.insert(novo.begin(), novo.end());
}
Simbolos NTerminal::get_first_NT(Simbolos *Ne){
    if(this->_first_NT.empty())
        this->first_NT(Ne);
    return this->_first_NT;
}

Simbolos NTerminal::first(Simbolos *X, Simbolos* Ne){
    Simbolos first;

    for(auto A = _producoes.begin(); A != _producoes.end();A++){
        FormaSentencial fs = *A;
        int i = 0;      //para iterar cada símbolo da produção
        bool e_found; //encontrou um & como first.
        Simbolos temp; //armazena o first intermediário para verificar se há & transição
        do{
            e_found = false;
            if(X->find(fs.at(i)) != X->end()){   // RE

                if(Ne->find(fs.at(i))!=Ne->end()){ //se Este símbolo leva a &
                    if(i != fs.size() - 1){//e ele não é o último, procura pelo próximo
                        i++;
                        e_found = true;
                        continue;
                    }
                    else{       //se ele for o último, adiciona & continua por outras produções;
                        first.insert(&_epsilon);
                        break;
                    }
                }
                else
                    break;
            }
            Simbolos teste = *X;
            teste.insert(fs.at(i));
            temp = fs.at(i)->first(&teste, Ne); // calcule o first do primeiro símbolo.
            teste.erase(fs.at(i));
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
    if(Ne->find(this) == Ne->end())
        removerEpsilon(&first);
    return first;
}

bool NTerminal::firstContemEpsilon(Simbolos s){
    for(auto A = s.begin(); A != s.end();A++){
        Simbolo * s1 = *A;
        if(s1->nome().compare(string("&")) == 0)
            return true;
    }
    return false;
}

void NTerminal::removerEpsilon(Simbolos *s){
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
Simbolos* NTerminal::get_follow(){
    return &_follow;
}
void NTerminal::set_follow(Simbolos *s){
    _follow.insert(s->begin(), s->end());
}

bool NTerminal::ehRE(Simbolos * Ne){
    Simbolos * firstNT = &get_first_NT(Ne);
    return firstNT->find(this) != firstNT->end();
}

Simbolo * NTerminal::contem(set<NTerminal*> simbolos, NTerminal s){
    for(auto A = simbolos.begin(); A != simbolos.end();A++){
        NTerminal * s1 = *A;
        if(s1->nome().compare(s.nome()) == 0)
            return s1;
    }
    return NULL;
}
