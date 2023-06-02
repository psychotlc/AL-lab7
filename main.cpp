#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

void func1(std::vector <int> vec1, std::vector <int> vec2, int n){
    for (int i = 0; i < n; i++){
        mtx.lock();
        std::cout << "Thread 1: " << vec1[i] << " * " << vec2[i] << " = " << vec1[i] * vec2[i] << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void func2(std::vector <int> vec1, std::vector <int> vec2, int n){
    for (int i = 0; i < n; i++){
        mtx.lock();
        std::cout << "Thread 2: " << vec1[i] << " + " << vec2[i] << " = " << vec1[i] + vec2[i] << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void func3(int n){
    for (int i = 0; i < n; i++){
        mtx.lock();
        std::cout << "Thread 3: " << rand() % 10 << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main(){
    int n1 = 25;
    int n2 = 25;
    int n3 = 25;

    std::vector <int> vec1_1(n1);
    std::vector <int> vec1_2(n1);
    std::vector <int> vec2_1(n2);
    std::vector <int> vec2_2(n2);

    std::cout << "vec1_1 : ";

    for (int i = 0; i < n1; i++) {
        vec1_1[i] = rand() % 10; 
        std::cout << vec1_1[i] << " ";
    }

    std::cout << std::endl << "vec1_2 : ";

    for (int i = 0; i < n1; i++) {
        vec1_2[i] = rand() % 10; 
        std::cout << vec1_2[i] << " ";
    }

    std::cout << std::endl << "vec2_1 : ";

    for (int i = 0; i < n1; i++) {
        vec2_1[i] = rand() % 10; 
        std::cout << vec2_1[i] << " ";
    }

    std::cout << std::endl << "vec2_2 : ";

    for (int i = 0; i < n1; i++) {
        vec2_2[i] = rand() % 10; 
        std::cout << vec2_2[i] << " ";
    }

    std::cout << std::endl << std::endl;


    std::thread thread1(func1, vec1_1, vec1_2, n1);
    std::thread thread2(func2, vec2_1, vec2_2, n2);
    std::thread thread3(func3, n3);

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Threads ended the work";

    return 0;
}