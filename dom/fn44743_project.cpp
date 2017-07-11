#include <iostream>
#include <fstream>
using namespace std;

class StringUtil// Contains some string operations not defined in string object.
{
public:
    static string replaceAll(string, const string&, const string&);// Replaces all occurrences of specified string in the string with another string.
    static string trimLeft(string);//Removes all white spaces at the start.
    static string trimRight(string);//Removes all white spaces at the end.
    static string trim(string);//Removes all white spaces at the end and the start.
    static bool startsWith(string,string);//true if the string starts with the specified string, false otherwise
};
bool StringUtil::startsWith(string str,string what)
{
    if(str.size()<what.size())
    {
        return false;
    }
    if(str.substr(0,what.size())==what)
    {
        return true;
    }
    return false;
}
string StringUtil::replaceAll(string subject, const string& old, const string& newStr)
{
    int pos = 0;
    while ((pos = subject.find(old, pos)) != string::npos)
    {
        subject.replace(pos, old.length(), newStr);
        pos += newStr.length();
    }
    return subject;
}
string StringUtil::trimLeft(string str)
{
    int trimIndex=0;
    for(int i=0; i<str.size(); i++)
    {
        if(str[i]==' ' || str[i]=='\t')
        {
            trimIndex++;
        }
        else
        {
            break;
        }
    }
    return str.substr(trimIndex,str.size());
}
string StringUtil::trimRight(string str)
{
    int trimIndex=str.size()-1;
    for(int i=str.size()-1; i>=0; i--)
    {
        if(str[i]==' ' || str[i]=='\t')
        {
            trimIndex--;
        }
        else
        {
            break;
        }
    }
    return str.substr(0,trimIndex+1);
}
string StringUtil::trim(string str)
{
    return trimLeft((trimRight(str)));
}
class Formater// All text manipulations are here
{
public:
    void format(string);// fixes the positions of "{}" and the instruction indentation.
    void removeComments(string);// removes all comments
    void normalizeNewLines(string,string);// all new lines are converted to the specified style (Windows,Linux etc.)
    void indentWithTabs(string);//All indentation is replaced with tabs
    void indentWithSpace(string);//All indentation is replaced with spaces
};

void Formater::format(string path)
{
    fstream in;
    ofstream out;
    in.open(path.c_str(),ios::in);
    path+="formated";
    out.open(path.c_str(),ios::out);

    char current;
    while (in >> noskipws >> current )
    {
        if(current=='}')
        {
            out<<"\n}";
        }
        else if(current=='{')
        {
            out<<"\n{";
        }
        else if(current==';')
        {
            in.get(current);
            if(current!='\n')
            {
                out<<';'<<endl;
            }
        }
        else
        {
            out<<current;
        }
    }
    out.close();
    in.close();
    in.open(path.c_str(),ios::in);
    string line;
    int tabCount=0;
    while(getline(in,line))
    {
        line=StringUtil::trim(line);
        string tabStr;
        for(int i=0; i<tabCount; i++)
        {
            tabStr+="    ";
        }
        cout<<tabStr<<line<<endl;
    }
}
void Formater::removeComments(string path)
{
    fstream in;
    in.open(path.c_str(),ios::in);
    char current;
    while (in >> noskipws >> current )
    {
        if (current=='\'' || current=='"')
        {
            char q=current;
            do
            {
                cout<<current;
                in.get(current);
            }
            while (current!=q);
            cout<<current;
        }
        else if (current=='/') //Comment
        {
            in.get(current);
            if(current=='/')
            {
                do
                {
                    in.get(current);
                }
                while (current!='\n'); // until new line is reached
                cout<<endl;
            }
            else if(current=='*')
            {
                char prev;
                do
                {
                    prev=current;
                    in.get(current);
                }
                while (current!='/' || prev!='*'); // until */ is reached
            }
            else
            {
                cout<<current;
            }
        }
        else
        {
            cout<<current;
        }
    }
    in.close();
}
void Formater::normalizeNewLines(string path,string newLineFormat)
{
    fstream in;
    in.open(path.c_str(),ios::in);
    string line;
    while (getline(in,line))
    {
        cout<<line<<newLineFormat;
    }
    in.close();
}
void Formater::indentWithTabs(string path)
{
    fstream in;
    in.open(path.c_str(),ios::in);
    string line;
    while(getline(in,line))
    {
        cout<<StringUtil::replaceAll(line,"    ","\t")<<endl;
    }
    in.close();
}
void Formater::indentWithSpace(string path)
{
    fstream in;
    in.open(path.c_str(),ios::in);
    string line;
    while(getline(in,line))
    {
        cout<<StringUtil::replaceAll(line,"\t","    ")<<endl;
    }
    in.close();
}


int main(int argc, char * argv[])
{
    string files[5];
    for(int i=0; i<5; i++)// Get 5 test files
    {
        files[i]="test";
    }

    Formater formater;
    for(int i=0; i<5; i++)//Apply all operations to them.
    {
        formater.removeComments(files[i]);
        formater.indentWithSpace(files[i]);
        formater.normalizeNewLines(files[i],"\n");//or "\r\n"
        formater.format(files[i]);
    }
    return 0;
}
