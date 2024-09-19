
#include <iostream>
#include <sys/wait.h>

#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

//int main(){
//    pid_t pid;
//    int ret;
//    int a=0;
//
//    pid = fork();
//
//    a+=5;
//
//    //pid_t pid1 = fork();
//
//    switch (pid){
//        // весь код после fork() дважды:
//        // в родительском процессе и в процессе потомке
//
//        case -1: //неудачная попытка создать процесс-потомок
//            exit(-1); //выход из родительского процесса
//
//        case 0: //потомок
//            std::cout<<"CHILD:: Hello, my pid = "<< getpid()<<"; my parent's pid (ppid) = "<<getppid()<<std::endl;
//            a+=10;
//            std::cout<<a<<std::endl;
//            exit(ret);
//
//        default: //родитель pid>0
//            std::cout<<"PARENT:: Hello, my pid = "<< getpid()<<"; my child's pid = "<<pid<<std::endl;
//            a+=20;
//            std::cout<<a<<std::endl;
//            wait(&pid);
//    }
//
//    return 0;
//}
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

void read_matrix(std::string name_file, std::vector<std::vector<int>>* matrix) {
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

    file.close();
}

int main() {

    std::vector<std::vector<int>> matrix;

    read_matrix("../input.txt", &matrix);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout<<matrix[i][j]<<" ";
        }
        std::cout<<"\n";
    }
//    pid_t pid_set_info = fork();
//    pid_t pid_multiplication = fork();
//    pid_t pid_print_result = fork();
//
//    switch (pid_set_info) {
//        // весь код после fork() дважды:
//        // в родительском процессе и в процессе потомке
//
//        case -1: //неудачная попытка создать процесс-потомок
//            exit(-1); //выход из родительского процесса
//
//        case 0: //потомок
//            if()
//            std::cout << "CHILD:: Hello, my pid = " << getpid() << "; my parent's pid (ppid) = " << getppid()
//                      << std::endl;
//
//            exit(0);
//
//        default: //родитель pid>0
//            std::cout << "PARENT:: Hello, my pid = " << getpid() << "; my child's pid = " << pid_set_info << std::endl;
//
//            wait(&pid_set_info);
//    }


    return 0;
}