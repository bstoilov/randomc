#include <iostream>

using namespace std;

class Employee //regular employee
{
private:
    string name;
    string address;
    string egn;
    string department;
    double salary;
public:
    Employee()//default constructor
    {
        this->name="default";
        this->address="default";
        this->egn="default";
        this->department="default";
        this->salary=0;
    }
    Employee(string name,string address,string egn,string department,double salary)
    {
        this->name=name;
        this->address=address;
        this->egn=egn;
        this->department=department;
        this->salary=salary;
    };

};
class Specialist:public Employee //An employee with speciality
{
private:
    string description;
public:
    Specialist() {};
    Specialist(string name,string address,string egn,string department,double salary,string description):Employee(name,address,egn,department,salary)
    {
        this->description=description;
    };
    string getDescription()
    {
        return description;
    }
};
class Lead : public Specialist//specialist with team of employees
{
private:
    string departmentInfo;
    Employee* employees;
public:
    Lead() {};
    Lead(string name,string address,string egn,string department,double salary,string description,string departmentInfo,Employee* employees):Specialist(name,address,egn,department,salary,description)
    {
        this->departmentInfo=departmentInfo;
        this->employees=employees;
    };

};

class Secretary//secretary
{
private:
    string* languges;
public:
    Secretary() {};
    Secretary(string* languges)
    {
        this->languges=languges;
    };
};
class Director//director
{
private:
    Secretary secretary;
    Employee* allEmployees;
public:
    Director(Secretary ns,Employee* allEmployees)
    {
        secretary=ns;
        this->allEmployees=allEmployees;
    };
};


class Pair//pair used for specifying required number of property
{
private:
    string property;
    int num;
public:
    Pair()
    {
        property="";
        num=0;
    };
    Pair(string prop,int num)
    {
        property=prop;
        this->num=num;
    };
    string getProperty()
    {
        return property;
    }
    int getNum()
    {
        return num;
    }
};

class CompanyRequierements//contains the requirements
{
private:
    Pair* specsNeeded;
    string* departments;
    int numRegulars;
public:
    CompanyRequierements() {};
    CompanyRequierements(string* deps,Pair* empSpec,int num)
    {
        departments=deps;
        specsNeeded=empSpec;
        numRegulars=num;
    };
    Pair* getSpecsNeeded()
    {
        return specsNeeded;
    }
    string* getDepartments()
    {
        return departments;
    }
    int getNumRegulars()
    {
        return numRegulars;
    }
};
class CompanyBuilder//creates a company from a specified list of employees and requirements
{

public:
    bool checkConfiguration(Specialist* specialists,Employee* regulars,Lead* leads,Director* directorList,CompanyRequierements reqs)
    {
        //Check for the specialists descriptions
        Pair* specPtr=reqs.getSpecsNeeded();
        for(int i=0; i<sizeof(specPtr)/sizeof(specPtr[0]); i++) // for each defined description
        {
            int specCount=0;
            for(int j=0; i<sizeof(specialists)/sizeof(specialists[0]); j++)// Count the specialist for the current description
            {
                if(specialists[j].getDescription()==specPtr[i].getProperty())
                {
                    specCount++;// found one
                }
            }
            if(specCount<specPtr[i].getNum())
            {
                cout<<"Not enough specialists for "<<specPtr[i].getProperty()<<endl;
                return false;
            }
        }
        string* deps=reqs.getDepartments();
        for(int i=0; i<sizeof(deps)/sizeof(deps[0]);i++)
        {
            bool found=false;
            for(int j=0; j<sizeof(leads)/sizeof(leads[0]);j++)
            {
                if(leads[j].getDescription()==deps[i])
                {
                    found=true;
                    break;
                }
            }
            if(!found)
            {
                cout<<"There is a missing department!"<<endl;
                return false;
            }
        }
    }
};

int main()
{
    return 0;
}
