#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configurationdialog.h"
#include "tictactoe.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameBoard->setEnabled(false);
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->gameBoard, SIGNAL(currentPlayerChanged(Player)), this, SLOT(updateNameLabels(Player)));
    connect(ui->gameBoard, SIGNAL(gameOver(tictactoe::Player)), this, SLOT(handleGameOver(tictactoe::Player)));
}

void MainWindow::startNewGame(){
    ConfigurationDialog dlg(this);
    if(dlg.exec()== QDialog::Rejected){
        return; //do nothing if dialog rejected
    }
    ui->player1->setText(dlg.player1Name());
    ui->player2->setText(dlg.player2Name());
    ui->gameBoard->initNewGame();
    ui->gameBoard->setEnabled(true);
    updateNameLabels();
}

void MainWindow::updateNameLabels(){
    QFont f = ui->player1->font();
    f.setBold(ui->gameBoard->currentPlayer()==tictactoe::Player1);
    ui->player1->setFont(f);
    f.setBold(ui->gameBoard->currentPlayer()==tictactoe::Player2);
    ui->player2->setFont(f);
}

void MainWindow::handleGameOver(tictactoe::Player winner){
    ui->gameBoard->setEnabled(false);
    QString message;
    if(winner == tictactoe::Draw){
        message = "Game ended with a draw.";
    }else {
        message = QString("%1 wins").arg(winner ==
        tictactoe::Player1 ? ui->player1->text() : ui->player2->text());
    }
    QMessageBox::information(this, "Info", message);
}

MainWindow::~MainWindow()
{
    delete ui;
}
