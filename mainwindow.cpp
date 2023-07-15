#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createBoardGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBoardGame()
{
    ui->gameBoard->setRowCount(3);
    ui->gameBoard->setColumnCount(3);

    ui->gameBoard->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gameBoard->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->gameBoard->verticalHeader()->hide();
    ui->gameBoard->horizontalHeader()->hide();

    startNewGame();
}

int MainWindow::rowCount()
{
    return ui->gameBoard->rowCount();
}

int MainWindow::columnCount()
{
    return ui->gameBoard->columnCount();
}

bool MainWindow::foundWinner(QString player)
{
    // returns true if any the eight winning combinations is complete

    return ((board[0][0] + board[0][1] + board[0][2] == player + player + player)
            || (board[1][0] + board[1][1] + board[1][2] == player + player + player)
            || (board[2][0] + board[2][1] + board[2][2] == player + player + player)
            || (board[0][0] + board[1][0] + board[2][0] == player + player + player)
            || (board[0][1] + board[1][1] + board[2][1] == player + player + player)
            || (board[0][2] + board[1][2] + board[2][2] == player + player + player)
            || (board[0][0] + board[1][1] + board[2][2] == player + player + player)
            || (board[2][0] + board[1][1] + board[0][2] == player + player + player));
}

bool MainWindow::isGameTied()
{
    // Check if every possible move is alreday made
    return (!board[0][0].isEmpty() && !board[0][1].isEmpty() && !board[0][2].isEmpty()
            && !board[1][0].isEmpty() && !board[1][1].isEmpty() && !board[1][2].isEmpty()
            && !board[2][0].isEmpty() && !board[2][1].isEmpty() && !board[2][2].isEmpty());
}

void MainWindow::placeMoveMark(int row, int col)
{
    QTableWidgetItem *move = new QTableWidgetItem(player);
    move->setTextAlignment(Qt::AlignCenter);

    //(player == playerX)? move->setForeground(QColor(230,0,0)) :  move->setForeground(QColor(0,0,230));
    move->setForeground(QColor(0,0,0));

    ui->gameBoard->setItem(row, col, move);
    move = nullptr;
}

void MainWindow::startNewGame()
{
    // Reset board and start a new game
    ui->gameBoard->clear();

    for (int row = 0; row < rowCount(); row++)
    {
        for (int col = 0; col < columnCount(); col++)
        {
            board[row][col] = "";
        }
    }

    gameOver = false;
}

void MainWindow::updateGameScore()
{
    (player == playerX)? xScore = xScore + 1 : oScore = oScore + 1;

    ui->gameScore->clear();
    QString xTotal = playerX + ": " + QString::number(xScore);
    QString oTotal = playerO + ": " + QString::number(oScore);

    ui->gameScore->setText(xTotal + "      ||     " + oTotal);
    gameOver = true;
}

void MainWindow::on_gameBoard_clicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    if (!board[row][col].isEmpty())
    {
        return;
    }

    // Add X or 0 to the board
    board[row][col] = player;
    placeMoveMark(row, col);

    if (foundWinner(player))
    {
        updateGameScore();
        QMessageBox::information(this, "Game Over!", "\n" + player + " won this game.\nPress Ok to start a new game.", QMessageBox::Ok);
        startNewGame();
    }
    else if (isGameTied())
    {
        QMessageBox::information(this, "Game Over!","\nIt's a tie.\nPress Ok to start a new game.", QMessageBox::Ok);
        gameOver = true;
        startNewGame();
    }
    else
    {
        // switch turn between X and 0
        player = (player == playerX)? playerO : playerX;
    }
}

void MainWindow::on_newGame_clicked()
{
    if (!gameOver)
    {
        int exec = QMessageBox::critical(this, "Game In-Progress!","The game is in progress.\nRestart game?",
                                         QMessageBox::Yes | QMessageBox::No);

        if (exec == QMessageBox::No)
            return;
    }

    startNewGame();
}

void MainWindow::on_exitGame_clicked()
{
    QApplication::exit(0);
}

