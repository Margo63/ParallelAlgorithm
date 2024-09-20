
#include <iostream>
#include <sys/wait.h>

#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> split_in_num(std::string line) {
    char *copy = const_cast<char *>(line.c_str());
    char *token = std::strtok(copy, " ");
    std::vector<int> result;
    while (token != NULL) {
        result.push_back(atoi(token));
        token = strtok(NULL, " ");
    }
    return result;
}

void read_matrix(std::string name_file, std::vector<std::vector<int>> *matrix) {
    std::ifstream file;
    file.open(name_file);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cout << "Error opening the file!\n";
        return;
    }

    std::string line; // Declare a string variable to store each
    std::string size_line;

    getline(file, size_line);
//    std::vector<int> result = split_in_num(size_line);
//    if (result.size() != 2)
//        return;
//
//    int row = result[0], column = result[1];

    while (getline(file, line)) {
        matrix->push_back(split_in_num(line));
    }
    std::cout<<"finish read\n";

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

int main() {
    std::vector<std::vector<int>> matrixA, matrixB,matrixC;

    pid_t pid = fork();

    switch (pid){
        // весь код после fork() дважды:
        // в родительском процессе и в процессе потомке

        case -1: //неудачная попытка создать процесс-потомок
            exit(-1); //выход из родительского процесса

        case 0: //потомок
            std::cout<<"CHILD:: Hello, my pid = "<< getpid()<<"; my parent's pid (ppid) = "<<getppid()<<std::endl;
            multiplication(matrixA, matrixB, &matrixC);
            print(matrixC);

            return 0;

        default: //родитель pid>0
            std::cout<<"PARENT:: Hello, my pid = "<< getpid()<<"; my child's pid = "<<pid<<std::endl;
            read_matrix("../input.txt", &matrixA);
            read_matrix("../test.txt", &matrixB);
            wait(&pid);
    }




//    read_matrix("../input.txt", &matrixA);
//    read_matrix("../test.txt", &matrixB);
//
//    multiplication(matrixA, matrixB, &matrixC);
//    print(matrixC);
//



    return 0;
}