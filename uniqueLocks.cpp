#include<iostream>
#include<mutex>
#include<thread>
#include<string>

using namespace std;

class bank_account{
private:  
  double balance;
  string name;
  mutex m;
public:
  bank_account(){}
  
  bank_account(double _balance, string _name): balance(_balance), name(_name){}
  bank_account(bank_account& const) = delete;
  bank_account& operator=(bank_account& const) = delete;
  
  void withdraw(double amount){
    lock_guard<mutex> lg(m);
    balance -= amount;
  }
  
  void deposit(double amount){
    lock_guard<mutex> lg(m);
    balance += amount;
  }
  
  void transfer(bank_account& from, bank_account& to, double amount){
    unique_lock<mutex> ul_1(from.m, defer_lock);
    unique_lock<mutex> ul_2(to.m, defer_lock);
    lock(ul_1, ul_2);
    from.balance -= amount;
    to.balance += amount;
  }
  
  void run_code(){
    bank_account account;
    bank_account account1(1000, "james");
    bank_account account2(2000, "Matthew");
    thread thread1(bank_account::transfer, &account, ref(account_1), ref(account_2), 500);
    thread thread2(bank_account::transfer, &account, ref(account_2), ref(account_1), 200);
    thread1.join();
    thread2.join();
  }
  
  void main(){
    run_code();
  }
  
  
  
  
