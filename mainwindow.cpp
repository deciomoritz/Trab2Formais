#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->OK, SIGNAL(clicked()), this, SLOT(ler()));

    connect(ui->salvar, SIGNAL(clicked()), this, SLOT(salvar()));

    connect(ui->lerDoArquivo, SIGNAL(clicked()), this, SLOT(recuperar()));

    connect(ui->fatorada, SIGNAL(clicked()), this, SLOT(verificarFatorada()));

    connect(ui->possuiRE, SIGNAL(clicked()), this, SLOT(verificarRE()));

    connect(ui->condicao3, SIGNAL(clicked()), this, SLOT(verificarCondicao3()));

    connect(ui->reconhecer, SIGNAL(clicked()), this, SLOT(efetuarAnalise()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ler(){
    string s = ui->gramatica->toPlainText().toStdString();

    LeitorGramatica l;

    g = l.ler(s);
    ui->gramatica->setText(QString(g.printaGramatica().c_str()));

    string fNT = "";
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        fNT += nt->nome() + "={";
        Simbolos sim = nt->get_first_NT(g.Ne());
        for(auto it = sim.begin(); it != sim.end(); it++){
            NTerminal * nt2 = *it;
            fNT += nt2->nome() + ",";
        }
        if(fNT.back() == ',')
            fNT.pop_back();
        fNT += "}\n";
    }
    ui->firstNT->setText(QString(fNT.c_str()));

    string f = "";
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        f += nt->nome() + "={";
        Simbolos first = nt->get_first(g.Ne());
        for(auto it = first.begin(); it != first.end(); it++){
            NTerminal * nt2 = *it;
            f += nt2->nome() + ",";
        }
        if(f.back() == ',')
            f.pop_back();
        f += "}\n";
    }
    ui->first->setText(QString(f.c_str()));

    string follow = "";
    for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
        NTerminal * nt = *it;
        follow += nt->nome() + "={";
        Simbolos * fo = nt->get_follow();
        for(auto it = fo->begin(); it != fo->end(); it++){
            NTerminal * nt2 = *it;
            follow += nt2->nome() + ",";
        }
        if(follow.back() == ',')
            follow.pop_back();
        follow += "}\n";
    }
    ui->follow->setText(QString(follow.c_str()));

    if(g.testaLL1()){
        string tabela = g.printarTP();

        ui->tabelaParse->setLineWrapMode(QTextEdit::NoWrap);
        ui->tabelaParse->setText(QString(tabela.c_str()));

        ui->gramatica->setLineWrapMode(QTextEdit::NoWrap);
        ui->gramatica->setText(QString(g.printaGramaticaNumerada().c_str()));
    }else{
        if(g.possuiRE())
            ui->tabelaParse->setText(QString("A gramática inserida não é LL(1), pois possui recursão à esquerda. A tabela não será construída."));
        else if(!g.estaFatorada())
            ui->tabelaParse->setText(QString("A gramática inserida não é LL(1), pois não está fatorada. A tabela não será construída."));
        else
            ui->tabelaParse->setText(QString("A gramática inserida não é LL(1), pois a terceira condição falha. A tabela não será construída."));
    }
}

void MainWindow::salvar(){

    ler();

    string nome = ui->nomeArquivo->toPlainText().toStdString();

    LeitorGramatica l;
    l.gravar(g,nome);
}

void MainWindow::recuperar(){
    string nome = ui->nomeArquivo->toPlainText().toStdString();

    LeitorGramatica l;
    g = l.recuperar(nome);

    ui->gramatica->setText(QString(g.printaGramatica().c_str()));
}

void MainWindow::verificarRE(){
    QMessageBox messageBox;

    if(g.possuiRE())
        messageBox.critical(0,"","Possui recursão à esquerda");
    else
        messageBox.critical(0,"","Não possui recursão à esquerda");
}

void MainWindow::verificarFatorada(){
    QMessageBox messageBox;

    if(g.estaFatorada())
        messageBox.critical(0,"","Está fatorada");
    else
        messageBox.critical(0,"","Não está fatorada");
}

void MainWindow::verificarCondicao3(){
    QMessageBox messageBox;

    if(g.testaFirstFollow())
        messageBox.critical(0,"","Passou na condição 3!");
    else
        messageBox.critical(0,"","Não passou na condição 3!");
}

void MainWindow::efetuarAnalise(){

    QMessageBox messageBox;

    AnalisadorSintatico a;

    string sentenca = ui->sentenca->toPlainText().toStdString();

    bool valida = a.analisar(sentenca,g);

    if(valida)
        messageBox.critical(0,"","Sentença válida!");
    else
        messageBox.critical(0,"","Sentença inválida!");
}
