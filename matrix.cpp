#include "matrix.h"
#include <thread>



Matrix::Matrix(size_t x, size_t y)
{
    this->init(x, y);
}

Matrix::Matrix(const char *fname)
{
    this->readFile(fname);
}

Matrix::Matrix(const Matrix & o)
{
    x = o.x;
    y = o.y;
    this-> mt = o.mt;
    this->coord = o.coord;
    this->mm = nullptr;
}

Matrix::Matrix(Matrix && o)
{
    this->x = o.x;
    this->y = o.y;
    this->mt = move(o.mt);
    this->coord = move(o.coord);
    this->mm = nullptr;

    o.x = o.y = 0;
    o.coord = {};
    o.mm = nullptr;
}

Matrix & Matrix::operator=(const Matrix & o)
{
    x = o.x;
    y = o.y;
    this->mt = o.mt;
    this->coord = o.coord;
    this->mm = nullptr;
    return *this;
}



Matrix &Matrix::operator=(Matrix && o)
{
    this->x = o.x;
    this->y = o.y;
    this->mt = move(o.mt);
    this->coord = move(o.coord);
    this->mm = nullptr;

    o.x = o.y = 0;
    o.coord = {};
    o.mm = nullptr;

    return *this;
}

/*
 * Dummy alghorythm realized in constructor
 */
Matrix::Matrix( Matrix & a, Matrix & b )
{
    // Dummy
    //
    // A.x == B.y
    //

    this->init(b.x, a.y);

    while( ! this->coord.end ){
        this->getNextCoordinate();        
        this->calculateElement(a, b, this->coord.x_p, this->coord.y_p);
    }
}

Matrix::~Matrix()
{
}


Matrix Matrix::operator*(const Matrix & o) const
{
    const Matrix & a = *this;
    const Matrix & b = o;

    Matrix mul = Matrix(b.x, a.y);
    Matrix * p_mul = &mul;

    mul.mm = new mutex();

    thread *tr = new thread[thrds];

    for ( size_t i = 0; i < thrds ; i++ ){
        cout << " +--+--> thread(" << i << ")" << endl;
        tr[i] = thread ( &Matrix::calculateAllElements, p_mul, cref(a), cref(b), i );

    }
    for ( size_t i = 0; i < thrds ; i++ ){
        tr[i].join();
    }

    delete[] (tr);
    delete (mul.mm);

    return move(Matrix(mul));
}





/* ************************** *
 *
 *  pulic:
 * 
 * ************************** */

int Matrix::getElement(size_t x, size_t y) const
{
    if (x > this->x || y > this->y) {
        cout << " Oops... out of index." << endl;
        return 0;
    }
    return mt[y][x];
}



void Matrix::setElement(size_t x, size_t y, int value)
{
    if ( x > this->x || y > this->y){
        return;
    }
    mt[x][y] = value;
}

void Matrix::writeFile(const char * fname)
{
    ofstream fh(fname);
    fh << *this;
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


/* ************************** *
 *
 *  private:
 * 
 * ************************** */
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

void Matrix::init(size_t x, size_t y)
{
    this->x = x;
    this->y = y;
    mt.resize(y);
    for ( auto & col : mt ){
        col.resize(x);
    }
}

void Matrix::calculateAllElements(const Matrix &a, const Matrix &b, size_t p)
{
    size_t x_th, y_th;
    uint timeout;
    while( ! this->coord.end ){

        this->mm->lock();
        this->getNextCoordinate();
        x_th = this->coord.x_p;
        y_th = this->coord.y_p;
        this->mm->unlock();

        timeout = rand() % 800 + 100;

        cout << "    +--> " << p << ": x,y=["<< x_th << "," << y_th << "] Begin, " << timeout << "ms" << endl;
        this->calculateElement(a, b, x_th, y_th);
        this_thread::sleep_for(chrono::milliseconds(timeout));
        cout << "    +--> " << p << ": x,y=["<< x_th << "," << y_th << "] END" << endl;
    }
}

void Matrix::calculateElement(const Matrix & a, const Matrix & b, size_t x, size_t y)
{
    size_t row = y;
    size_t col = x;
    for (int inner = 0; inner < a.x; inner++) {
        mt[row][col] += a.getElement(inner, row) * b.getElement(col, inner);
    }
}

void Matrix::getNextCoordinate()
{
    if (this->coord.empty){
        this->coord.empty = false;
        return;
    }else if (this->coord.x_p == this->x-1 && this->coord.y_p == this->y-1) {
        return;
    }else if (this->coord.x_p == this->x-2 && this->coord.y_p == this->y-1) {
        this->coord.end = true;
        this->coord.x_p += 1;
        return;
    }else if (this->coord.x_p == this->x-1) {
        this->coord.x_p = 0;
        this->coord.y_p += 1;
        return;
    }else {
        this->coord.x_p += 1;
    }
}
