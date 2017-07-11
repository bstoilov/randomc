#include <iostream>

using namespace std;
class Point
{
private:
    float x,y;
public:
    Point();
    Point(float x,float y)
    {
        this->x=x;
        this->y=y;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
};
class Polygon
{


};
class Circle:public Polygon
{
private:
    Point center;
    float radius;
public:
    Circle();
    Circle(Point pos,float r)
    {
        radius=r;
        center=pos;
    }
};

class Rectangle:public Polygon
{

};
class Group
{
private:
    Polygon* members;
};


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
