#include <iostream>
#include<math.h>

using namespace std;

class Vector
{
private :
    int size;//the current max size of the vector
    double* values;
public:
    Vector(int);//constructor which defines the size
    double* getValues();//returns array with the values
    double& operator[](const int);//operator for getting specific index
    int getSize();
    Vector& operator+(Vector&) const;//returns sum of the current vector and the passed vector
    void operator+=(Vector&);//adds the passed vector to the current vector
    Vector& operator-(Vector&) const;//returns the subtraction of the current vector and the passed vector
    void operator-=(Vector&);//subtract  the passed vector from the current
    Vector& operator*(double) const;//returns the current vector multiplied by the passed number
    void operator*=(double);//multiplies the vector by the passed number
    Vector& operator/(double) const;//returns the current vector divided by the passed number
    void operator/=(double);//divides the current vector by the passed number
    ~Vector();//destructor
};


Vector::Vector(int size)
{
    this->size=size;
    values=new double[size];
};

double* Vector::getValues()
{
    return values;
}


Vector& Vector::operator/(double num) const
{
    Vector product (size);
    for(int i=0; i<size; i++)
    {
        product[i]=values[i]/num;
    }
    return product;
}
void Vector::operator/=(double num)
{
    for(int i=0; i<size; i++)
    {
        values[i]=values[i]/num;
    }
}


void  Vector::operator*=(double num)
{
    for(int i=0; i<size; i++)
    {
        values[i]=values[i]*num;
    }
}

Vector& Vector::operator*(double num) const
{
    Vector product (size);
    for(int i=0; i<size; i++)
    {
        product[i]=values[i]*num;
    }
    return product;
}
void Vector::operator-=(Vector& other)
{
    int bigger=max(size,other.getSize());
    Vector result(bigger);
    for(int i=0; i<bigger; i++)
    {
        if(i>size-1)
        {
            result[i]=0-other[i];
        }
        else if(i>other.getSize())
        {
            result[i]=values[i]-0;
        }
        else
        {
            result[i]=values[i]-other[i];
        }
    }
    values=result.getValues();
}
Vector& Vector::operator-(Vector& other) const
{
    int bigger=max(size,other.getSize());
    Vector result(bigger);
    for(int i=0; i<bigger; i++)
    {
        if(i>size-1)
        {
            result[i]=0-other[i];
        }
        else if(i>other.getSize())
        {
            result[i]=values[i]-0;
        }
        else
        {
            result[i]=values[i]-other[i];
        }
    }
    return result;
}
void Vector::operator+=(Vector& other)
{
    int bigger=max(size,other.getSize());
    Vector result(bigger);
    for(int i=0; i<bigger; i++)
    {
        if(i>size-1)
        {
            result[i]=0+other[i];
        }
        else if(i>other.getSize())
        {
            result[i]=values[i]+0;
        }
        else
        {
            result[i]=values[i]+other[i];
        }
    }
    values=result.getValues();
}

Vector& Vector::operator+(Vector& other) const
{
    int bigger=max(size,other.getSize());
    Vector result(bigger);
    for(int i=0; i<bigger; i++)
    {
        if(i>size-1)
        {
            result[i]=0+other[i];
        }
        else if(i>other.getSize())
        {
            result[i]=values[i]+0;
        }
        else
        {
            result[i]=values[i]+other[i];
        }
    }
    return result;
}
int Vector::getSize()
{
    return size;
}

double& Vector::operator[](int index)
{
    if(index < 0 || index>(size-1) || size==0)
    {
        cout<<"Incorrect index"<<endl;
    }
    else
    {
        return values[index];
    }
}
Vector::~Vector()
{
    delete[] values;
}


class BoolVector
{
private:
    bool values[32];
public:
    bool& operator[](const int);
    bool set(int);//sets the value at the specified index to true
    bool clear(int);//sets the value at the specified index to false
};
bool& BoolVector::operator[](const int index)
{
    if(index>31 || index<0)
    {
        bool b=false;
        return b;
    }
    return values[index];
}
bool BoolVector::set(int index)
{
    if(index>31 || index<0)
    {
        return false;
    }
    values[index]=true;
}
bool BoolVector::clear(int index)
{
    if(index>31 || index<0)
    {
        return false;
    }
    values[index]=false;
}




int main()
{
    int size=10;
    Vector vect(size);
    Vector other(size);
    for(int i=0; i<size; i++)// set some default values
    {
        vect[i]=i;
        other[i]=2;
    }
    vect=vect+other;
    vect-=other;
    vect=vect-other;
    vect=vect/5;
    vect/=5;
    vect=vect*6;
    vect*=5;
    for(int i=0; i<size; i++)// print the vector
    {
        cout<<vect[i]<<endl;
    }
    BoolVector bVect;
    for(int i=0; i<32; i++) //set all values to true
    {
        bVect.set(i);
    }
    for(int i=0; i<32; i++) //set all values to false
    {
        bVect.clear(i);
    }
    bVect.set(32);//return false;
    bVect.clear(32);//return false;
    for(int i=0; i<32; i++) //print all values in the array
    {
        cout<<bVect[i]<<" ";
    }
    cout<<endl;
    cout<<endl;
    return 0;
}
