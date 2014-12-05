#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>

#include "leitorgramatica.h"
#include "analisadorsintatico.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ler();
    void salvar();
    void recuperar();
    void verificarRE();
    void verificarFatorada();
    void verificarCondicao3();
    void efetuarAnalise();

private:
    Ui::MainWindow *ui;

    Gramatica g;
};

#endif // MAINWINDOW_H
