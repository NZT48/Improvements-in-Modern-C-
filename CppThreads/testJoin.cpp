#include <thread>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;


void t1(){
    std::this_thread::sleep_for(3s);
    std::cout << 1 << std::endl;
}

void t2(std::thread t){
    t.join();
    std::cout << 2 << std::endl;
}

void t3(std::thread t){
    t.join();
    std::cout << 3 << std::endl;
}


int main() {
    std::thread thread1(t1);
    std::thread thread2(t2, std::move(thread1));
    t3(std::move(thread2));
}
