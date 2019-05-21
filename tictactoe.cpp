#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>

tictactoe::tictactoe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tictactoe)
{
    ui->setupUi(this);
    setupBoard();
}

void tictactoe::initNewGame()
{
    for(int i=0;i<9;++i) board.at(i)->setText(" ");
    m_currentPlayer = tictactoe::Player1;
}

tictactoe::~tictactoe()
{
    delete ui;
}

void tictactoe::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper(this);
    for (int row = 0; row < 3; ++row){
        for(int column=0;column<3;++column){
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
            button->setText("");
            gridLayout->addWidget(button, row, column);
            board.append(button);
            mapper->setMapping(button, board.count()-1);
            connect(button,SIGNAL(clicked()),mapper,SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
    initNewGame();
}

void tictactoe::handleButtonClick(int index) {
    if (index <0 || index >= board.size() ) return;
    QPushButton *button = board.at(index);
    if(button->text() != " ") return;
    button->setText(currentPlayer() == tictactoe::Player1 ? "X" : "O");
    Player winner = checkWinCondition(index/3, index%3);
    if(winner == Invalid){
        setCurrentPlayer(currentPlayer() == tictactoe::Player1 ? tictactoe::Player2 : tictactoe::Player1);
        return;
    } else {
        emit gameOver(winner);
    }
}

tictactoe::Player tictactoe::checkWinCondition(int row, int column) {
    bool three_same_in_row = true;
    const int lim = tictactoe::nr_rows+row*3;
    for (int i=1+row*3;i<lim;++i){
        if(board.at(i)->text() != board.at(i-1)->text()){
            three_same_in_row = false;
            break;
        }
    }
    if (three_same_in_row){
        return currentPlayer();
    }
    if(row==column){
        //diagonal
    }
    return Invalid;
};
