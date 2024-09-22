//
// Created by Маргарита  on 21.09.2024.
//

#include <iostream>
#include <thread>
#include "matrix.h"


bool flagMultiplicationDone=false;
std::mutex m;
std::condition_variable data_cond;
std::vector<std::vector<int>> matrixC;

void threadFunc(std::vector<std::pair<int,int>>positions, std::vector<std::vector<int>>matrixA,std::vector<std::vector<int>>matrixB){
    std::lock_guard<std::mutex>lg(m);
    for(int i=0;i<positions.size();i++){
        int cur=0;
        for (int k = 0; k < matrixB.size(); k++) {
            cur += matrixA[positions[i].first][k] * matrixB[k][positions[i].second];
        }
        matrixC[positions[i].first][positions[i].second] = cur;
    }

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
    int n = matrixA.size(), m = matrixB[0].size();
    for (int i = 0; i < n; i++) {
        std::vector<int> line;
        for (int j = 0; j < m; j++) {
            int cur = 0;
            line.push_back(cur);
        }
        matrixC.push_back(line);
    }

    std::thread myThreads[n*m];

    int amountOfThread = 16;
    int step = n*m/amountOfThread;
    std::vector<std::pair<int,int>> amountOfElements;
    int k=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            amountOfElements.push_back(std::pair(i,j));
            if(amountOfElements.size()==step){
                //int k=n*i+j;
                myThreads[k] = std::thread(threadFunc,amountOfElements,matrixA,matrixB);
                k++;
                amountOfElements.clear();
            }
            //std::thread th(thread,i,j,matrixA,matrixB);

        }
    }
    //std::cout<<k;
//    for(int i=0;i<n*m;i+=step){
//
//
//    }

    //std::thread th(threadPrint);
    for (int i=0; i<amountOfThread; i++){
        myThreads[i].join();
    }
    //th.join();

    //print(matrixC);
    writeToFile(matrixC,"../output_thread_p.txt");
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout<<elapsed_seconds.count();
    return 0;
}
