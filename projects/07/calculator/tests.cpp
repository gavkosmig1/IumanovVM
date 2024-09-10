#include <iostream>

class Matrix {
    public:
    int rows;
    int columns;
    double *data;

    // Конструктор
    Matrix(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
        this->data = new double[rows * columns];
    }

    // Конструктор копирования
    Matrix(const Matrix& other) {
        this->rows = other.rows;
        this->columns = other.columns;
        this->data = new double[rows * columns];
        std::copy(other.data, other.data + rows * columns, this->data);
    }

    // Деструктор
    ~Matrix() {
        delete[] data;
    }

    // Оператор «
    friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                os << matrix.data[i * matrix.columns + j] << " ";
            }
        os << std::endl;
        }
    return os;
    }
};