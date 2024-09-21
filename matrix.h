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

std::vector<int> splitInNum(std::string line);
void readMatrix(std::string name_file, std::vector<std::vector<int>> *matrix);
void multiplication(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB,
                    std::vector<std::vector<int>> *matrixC);
void print(std::vector<std::vector<int>> matrix);
void writeToFile(std::vector<std::vector<int>> matrix, std::string name_file);

#endif //LAB1_PAR_ALG_MATRIX_H
