#include<iostream>
#include<thread>
#include<string>
#include<mutex>
#include<condition_variable>
#include<chrono>

using namespace std;

bool have_i_reached = false;
int total_distance = 5;
int distance_covered = 0;
condition_variable cv;
mutex m;

void keep_moving(){
  while(true){
    this_thread::sleep_for(chrono::milliseconds(1000));
    ++distance_covered;
    if(distance_covered >= total_distance){
      cv.notify_one();
      break;
    }
  }
}

void ask_driver_to_wake_up_at_right_time(){
  unique_lock<mutex> ul(m);
  cv.wait(ul, []{return distance_covered == total_distance;});
  cout << "Finally I am there, distance_covered = "<< distance_covered << endl;
}

int main(){
  thread driver_thread(keep_moving);
  thread passenger_thread(ask_driver_to_wake_up_at_right_time);
  passenger_thread.join();
  driver_thread.join();
}
  
