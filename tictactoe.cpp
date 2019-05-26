#include "tictactoe.h"
#include "ui_tictactoe.h"
#include "ai.h"
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
    m_aiOn=false;
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
    if(m_aiOn){
        for(int i=0;i<9;++i)ai_board[i]=0;
    }
}

void tictactoe::handleButtonClick(int index) {
    if (index <0 || index >= board.size() ) return;
    QPushButton *button = board.at(index);

    if(button->text() != " ") return;
    if(currentPlayer() == tictactoe::Player1){
        button->setText("X");
        if(m_aiOn){
            ai_board[index]=1;
        }
    } else {
        button->setText("O");
        //ai is always second player so it must be disabled
    }
    Player winner = checkWinCondition(index/3, index%3);
    if(winner == Invalid){
        setCurrentPlayer(currentPlayer() == tictactoe::Player1 ? tictactoe::Player2 : tictactoe::Player1);
        if(m_aiOn){
            //ai finds best move
            int ai_index=0;
            ai_index = ai::minmax(ai_board,0,false);
            //ai makes move
            ai_board[ai_index]=-1;
            QPushButton *button = board.at(ai_index);
            button->setText("O");
            Player winner = checkWinCondition(ai_index/3, ai_index%3);
            if(winner!=Invalid)emit gameOver(winner);
            setCurrentPlayer(currentPlayer() == tictactoe::Player1 ? tictactoe::Player2 : tictactoe::Player1);
        }
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

    bool three_same_in_column = true;
    for(int j=column;j<(column+6);j+=3){
        if(board.at(j)->text() != board.at(j+3)->text()){
            three_same_in_column = false;
            break;
        }
    }
    if (three_same_in_column){
        return currentPlayer();
    }

    if(row==column){
        //diagonal
        bool three_same_on_diagonal = true;
        for(int k=0;k<8;k+=4){
            if(board.at(k)->text() != board.at(k+4)->text()){
                three_same_on_diagonal = false;
                break;
            }
        }
        if (three_same_on_diagonal){
            return currentPlayer();
        }
    }

    if ( ((row==1)&&(column==1)) ||
         ((row==2)&&(column==0)) ||
         ((row==0)&&(column==2))){
        bool three_same_on_counterdiagonal = true;
        for(int l=2;l<6;l+=2){
            if(board.at(l)->text() != board.at(l+2)->text()){
                three_same_on_counterdiagonal = false;
                break;
            }
        }
        if(three_same_on_counterdiagonal){
            return currentPlayer();
        }
    }

    bool its_draw = true;
    for(int field=0;field<9;++field){
        if( board.at(field)->text()==" "){
            its_draw = false;
            break;
        }
    }
    if(its_draw){
        return Draw;
    }
    return Invalid;
};
