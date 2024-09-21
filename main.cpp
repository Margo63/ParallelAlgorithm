
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

// Функция для сериализации 2D вектора
std::string serialize(const std::vector<std::vector<int>>& vec) {
    std::ostringstream oss;
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            oss << elem << " "; // добавляем пробел в качестве разделителя
        }
        oss << "\n"; // новая строка для новой строки вектора
    }
    return oss.str();
}

// Функция для десериализации строки в 2D вектор
std::vector<std::vector<int>> deserialize(const std::string& str) {
    std::vector<std::vector<int>> vec;
    std::istringstream iss(str);
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::vector<int> row;
        int val;
        while (lineStream >> val) {
            row.push_back(val);
        }
        vec.push_back(row);
    }
    return vec;
}

void p1(int fdMatrixA,int fdMatrixB){
    std::vector<std::vector<int>> matrixA, matrixB;
    read_matrix("../input.txt", &matrixA);
    read_matrix("../test.txt", &matrixB);

    std::string x = serialize(matrixA);
    std::string y = serialize(matrixB);
    write(fdMatrixA,x.c_str(),x.size()+1);
    write(fdMatrixB, y.c_str(),y.size()+1);
}

void p2(int fdMatrixA,int fdMatrixB,int fdMatrixC){
    char buffer[1024];

    read(fdMatrixA,&buffer,sizeof(buffer));
    std::string matrixAData(buffer);

    char buffer2[1024];
   read(fdMatrixB,&buffer2,sizeof(buffer2));
    std::string matrixBData(buffer2);

    std::vector<std::vector<int>> matrixA = deserialize(matrixAData);
    std::vector<std::vector<int>> matrixB = deserialize(matrixBData);

    print(matrixA);
    std::cout<<"//////////\n";
    print(matrixB);
    std::vector<std::vector<int>> matrixC;
    multiplication(matrixA,matrixB,&matrixC);
    std::string c = serialize(matrixC);
    write(fdMatrixC,c.c_str(),c.size()+1);
}

void p3(int fdMatrixC){
    char buffer[1024];
    read(fdMatrixC,&buffer,sizeof(buffer));
    std::string matrixCData(buffer);
    std::vector<std::vector<int>> matrixC = deserialize(matrixCData);
    print(matrixC);
    write_to_file(matrixC);
}
int main() {
    //std::vector<std::vector<int>> matrixA, matrixB,matrixC;



/*
//
//    multiplication(matrixA, matrixB, &matrixC);
//    print(matrixC);
//
    // create a semaphore for each child: value=0
//    sem_t *sem1 = sem_open("test_semaphore", O_CREAT|O_EXCL);
//    sem_t *sem2 = sem_open("test_semaphore", O_CREAT|O_EXCL);
//
//    pid_t id = fork();
//    int fd[2];
//
//    if(id==-1){
//        std::cout<<"bad\n";
//        exit(0);
//    }
//
//    pid_t id2;
//
//    if(id==0){
//        sem_wait(sem1);
//        std::cout<<"process3\n";
////        close(fd[0]);
////        int x;
////        std::cin>>x;
////        write(fd[1],&x,sizeof(int));
////        close(fd[1]);
////        std::cout<<"write num\n";
////        exit(0);
//    }else{
//        //wait(&id);
//        id2 = fork();
//        if(id2==-1) exit(0);
//        if(id2==0){
//            sem_wait(sem2);
//            std::cout<<"process2\n";
////            close(fd[1]);
////            int y;
////            read(fd[0],&y,sizeof(int));
////            close(fd[0]);
////            std::cout<<"get num:"<<y<<"\n";
////            exit(0);
//        }else{
//            //wait(&id2);
//            //parent
//            // signal semaphore1 (increment) releasing child 1
//            sem_post(sem1);
//            // signal semaphore2 (increment) releasing child 2
//            sem_post(sem2);
//
//            // do work
//            std::cout<<"process1\n";
//
//            // wait for child1/child2
//            int status;
//            wait(&status); // a child has exited
//            // do something with status
//            wait(&status); // another child has exited
//            // do something with status
//
//            //wait(&id2);
//        }
//        //wait(&id);
//    }

//    std::cout<<"he";
*/
    int fdMatrixA[2];
    int fdMatrixB[2];
    int fdMatrixC[2];
    if(pipe(fdMatrixA) == -1){
        return -1;
    }
    if(pipe(fdMatrixB) == -1){
        return -1;
    }
    if(pipe(fdMatrixC) == -1){
        return -1;
    }
    pid_t pid1 = fork();
    if(pid1==0){
        std::cout<<"process1\n";
        //close fd1 read
        close(fdMatrixA[0]);
        close(fdMatrixB[0]);

        //write to fd1
        p1(fdMatrixA[1],fdMatrixB[1]);
        close(fdMatrixA[1]);
        close(fdMatrixB[1]);
        return 0;
    }
    pid_t pid2 = fork();
    if(pid2==0){
        std::cout<<"process2\n";
        close(fdMatrixA[1]);
        close(fdMatrixB[1]);
        close(fdMatrixC[0]);
        p2(fdMatrixA[0], fdMatrixB[0], fdMatrixC[1]);
        close(fdMatrixA[0]);
        close(fdMatrixB[0]);
        close(fdMatrixC[1]);
        return 0;
    }

    pid_t pid3 = fork();
    if(pid3==0){
        std::cout<<"process3\n";
        close(fdMatrixC[1]);
        p3(fdMatrixC[0]);
        close(fdMatrixC[0]);
        return 0;
    }

    wait(nullptr);
    wait(nullptr);
    wait(nullptr);
    return 0;
}