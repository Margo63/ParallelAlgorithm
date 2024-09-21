//
// Created by Маргарита  on 21.09.2024.
//

#include <iostream>
#include <thread>
#include "matrix.h"

int n=4;
bool flagMultiplicationDone=false;
std::mutex m;
std::condition_variable data_cond;
std::vector<std::vector<int>> matrixC;
void threadFunc(int positionX, int positionY, std::vector<std::vector<int>>matrixA,std::vector<std::vector<int>>matrixB){
    std::lock_guard<std::mutex>lg(m);
    int cur=0;
    for (int k = 0; k < matrixB.size(); k++) {
        cur += matrixA[positionX][k] * matrixB[k][positionY];
    }
    matrixC[positionX][positionY] = cur;
//    std::cout<<4*positionX+positionY<<" ";
//    if(4*positionX+positionY==n*n-1){
//        flagMultiplicationDone=true;
//        data_cond.notify_one();
//    }
}


//void threadPrint(){
//    std::unique_lock<std::mutex> ul(m);
//    data_cond.wait(ul,[]{return flagMultiplicationDone;});
//    print(matrixC);
//}
int main(){
    auto start = std::chrono::system_clock::now();

    std::vector<std::vector<int>> matrixA, matrixB;
    readMatrix("../input.txt",&matrixA);
    readMatrix("../test.txt",&matrixB);
    for (int i = 0; i < matrixA.size(); i++) {
        std::vector<int> line;
        for (int j = 0; j < matrixB[0].size(); j++) {
            int cur = 0;
            line.push_back(cur);
        }
        matrixC.push_back(line);
    }

    std::thread myThreads[16];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            //std::thread th(thread,i,j,matrixA,matrixB);
            int k=4*i+j;
            myThreads[k] = std::thread(threadFunc,i,j,matrixA,matrixB);
        }
    }
    //std::thread th(threadPrint);
    for (int i=0; i<16; i++){
        myThreads[i].join();
    }
    //th.join();

    print(matrixC);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout<<elapsed_seconds.count();
    return 0;
}
