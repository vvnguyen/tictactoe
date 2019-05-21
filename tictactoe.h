#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
class QPushButton;

namespace Ui {
class tictactoe;
}

class tictactoe : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Player)
    Q_PROPERTY(Player currentPlayer READ currentPlayer
               WRITE setCurrentPlayer NOTIFY currentPlayerChanged)

    static const int nr_rows = 3;
    static const int nr_columns =3;
public:
    enum Player {
        Invalid, Player1, Player2, Draw
    };
signals:
    void currentPlayerChanged(Player);
    void gameOver(tictactoe::Player);

public slots:
    void handleButtonClick(int);

public:
    explicit tictactoe(QWidget *parent = nullptr);
    void initNewGame();
    Player currentPlayer() const {return m_currentPlayer;}
    void setCurrentPlayer(Player p){
        if(m_currentPlayer == p) return;
        m_currentPlayer = p;
        emit currentPlayerChanged(p);
    }
    ~tictactoe();

private:
    Ui::tictactoe *ui;
    QList<QPushButton*> board;
    Player m_currentPlayer;
    void setupBoard();
    Player checkWinCondition(int, int);
};

#endif // TICTACTOE_H
