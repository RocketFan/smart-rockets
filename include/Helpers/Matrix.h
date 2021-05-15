#pragma once

#include <vector>
#include <memory>

class Matrix {
public:
    int rows;
    int cols;
    std::vector<float> matrix;

    Matrix(int rows, int cols);

    template<size_t rows, size_t cols>
    Matrix(float (&matrix)[rows][cols]) {
        this->matrix = std::vector<float>(rows * cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this->matrix[i * cols + j] = matrix[i][j];
            }
        }

        this->rows = rows;
        this->cols = cols;
    };

    Matrix(const Matrix &matrix);

    void print() const;

    void randomize();

    void mutate(float mutationRate);

    std::shared_ptr<Matrix> crossover(const Matrix &n) const;

    std::shared_ptr<Matrix> dot(const Matrix &n) const;

    std::shared_ptr<Matrix> add(const Matrix &n) const;

    std::shared_ptr<Matrix> apply(float (*function)(float)) const;

    float &operator()(int x, int y);

    const float &operator()(int x, int y) const;
};