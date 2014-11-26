#ifndef LEITORGRAMATICA_H
#define LEITORGRAMATICA_H

#include "gramatica.h"

class LeitorGramatica
{
public:
    LeitorGramatica();

    Gramatica ler(string s);
    vector<string> split(string s, string delimiter) ;
};

#endif // LEITORGRAMATICA_H
