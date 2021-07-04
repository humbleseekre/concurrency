#include<queue>
#include<mutex>
#include<condition_variable>

class BoundedBlockingQueue {
private:
    int size_;
    int capacity;
    mutex m;
    condition_variable full;
    condition_variable empty;
    queue<int> q;
public:
    BoundedBlockingQueue(int capacity_) {
        capacity = capacity_;
        size_ = 0;
    }
    
    void enqueue(int element) {
        // wait for the mutex and condition variable (full) should not be set to true
        unique_lock<mutex> lk(m);
        full.wait(lk, [=]{return size_ < capacity;});
        size_++;
        q.push(element);
        lk.unlock();
        empty.notify_one();
    }
    
    int dequeue() {
        // wait for the mutex and condition variable (empty) should be set to true
        unique_lock<mutex> lk(m);
        empty.wait(lk, [=]{return size_ != 0;});
        size_--;
        auto res = q.front(); 
        q.pop();
        lk.unlock();
        full.notify_one();
        
        return res;
    }
    
    int size() {
        unique_lock<mutex> lk(m);
        return size_;
    }
};
