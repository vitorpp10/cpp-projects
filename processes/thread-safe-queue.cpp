#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<cstdlib>
#include<chrono>
#include<queue>

class ThreadSafeQueue
{
  private:
    std::queue<int> fila;
    std::mutex mtx;
    std::condition_variable cv_produtor, cv_consumidor;
    size_t capacidade_maxima;
    
  public:
    ThreadSafeQueue(size_t max_size) : capacidade_maxima(max_size) {}

    void push(int item) 
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv_produtor.wait(lock, [this]() { return fila.size() < capacidade_maxima; });
      fila.push(item);
      cv_consumidor.notify_one();
    }

    int pop() 
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv_consumidor.wait(lock, [this]() { return !fila.empty(); });
      
      int valor = fila.front();
      fila.pop();
      cv_produtor.notify_one();
      
      return valor;
    }
};

ThreadSafeQueue fila_segura(5); 

void produtor() 
{
  for(int i=0; i<15; ++i) 
  {
    fila_segura.push(i);
    std::cout << "Push: " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void consumidor() 
{
  for(int i=0; i<15; ++i) 
  {
    int v = fila_segura.pop();
    std::cout << "Pop: " << v << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
  }
}

int main()
{
  std::thread t1(produtor);
  std::thread t2(consumidor);

  t1.join();
  t2.join();
  
  std::cout << "\nFila Thread-Safe operando com sucesso!\n";
  return EXIT_SUCCESS;
}
