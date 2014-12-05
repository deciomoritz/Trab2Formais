#ifndef LEITORGRAMATICA_H
#define LEITORGRAMATICA_H

#include "gramatica.h"

#include <iostream>
#include <fstream>

class LeitorGramatica
{
public:
    /*! \brief Construtor padrão
     *
     */
    LeitorGramatica();

    /*! \brief Recebe uma string contendo uma representação de uma gramática e a converte para um objeto Gramatica
     *
     * \param string s
     *
     */
    static Gramatica ler(string s);

    /*! \brief Recebe uma string s e a quebra em pedaços, separados pelo string delimiter
     *
     * \param string s, string delimiter
     *
     */
    static vector<string> split(string s, string delimiter) ;

    /*! \brief Salva a Gramatica g em um arquivo com nome nomeArquivo no diretório onde está o executável
     *
     * \param Gramatica g, string nomeArquivo
     *
     */
    static void gravar(Gramatica g, string nomeArquivo);

    /*! \brief Lê a Gramatica a partir do arquivo com nome nomeArquivo, localizado na pasta do executável
     *
     * \param string nomeArquivo
     *
     */
    static Gramatica recuperar(string nomeArquivo);
};

#endif // LEITORGRAMATICA_H
