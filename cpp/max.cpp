#include <iostream>

using namespace std;


int max(int a, int b){
    return a > b ? a : b;
}

int main(int argc, char const *argv[])
{
    int a, b;
    cin >> a;
    cin >> b;
    cout << max(a, b) << endl;
}
