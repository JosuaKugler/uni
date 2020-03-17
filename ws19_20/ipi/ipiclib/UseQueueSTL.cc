#include<queue>
#include<iostream>

int main () {
  std::queue<int> q;
  for (int i=1; i<=5; i++)
    q.push(i);
    
  while (!q.empty()) {
    std::cout << q.front() << std::endl;
    q.pop();
  }
}
