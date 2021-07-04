pragma once

#include<iostream>
#include<stack>
#include<stack>
#include<thread>
#include<memory>
#include<stdexcept>

template<typename T>
class thread_safe_stack{
private:
  stack<shared_ptr<T>> stk;
  mutex m;
public:
  void push(T elem){
    lock_guard<mutex> lg(m);
    stk.push(elem);
  }
  
  void pop(){
    lock_guard<mutex> lg(m);
    if(stk.empty()){
      return;
    }
    stk.pop();
  }
  
  shared_ptr<T> top(){
    lock_guard<mutex> lg(m);
    if(isEmpty()){
      throw runtime_error("stack is empty");
    }
    return stk.top();
  }
  
  bool isEmpty(){
    lock_guard<mutex> lg(m);
    return stk.empty();
  }
  
  size_t size(){
    lock_guard<mutex> lg(m);
    return stk.size();
  }
};
  
