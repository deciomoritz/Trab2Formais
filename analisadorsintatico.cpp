#include "analisadorsintatico.h"

AnalisadorSintatico::AnalisadorSintatico()
{
}

bool AnalisadorSintatico::analisar(string sentenca, Gramatica g){
    g.construirTabelaParse();

    Sentenca s = lerSentenca(sentenca,g);

    unordered_map<NTerminal*,unordered_map<Terminal*,pair<FormaSentencial,int>>> & tabela = *g.tabelaParse();

    stack<Simbolo*> pilha;
    pilha.push(g.inicial());

    s.push_back(g.getDollar());

    int posSimboloAtual = 0;

    while (!pilha.empty()) {
        Simbolo * topoPilha = pilha.top();
        pilha.pop();

        Terminal * atual = s.at(posSimboloAtual);

        FormaSentencial fs = tabela[topoPilha][atual].first;

        if(!topoPilha->ehNTerminal())
            if(topoPilha->nome().compare(atual->nome()) == 0){
                pilha.pop();
                posSimboloAtual++;
            }
        else
            return false;

        if(fs.begin() != fs.end()){
            for (int i = 0; i < fs.size(); ++i) {
                Simbolo * s = fs.at(i);
                pilha.push(s);
            }
        }else
            return false;


        posSimboloAtual++;
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
            cout << "algum simbolo não pertence ao alfabeto!";
    }
    return sentenca;
}
