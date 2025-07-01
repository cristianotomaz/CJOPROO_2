// Inclui o cabeçalho da janela principal do programa
#include "mainwindow.h"

// Inclui a biblioteca principal de aplicação Qt (necessária para aplicações GUI)
#include <QApplication>

// Função principal do programa - ponto de entrada da aplicação
int main(int argc, char *argv[]) {
    // Cria um objeto QApplication, que gerencia recursos da aplicação e eventos do sistema
    QApplication a(argc, argv);

    // Cria uma instância da janela principal (MainWindow)
    MainWindow w;

    // Exibe a janela principal na tela
    w.show();

    // Inicia o loop de eventos da aplicação, aguardando interações do usuário
    return a.exec();
}
