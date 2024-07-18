
/*
also called as Bounded Buffer Problem

1) Producer Thread
2) Consumer Thread
The buffer is the Critical Section 
There should be "synchornization" in the process they are doing
means when the producer is producing something at particular buffer
section the consumer should be consuming in that section 
it can consume at another section which has already procduced

Problem?
->Critical Section (Buffer ) synchronization between producer and consumer thread
->The Producer should not be producing when the buffer is full
->Consumer Must not remove the data when the buffer is empty
*/

/*
Method using Semaphore

1) m,mutex -> binary semaphore used to acquire lock on buffer
2) empty -> a counting semaphore initial value is n tracks empty slots
3) Fill -> tracks filled slots initial value is 0

Producer
do{
wait(empty);wait until empty>0 then empty->value--;
wait(mutex);
//critical section  add data to buffer
signal(mutex);
signal(full);//increment full->value
}while(1);

Consumer
do{
wait(full); // wait until full>0 then fill--;
wait(mutex);
//remove data from buffer
signal(mutex);
signal(empty);//increment empty
}while(1);

}

*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <semaphore.h>
#include <semaphore>
using namespace std;

const int MAX_BUFFER_SIZE=10;
queue<int>buffer;
mutex mtx;
counting_semaphore<MAX_BUFFER_SIZE> emptySemaphore(MAX_BUFFER_SIZE);
counting_semaphore<0> fillSemaphore(0);

void producer(int id,int itemCount){
    for(int i=0;i<itemCount;i++){
        emptySemaphore.acquire();//wait for an empty slot
        {
            lock_guard<mutex>lock(mtx);
            buffer.push(i);
            cout<<"The producer "<<id<<" Produced item";
        }
        fillSemaphore.release();//signal that a new item is Produced
        }
}

void consumer(int id){
    while(true){
        fillSemaphore.acquire();
        int item;
        {
            lock_guard<mutex>lock(mtx);
            if(buffer.empty()){
                fillSemaphore.release();//release and exit
                break;
            }
            item =buffer.front();
            buffer.pop();
            cout<<"The Consumer "<<id<<" consumed item "<<item<<endl;
        }
        emptySemaphore.release()l//Signal that an empty  slot is available
    }
}int main() {
    int numProducers = 2;
    int numConsumers = 2;
    int itemsPerProducer = 20;
    vector<thread> producers, consumers;

    for (int i = 0; i < numProducers; ++i) {
        producers.emplace_back(producer, i, itemsPerProducer);
    }
    for (int i = 0; i < numConsumers; ++i) {
        consumers.emplace_back(consumer, i);
    }

    for (auto& p : producers) {
        p.join();
    }
  // After all producers are done, let consumers finish
    for (int i = 0; i < numConsumers; ++i) {
        fillSemaphore.release(); // Ensure consumers can exit if the buffer is empty
    }

    for (auto& c : consumers) {
        c.join();
    }
    return 0;
}