#define T_SIZE 4
#define BUF_SIZE 1024
#include<cstring>
#include<string>
#include<sys/wait.h>
#include<vector>
#include<iostream>
#include<thread>
#include<atomic>
#include<cstdlib>
#include<sys/syscall.h>
#include<cstdint>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/resource.h>

std::atomic<int> count{0};
int tt = 4096;

void c() {
    const char* p = "database.db";
    int o = open(p, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (o < 0) { perror("open create"); exit(EXIT_FAILURE); }
    
    const char* txt = "A";
    for (int i = 0; i < tt; i++) {
        write(o, txt, strlen(txt));
    }
    ftruncate(o, tt);
    close(o);
}

void t1(char* m) {
    std::vector<char> c;
    for (int i = 0; i < 1024; i++) {
        if (m[i] == 'A') {
            c.push_back(m[i]);
        }
    }
    int s = c.size();
    count += s;
}

void t2(char* m) {
    std::vector<char> c;
    for (int i = 1024; i < 2048; i++) {
        if (m[i] == 'A') {
            c.push_back(m[i]);
        }
    }
    int s = c.size();
    count += s;
}

void t3(char* m) {
    std::vector<char> c;
    for (int i = 2048; i < 3072; i++) {
        if (m[i] == 'A') {
            c.push_back(m[i]);
        }
    }
    int s = c.size();
    count += s;
}

void t4(char* m) {
    std::vector<char> c;
    for (int i = 3072; i < 4096; i++) {
        if (m[i] == 'A') {
            c.push_back(m[i]);
        }
    }
    int s = c.size();
    count += s;
}

void print(int who, const char* msg) {
    struct rusage usage;
    getrusage(who, &usage);
    std::cout << msg << "Tempo: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << "s | " << "RSS: " << usage.ru_maxrss << "kB \n\n"; 
}

struct dents {
    uint64_t d_ino;
    int64_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};

int main() {
    c();
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(EXIT_FAILURE); }
    if (pid == 0) {
        const char* path = ".";
        int fd = open(path, O_RDONLY | O_DIRECTORY);
        if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
        
        const char* pp = "database.db";
        int fdd = open(pp, O_RDONLY);
        if (fdd < 0) { perror("open data"); exit(EXIT_FAILURE); }

        char buffer[BUF_SIZE];
        while (true) {
            int bpos = syscall(SYS_getdents64, fd, buffer, BUF_SIZE);
            if (bpos < 0) { perror("getdents64"); exit(EXIT_FAILURE); }
            if (bpos == 0) { break; }

            for (int i = 0; i < bpos; ) {
                struct dents* d = reinterpret_cast<struct dents*>(buffer + i);
                if (std::string(d->d_name) == "database.db") {
                    char* map = (char*)mmap(NULL, tt, PROT_READ, MAP_SHARED, fdd, 0);  
                    if (map == MAP_FAILED) { perror("mmap"); exit(EXIT_FAILURE); }
                    std::thread t1_(t1, map);
                    std::thread t2_(t2, map);
                    std::thread t3_(t3, map);
                    std::thread t4_(t4, map);

                    if (t1_.joinable()) { t1_.join(); }
                    if (t2_.joinable()) { t2_.join(); }
                    if (t3_.joinable()) { t3_.join(); }
                    if (t4_.joinable()) { t4_.join(); }
                    
                    if (bpos == 0) { munmap(map, tt); }
                }
                i += d->d_reclen;
            }               
        }
        close(fd);
        close(fdd);
        std::cout << "\n\nTotal letters: " << count << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        waitpid(pid, NULL, 0);
        print(RUSAGE_SELF, "\nStatistics:\n");
    }
    return EXIT_SUCCESS;
}
