#include "matrix.h"

Matrix::Matrix(const char *fname)
{
    this->readFile(fname);
}

Matrix::Matrix(size_t x, size_t y)
{
    this->resize(x, y);
}

Matrix::Matrix( Matrix & a, Matrix & b )
{
    this->resize(b.x, a.y);

    //
    // Dummy
    //
    // A.x == B.y
    //

    for (size_t row = 0 ; row < a.y ; row ++){
        for (size_t col = 0 ; col < b.x ; col ++){

            for (int inner = 0; inner < a.x; inner++) {
                mt[row][col] += a.getElement(inner, row) * b.getElement(col, inner);
            }

        }
    }

}

Matrix::Matrix( Matrix & a, Matrix & b, size_t p )
{

}

Matrix::~Matrix()
{
}

void Matrix::setElement(size_t x, size_t y, int value)
{
    if ( x > this->x || y > this->y){
        return;
    }
    mt[x][y] = value;
}

int Matrix::getElement(size_t x, size_t y)
{
    if (x > this->x || y > this->y) {
        cout << " Oops... out of index." << endl;
        return 0;
    }
    return mt[y][x];
}

void Matrix::writeFile(const char * fname)
{
    ofstream fh(fname);
    fh << *this;
}

void Matrix::readFile(const char *fname)
{
    ifstream fh(fname);

    int tmp;
    vector<int> tmp_arr;

    while( ! fh.eof() ){

        fh >> tmp;
        tmp_arr.push_back(tmp);
        
        if ( fh.peek() == '\n' ){
            mt.push_back(move(tmp_arr));
        }

    }
    
    this->x = mt[0].size();
    this->y = mt.size();

    fh.close();
}

void Matrix::resize(size_t x, size_t y)
{
    this->x = x;
    this->y = y;
    mt.resize(y);
    for ( auto & col : mt ){
        col.resize(x);
    }
}

ostream &operator<<(ostream & os, Matrix & o)
{
    for (size_t y = 0 ; y < o.y; y++){
        for (size_t x = 0 ; x < o.x ; x++ ){
            os << o.mt[y][x] << " ";
        }
        os << endl;
    }
    return os;
}
