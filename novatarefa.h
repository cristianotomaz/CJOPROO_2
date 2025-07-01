#ifndef NOVATAREFA_H
#define NOVATAREFA_H

// Inclui a classe base QDialog do Qt, que representa uma janela de diálogo
#include <QDialog>

// Cria um namespace 'Ui' contendo a classe 'NovaTarefa' gerada automaticamente pelo Qt Designer
namespace Ui {
class NovaTarefa;
}

// Define a classe NovaTarefa, que herda de QDialog (janela de diálogo do Qt)
class NovaTarefa : public QDialog {
    Q_OBJECT  // Macro necessária para o sistema de sinais e slots do Qt

public:
    // Construtor da janela de diálogo. O parâmetro parent é opcional (padrão é nullptr)
    explicit NovaTarefa(QWidget *parent = nullptr);

    // Destrutor da classe
    ~NovaTarefa();

    // Função que retorna o nome da tarefa preenchido pelo usuário
    QString nomeTarefa() const;

    // Função que retorna o tipo da tarefa selecionado pelo usuário
    QString tipoTarefa() const;

    // Função que retorna a data da tarefa escolhida pelo usuário
    QDate dataTarefa() const;

private:
    // Ponteiro para a interface da janela gerada pelo Qt Designer (NovaTarefa.ui)
    Ui::NovaTarefa *ui;
};

#endif // NOVATAREFA_H
