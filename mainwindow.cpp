#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QString>
#include <QFont> //word_type
#include <QAction>
#include <QIntValidator>
//#include <solvedialog.h>

int arr[81];
static int sec = 0;
static int min = 0;
int isStart = 0;
int clickTime = 1;

bool solve(sudoku question,sudoku &answer){
    int firstZero;
    firstZero = question.getFirstZero();
    if(firstZero == -1){
        if(question.isCorrect()){
            answer = question;
            return true;
        }
        else
            return false;
    }
    else{
        for(int num=1;num<=9;++num){            
            if(question.row(firstZero,num) && question.col(firstZero,num) && question.square(firstZero,num)){
                question.setElement(firstZero,num);
                if(solve(question,answer))
                    return true;
            }
        }
    return false;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  
{
    ui->setupUi(this);
    for(int i=0;i<81;++i){
        sudokuArray[i] = new QLineEdit(this);
        sudokuArray[i] ->setValidator(new QIntValidator(1,9,this));
        sudokuArray[i] ->setMaxLength(1);
        sudokuArray[i] ->setAlignment(Qt::AlignCenter);
        sudokuArray[i] ->setFont(QFont("Newyork",15,QFont::Normal));
        sudokuArray[i] ->resize(40,40);
        sudokuArray[i] ->move(80+40*(i%9)+3*((i-9*(i/9))/3),102+40*(i/9)+3*(i/27));
        sudokuArray[i] ->show();
    }
    /*
    for(int i=3;i<12;++i)
        sudokuArray[i+6*((i-3)/3)]->setStyleSheet("background-color:lightgray");
    for(int i=27;i<36;++i)
        sudokuArray[i+6*((i-27)/3)]->setStyleSheet("background-color:lightgray");
    for(int i=33;i<42;++i)
        sudokuArray[i+6*((i-33)/3)]->setStyleSheet("background-color:lightgray");
    for(int i=57;i<66;++i)
        sudokuArray[i+6*((i-57)/3)]->setStyleSheet("background-color:lightgray");
    */

    solveTime = new QTimer(this);
    solveTime ->start(1000);
    /*solveLCD = new QLCDNumber(this);
    solveLCD -> setGeometry(445,35,80,30);
    solveLCD -> setDigitCount(8);
    showTime();
    */
    ui->actionHard->setShortcut(Qt::Key_H);
    ui->space->setEnabled(0);
    ui->space2->setEnabled(0);
    ui->space3->setEnabled(0);
    ui->space4->setEnabled(0);
    ui->space5->setEnabled(0);
    //connect(ui->NewGame,SIGNAL(clicked()),this,SLOT(on_NewGame_clicked()));
    //connect(ui->NewGame,SIGNAL(clicked()),this,SLOT(StoreResetValue()));
    connect(ui->Solve,SIGNAL(clicked()),this,SLOT(on_Solve_clicked()));    
    connect(ui->Check,SIGNAL(clicked()),this,SLOT(on_Check_clicked()));

    connect(ui->actionEasy,SIGNAL(triggered()),this,SLOT(on_actionEasy_triggered()));
    connect(ui->actionEasy,SIGNAL(triggered()),this,SLOT(StoreResetValue()));
    connect(ui->actionModerate,SIGNAL(triggered()),this,SLOT(on_actionModerate_triggered()));
    connect(ui->actionModerate,SIGNAL(triggered()),this,SLOT(StoreResetValue()));
    connect(ui->actionHard,SIGNAL(triggered()),this,SLOT(on_actionHard_triggered()));
    connect(ui->actionHard,SIGNAL(triggered()),this,SLOT(StoreResetValue()));
    connect(ui->actionReset,SIGNAL(triggered()),this,SLOT(on_actionReset_triggered()));
    connect(ui->actionClear,SIGNAL(triggered()),this,SLOT(on_actionClear_triggered()));
    //connect(solveTime,SIGNAL(timeout()),this,SLOT(showTime()));
    connect(solveTime,SIGNAL(timeout()),this,SLOT(GameTime()));
    connect(ui->actionEasy,SIGNAL(triggered()),this,SLOT(ResetGameTime()));
    connect(ui->actionModerate,SIGNAL(triggered()),this,SLOT(ResetGameTime()));
    connect(ui->actionHard,SIGNAL(triggered()),this,SLOT(ResetGameTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_NewGame_clicked()
{
    sudoku gener;
    sudoku genans;
    for(int i=0;i<81;++i){
        sudokuArray[i] -> setText(NULL);
        sudokuArray[i] -> setStyleSheet("color:blue");
    }//clear last edit.
    srand(time(NULL));
    for(int i=0;i<10;++i){
        gener.setElement(rand()%80,i);
    }
    if(solve(gener,genans)==true){
        for(int i=0;i<30;++i){
            int index = rand()%80;
                genans.setElement(index,0);
        }
        for(int i=0;i<81;++i){
            if(genans.getElement(i) == 0)
                sudokuArray[i]->setText(NULL);                
            else{
                sudokuArray[i]->setText(QString("%1").arg(genans.getElement(i)));
                sudokuArray[i] ->setStyleSheet("color:black");
            }
        }
    }

}
*/
void MainWindow::on_Solve_clicked()
{
    sudoku solver;
    sudoku solverAns;
    for(int i=0;i<81;++i){
        solver.setElement(i,sudokuArray[i]->text().toInt());
    }
    if(solve(solver,solverAns)==true){
        for(int i=0;i<81;++i){
            if(sudokuArray[i]->text() == NULL)
                sudokuArray[i]->setStyleSheet("color:blue");
            sudokuArray[i]->setText(QString("%1").arg(solverAns.getElement(i)));            
        }
    }
}
void MainWindow::StoreResetValue(){
    for(int i=0;i<81;++i)
            arr[i] = sudokuArray[i]->text().toInt();
}
void MainWindow::on_Check_clicked()
{
    sudoku check;
    sudoku checkAns;
    for(int i=0;i<81;++i){
        check.setElement(i,arr[i]);//sudokuArray[i]->text().toInt());
    }
    if(solve(check,checkAns)==true){
        for(int i=0;i<81;++i){
            if(sudokuArray[i]->text().toInt() != checkAns.getElement(i))
                sudokuArray[i]->setStyleSheet("color:red");
            else
                sudokuArray[i]->setStyleSheet("color:blue");
        }
        for(int i=0;i<81;++i){
            if(check.getElement(i) != 0)
                sudokuArray[i]->setStyleSheet("color:black");
        }//setQuestion to black
        for(int i=0;i<81;++i){
            if(sudokuArray[i]->text() == NULL)
                //qDebug() << "gogogo";
                return;
        }
        ui->Complexity->setText("Congratulations!");
        //solveTime->stop();
        //solveDialog mydialog;
        //mydialog.setModal(true);
        //mydialog.exec();

    }

}
void MainWindow::on_actionEasy_triggered()
{
    ui->Complexity->setText(QString("%1").arg("Easy"));//setComplexity
    isStart = 1;
    sudoku gener;
    sudoku genans;
    for(int i=0;i<81;++i){
        sudokuArray[i] -> setText(NULL);
        sudokuArray[i] -> setStyleSheet("color:black");
        sudokuArray[i] -> setReadOnly(0);
    }//clear last edit.
    srand(time(NULL));
    for(int i=0;i<10;++i){
        gener.setElement(rand()%80,i);
    }
    if(solve(gener,genans)==true){
        for(int i=0;i<35;++i){
            int index = rand()%80;
                genans.setElement(index,0);
        }
        for(int i=0;i<81;++i){
            if(genans.getElement(i) == 0){
                sudokuArray[i]->setText(NULL);
                sudokuArray[i]->setStyleSheet("color:blue");
            }
            else{
                sudokuArray[i]->setText(QString("%1").arg(genans.getElement(i)));
                sudokuArray[i] -> setReadOnly(1);
            }
        }
    }
}
void MainWindow::on_actionModerate_triggered()
{
    ui->Complexity->setText(QString("%1").arg("Moderate"));
    isStart = 1;
    sudoku gener;
    sudoku genans;
    for(int i=0;i<81;++i){
        sudokuArray[i] -> setText(NULL);
        sudokuArray[i] -> setStyleSheet("color:black");
        sudokuArray[i] -> setReadOnly(0);
    }//clear last edit.
    srand(time(NULL));
    for(int i=0;i<10;++i){
        gener.setElement(rand()%80,i);
    }
    if(solve(gener,genans)==true){
        for(int i=0;i<50;++i){
            int index = rand()%80;
                genans.setElement(index,0);
        }
        for(int i=0;i<81;++i){
            if(genans.getElement(i) == 0){
                sudokuArray[i]->setText(NULL);
                sudokuArray[i]->setStyleSheet("color:blue");
            }
            else{
                sudokuArray[i]->setText(QString("%1").arg(genans.getElement(i)));
                sudokuArray[i] -> setReadOnly(1);
            }
        }
    }
}
void MainWindow::on_actionHard_triggered()
{
    ui->Complexity->setText(QString("%1").arg("Hard"));
    isStart = 1;
    sudoku gener;
    sudoku genans;
    for(int i=0;i<81;++i){
        sudokuArray[i] -> setText(NULL);
        sudokuArray[i] -> setStyleSheet("color:black");
        sudokuArray[i] -> setReadOnly(0);
    }//clear last edit.
    srand(time(NULL));
    for(int i=0;i<10;++i){
        gener.setElement(rand()%80,i);
    }
    if(solve(gener,genans)==true){
        for(int i=0;i<70;++i){
            int index = rand()%80;
                genans.setElement(index,0);
        }
        for(int i=0;i<81;++i){
            if(genans.getElement(i) == 0){
                sudokuArray[i]->setText(NULL);
                sudokuArray[i]->setStyleSheet("color:blue");
            }
            else{
                sudokuArray[i]->setText(QString("%1").arg(genans.getElement(i)));
                sudokuArray[i]->setReadOnly(1);
            }
        }
    }
}
/*
void MainWindow::showTime(){
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    solveLCD ->display(text);
}
*/
void MainWindow::GameTime(){
    if(isStart){
        ++sec;
        if(sec == 60){
            sec = 0;
            ++min;
        }
    ui->GameMin->setText(QString::number(min).rightJustified(2,'0').append(" : "));
    ui->GameSec->setText(QString::number(sec).rightJustified(2,'0'));
    }
}
/*
void MainWindow::paintEvent(QPaintEvent *){    
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,6));
    painter.drawLine(80,98,80,455);
    painter.drawLine(200,98,200,458);
    painter.drawLine(320+3*2,98,320+3*2,458);
    painter.drawLine(437+3*3,95,437+3*3,458);//vertical
    painter.drawLine(80,95,445,95);
    painter.drawLine(80,215,445,215);
    painter.drawLine(80,335+3*1,445,335+3*1);
    painter.drawLine(80,455+3*2,445,455+3*2);//horizontal
}
*/
void MainWindow::on_actionReset_triggered()
{
    for(int i=0;i<81;++i){
        sudokuArray[i]->setText(NULL);
    }
    for(int i=0;i<81;++i){
        if(arr[i] == 0)
            sudokuArray[i]->setText(NULL);
        else
            sudokuArray[i]->setText(QString("%1").arg(arr[i]));
    }
}
void MainWindow::ResetGameTime(){
    sec = 0;
    min = 0;
}
void MainWindow::on_PauseButton_clicked()
{   if(clickTime==1){
        solveTime->stop();
        for(int i=0;i<81;++i){
            sudokuArray[i]->setHidden(1);
            sudokuArray[i]->setEnabled(0);
        }
        ui->actionEasy->setEnabled(0);
        ui->actionModerate->setEnabled(0);
        ui->actionHard->setEnabled(0);
        ui->actionReset->setEnabled(0);
        ui->actionClear->setEnabled(0);
        ui->Check->setEnabled(0);
        ui->Solve->setEnabled(0);
        clickTime = -1;

    }
    else{
        solveTime->start();
        for(int i=0;i<81;++i){
            sudokuArray[i]->setHidden(0);
            sudokuArray[i]->setEnabled(1);
        }
        ui->actionEasy->setEnabled(1);
        ui->actionModerate->setEnabled(1);
        ui->actionHard->setEnabled(1);
        ui->actionReset->setEnabled(1);
        ui->actionClear->setEnabled(1);
        ui->Check->setEnabled(1);
        ui->Solve->setEnabled(1);
        clickTime = 1;
    }
}
void MainWindow::on_actionClear_triggered()
{
    for(int i=0;i<81;++i){
        sudokuArray[i]->setEnabled(1);
        sudokuArray[i]->setReadOnly(0);
        sudokuArray[i]->setText(NULL);
        sudokuArray[i]->setStyleSheet("color:black");
    }
    ui->Complexity->setText("Create your own Sudoku");
}
