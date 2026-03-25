// Ref: s2_quinta - Obsidian
// Module: System I/O
// Concept: Page Cache (Write-Back) vs Durable Writes (fsync)

#include <iostream>
#include <chrono>
#include <cstring>
#include <unistd.h>   // write, fsync, close
#include <fcntl.h>    // open, O_WRONLY

class PersistenceBenchmark {
    int fd;

public:
    PersistenceBenchmark(const char* filename) {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    ~PersistenceBenchmark() {
        if (fd > 0) close(fd);
    }

    void RunWriteBenchmark(bool use_fsync)
    {
        const int iterations = 5000; // Reduzi para teste rápido, aumente para 100k
        const int record_size = 100;
        char buffer[record_size];
        memset(buffer, 'A', record_size);

        std::cout << "Running with fsync: " << (use_fsync ? "ON (Durable)" : "OFF (Page Cache)") << "...\n";

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; ++i)
        {
            write(fd, buffer, record_size); // Escreve na RAM (normalmente)

            if (use_fsync)
            {
                fsync(fd); // Força descida para o Disco
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double total_bytes = iterations * record_size;
        double throughput_MBps = (total_bytes / (1024.0 * 1024.0)) / elapsed.count();

        std::cout << "  -> Throughput: " << throughput_MBps << " MB/s\n" << std::endl;
    }
};

int main() {
    {
        PersistenceBenchmark bench("test_cache.dat");
        bench.RunWriteBenchmark(false);
    }

    {
        PersistenceBenchmark bench("test_persistence.dat");
        bench.RunWriteBenchmark(true);
    }
    
    return 0;
}
