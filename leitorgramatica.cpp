#include "leitorgramatica.h"

LeitorGramatica::LeitorGramatica()
{
}

Gramatica LeitorGramatica::ler(string s) {

    Gramatica g;
    vector<string>producoes = split(s, "\n");

    NTerminal * inicial = new NTerminal(split(producoes.front()," ").front());
    g.addNTerminal(inicial);
    g.setInicial(inicial);

    for (int i = 0; i < producoes.size(); ++i) {
        string producao = producoes.at(i);

        vector<string> formaSentencial = split(producao, " ");

        NTerminal * novoNT;
        NTerminal * aux = NTerminal::contem(*g.nTerminais(), NTerminal(formaSentencial.front()));
        if(aux == NULL)
            novoNT = new NTerminal(formaSentencial.front());
        else
            novoNT = aux;

        g.addNTerminal(novoNT);

        FormaSentencial novaFS;
        novaFS.clear();
        for (int i = 2; i < formaSentencial.size(); ++i) {
            string simbolo = formaSentencial.at(i);

            if(isupper(simbolo.at(0))){
                aux = NTerminal::contem(*g.nTerminais(), NTerminal(simbolo));

                NTerminal * nt;
                if(aux == NULL){
                    nt = new NTerminal(simbolo);
                    g.addNTerminal(nt);
                }else
                    nt = aux;

                novaFS.push_back(nt);
            }else if(simbolo.compare(string("|")) != 0){
                Terminal * novoTerminal = Terminal::contem(*g.alfabeto(), Terminal(simbolo));

                Terminal * t;

                if(simbolo.compare(g.getEpsilon()->nome()) == 0)
                    novoTerminal = g.getEpsilon();

                if(novoTerminal == NULL){
                    t = new Terminal(simbolo);
                    g.alfabeto()->insert(t);
                }else
                    t = novoTerminal;

                novaFS.push_back(t);
            }

            if(simbolo.compare(string("|")) == 0 || i == formaSentencial.size() - 1){
                novoNT->addProducao(novaFS);
                novaFS.clear();
                continue;
            }
        }
    }
    g.calculaNe();
    g.follow();
    g.first();
    g.first_NT();

    return g;
}

vector<string> LeitorGramatica::split(string s, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}
