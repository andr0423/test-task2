#include <iostream>

#include "matrix.h"

using namespace std;

int main(void){

    cout << "Test task2" << endl;

    Matrix m_a {"A.txt"};
    cout << m_a;

    cout << "" << endl;

    Matrix m_b {"B.txt"};
    cout << m_b;

    cout << "" << endl;

    Matrix m_c(m_a, m_b);
    cout << m_c;
    m_c.writeFile("C.txt");

    return 0;
}

