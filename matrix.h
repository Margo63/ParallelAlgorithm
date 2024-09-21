//
// Created by Маргарита  on 21.09.2024.
//

#ifndef LAB1_PAR_ALG_MATRIX_H
#define LAB1_PAR_ALG_MATRIX_H
#include <iostream>
#include <sys/wait.h>

#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> split_in_num(std::string line);
void read_matrix(std::string name_file, std::vector<std::vector<int>> *matrix);
void multiplication(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB,
                    std::vector<std::vector<int>> *matrixC);
void print(std::vector<std::vector<int>> matrix);
void write_to_file(std::vector<std::vector<int>> matrix);

#endif //LAB1_PAR_ALG_MATRIX_H
