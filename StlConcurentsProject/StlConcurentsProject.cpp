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
        //int n;
        lock_guard<mutex> l(m);
        //m.lock();
        cout << "\t" << this_thread::get_id() << " sub thread " << i << "\n";
        //this_thread::sleep_for(1000ms);
        //m.unlock();
    }
}
void FuncForThread2(int a, int b)
{
    for (int i = a; i < b; i++)
    {
        lock_guard<mutex> l(m);
        //m.lock();
        cout << "\t" << this_thread::get_id() << " sub thread " << i << "\n";
        //this_thread::sleep_for(1s);
        //m.unlock();
    }
}

int main()
{
    
    int n = 50;
    thread th1(FuncForThread1, n);
    thread th2(FuncForThread2, 300, 350);

    for (int i = 0; i < 50; i++)
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
