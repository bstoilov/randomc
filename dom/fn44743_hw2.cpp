#include <iostream>
#include <fstream>
using namespace std;

//Class holding array of cookies
class Jar
{
private:
    int size;
    int index;
    string *cookies;
    void resizeJar(int);
    void unalocateArray();
public:
    Jar();
    void addCookie(string);
    void printCookies();
    void removeCookie();
    void saveToFile(string);
    void loadFromFile(string);
    ~Jar();
};

//Saves the content of cookies to file named 'path'.
void Jar::saveToFile(string path)
{
    ofstream out(path.c_str(),ios::out);
    for(int i=0; i<index; i++)
    {
        out<<cookies[i]<<endl;
    }
    out.close();
}
//Load cookies from file named 'path' and saves them in cookies.
void Jar::loadFromFile(string path)
{
    ifstream in(path.c_str(),ios::in);
    string line;
    while(getline(in,line))
    {
        addCookie(line);
    }
    in.close();
}


//Default constructor
Jar::Jar()
{
    size=2;
    index=0;
    cookies = new string[size];
    for(int i = 0; i < size; ++i)
    {
        cookies[i] = "";
    }
}
//Destructor
Jar::~Jar()
{
    unalocateArray();
}
void Jar::unalocateArray()
{
    delete [] cookies;
}

//Used to keep the array size optimal.
void Jar::resizeJar(int newSize)
{
    string* newCookies=new string[newSize];
    for(int i = 0; i < newSize; ++i)
    {
        newCookies[i] = "";
    }

    for(int i=0; i<index; i++)
    {
        newCookies[i]=cookies[i];
    }
    unalocateArray();
    cookies=newCookies;
    size=newSize;
}
//Adds a cookie named 'cookieName' to the from of cookies.
void Jar::addCookie(string cookieName)
{
    if(index>(size-1))
    {
        resizeJar(size*2);
    }
    cookies[index]=cookieName;
    index++;
}
//Removes cookie from the front of the array.
void Jar::removeCookie()
{
    if(index<size/2)
    {
        resizeJar(size/2);
    }
    else if(index>0)
    {
        cookies[index]="";
        index--;
    }
    else
    {
        cout<<"No more cookies"<<endl;
    }
}
//Prints all cookie names to the standard output stream.
void Jar::printCookies()
{
    if(index==0)
    {
        cout<<"Jar is empty"<<endl;
    }
    else
    {
        for(int i=0; i<index; i++)
        {
            cout<<cookies[i]<<" - ";
        }
    }
}


int main()
{
    Jar jar;
    string saveFile="save.txt";
    string saveFile2="custom.txt";
    for(int i=0; i<10; i++) //add 10 cookies named "Cookie"
    {
        jar.addCookie("Cookie");
    }
    for(int i=0; i<11; i++) //Remove the last 11 added cookies. Will display error on 11-th cookie.
    {
        jar.removeCookie();
    }
    jar.saveToFile(saveFile);// Save the current cookies in save.txt
    jar.loadFromFile(saveFile2);// Load cookies from custom.txt
    jar.printCookies();
    return 0;
}
