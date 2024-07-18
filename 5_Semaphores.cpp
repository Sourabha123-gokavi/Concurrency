#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include<semaphore>
#include<vector>

using namespace std;
/*
Semaphore is just an integer
we decrement when the thread uses resource 
we increment when the thread releases the resource
when there are multiple instance of same resource
we can run multiple threads simultaneously
more instances means more threads can run simultaneously

wait(s){                                Signal(S){
s->value --;                                s->value++
if(s->value <0){                            if(s->value<=0){    
add to s->blockList                         Remove P from s->BlockList        
Block();                                    WakeUp(P)   
    }                                       }
}                                       }

*/

class Semaphore{
    private:
        mutex mtx;
        condition_variable cv;
        int count;

    public:
        Semaphore(int count=3):count(count){}

    void acquire(){
        unique_lock<mutex>lock(mtx);
        cv.wait(lock,[this]{return count>0;});
        --count;
    }
    void release(){
        unique_lock<mutex>lock(mtx);
        ++count;
        cv.notify_one();
    }
    
};

void task(int id,Semaphore& sem){
    cout<<"Task "<<id<<" is waiting to acquire the semaphore ...\n";
    sem.acquire();
    cout<<"Task "<<id<<" has acquired the semaphore \n";
    // wait for some work
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"Task "<<id<<" is releasing the semaphore.\n";
    sem.release(); 
}

int main(){
    Semaphore sem(3);
    vector<thread>threads;
    for(int i=0;i<10;i++){
        threads.emplace_back(task,i,ref(sem));
    }
    for(auto &t:threads){
        t.join();
    }
    return 0;
}

