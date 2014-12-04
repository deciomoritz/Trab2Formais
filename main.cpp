#include "mainwindow.h"
#include <QApplication>

#include "terminal.h"

#include <set>
using namespace std;

#include <vector>

#include "leitorgramatica.h"

#include "analisadorsintatico.h"

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    //    return a.exec();
    LeitorGramatica l;
    string s;
    //    s = "E -> E + T | E - T | T\n"
    //               "T -> T * F | T / F | F\n"
    //               "F -> ( E ) | id";

    //    l.ler(s);

    s =
            "S -> a A B | B | A\n"
            "A -> C | B\n"
            "B -> a | b | E\n"
            "D -> a | b | F\n"
            "C -> A | E\n"
            "E -> F\n"
            "F -> E";
    Gramatica g = l.ler(s);
    g.eliminarInalcancaveis();
    string teste1 =
            "S(inicial) -> a A B | A | B \n"
            "A -> B | C \n"
            "B -> a | b | E \n"
            "C -> A | E \n"
            "E -> F \n"
            "F -> E \n";
    if(g.printaGramatica().compare(teste1) == 0)
        cout << "Eliminar inalcançaveis OK!" << endl;
    else
        cout << "Eliminar inalcançaveis falhou!" << endl;

    g.eliminarInferteis();
    string teste2 = "S(inicial) -> a A B | A | B \n"
                    "A -> B | C \n"
                    "B -> a | b \n"
                    "C -> A \n";
    if(g.printaGramatica().compare(teste2) == 0)
        cout << "Eliminar inférteis OK!" << endl;
    else
        cout << "Eliminar inférteis falhou!" << endl;

    s =
            "S -> a A B | B | A\n"
            "A -> C | B\n"
            "B -> a | b | E\n"
            "D -> a | b | F\n"
            "C -> A | E\n"
            "E -> F\n"
            "F -> E";
    teste2 =
            "S(inicial) -> a A B | A | B \n"
            "A -> B | C \n"
            "B -> a | b \n"
            "C -> A \n";
    g = l.ler(s);
    g.eliminarInuteis();
    if(g.printaGramatica().compare(teste2) == 0)
        cout << "Eliminar inúteis OK!" << endl;
    else
        cout << "Eliminar inúteis falhou!" << endl;

    s =
            "S -> A C\n"
            "A -> E F B\n"
            "B -> a B | &\n"
            "C -> b A C D | D\n"
            "D -> e D | &\n"
            "E -> c D | &\n"
            "F -> d F | &";
    g = l.ler(s);
    cout << "=============TESTE FIRST NT============="<<endl;
    unordered_map<Simbolo*,Simbolos> teste = g.first_NT();
    for(auto it = teste.begin(); it != teste.end(); it++){
        Simbolo *A = it->first;
        string name = A->nome();
        cout<<"First NT de : " <<name<< endl;
        for(auto it2 = (it->second).begin();it2 !=(it->second).end(); it2++){
            Simbolo * b = *it2;
            cout << b->nome() << " , ";
        }
        cout << endl;
    }
    cout << "===================================="<<endl;
    s = "S -> B A a | b\n"
        "B -> a a | & | A\n"
        "A -> S b b | B";
    g = l.ler(s);
    vector<bool> testeB = {false, true, true};
    int i = 0;
    for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
        NTerminal * s = *A;

        if(g.derivaEpsilon(s) == testeB.at(i))
            cout << "Deriva epsilon ok!" << endl;
        else
            cout << "Deriva epsilon fail!" << endl;
        i++;
    }

    s = "S -> B A a | b | B A\n"
        "B -> a a | & | A | D\n"
        "A -> S b b | B\n"
        "D -> S A | S a";
    g = l.ler(s);
    vector<bool> testeC = {true, true, true, true};
    i = 0;
    for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
        NTerminal * s = *A;

        if(g.derivaEpsilon(s) == testeC.at(i))
            cout << "Deriva epsilon ok!" << endl;
        else
            cout << "Deriva epsilon fail!" << endl;
        i++;
    }

    s = "S -> B A a | b | A B\n"
        "B -> a a | & | A\n"
        "A -> S b b | B";
    g = l.ler(s);
    vector<bool> testeD = {true, true, true};
    i = 0;
    for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
        NTerminal * s = *A;

        if(g.derivaEpsilon(s) == testeD.at(i))
            cout << "Deriva epsilon ok!" << endl;
        else
            cout << "Deriva epsilon fail!" << endl;
        i++;
    }

    s = "S -> B A a | b | B A\n"
        "B -> a a | & | A | D\n"
        "A -> S b b | B\n"
        "D -> S A | S a";
    g = l.ler(s);
    cout << "Detectar NT RE da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        if(nt->ehRE(g.Ne()))
            cout << nt->nome() << " é RE" << endl;
        else
            cout << nt->nome() << "não é RE" << endl;
    }

    s = "S -> A a | & | d\n"
        "B -> c\n"
        "A -> S B b | b";
    g = l.ler(s);
    cout << "Detectar NT RE da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        if(nt->ehRE(g.Ne()))
            cout << nt->nome() << " é RE" << endl;
        else
            cout << nt->nome() << " não é RE" << endl;
    }

    //------------------------------------------------------------------------------------------------------------------
    s = "S -> A a | & | d\n"
        "B -> c\n"
        "A -> S B b | b";
    g = l.ler(s);
    cout << "Calcular first da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        Simbolos first = nt->get_first(g.Ne());
        for(auto it = first.begin(); it != first.end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    string esperado =
            "S={&,d,b,c}\n"
            "A={d,b,c}\n"
            "B={c}\n";
    cout << "Esperado: " << esperado << endl;

    //------------------------------------------------------------------------------------------------------------------

    s = "S -> A a | & | d\n"
        "B -> c\n"
        "A -> S A B b | b";
    g = l.ler(s);
    cout << "Calcular first da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        Simbolos first = nt->get_first(g.Ne());
        for(auto it = first.begin(); it != first.end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "S={&,d,b}\n"
            "A={d,b}\n"
            "B={c}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "S -> A a | & | d\n"
        "B -> c\n"
        "A -> S A B b | b";
    g = l.ler(s);
    cout << "Calcular first da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        Simbolos first = nt->get_first(g.Ne());
        for(auto it = first.begin(); it != first.end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "S={&,d,b}\n"
            "A={d,b}\n"
            "B={c}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "P -> B P1\n"
        "P1 -> ; B P1 | &\n"
        "B -> K V C\n"
        "K -> c K | &\n"
        "V -> v V | &\n"
        "C -> b C2 | C1\n"
        "C1 -> com C1 | &\n"
        "C2 -> K V ; C e C1 | C e C1";
    g = l.ler(s);
    cout << "Calcular first da gramática __7a__: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        Simbolos first = nt->get_first(g.Ne());
        for(auto it = first.begin(); it != first.end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "P={&,c,v,com,;}\n"
            "P1={&,;}\n"
            "B={c,v,b,com,&}\n"
            "K={c,&}\n"
            "V={v,&}\n"
            "C={b,com,&}\n"
            "C1={com,&}\n"
            "C2={c,v,;,b,com,e}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "S -> A a | & | d\n"
        "B -> c\n"
        "A -> S A B b | b";
    g = l.ler(s);
    cout << "Calcular follow da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        g.follow();
        Simbolos * follow = nt->get_follow();
        for(auto it = follow->begin(); it != follow->end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "S={$,d,b}\n"
            "A={a,c}\n"
            "B={b}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "S -> A B\n"
        "A -> C D A1\n"
        "A1 -> a A1 | &\n"
        "B -> b A B B1 | B1\n"
        "B1 -> e B1 | &\n"
        "C -> c C | &\n"
        "D -> d D | &\n";
    g = l.ler(s);
    cout << "Calcular follow da gramática: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        g.follow();
        Simbolos * follow = nt->get_follow();
        for(auto it = follow->begin(); it != follow->end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "S={$}\n"
            "A={b,e,$}\n"
            "A1={b,e,$}\n"
            "B={e,$}\n"
            "B1={e,$}\n"
            "C={b,d,e,a,$}\n"
            "D={b,e,a,$}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "P -> B P1\n"
        "P1 -> ; B P1 | &\n"
        "B -> K V C\n"
        "K -> c K | &\n"
        "V -> v V | &\n"
        "C -> b C2 | C1\n"
        "C1 -> com C1 | &\n"
        "C2 -> K V ; C e C1 | C e C1";
    g = l.ler(s);
    cout << "Calcular follow da gramática __7a__: " << endl << endl << g.printaGramatica();
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        cout << "NT: " << nt->nome() << endl;
        g.follow();
        Simbolos * follow = nt->get_follow();
        for(auto it = follow->begin(); it != follow->end(); it++){
            NTerminal * nt2 = *it;
            cout << nt2->nome() << " ";
        }
        cout << endl;
    }
    esperado =
            "P={$}\n"
            "P1={$}\n"
            "B={;,$}\n"
            "K={v,;,b,com,$}\n"
            "V={b,com,;,$}\n"
            "C={e,;,$}\n"
            "C1={e,;,$}\n"
            "C2={e,;,$}\n";
    cout << "Esperado: " << esperado << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "P -> B P1\n"
        "P1 -> ; B P1 | &\n"
        "B -> K V C\n"
        "K -> c K | &\n"
        "V -> v V | &\n"
        "C -> b C2 | C1\n"
        "C1 -> com C1 | &\n"
        "C2 -> K V ; C e C1 | C e C1";
    g = l.ler(s);
    cout << "Calcular tabela de parse da gramática __7a__: " << endl << endl;
    cout << g.printaGramatica();
    g.construirTabelaParse();
    string tabela = g.printarTP();

    cout << endl;
    cout << tabela;
    //------------------------------------------------------------------------------------------------------------------
    s = "P -> B P1\n"
        "P1 -> ; B P1 | &\n"
        "B -> K V C\n"
        "K -> c K | &\n"
        "V -> v V | &\n"
        "C -> b C2 | C1\n"
        "C1 -> com C1 | &\n"
        "C2 -> K V ; C e C1 | C e C1";
    g = l.ler(s);
    cout << "Verificar se está fatorada __7a__: " << endl << endl;
    cout << g.printaGramatica();
//    cout << g.testaFatorada() << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "E -> E + T | E - T | T\n"
            "T -> T * F | T / F | F\n"
            "F -> ( E ) | id";

    g = l.ler(s);
    cout << "Verificar se possui RE __7a__: " << endl << endl;
    cout << g.printaGramatica();
    cout << "Possui RE: " << g.testaRE() << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "E -> T E1\n"
        "E1 -> + T E1 | &\n"
        "T -> F T1\n"
        "T1 -> * F T1 | &\n"
        "F -> ( E ) | id";

    g = l.ler(s);
    cout << "Verificar se possui RE __7a__: " << endl << endl;
    cout << g.printaGramatica();
    cout << "Possui RE: " << g.testaRE() << endl;
    //------------------------------------------------------------------------------------------------------------------
    s = "E -> T E1\n"
        "E1 -> + T E1 | &\n"
        "T -> F T1\n"
        "T1 -> * F T1 | &\n"
        "F -> ( E ) | id";

    g = l.ler(s);
    cout << "Teste de escrita: " << endl << endl;
    l.gravar(g, "Expressoes.txt");
    //------------------------------------------------------------------------------------------------------------------
    s = "E -> T E1\n"
        "E1 -> + T E1 | &\n"
        "T -> F T1\n"
        "T1 -> * F T1 | &\n"
        "F -> ( E ) | id";

    g = l.ler(s);
    cout << "Teste de recuperação: " << endl << endl;
    Gramatica g1 = l.recuperar("Expressoes.txt");
    cout << g1.printaGramatica();
    //------------------------------------------------------------------------------------------------------------------
    s = "E -> T E1\n"
        "E1 -> + T E1 | &\n"
        "T -> F T1\n"
        "T1 -> * F T1 | &\n"
        "F -> ( E ) | id";

    g = l.ler(s);
    cout << "Teste análise de sentença: id+id" << endl << endl;
    AnalisadorSintatico a;
    cout << a.analisar("id + id", g) << endl;

}
