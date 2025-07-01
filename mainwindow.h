#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Inclui a definição da classe QMainWindow do Qt
#include <QMainWindow>

// Inclui a interface gráfica gerada pelo Qt Designer (mainwindow.ui)
#include "ui_mainwindow.h"

// Declaração da classe MainWindow, que herda de QMainWindow (janela principal do Qt)
class MainWindow : public QMainWindow {
    Q_OBJECT  // Macro do Qt necessária para o funcionamento do sistema de sinais e slots

public:
    // Construtor explícito com argumento opcional de QWidget* (padrão é nullptr)
    explicit MainWindow(QWidget *parent = nullptr);

    // Destrutor da classe
    ~MainWindow();

private:
    // Ponteiro para a interface da janela principal (gerada automaticamente)
    Ui::MainWindow *ui;

    // Função que salva as tarefas da tabela em um arquivo
    void salvarTarefas();

    // Função que carrega as tarefas do arquivo e preenche a tabela
    void carregarTarefas();

    // Evento chamado automaticamente quando o usuário fecha a janela
    // Usado aqui para chamar a função salvarTarefas()
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
