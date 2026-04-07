#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>

std::queue<int> fila;
std::mutex mtx;
std::condition_variable cv;

void producer()
{
	for (int i = 0; i < 10; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
		fila.push(i);
		std::cout << "Produziu: " << i << std::endl;
	}
	cv.notify_one();
}

void consumer()
{
	for (int i = 0; i < 10; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
		
		cv.wait(lock, [], { return !fila.empty(); });
		int valor = fila.front();
		fila.pop();
		
		std::cout << "Consumiu: " << valor << " (Index: " << i << ")" << std::endl;
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	
	t1.join();
	t2.join();
	std::cout << "Threads finalizadas.\n";
	return 0;
}
