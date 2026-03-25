// Ref: s2_quarta - Obsidian
// Module: System I/O
// Concept: Block Size impact on Read Throughput (IOPS vs Bandwidth)

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

class DiskReader
{
private:
    std::string filename;
    size_t totalBytes;
    std::vector<size_t> blocksizes;

public:
    DiskReader(std::string filename, size_t totalBytes, std::vector<size_t> blocksizes)
    {
        this->filename = filename;
        this->totalBytes = totalBytes;
        this->blocksizes = blocksizes;
        srand(time(0));
    }

    void runBenchmark()
    {
        std::vector<std::string> modes = {"seq", "rand"};

        for (const std::string& mode : modes)
        {
            std::cout << "\n--- Mode: " << mode << " ---\n";

            for (size_t blocksize : blocksizes)
            {
                size_t numreads = totalBytes / blocksize;
                std::vector<char> buffer(blocksize);

                std::ifstream file(filename, std::ios::binary);
                if (!file.is_open())
                {
                    std::cerr << "Error: Generate 'bigfile.dat' first!\n";
                    return;
                }

                auto start = std::chrono::high_resolution_clock::now();

                for (size_t i = 0; i < numreads; i++)
                {
                    size_t pos;
                    if (mode == "seq")
                        pos = i * blocksize;
                    else
                        pos = (rand() % (totalBytes / blocksize)) * blocksize;

                    file.seekg(pos, std::ios::beg);
                    file.read(buffer.data(), blocksize);
                }

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;

                double totalMB = static_cast<double>(totalBytes) / 1024 / 1024;
                double throughput = totalMB / elapsed.count();

                std::cout << "BlockSize: " << blocksize << " bytes | "
                          << "Time: " << elapsed.count() << "s | "
                          << "Speed: " << throughput << " MB/s\n";

                file.close();
            }
        }
    }
};

int main()
{
    DiskReader reader("bigfile.dat", 100 * 1024 * 1024, {4096, 1024 * 1024}); // Testando com 100MB para ser rápido
    reader.runBenchmark();
    return 0;
}
