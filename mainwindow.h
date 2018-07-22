#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit> //sudokuArray
#include <QLine>
#include <QPainter> //draw thick lines
#include <QTimer> //start(1000),timeout()signals
#include <QTime> //get current time
#include <QLCDNumber> //show time with LCD
#include <QElapsedTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_NewGame_clicked();
    void on_Solve_clicked();
    void StoreResetValue();
    void on_Check_clicked();
    void on_actionEasy_triggered();
    void on_actionModerate_triggered();
    void on_actionHard_triggered();
    void on_actionReset_triggered();
    void on_actionClear_triggered();
    //void showTime();
    void GameTime();
    void ResetGameTime();
    //void paintEvent(QPaintEvent*);
    void on_PauseButton_clicked();

private:
    QLineEdit *sudokuArray[81];
    QTimer *solveTime;
    QLCDNumber *solveLCD;
    QElapsedTimer *elapsedTime;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
