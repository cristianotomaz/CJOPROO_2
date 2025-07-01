// Importa a definição da classe MainWindow
#include "mainwindow.h"
// Importa a interface gerada pelo Qt Designer
#include "ui_mainwindow.h"
// Importa a janela de criação de nova tarefa
#include "NovaTarefa.h"
// Biblioteca para manipulação de datas
#include <QDate>
// Bibliotecas para leitura e escrita de arquivos
#include <QFile>
#include <QTextStream>
// Para interceptar o fechamento da janela
#include <QCloseEvent>
// Para exibir caixas de diálogo (mensagens)
#include <QMessageBox>

// Função que salva todas as tarefas na tabela em um arquivo CSV
void MainWindow::salvarTarefas() {
    QFile file("tarefas.csv");  // Nome do arquivo
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Abre para escrita
        QTextStream out(&file);  // Cria stream de texto
        int rows = ui->tableWidget->rowCount();  // Número de linhas da tabela
        for (int i = 0; i < rows; ++i) {
            // Extrai os dados de cada célula da linha
            QString nome = ui->tableWidget->item(i, 0)->text();
            QString tipo = ui->tableWidget->item(i, 1)->text();
            QString data = ui->tableWidget->item(i, 2)->text();
            QString status = ui->tableWidget->item(i, 3)->text();
            // Salva os dados separados por ponto e vírgula
            out << nome << ";" << tipo << ";" << data << ";" << status << "\n";
        }
        file.close();  // Fecha o arquivo
    }
}

// Função que carrega tarefas salvas anteriormente do arquivo CSV
void MainWindow::carregarTarefas() {
    QFile file("tarefas.csv");  // Nome do arquivo
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Abre para leitura
        QTextStream in(&file);  // Stream de leitura
        while (!in.atEnd()) {
            QString linha = in.readLine();            // Lê uma linha
            QStringList dados = linha.split(";");     // Separa por ponto e vírgula
            if (dados.size() == 4) {
                int row = ui->tableWidget->rowCount(); // Nova linha na tabela
                ui->tableWidget->insertRow(row);
                for (int i = 0; i < 4; ++i) {
                    ui->tableWidget->setItem(row, i, new QTableWidgetItem(dados[i]));
                }
            }
        }
        file.close();  // Fecha o arquivo
    }
}

// Construtor da janela principal
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),  // Inicializa o QMainWindow com o pai
    ui(new Ui::MainWindow)  // Cria a interface da janela
{
    ui->setupUi(this);  // Aponta os widgets do .ui para o ponteiro "ui"

    carregarTarefas();  // Carrega as tarefas ao abrir

    // Expande as colunas da tabela igualmente para melhor visualização
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Ajusta a altura das linhas conforme o conteúdo
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Remove a barra de rolagem horizontal
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Conecta o botão "Nova Tarefa" à ação de abrir a janela de cadastro
    connect(ui->btnNovaTarefa, &QPushButton::clicked, this, [this]() {
        NovaTarefa dialog(this);  // Cria o diálogo de nova tarefa
        if (dialog.exec() == QDialog::Accepted) {
            // Recupera os dados preenchidos
            QString nome = dialog.nomeTarefa();
            QString tipo = dialog.tipoTarefa();
            QString data = dialog.dataTarefa().toString("dd/MM/yyyy");

            // Adiciona os dados à tabela
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(nome));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(tipo));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(data));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem("❌")); // Marca como pendente
        }
    });

    // Conecta o botão de excluir tarefa com confirmação
    connect(ui->btnExcluirTarefa, &QPushButton::clicked, this, [this]() {
        int row = ui->tableWidget->currentRow();  // Linha selecionada
        if (row >= 0) {
            // Caixa de diálogo de confirmação
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Excluir Tarefa",
                                          "Deseja realmente excluir esta tarefa?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                ui->tableWidget->removeRow(row);  // Remove a linha
            }
        }
    });

    // Permite alternar o status da tarefa (pendente/concluído) ao clicar
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, [this](int row, int column) {
        if (column == 3) {  // Coluna do status
            QString status = ui->tableWidget->item(row, column)->text();
            if (status == "❌") {
                ui->tableWidget->item(row, column)->setText("✅");  // Marca como concluída
            } else {
                ui->tableWidget->item(row, column)->setText("❌");  // Marca como pendente
            }
        }
    });
}

// Sobrescreve o evento de fechar a janela
void MainWindow::closeEvent(QCloseEvent *event) {
    salvarTarefas();  // Salva os dados ao fechar
    event->accept();  // Fecha normalmente
}

// Destrutor da MainWindow
MainWindow::~MainWindow() {
    delete ui;  // Libera a memória da interface
}
