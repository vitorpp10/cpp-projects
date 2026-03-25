// Ref: s2_terca - Obsidian
// Module: System I/O
// Concept: Sequential vs Random Write penalties & Struct Alignment

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <ctime>

struct data_record
{
    uint64_t id;       // 8 bytes
    double value;      // 8 bytes
    char metadata[16]; // 16 bytes
    // Total: 32 bytes
};

class stbench
{
    int fd;
    size_t num_records = 1000000;

public:
    stbench(const char* filename)
    {
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
    }

    ~stbench() {
        if (fd > 0) close(fd);
    }

    void run_sequential()
    {
        std::cout << "[Sequential Write] Starting..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_records; i++)
        {
            data_record r = {i, 100.5, "DATA"};
            write(fd, &r, sizeof(data_record));
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time: " << elapsed.count() << "s\n";
    }

    void run_random()
    {
        std::cout << "[Random Write] Starting (Simulation of bad I/O pattern)..." << std::endl;
        srand(time(nullptr)); 
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_records; i++)
        {
            off_t offset = (rand() % num_records) * sizeof(data_record);
            
            lseek(fd, offset, SEEK_SET);
            data_record r = {i, 100.5, "DATA"};
            write(fd, &r, sizeof(data_record));
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time: " << elapsed.count() << "s\n";
    }
};

int main()
{
    {
        stbench bench("append_only_logs.dat");
        bench.run_sequential();
    }

    {
        stbench bench("update_in_place.dat");
        bench.run_random();
    }

    return 0;
}
