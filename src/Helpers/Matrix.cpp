#include "../../include/Helpers/Matrix.h"

#include "../../include/Helpers/Random.h"
#include <iostream>

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<float>(rows * cols);
}

Matrix::Matrix(const Matrix &matrix) {
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix = std::vector<float>(matrix.matrix);
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i * cols + j] << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = Random::RangeFloat(-1, 1);
        }
    }
}

void Matrix::mutate(float mutationRate) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float rand = Random::RangeFloat(0, 1);

            if(rand <= mutationRate)
                matrix[i * cols + j] = Random::RangeFloat(-1, 1);
        }
    }
}

std::shared_ptr<Matrix> Matrix::crossover(const Matrix &n) const {
    auto result = std::make_shared<Matrix>(rows, cols);
    int rand = Random::RangeInt(0, result->matrix.size());

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float index = i * cols + j;

            if(index < rand)
                result->matrix[index] = matrix[index];
            else
                result->matrix[index] = n.matrix[index];
        }
    }

    return result;
}

std::shared_ptr<Matrix> Matrix::dot(const Matrix &n) const {
    auto result = std::make_shared<Matrix>(rows, n.cols);

    if (cols == n.rows) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < n.cols; j++) {
                float sum = 0;

                for (int k = 0; k < cols; k++) {
                    sum += matrix[i * cols + k] * n.matrix[k * n.cols + j];
                }

                result->matrix[i * n.cols + j] = sum;
            }
        }
    } else {
        std::cout << "Dot error" << std::endl;
    }

    return result;
}

std::shared_ptr<Matrix> Matrix::add(const Matrix &n) const {
    auto result = std::make_shared<Matrix>(rows, cols);

    if (cols == n.cols && rows == n.rows) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->matrix[i * cols + j] = matrix[i * cols + j] + n.matrix[i * cols + j];
            }
        }
    } else if (cols == n.cols && n.rows == 1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->matrix[i * cols + j] = matrix[i * cols + j] + n.matrix[j];
            }
        }
    } else if (rows == n.rows && n.cols == 1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->matrix[i * cols + j] = matrix[i * cols + j] + n.matrix[i];
            }
        }
    } else
        std::cout << "Add error" << std::endl;

    return result;
}

std::shared_ptr<Matrix> Matrix::apply(float (*function)(float)) const {
    auto result = std::make_shared<Matrix>(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result->matrix[i * cols + j] = function(matrix[i * cols + j]);
        }
    }

    return result;
}

float &Matrix::operator()(int x, int y) {
    return matrix[x * cols + y];
}

const float &Matrix::operator()(int x, int y) const {
    return matrix[x * cols + y];
}