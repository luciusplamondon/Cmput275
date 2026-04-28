#include <iostream>

using namespace std;

class Rect {
int x, y, w, h;
public:
Rect() : x{1}, y{1}, w{2}, h{3}{}
Rect(int x, int y, int w, int h): x{x}, y{y}, w{w}, h{h}{}
int area() {
return this->w* this ->h;
}
void set(int x, int y, int w, int h){ //setter
    this -> x = x;
    this -> y = y;
    this -> w = w;
    this -> h = h;
}
int getx() {return x;}; //getter
void print(){
    cout << " x:" << this -> x;
    cout << " y:" << this ->y;
    cout << " w:" << this ->w;
    cout << " h:" << this ->h << endl;
}
friend ostream &operator<<(ostream &out, const Rect &r){// friend not a memeber of the class but have access to private data like r.x, r.y ect..
    cout << " x:" << r.x;
    cout << " y:" << r.y;
    cout << " w:" << r.w;
    return cout << " h:" << r.h << endl;}
};

int main(int argc, char const *argv[]){
Rect v;
cout << v.area() << endl;
Rect c{1,1,1,4};
cout << c.area() << endl;
Rect d{1,1,3,4};
cout << d.area() << endl;
v.print();
c.print();
d.print();
v.set(1,1,1,1);
cout << v.getx() << endl;
v.print();
cout << v;
}

