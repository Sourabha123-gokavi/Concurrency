/*
to use threads 
use <pthreads> library
of POSIX threads

all threads classes and related functions are defined in the <thread> header file

thread thread_object (callable object);
A callable can be any of the five:

1) A Function Pointer

void foo(param){ Statements; }
std::thread thread_obj(foo, params);


2)A Lambda Expression

auto f = [](params){Statements;};
std::thread thread_object(f, params);


3)A Function Object
class fn_object_class {
    void operator()(params)
    { Statements;}
}
std::thread thread_object(fn_object_class(), params)



4)Non-Static Member Function
class Base {
public:
    void foo(param) { Statements; }
}
Base b;
std::thread thread_obj(&Base::foo, &b, params);


5)Static Member Function
class Base {
public:
    static void foo(param) { Statements; }
}
Base b;
std::thread thread_obj(&Base::foo, params);

Waiting for threads to finish
use thread_name.join();
this will block the main thread until the thread t1 has finished
*/

#include<iostream>
#include<thread>
using namespace std;

//function
void foo(int z){
    for(int i=0;i<z;i++){
        cout<<"Thread using function pointer as callable\n";
    }
}

// A callable object
class thread_obj{
    public:
        void operator()(int x){
            for(int i=0;i<x;i++){
                cout<<"THrread using function object as callable\n";
            }
        }
}
;
//class definition

class Base{
    public:
        //non static
        void foo(){
            cout<<"Thread using non-static member function as callable\n";
        }
        //static
        static void foo1(){
            cout<<"Thread using stati cmember function as callable\n";
        }
}
;
int main(){
    cout<<"Threads 1 and 2 and 3 Operating independently\n";

    thread t1(foo,3);
    thread t2(thread_obj(),3);
    auto f=[](int x){
        for(int i=0;i<x;i++){
            cout<<"Thread using lambda expression as callable\n";
        }
    };

    thread t3(f,3);
    Base b;
    thread t4(&Base::foo,&b);
    thread t5(&Base::foo1);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();


    return 0;
}