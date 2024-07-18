#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
/*
main advantage of this is that 
it will wait until another thread notify it, if the thread dies inbetween then it will be detected
here.
*/
using namespace std;

int count = 0;
mutex m;
condition_variable cv;
bool ready = false;

void task2() {
    unique_lock<mutex> lock(m);
    cout << "This is from thread 2 count = " << count << endl;
    for (int i = 0; i < 5; i++) {
        count++;
    }
    ready = true;
    cv.notify_one();  // use notify_all() for multiple waiting threads
    cout<<"This is after notification\n";
}

void task1() {
    unique_lock<mutex> lock(m);
    cout<<"Waiting for the completion of the task2\n";
    cv.wait(lock, [] { return ready; });
    cout << "This is from thread 1 count = " << count << endl;
    for (int i = 0; i < 5; i++) {
        count++;
    }
    cout<<"This is completion of task1";
}

int main() {
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();

    cout << "Final count = " << count << endl;

    return 0;
}
