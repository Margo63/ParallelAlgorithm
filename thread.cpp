
#include <iostream>
#include <thread>
#include "matrix.h"
//bool flagInitializationDone=false;
//bool flagMultiplicationDone=false;
//std::mutex m;
//std::condition_variable data_cond;

void threadInitializeMatrix(std::vector<std::vector<int>>* matrixA, std::vector<std::vector<int>>* matrixB){
    //std::lock_guard<std::mutex>lg(m);
    readMatrix("../input.txt", matrixA);
    readMatrix("../test.txt", matrixB);
//    flagInitializationDone=true;
//    data_cond.notify_one();
}
void threadMultiplitacionMatrix(std::vector<std::vector<int>>* matrixA, std::vector<std::vector<int>>* matrixB,std::vector<std::vector<int>>* matrixC){
    //std::unique_lock<std::mutex> ul(m);
    //data_cond.wait(ul,[]{return flagInitializationDone;});
    multiplication(*matrixA,*matrixB,matrixC);
    //flagMultiplicationDone=true;
    //data_cond.notify_one();
}

void threadWriteResult(std::vector<std::vector<int>>* matrixC){
    //std::unique_lock<std::mutex> ul(m);
    //data_cond.wait(ul,[]{return flagMultiplicationDone;});
    writeToFile(*matrixC,"../output_thread.txt");
}

int main(){
    auto start = std::chrono::system_clock::now();
    std::vector<std::vector<int>> matrixA, matrixB, matrixC;

    std::thread thread1(threadInitializeMatrix, &matrixA, &matrixB);
    thread1.join();
    std::thread thread2(threadMultiplitacionMatrix,&matrixA, &matrixB,&matrixC);
    thread2.join();
    std::thread thread3(threadWriteResult,&matrixC);

    //std::cout<<"Hello from main! "<<std::endl;




    thread3.join();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout<<elapsed_seconds.count();
    return 0;
}

