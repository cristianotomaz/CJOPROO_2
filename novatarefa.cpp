// Inclui o cabeçalho da classe NovaTarefa (declaração da classe)
#include "NovaTarefa.h"
// Inclui o arquivo gerado automaticamente com os elementos gráficos do formulário
#include "ui_NovaTarefa.h"

// Construtor da janela de Nova Tarefa
NovaTarefa::NovaTarefa(QWidget *parent) :
    QDialog(parent),                   // Inicializa o QDialog (janela modal)
    ui(new Ui::NovaTarefa)            // Cria a interface gráfica da janela
{
    ui->setupUi(this);                // Associa os elementos gráficos definidos no .ui à variável ui

    // Adiciona opções pré-definidas no ComboBox de tipo de tarefa
    ui->comboTipo->addItem("Prova");
    ui->comboTipo->addItem("Trabalho");

    // Conecta os botões OK e Cancelar às ações de aceitar ou rejeitar o diálogo
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NovaTarefa::accept);   // Fecha a janela e retorna QDialog::Accepted
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &NovaTarefa::reject);   // Fecha a janela e retorna QDialog::Rejected
}

// Destrutor da janela de Nova Tarefa
NovaTarefa::~NovaTarefa() {
    delete ui;  // Libera a memória alocada para a interface gráfica
}

// Retorna o nome da tarefa preenchido no campo de texto
QString NovaTarefa::nomeTarefa() const {
    return ui->lineEditNome->text();
}

// Retorna o tipo da tarefa selecionado no ComboBox
QString NovaTarefa::tipoTarefa() const {
    return ui->comboTipo->currentText();
}

// Retorna a data da tarefa selecionada no calendário
QDate NovaTarefa::dataTarefa() const {
    return ui->dateEdit->date();
}
