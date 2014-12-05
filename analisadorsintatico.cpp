#include "analisadorsintatico.h"

AnalisadorSintatico::AnalisadorSintatico()
{
}

bool AnalisadorSintatico::analisar(string sentenca, Gramatica & g){

    Sentenca s = lerSentenca(sentenca,g);

    if(s.front() == invalido)
        return false;

    unordered_map<NTerminal*,unordered_map<Terminal*,FormaSentencial*>> & tabela = *g.tabelaParse();

    stack<Simbolo*> pilha;
    pilha.push(g.inicial());

    s.push_back(g.getDollar());

    int posSimboloAtual = 0;

    while (!pilha.empty()) {
        Simbolo * topoPilha = pilha.top();

        Terminal * atual = s.at(posSimboloAtual);

        FormaSentencial * fs = tabela[topoPilha][atual];

        if(!topoPilha->ehNTerminal())
            if(topoPilha->nome().compare(atual->nome()) == 0){
                posSimboloAtual++;
                pilha.pop();
                continue;
            }
        else
            return false;

        if(fs != NULL){
            pilha.pop();
            for (int i = fs->size()-1; i >= 0; i--) {
                Simbolo * s = fs->at(i);

                if(s->nome().compare(g.getEpsilon()->nome()) != 0)
                    pilha.push(s);
            }
        }else
            return false;
    }
    return true;
}

Sentenca AnalisadorSintatico::lerSentenca(string s, Gramatica g){

    Sentenca sentenca;

    vector<string> simbolos = LeitorGramatica::split(s," ");

    for (int i = 0; i < simbolos.size(); ++i) {
        Terminal * t = Terminal::contem(*g.alfabeto(),Terminal(simbolos.at(i)));

        if(t != NULL){
            sentenca.push_back(t);
        }else
            sentenca.push_back(invalido);
    }
    return sentenca;
}
