#include <iostream>
#include <thread>
#include<atomic>
#include<mutex>
#include<condition_variable>
using namespace std;
/*
Race condition:
If more than one threads are making changes on the cirtical section 
then this problem leads to inconsistency to the database so which 
leads to the race condition.

Solution of Critical Section should have 3 conditions.
1) Mutual Exclustion
2) Progress -> there should be some progress by either thread t1 or t2 
3) Bounded waiting (not a mandotory condition)
*/

// this is leading to race condition


// void task(int &count) {
//     for(int i = 0; i < 100; i++) {
//         count+=1;
//     }
// }

// int main() {
//     int count = 0;

//     thread t1(task, ref(count));
//     thread t2(task, ref(count));

//     t1.join();
//     t2.join();

//     cout << count << endl;

//     return 0;
// }

/*
To solve this critical condition we can use it atomic int which will update the value in single cpu cycle
like it will not take   temp=count+1;
                        count=temp;
*/

// Method 1 
// void task(atomic<int> &count) {
//     for(int i = 0; i < 100; i++) {
//         count++;
//     }
// }

// int main() {
//     atomic<int> count(0);

//     thread t1(task, ref(count));
//     thread t2(task, ref(count));

//     t1.join();
//     t2.join();

//     cout << count << endl;

//     return 0;
// }

/*
Method-2
Single flag 
we are using turn flag it's value is either 0 or 1
while(1){                               while(1){
    while(turn !=0);                        while(turn !=1);
    critical section                        critical section
    turn =1                                 turn =0
    RS                                      RS
}                                       }
if turn =0  t1 -> t2
if turn =1  t2 -> t1

There is fixed order of execution if the value of flag is fixed 
therefore the Progress property will not be satisfied here
*/

/*
Method -3 Peterseon's Solution
Improvement of single flag solution is Peterson's solution

turn -> indicates those turn is to enter the critical section 
flag[2] -> array of flag
indicate if a thread is ready to enter the critical section 
flag[i]=true implies that Pi is ready

T1                                              T2
while(1){                                       while(1){
flag[0]=true;                                   flag[0]=true;
turn=1                                          turn=0;
while(turn ==1 && flag[1]=True);                while(turn ==0 && flag[1]=True);
Critical Section                                Critical Section
flag[0]=False                                   flag[0]=False
}                                               }
Problem with Peterson's solution is safe only for 2 threads

*/

// Method-3
/*
using mutual exclusion principle using locks  (Mutex)
that is when one thread is executing lock the resoucrce and then relase it after completion of the 
work

Disadvantages:
1) Contension:
lets say if one thread is has locked the critical section then now
other threads are waiting for it, if the thread locked has dead then the 
remaining threads should wait for the infinite time this leads to 
contension.

2)Deadlock:
2 Processes held the resources and they both want other resources held by
the processes which leads to deadlock

3)Debugging issues:Because of unexpected 
4)Starvation
*/



void task(int &count,mutex &m) {
    for(int i = 0; i < 100; i++) {
        m.lock();
        cout<<"mutex locked\n";
        count++;
        m.unlock();
        cout<<"Lock released\n";
    }
}

int main() {
    int count=0;
    mutex m;
    thread t1(task, ref(count),ref(m));
    thread t2(task, ref(count),ref(m));
    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}
