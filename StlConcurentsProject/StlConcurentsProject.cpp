#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter{};
mutex m;

void CountInc()
{
    for (int i = 0; i < 10000; i++)
    {
        m.lock();
        counter++;
        m.unlock();
    }
        
}

void FuncForThread1(int a)
{
    for (int i = 0; i < a; i++)
    {
        m.lock();
        cout << "\t" << this_thread::get_id() << " sub thread " << i << "\n";
        m.unlock();
    }
}
void FuncForThread2(int a, int b)
{
    for (int i = a; i < b; i++)
    {
        m.lock();
        cout << "\t" << this_thread::get_id() << " sub thread " << i << "\n";
        m.unlock();
    }
}

int main()
{
    
    int n = 100;
    jthread th1(FuncForThread1, n);
    jthread th2(FuncForThread2, 300, 400);

    for (int i = 0; i < 100; i++)
    {
        m.lock();
        cout << this_thread::get_id() << " main thread " << i << "\n";
        m.unlock();
    }

    th1.join();
    th2.join();

    cout << "------------ main work again ------------\n";
    
    
    /*
    thread counter1(CountInc);
    thread counter2(CountInc);

    counter1.join();
    counter2.join();
    cout << counter << "\n";
    */
    return 0;
}
