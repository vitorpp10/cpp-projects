#include<mutex>
#include<iostream>
#include<cstring>
#include<thread>
#include<condition_variable>
#include<sys/mman.h>
#include<cstdlib>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZ 1024

bool x = false;
std::mutex mtx;
std::condition_variable cv;

const char* path = "a.txt";

void p() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        int fd = open(path, O_RDWR);
        if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
        off_t size = lseek(fd, 0, SEEK_END);
        char* map = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }
        map[0] = 'g';
        msync(map, size, MS_ASYNC);
        x = true;
        close(fd);
        munmap(map, size);
    }
    cv.notify_one();
}

void c() {
    { 
        std::unique_lock<std::mutex> lock(mtx);
        int fd = open(path, O_RDONLY);
        if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
        cv.wait(lock, []{ return x; });
        off_t size = lseek(fd, 0, SEEK_END);
        char* map = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }
        std::cout << "OLHA ELE AQUI>  " << map << std::endl;
        close(fd);
        munmap(map, size); 
    }
}

int main() {
    std::thread t1(p);
    std::thread t2(c);
    if (t1.joinable()) {t1.join();}
    if (t2.joinable()) {t2.join();}
    return EXIT_SUCCESS;
}
