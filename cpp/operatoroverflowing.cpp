#include <iostream>
#include <iomanip>

using namespace std;
struct Vec3D{
    int x,y,z;
};

Vec3D operator * (Vec3D v, int num){
        Vec3D ret;
        ret.x = v.x*num;
        ret.y = v.y*num;
        ret.z = v.z*num;
        return ret;
    }

Vec3D operator+(Vec3D v, Vec3D c){
        Vec3D ret;
        ret.x = v.x+c.x;
        ret.y = v.y+c.y;
        ret.z = v.z+c.z;
        return ret;
    }


int main(int argc, char const *argv[]){
    Vec3D v;
    v.x = 1;
    v.y = 2;
    v.z = 3;
    Vec3D w = v*3;
    Vec3D u = v + w;
    cout << v.x << " " << v.y << " " << v.z << endl;
    cout << w.x << " " << w.y << " " << w.z << endl;
    cout << u.x << " " << u.y << " " << u.z << endl;
}

