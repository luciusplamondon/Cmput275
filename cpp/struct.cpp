#include <iostream>

using namespace std;

struct Rect {
int x, y, w, h;
Rect() : x{1}, y{1}, w{2}, h{3}{}
int area() {
return this->w* this ->h;
}
void setDim(int w, int h){ //do you see why "this" is important
    this->w = w;
    this->h = h;
}
void print(){
    cout << " x:" << x;
    cout << " y:" << y;
    cout << " w:" << w;
    cout << " h:" << h << endl;
}
};

int main(int argc, char const *argv[]){
Rect v;
cout << v.area() << endl;
v.w = 4;
cout << v.area() << endl;
v.setDim(1,1);
cout << v.area() << endl;
v.x = 3;
v.y = 4;
v.print();
}

