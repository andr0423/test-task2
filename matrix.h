#pragma once
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Matrix{

    size_t x = 0;
    size_t y = 0;

    vector<vector<int>> mt = {};

    size_t p = 0;

public:
    Matrix(const char * fname);

    Matrix(size_t = 0, size_t = 0);

    Matrix(Matrix &, Matrix &);

    Matrix(Matrix &, Matrix &, size_t);

    ~Matrix();

    void setElement(size_t x, size_t y, int value);
    int getElement(size_t x, size_t y);

    void writeFile(const char *);

    friend ostream & operator<<(ostream &, Matrix &);

private:
    void readFile(const char * fname);
    void resize(size_t, size_t);


};
