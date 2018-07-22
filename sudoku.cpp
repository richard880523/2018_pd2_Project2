#include "sudoku.h"
sudoku::sudoku(){
    for(int i=0;i<sudokuSize;i++)
        map[i] = 0;
}
sudoku::sudoku(const int init_map[]){
    for(int i=0;i<sudokuSize;i++)
        map[i] = init_map[i];
}
void sudoku::setMap(const int set_map[]){
    for(int i=0;i<sudokuSize;i++)
        map[i] = set_map[i];
}
int sudoku::getElement(int index){
    return map[index];
}
bool sudoku::checkUnity(int arr[]){
    int arr_unity[9];//counter

    for(int i=0;i<9;++i)
        arr_unity[i] = 0;//initialize
    for(int i=0;i<9;++i)
        ++arr_unity[arr[i]-1];//count
    for(int i=0;i<9;++i)
        if(arr_unity[i]!=1)
            return false;
    return true;
}
bool sudoku::isCorrect(){
    bool check_result;
    int check_arr[9];
    int location;

    for(int i=0;i<81;i+=9){
        for(int j=0;j<9;++j)
            check_arr[j] = map[i+j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }//check rows
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j)
            check_arr[j] = map[i+9*j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }//check columns
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            location = 27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
        check_arr[j] = map[location];
    }
    check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
        return true;
}
void sudoku::setElement(int index, int value){
    map[index] = value;
}
int sudoku::getFirstZero(){
    for(int i=0;i<sudokuSize;++i)
        if(map[i] == 0)
            return i;
    return -1;
}
bool sudoku::row(int index, int num){
    int r = (index+9)/9;
    for(int i=9*(r-1);i<9*r;++i){
        if(map[i] == num)
            return false;
    }
        return true;
}
bool sudoku::col(int index, int num){
    int c = (index%9);
    for(int i=c;i<81;i+=9){
        if(map[i] == num)
            return false;
    }
        return true;
}
bool sudoku::square(int index, int num){
    int r = (index/9);
    int c = (index%9);
    int r_sqr = (r/3);
    int c_sqr = (c/3);
    int location;
    for(int i=0;i<9;++i){
        location = 27*(r_sqr) + 3*(c_sqr) + 9*(i/3) + (i%3);
        if(map[location] == num)
            return false;
    }
        return true;
}
