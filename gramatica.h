#ifndef GRAMATICA_H
#define GRAMATICA_H

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

#include<set>
using std::set;

#include "nterminal.h"

typedef vector<Terminal*> Sentenca;

class Gramatica
{
    NTerminal * _inicial;
    set<NTerminal*> _NTerminais;
    set<Terminal*> _alfabeto;
    Simbolos _Ne;
    unordered_map<FormaSentencial*, int> _FSparaInt;
    unordered_map<NTerminal*,unordered_map<Terminal*,FormaSentencial*>> _tabelaParse;

public:
    /*! \brief Construtor padrão
     *
     */
    Gramatica();

    /*! \brief Adiciona nt ao conjunto de não terminais
     *
     * \param NTerminal * nt
     *
     */
    void addNTerminal(NTerminal * nt);

    /*! \brief Elimina os símbolos inférteis da Gramatica
     *
     */
    void eliminarInferteis();

    /*! \brief Elimina os símbolos inalcançáveis da Gramatica
     *
     */
    void eliminarInalcancaveis();

    /*! \brief Elimina os símbolos inúteis e os inférteis da Gramatica
     *
     */
    void eliminarInuteis();

    /*! \brief Constrói tabela de parse
     *
     */
    void construirTabelaParse();

    /*! \brief Calcula conjunto Ne
     *
     */
    void calculaNe();

    /*! \brief Seta inicial como sendo o simbolo inicial da Gramática
     *
     * \param NTerminal * inicial
     *
     */
    void setInicial(NTerminal * inicial);

    /*! \brief Calcula o conjunto follow de todos os não terminais
     *
     */
    void follow();

    /*! \brief Seta o mapa de FormaSentencial para int como sendo fs
     *
     * \param unordered_map<FormaSentencial*, int> fs
     *
     */
    void setFSParaInt(unordered_map<FormaSentencial*, int> fs){
        _FSparaInt = fs;
    }

    /*! \brief Calcula o first de uma FormaSentencial
     *
     * \param FormaSentencial::iterator it,FormaSentencial::iterator end, Simbolos * s
     *
     */
    void get_first(FormaSentencial::iterator it,FormaSentencial::iterator end, Simbolos * s);

    /*! \brief Calcula o first-NT de todos os não terminais
     *
     */
    unordered_map<Simbolo*,Simbolos>  first_NT();

    /*! \brief Calcula o first de todos os não terminais
     *
     */
    unordered_map<Simbolo*,Simbolos>  first();

    /*! \brief Retorna ponteiro para o mapa FormaSentencial para int
     *
     */
    unordered_map<FormaSentencial*, int> * FSparaInt(){
        return &_FSparaInt;
    }

    /*! \brief Retorna ponteiro para o conjunto de não terminais
     *
     */
    set<NTerminal*> * nTerminais(){
        return &_NTerminais;
    }


    /*! \brief Retorna ponteiro para o símbolo inicial
     *
     */
    NTerminal * inicial(){
        return _inicial;
    }

    /*! \brief Retorna ponteiro para o conjunto Ne
     *
     */
    Simbolos * Gramatica::Ne(){
        return &_Ne;
    }

    /*! \brief Retorna ponteiro para o alfabeto
     *
     */
    set<Terminal*> * alfabeto(){
        return &_alfabeto;
    }

    /*! \brief Retorna ponteiro para o
     *
     */
    unordered_map<NTerminal*,unordered_map<Terminal*,FormaSentencial*>> * tabelaParse(){
        return &_tabelaParse;
    }

    /*! \brief Retorna ponteiro para o símbolo epsilon
     *
     */
    Terminal * getEpsilon();

    /*! \brief Retorna ponteiro para o símbolo dollar
     *
     */
    Terminal * getDollar();

    /*! \brief Retorna true se todos os simbolos de fs pertencem a ferteis
     *
     * \param FormaSentencial fs, set<NTerminal*> ferteis
     *
     */
    bool fertil(FormaSentencial fs, set<NTerminal*> ferteis);

    /*! \brief Retorna true se nt deriva epsilon em um ou mais passos
     *
     * \param NTerminal * nt
     *
     */
    bool derivaEpsilon(NTerminal * nt);

    /*! \brief Retorna true se a Gramatica é LL(1)
     *
     */
    bool testaLL1();

    /*! \brief Retorna true se a Gramatica possui RE
     *
     */
    bool possuiRE();

    /*! \brief Retorna true se a Gramatica está fatorada
     *
     */
    bool testaFatorada();

    /*! \brief Retorna true se a condição 3 for satisfeita
     *
     */
    bool testaFirstFollow();

    /*! \brief Retorna true se a intersecção dos conjuntos dentro de conj for vazia
     *
     */
    bool interseccaoVazia(vector<Simbolos> conj);

    /*! \brief Printa a Gramatica
     *
     */
    string printaGramatica();
    /*! \brief Printa a Gramatica com suas produções numeradas
     *
     */
    string printaGramaticaNumerada();
    /*! \brief Printa a tabela de parse
     *
     */
    string printarTP();

    /*! \brief Printa a tabela de parse com as produções em vez de números das produções
     *
     */
    string printarTPParaDebug();

};

#endif // GRAMATICA_H
