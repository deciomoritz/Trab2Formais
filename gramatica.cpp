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

Terminal * Gramatica::getEpsilon(){
    return &_epsilon;
}

Terminal * Gramatica::getDollar(){
    return &_dollar;
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

string Gramatica::printaGramatica(){

    string saida = "";
    vector<string> saida2;

    int iniPos = 0;
    int k = 0;

    for(auto A = _NTerminais.begin(); A != _NTerminais.end();A++){
        NTerminal * nt = *A;

        if(nt->nome().compare(_inicial->nome()) == 0)
            iniPos = k;

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
        saida2.push_back(saida);
        saida = "";
        k++;
    }

    saida = saida2.at(iniPos);
    for (int i = 0; i < saida2.size(); ++i) {
        if(i == iniPos)
            continue;
        saida += saida2.at(i);
    }

    return saida;
}

void Gramatica::setInicial(NTerminal * inicial){
    _inicial = inicial;
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
                    if(NTerminal::contemEpsilon(first)){
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

    if(NTerminal::contemEpsilon(first)){
        if(++it != end){
            NTerminal::removerEpsilon(&first);
            it--;
            get_first(++it, end, retorno);
        }
    }
    retorno->insert(first.begin(), first.end());
}

void Gramatica::construirTabelaParse(){

    unordered_map<NTerminal*,unordered_map<Terminal*,pair<FormaSentencial,int>>> tabela;

    int k = 1;

    for(auto it_NTs = _NTerminais.begin(); it_NTs != _NTerminais.end(); it_NTs++){
        NTerminal * nt = *it_NTs;
        for(auto it_prod = nt->producoes()->begin(); it_prod != nt->producoes()->end(); it_prod++){
            FormaSentencial fs = *it_prod;

            Simbolos first;
            get_first(fs.begin(), fs.end(), &first);

            FormaSentencial prodQueContemEpsilon;
            if(NTerminal::contemEpsilon(first)){
                prodQueContemEpsilon = fs;

                Simbolos * follow = nt->get_follow();

                for(auto it_follow = follow->begin(); it_follow != follow->end(); it_follow++){
                    Simbolo * terminal = *it_follow;

                    tabela[nt][terminal] = make_pair(fs,k);
                }
            }

            for(auto it_first = first.begin(); it_first != first.end(); it_first++){
                Simbolo * terminal = *it_first;

                if(terminal->nome().compare(_epsilon.nome()) == 0)
                    continue;

                tabela[nt][terminal] = make_pair(fs,k);
            }
            k++;
        }
    }
    _tabelaParse = tabela;
}

string Gramatica::printarTP(){

    string tabela;

    tabela += "\t";

    for(auto it_Ts = _alfabeto.begin(); it_Ts != _alfabeto.end(); it_Ts++){
        Terminal * t = *it_Ts;
        tabela += t->nome() + "\t";
    }
    tabela += "$\t";
    tabela += "\n";

    for(auto it_NTs = _NTerminais.begin(); it_NTs != _NTerminais.end(); it_NTs++){
        NTerminal * nt = *it_NTs;
        tabela += nt->nome() + "\t";
        for(auto it_Ts = _alfabeto.begin(); it_Ts != _alfabeto.end(); it_Ts++){
            Terminal * t = *it_Ts;

            pair<FormaSentencial,int> fs = _tabelaParse[nt][t];

            if(fs.first.begin() != fs.first.end())
                tabela += to_string(fs.second);
            else
                tabela += "-";

            tabela += "\t";
        }
        pair<FormaSentencial,int> fs2 = _tabelaParse[nt][&_dollar];
        if(fs2.first.begin() != fs2.first.end())
            tabela += to_string(fs2.second);
        else
            tabela += "-";

        tabela += "\t";

        tabela += "\n";
    }
    return tabela;
}

bool Gramatica::testaRE(){
    for(auto it_NT = _NTerminais.begin(); it_NT!= _NTerminais.end(); it_NT++){
        NTerminal *nt = *it_NT;
        vector<Simbolos> teste;
        Simbolos conj;
        conj.insert(nt);
        teste.push_back(conj);
        teste.push_back(nt->get_first_NT(&_Ne));
        if(!interseccaoVazia(teste))
            return true;
    }
    return false;
}

bool Gramatica::testaFatorada(){
    for(auto it_NT = _NTerminais.begin(); it_NT!= _NTerminais.end(); it_NT++){
        NTerminal *nt = *it_NT;
        set<FormaSentencial> *prod = nt->producoes();
        if(prod->size()==1)
            continue;

        for(auto it_prod = prod->begin(); it_prod != prod->end(); it_prod++){
            FormaSentencial fs1 = *it_prod;
            Simbolos first_fs1;
            get_first(fs1.begin(), fs1.end(), &first_fs1);
            for(auto it_prod2 = ++it_prod; it_prod2 != prod->end(); it_prod2++){
                vector<Simbolos> teste;
                FormaSentencial fs2= *it_prod2;
                Simbolos first_fs2;
                get_first(fs2.begin(), fs2.end(), &first_fs2);
                teste.push_back(first_fs1);
                teste.push_back(first_fs2);
                it_prod--;
                if(!interseccaoVazia(teste))
                    return false;
            }
        }
    }
    return true;
}

bool Gramatica::testaFirstFollow(){
    this->follow();
    for(auto it_NT = _NTerminais.begin(); it_NT!= _NTerminais.end(); it_NT++){
        NTerminal *nt = *it_NT;
        vector<Simbolos> teste;
        Simbolos first = nt->get_first(&_Ne);
        if(!NTerminal::contemEpsilon(first))
            continue;
        Simbolos *follow = nt->get_follow();
        teste.push_back(first);
        teste.push_back(*follow);
        if(!interseccaoVazia(teste))
            return false;
    }
    return true;
}
bool Gramatica::testaLL1(){
    return (this->testaRE() && this->testaFatorada() && this->testaFirstFollow());

}

bool Gramatica::interseccaoVazia(vector<Simbolos> conj){
       Simbolos velho = conj.at(0);

       for(auto it_conj = ++conj.begin(); it_conj!= conj.end(); it_conj++){
           Simbolos teste = *it_conj;
           Simbolos novo;
           for(auto it_simb = velho.begin(); it_simb!= velho.end();it_simb++){
               Simbolo *simb =*it_simb;
               if(teste.find(simb)!= teste.end())
                   novo.insert(simb);
           }
           velho = novo;
       }
       return velho.empty();
}
