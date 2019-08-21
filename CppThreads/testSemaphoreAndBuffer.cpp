#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
#include <ctype.h>

#define RING_BUFFER_SIZE 8

class Semaphore {
        int m_s = 0;
        std::mutex m_mut;
        std::condition_variable m_cv;
    public:
        Semaphore() = default;
        Semaphore(int x) : m_s(x) {}

        void signal() {
            std::unique_lock<std::mutex> lock(m_mut);
            m_s += 1;
            m_cv.notify_one();
        }

        void wait() {
            std::unique_lock<std::mutex> lock(m_mut);
            m_cv.wait(lock, [this]() {return m_s != 0; });
            m_s -= 1;
        }
};

class RingBuffer {
        std::array<char, RING_BUFFER_SIZE> m_buff;
        int m_w{0};
        int m_r{0};
        Semaphore m_free{RING_BUFFER_SIZE};
        Semaphore m_taken{0};
        std::mutex m_mut;
    public:
        RingBuffer() = default;

        void write(char x);
        char read();
};

void RingBuffer::write(char x) {
    m_free.wait();
    std::lock_guard<std::mutex> l(m_mut);
    m_buff[m_w] = x;
    m_w = (m_w + 1) % 8;
    m_taken.signal();
}

char RingBuffer::read() {
    m_taken.wait();
    std::lock_guard<std::mutex> l(m_mut);
    char res = m_buff[m_r];
    m_r = (m_r + 1) % 8;
    m_free.signal();
    return res;
}

void producer(RingBuffer* buff) {
    int i = 0;
    std::string a = "NasumicnoOdabranNizKaraktera";
    char c;
    while(true) {
        c = a[i];
        i = (i + 1) % 28;
        buff->write(c);
    }
}

void processor(RingBuffer* buff1, RingBuffer* buff2) {
    char c;
    while(true){
        c = buff1->read();
        c = toupper(c);
        buff2->write(c);
    }
}

void consumer(RingBuffer* buff) {
    char c;
    while(true) {
        c = buff->read();
        std::cout << c << std::endl;;
    }
}




int main() {
    RingBuffer b1;
    RingBuffer b2;

    std::thread thread1(producer, &b1);
    std::thread thread2(processor, &b1, &b2);
    std::thread thread3(consumer, &b2);

    thread1.join();
    thread2.join();
    thread3.join();

}
