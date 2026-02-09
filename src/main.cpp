#include <iostream>
#include "List.hpp"

void print(const List<int>& l, const std::string& name) {
    std::cout << name << " (size = " << l.size() << "): ";
    List<int> tmp = l;   
    while(!tmp.empty()) {
        std::cout << tmp.front() << " ";
        tmp.pop_front();
    }
    std::cout << "\n";
}

int main() {
    std::cout << "===== 1) Default constructor =====\n";
    List<int> a;
    print(a, "a");

    std::cout << "\n===== 2) push_back / push_front =====\n";
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_front(5);
    print(a, "a");

    std::cout << "\n===== 3) initializer_list constructor =====\n";
    List<int> b = {1,2,3,4,5};
    print(b, "b");

    std::cout << "\n===== 4) copy constructor =====\n";
    List<int> c = b;
    print(c, "c (copy of b)");

    std::cout << "\n===== 5) move constructor =====\n";
    List<int> d = std::move(c);
    print(d, "d (moved from c)");
    print(c, "c after move");

    std::cout << "\n===== 6) insert tests =====\n";
    b.insert(0, 100);           
    b.insert(b.size(), 200);  
    b.insert(3, 300);          
    print(b, "b after inserts");

    std::cout << "\n===== 7) erase tests =====\n";
    b.erase(0);          
    b.erase(b.size()); 
    b.erase(2);          
    print(b, "b after erase");

    std::cout << "\n===== 8) resize tests =====\n";
    b.resize(8, 9);
    print(b, "b after resize(8,9)");

    b.resize(3);
    print(b, "b after resize(3)");

    std::cout << "\n===== 9) unique test =====\n";
    List<int> e = {1,1,2,2,3,3,3,4,4};
    print(e, "e before unique");
    e.unique();
    print(e, "e after unique");

    std::cout << "\n===== 10) sort + unique logic =====\n";
    List<int> f = {3,1,2,1,3,2,2,4};
    f.unique();
    print(f, "f after sort + unique");

    std::cout << "\n===== 11) merge test =====\n";
    List<int> g = {1,3,5,7};
    List<int> h = {2,4,6,8};

    print(g, "g before merge");
    print(h, "h before merge");

    g.merge(h);

    print(g, "g after merge");
    print(h, "h after merge (should be empty)");

    std::cout << "\n===== 12) swap test =====\n";
    List<int> x = {10,20,30};
    List<int> y = {100,200};

    print(x, "x before swap");
    print(y, "y before swap");

    x.swap(y);

    print(x, "x after swap");
    print(y, "y after swap");

    std::cout << "\n===== 13) assign tests =====\n";
    List<int> z;
    z.assign(5, 7);
    print(z, "z after assign(5,7)");

    z.assign({1,2,3});
    print(z, "z after assign({1,2,3})");

    std::cout << "\n===== ALL TESTS DONE =====\n";
}
