#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tictactoe.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void startNewGame();

private slots:
    void updateNameLabels();
    void handleGameOver(tictactoe::Player winner);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
