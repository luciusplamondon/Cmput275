#include <iostream>

using namespace std;

void even(int &n){
    if (n%2 != 0) n = n-1;
}
void print(int &n, int t){
    for (int i = 0; i < t; ++i){
        cout << n << endl;
    }
}


int &larger(int &a, int &b){
    return a > b ? a : b;
}


int main(int argc, char const *argv[])
{
    int a;
    int c = 0;
    cin >> a;
    even(a);
    print(a, c);// 
    print(a, 0);// since parameter isnt a reference
    int x = 10;
    int y = 11;
    cout << larger(x, y) << endl; // return the largerst x or y parameter here return y
    cout << --larger(x, y) << endl; // return y = y-1
    cout << --larger(x, y) << endl; // return x = x-1
    cout << --larger(x, y) << endl; // return y = y-1
    cout << x << " " << y << endl;
}


