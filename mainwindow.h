#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    const QString playerX = "X";
    const QString playerO = "O";

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void createBoardGame();
    bool foundWinner(QString winner);
    bool isGameTied();
    void placeMoveMark(int row, int col);
    int rowCount();
    int columnCount();


protected:
    void startNewGame();
    void updateGameScore();


private slots:
    void on_gameBoard_clicked(const QModelIndex &index);
    void on_newGame_clicked();
    void on_exitGame_clicked();


private:
    Ui::MainWindow *ui;

    QString board[3][3];
    int xScore = 0, oScore = 0;
    bool gameOver = false;
    QString player = playerX;
};

#endif // MAINWINDOW_H
