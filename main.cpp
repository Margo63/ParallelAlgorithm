
#include <iostream>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include "matrix.h"
#include <sstream>
#include <cstring>
#include <unistd.h>

//trasnform 2d vector to string
std::string serialize(const std::vector<std::vector<int>> &vector) {
    std::ostringstream stringVector;
    for (const auto &row: vector) {
        for (const auto &element: row) {
            stringVector << element << " ";
        }
        stringVector << "\n";
    }
    return stringVector.str();
}

// trsansform string to 2d vector
std::vector<std::vector<int>> deserialize(const std::string &stringVector) {
    std::vector<std::vector<int>> vector;
    std::istringstream data(stringVector);
    std::string line;
    while (std::getline(data, line)) {
        std::istringstream lineStream(line);
        std::vector<int> row;
        int val;
        while (lineStream >> val) {
            row.push_back(val);
        }
        vector.push_back(row);
    }
    return vector;
}

void processInitializeMatrix(int fdMatrixA, int fdMatrixB) {
    std::vector<std::vector<int>> matrixA, matrixB;
    readMatrix("../input.txt", &matrixA);
    readMatrix("../test.txt", &matrixB);

    std::string x = serialize(matrixA);
    std::string y = serialize(matrixB);
    write(fdMatrixA, x.c_str(), x.size() + 1);
    write(fdMatrixB, y.c_str(), y.size() + 1);
}

void processMultiplitacionMatrix(int fdMatrixA, int fdMatrixB, int fdMatrixC) {
    char buffer[1024];

    read(fdMatrixA, &buffer, sizeof(buffer));
    std::string matrixAData(buffer);

    char buffer2[1024];
    read(fdMatrixB, &buffer2, sizeof(buffer2));
    std::string matrixBData(buffer2);

    std::vector<std::vector<int>> matrixA = deserialize(matrixAData);
    std::vector<std::vector<int>> matrixB = deserialize(matrixBData);

    //print(matrixA);
    //std::cout<<"//////////\n";
    //print(matrixB);
    std::vector<std::vector<int>> matrixC;
    multiplication(matrixA, matrixB, &matrixC);
    std::string c = serialize(matrixC);
    write(fdMatrixC, c.c_str(), c.size() + 1);
}

void processWriteResult(int fdMatrixC) {
    char buffer[1024];
    read(fdMatrixC, &buffer, sizeof(buffer));
    std::string matrixCData(buffer);
    std::vector<std::vector<int>> matrixC = deserialize(matrixCData);
    //print(matrixC);
    writeToFile(matrixC,"../output_process.txt");
}

int main() {
    auto start = std::chrono::system_clock::now();

    int fdMatrixA[2];
    int fdMatrixB[2];
    int fdMatrixC[2];
    if (pipe(fdMatrixA) == -1) {
        return -1;
    }
    if (pipe(fdMatrixB) == -1) {
        return -1;
    }
    if (pipe(fdMatrixC) == -1) {
        return -1;
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(fdMatrixA[0]);
        close(fdMatrixB[0]);

        processInitializeMatrix(fdMatrixA[1], fdMatrixB[1]);

        close(fdMatrixA[1]);
        close(fdMatrixB[1]);
        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(fdMatrixA[1]);
        close(fdMatrixB[1]);
        close(fdMatrixC[0]);

        processMultiplitacionMatrix(fdMatrixA[0], fdMatrixB[0], fdMatrixC[1]);

        close(fdMatrixA[0]);
        close(fdMatrixB[0]);
        close(fdMatrixC[1]);
        return 0;
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(fdMatrixC[1]);

        processWriteResult(fdMatrixC[0]);

        close(fdMatrixC[0]);
        return 0;
    }

    wait(nullptr);
    wait(nullptr);
    wait(nullptr);


    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count();
    return 0;
}