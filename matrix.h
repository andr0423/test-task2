#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std;

static size_t thrds = 4; 

class Matrix{

    size_t x = 0;
    size_t y = 0;

    vector<vector<int>> mt = {};

    struct xy {
        size_t x_p = 0;
        size_t y_p = 0;
        bool empty = true;
        bool end = false;
    } coord;

    mutex * mm = nullptr;

public:
    Matrix(size_t = 0, size_t = 0);
    Matrix(const char * fname);         

    Matrix(const Matrix &);
    Matrix(Matrix &&);

    Matrix & operator=(const Matrix &);
    Matrix & operator=(Matrix &&);

    Matrix(Matrix &, Matrix &);   // Dummy multiply
    
    ~Matrix();

    Matrix operator*(const Matrix &) const;

    void setElement(size_t x, size_t y, int value);
    int getElement(size_t x, size_t y) const;
    void writeFile(const char *);
    friend ostream & operator<<(ostream &, Matrix &);

private:
    void readFile(const char * fname);
    void init(size_t, size_t);

    void calculateAllElements(const Matrix & a, const Matrix & b, size_t);
    void calculateElement(const Matrix & a, const Matrix & b, size_t, size_t);
    void getNextCoordinate();

};
