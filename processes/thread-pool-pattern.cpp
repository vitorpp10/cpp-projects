#include<iostream>
#include<atomic>
#include<queue>
#include<condition_variable>
#include<cstdlib>
#include<thread>
#include<sys/types.h>
#include<vector>
#include<unistd.h>
#include<chrono>
#include<ctime>

#define threads_count 3

std::mutex mtx_texto;
std::atomic<int> total_jobs{0};

class ThreadSafeQueue
{
  private:
    std::queue<int> fila; 
    std::mutex mtx;
    std::condition_variable cv_consumidor, cv_produtor;
    size_t capacidade_maxima;
  public:
    ThreadSafeQueue(size_t max_size) : capacidade_maxima(max_size) {} 

    void push(int item)
    {
      std::unique_lock<std::mutex> lock(mtx);

      cv_produtor.wait(lock, [this]() {return fila.size() < capacidade_maxima; });

      fila.push(item);
      cv_consumidor.notify_one();
    }

    int pop()
    {
      std::unique_lock<std::mutex> lock(mtx);

      cv_consumidor.wait(lock, [this]() {return !fila.empty(); });

      int valor = fila.front();
      fila.pop();
      cv_produtor.notify_one();

      return valor;
    }
};

 ThreadSafeQueue fila_segura(15);

void worker_task(int id)
{
  srand(time(0) + id);
  while (true)
  {
    int job = fila_segura.pop();

    if (job == -1)
    { 
      std::unique_lock<std::mutex> lock(mtx_texto);
      std::cout << "Worker [" << id << "] recebeu Poison Pill. Encerrando.\n";
      break;
    } else 
    {
      {
        std::unique_lock<std::mutex> lock(mtx_texto);
        std::cout << "Worker [" << id << "] processando job [" << job << "]\n";  
      } 
      int random = rand() % 200 + 10;
      std::this_thread::sleep_for(std::chrono::milliseconds(random));
      total_jobs++;
    }
  }
}

int main()
{
  std::vector<std::thread> pool;
  for (int i = 0; i < threads_count; i++)
  {
    pool.emplace_back(worker_task, i);
  }

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 15; i++)
  { 
    fila_segura.push(i); 
  }
  for (int i = 0; i < threads_count; i++) 
  { 
    fila_segura.push(-1); 
  }

  for (auto& t : pool)
  {
    if (t.joinable()) { t.join(); }
  }

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Processados " << total_jobs << " jobs em " << elapsed.count() << " segundos.\n";
  double throughput = total_jobs / elapsed.count();
  std::cout << "Throughput: " << throughput << std::endl;
  return EXIT_SUCCESS;
}
