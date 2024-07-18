// threads 

/*
to run this file
g++ 1_threads.cpp
./a.exe
*/


#include<iostream>
#include<thread>
#include<unistd.h>

using namespace std;

void taskA(){
    for(int i=0;i<10;i++){
        sleep(1);
        printf("TaskA: %d\n",i);
        fflush(stdout);
    }
}

void taskB(){
    for(int i=0;i<10;i++){
        sleep(1);
        printf("TaskB: %d\n",i);
        fflush(stdout);
    }
}

int main(){
    thread t1(taskA);
    thread t2(taskB);
    //if we simply run these things it will not run completely
    /*
    To make it run use thread_name.join() so that the main function will wait
    until the threads execution will completes its execution
    */
    t1.join();
    t2.join();
    return 0;
    
}