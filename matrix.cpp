//
// Created by Маргарита  on 21.09.2024.
//
#include "matrix.h"
//get vector from line
std::vector<int> splitInNum(std::string line) {
    char *copy = const_cast<char *>(line.c_str());
    char *token = std::strtok(copy, " ");
    std::vector<int> result;
    while (token != NULL) {
        result.push_back(atoi(token));
        token = strtok(NULL, " ");
    }
    return result;
}

void readMatrix(std::string name_file, std::vector<std::vector<int>> *matrix) {
    std::ifstream file;
    file.open(name_file);

    if (!file.is_open()) {
        std::cout << "Error opening the file!\n";
        return;
    }

    std::string line;
    while (getline(file, line)) {
        matrix->push_back(splitInNum(line));
    }
    //std::cout<<"finish read\n";

    file.close();
}

void multiplication(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB,
                    std::vector<std::vector<int>> *matrixC) {
    for (int i = 0; i < matrixA.size(); i++) {
        std::vector<int> line;
        for (int j = 0; j < matrixB[0].size(); j++) {
            int cur = 0;
            for (int k = 0; k < matrixB.size(); k++) {
                cur += matrixA[i][k] * matrixB[k][j];
            }
            line.push_back(cur);
            //std::cout << cur << "\t";
        }
        matrixC->push_back(line);

        //std::cout << "\n";
    }
}

void print(std::vector<std::vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

}
void writeToFile(std::vector<std::vector<int>> matrix,std::string name_file){
    std::ofstream file;
    file.open(name_file);

    if (!file.is_open()) {
        std::cout << "Error opening the file!\n";
        return;
    }
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            file << matrix[i][j] << " ";
        }
        file << "\n";
    }
}