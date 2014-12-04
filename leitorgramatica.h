#ifndef LEITORGRAMATICA_H
#define LEITORGRAMATICA_H

#include "gramatica.h"

#include <iostream>
#include <fstream>

class LeitorGramatica
{
public:
    LeitorGramatica();

    static Gramatica ler(string s);
    static vector<string> split(string s, string delimiter) ;

    static void gravar(Gramatica g, string nomeArquivo);
    static Gramatica recuperar(string nomeArquivo);
};

#endif // LEITORGRAMATICA_H
