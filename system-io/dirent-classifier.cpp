#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<cstdlib>
#include<cstdint>
#include<dirent.h>

#define BUF_SIZE 1024

struct linux_dirent64 {
    uint64_t d_ino;
    int64_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};

int main() {
    const char* dir_path = ".";
    char buffer[BUF_SIZE];

    int fd = open(dir_path, O_RDONLY | O_DIRECTORY);
    if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }

    while (true) {
        //syntax do getdents64
        int bpos = syscall(SYS_getdents64, fd, buffer, BUF_SIZE);
        if (bpos < 0) { perror("getdents64"); exit(EXIT_FAILURE); }
        if (bpos == 0) { break; }

        for (int i = 0; i < bpos;) {
            /* para fazer o c++ criar uma variável que vai ler os dados armazenados no buffer pelo 
            getdents64 e separar eles como está separado 
            no linux_dirent64, pulando de arquivo em arquivo(buffer+i) 
            */
            struct linux_dirent64* d = reinterpret_cast<struct linux_dirent64*>(buffer + i);
            switch (d->d_type) {
                case DT_REG: 
                std::cout << "[" << "FILE" << "] " << d->d_name << " (Inode: " << d->d_ino << ")" << '\n';
                break;
                case DT_DIR:
                std::cout << "[" << "DIR" << "] " << d->d_name << " (Inode: " << d->d_ino << ")" << '\n';
                break;
                case DT_LNK: 
                std::cout << "[" << "LINK" << "] " << d->d_name << " (Inode: " << d->d_ino << ")" << '\n';
                break;
                default: 
                std::cout << "[" << "NONE" << "] " << d->d_name << " (Inode: " << d->d_ino << ")" << '\n';
            }
            i += d->d_reclen;
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}
