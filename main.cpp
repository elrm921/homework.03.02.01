#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

atomic_flag flag = ATOMIC_FLAG_INIT;

void client(atomic<int> &cnt)
{
    while (cnt < 5)
    {
        int value = cnt.load(memory_order_seq_cst) + 1;
        //flag.test_and_set(memory_order_acquire);
        cout << "Clients: " << value << endl;
        //flag.clear(memory_order_release);
        cnt.store(value,memory_order_seq_cst);
        this_thread::sleep_for(1s);
    }
}

void operatr(atomic<int> &cnt)
{
    this_thread::sleep_for(100ms);
    while (cnt > 0)
    {
        int value = cnt.load(memory_order_seq_cst) - 1;
        //flag.test_and_set(memory_order_acquire);
        cout << "Clients: " << value << endl;
        //flag.clear(memory_order_release);
        cnt.store(value,memory_order_seq_cst);
        this_thread::sleep_for(2s);
    }
}

int main()
{
    atomic<int> num = 0;
    thread T1(client, ref(num));
    thread T2(operatr, ref(num));
    T1.join();
    T2.join();

    return 0;
}