#include<iostream>
#include<mutex>
#include<list>
#include<thread>

using namespace std;

mutex m;
list<int> my_list;

void add_to_list_1(int const& x){
  m.lock();
  my_list.push_front(x);
  m.unlock();
}

void size1(){
  m.lock();
  int size = my_list.size();
  m.unlock();
  cout << "Size of the list is: " << size << endl;
}

void add_to_list_2(int const& x){
  lock_guard<mutex> lg(m);
  my_list.push_front(x);
}

void size2(){
  lock_guard<mutex> lg(m);
  int size = my_list.size();
  cout << "Size of the list is: " << size << endl;
}

int main(){
  thread thread_1(add_to_list_1, 4);
  thread thread_2(add_to_list_2, 11);
  
  thread_1.join();
  thread_2.join();
}
  
