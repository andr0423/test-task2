#include <iostream>
#include <random>

#include "matrix.h"

using namespace std;

//size_t thrds = 3; 

int main(void){

    uniform_int_distribution<> rnddist(100,900);

    cout << "+-----------------------+" << endl;
    cout << "|      Test task2       |" << endl;
    cout << "+-----------------------+" << endl;
    
    cout << "" << endl;

    cout << "==== A from file A.txt = ==== ====" << endl;
    Matrix m_a {"A.txt"};
    cout << m_a;
    cout << "" << endl;

    cout << "==== B from file B.txt = ==== ====" << endl;
    Matrix m_b {"B.txt"};
    cout << m_b;
    cout << "" << endl;

    // cout << "==== D(A), E=B - COPY == ==== ====" << endl;
    // Matrix m_d(m_a);
    // Matrix m_e;
    // m_e = m_b;
    // cout << m_d << endl << m_e << endl;;
    // cout << "" << endl;
    //
    // cout << "==== F(&&A.txt), G=&& - MOVE =====" << endl;
    // Matrix m_f(move(Matrix{2,3}));
    // Matrix m_g;
    // m_g = Matrix("B.txt");
    // cout << m_f << endl << m_g << endl;;
    // cout << "" << endl;
    //
    // cout << "==== Dummy Alghorythm == ==== ====" << endl;
    // Matrix m_c_dummy(m_a, m_b);
    // cout << m_c_dummy;
    // m_c_dummy.writeFile("C_dummy.txt");
    // cout << "" << endl;

    cout << "==== Threading Alghorythm * ======" << endl;
    Matrix m_c = m_a * m_b;
    cout << endl << m_c;
    m_c.writeFile("C.txt");
    cout << "" << endl;

    return 0;
}

