#include "leitorgramatica.h"

LeitorGramatica::LeitorGramatica()
{
}

Gramatica LeitorGramatica::ler(string s) {

    Gramatica g;
    vector<string>producoes = split(s, "\n");

    for (int i = 0; i < producoes.size(); ++i) {
        string producao = producoes.at(i);

        vector<string> formasSentenciais = split(producao, " ");

        NTerminal * novoNT = new NTerminal(formasSentenciais.front());
        g.addNTerminal(novoNT);

        FormaSentencial novaFS;
        novaFS.clear();
        for (int i = 2; i < formasSentenciais.size(); ++i) {
            string formaSentencial = formasSentenciais.at(i);

            if(isupper(formaSentencial.at(0))){
                NTerminal * nt = new NTerminal(formaSentencial);
                novaFS.push_back(nt);
            }else if(formaSentencial.compare(string("|")) != 0){
                Terminal * t = new Terminal(formaSentencial);
                novaFS.push_back(t);
            }

            if(formaSentencial.compare(string("|")) == 0 || i == formasSentenciais.size() - 1){
                novoNT->addProducao(novaFS);
                novaFS.clear();
                continue;
            }
        }
    }

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
