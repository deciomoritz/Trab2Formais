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

Simbolos NTerminal::first(){
    Simbolos first;
    for(auto A = _producoes.begin(); A != _producoes.end();A++){
        FormaSentencial fs = *A;
            int i =0;      //para iterar cada símbolo da produção
            bool e_found = true; //encontrou um & como first.
            Simbolos temp; //armazena o first intermediário para verificar se há & transição
            do{
                e_found = false;
                temp = fs.at(i)->get_first();  // calcule o first do primeiro símbolo.

//                first = first U temp;
                first.insert(temp.begin(), temp.end());

               if(firstContemEpsilon(temp)){ //encontrou & transição;
                    if(i != fs.size() - 1){	//se ainda não for o último símbolo da produção, não se pode concluir que & pertence a first ainda. Calcular first do próximo.
                        e_found = true; //avisa que & foi encontrado e
                        i++;//indice para calcular o first do próximo símbolo
                        removerEpsilon(first); //& foi adicionado ao retorno por engano.
                    }
                }
            }while(e_found);
    this->_first = first;
    }
}

Simbolos NTerminal::follow(){
    Simbolos s;
    cout << "porra";
    return s;
}

bool NTerminal::firstContemEpsilon(Simbolos s){
    bool encontrou = false;
    for(auto A = s.begin(); A != s.end();A++){
        Simbolo * s1 = *A;
        encontrou = s1->nome().compare(string("&")) == 0;
    }
    return encontrou;
}

void NTerminal::removerEpsilon(Simbolos s){
    for(auto A = s.begin(); A != s.end();A++){
        Simbolo * s1 = *A;
        if(s1->nome().compare(string("&")) == 0)
            s.erase(A);
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
