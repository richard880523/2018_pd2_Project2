#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
class sudoku{
    public:
        sudoku();//constructor
        sudoku(const int inti_map[]);//can input a sudoku array and solve it
        void setMap(const int set_map[]);
        int getElement(int index);//return a index
        bool isCorrect();
        static const int sudokuSize = 81;
        void setElement(int index,int value);
        int getFirstZero();
        bool row(int index, int num);
        bool col(int index, int num);
        bool square(int index, int num);
        void generate();

    private:
        bool checkUnity(int arr[]);//check 1-9
        int map[sudokuSize];
};
#endif // SUDOKU_H
