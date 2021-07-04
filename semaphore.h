#pragma once

#include<mutex>
#include<condition_variable>

using namespace std;

class Semaphore{
  const size_t num_permissions;
  size_t avail;
  mutex m;
  condition_variable cv;

public:
  explicit Semaphore(const size_t& num_permissions=1): num_permissions(num_permissions), avail(num_permissions){}
  
  Semaphore(const Semaphore& s): num_permissions(s.num_permissions), avail(s.avail){}
  
  void acquire(){
    unique_lock<mutex> ul(m);
    cv.wait(ul, []{return avail > 0;});
    --avail;
  }
  
  void release(){
    unique_lock<mutex> ul(m);
    cv.wait(ul, []{return avail < num_permissions;});
    ++avail;
    cv.notify_one();
  }
  
  size_t available() const{
    return avail;
  }
};
