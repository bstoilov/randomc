#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
const int maxCars=30;
const int maxPairs=30;
const int maxPeople=30;
class Human // represents owners of cars
{
private:
    string name;
public:
    Human() // default constructor
    {
        setName("......");
    };

    string getName()
    {
        return name;
    }
    void setName(string newName)
    {
        if(newName.length()<23) //validate correct name
        {
            name=newName;
        }
        else
        {
            cout <<"Name is more than 23 symbols!";
        }
    }
};
class Car //represents the car
{
private:
    string name;
    int id;
    unsigned int reg;
    int power;
public:
    Car() //default constructor
    {
        name="unknown";
        id=0;
        reg=0;
        power=0;
    };
    Car (string newName,int newId,unsigned int newReg,int newPower)
    {
        name=newName;
        id=newId;
        reg=newReg;
        power=newPower;
    };
    string getName()
    {
        return name;
    };
    void setName(string newName)
    {
        name=newName;
    };
    int getId()
    {
        return id;
    };
    void setId(int newId)
    {
        id=newId;
    };
    unsigned int getReg()
    {
        return reg;
    };
    void setReg(unsigned int newReg)
    {
        reg=newReg;
    };
    int getPower()
    {
        return power;
    };
    void setPower(int newPower)
    {
        power=newPower;
    };
};

class Database // database with owners, cars and links between them
{
    class Pair // the link between owner and car
    {
    private:
        Human human;
        unsigned int reg;
    public:
        Pair() {};
        Pair(Human newHuman, unsigned int newReg)
        {
            human=newHuman;
            reg=newReg;
        };
        Human getHuman()
        {
            return human;
        };
        unsigned int getReg()
        {
            return reg;
        };
    };

private:
    Pair pairs[maxPairs]; //holds information about links between owner and car
    int counterPairs=0; //stores the last free index in pairs array
    int counter=0;//stores the last free index in cars array
    int counterPeople=0;//stores the last free index in people array
    Car cars[maxCars];//cars
    Human people[maxPeople];//owners

    int getOcurances(Pair links[],unsigned int searched) //Finds the number of owners the car with registration number 'searched' has.
    {
        int num=0;
        for(int i=0; i<counterPairs; i++)
        {
            if(links[i].getReg()==searched)
            {
                num++;
            }
        }
        return num;
    }

public:

    void addPeople(Human newHuman) //add new owner
    {
        if(counterPeople<maxPeople)
        {
            bool found=false;
            for(int i=0; i<counterPeople; i++)
            {
                if(people[i].getName()==newHuman.getName())
                {
                    found=true;
                    break;
                }
            }
            if(found)
            {
                cout<<"Human already exist. "<<endl;
            }
            else
            {
                people[counterPeople]=newHuman;
                counterPeople++;
            }
        }
        else
        {
            cout<<"No more space for people.";
        }


    };

    void printPeople()
    {
        for(int i=0; i<counterPeople; i++)
        {
            cout<<people[i].getName()<<endl;
        };
    }

    double averagePower() // give the average power of all cars
    {
        double avg=0;
        for(int i=0; i<counter; i++)
        {
            avg += cars[i].getPower();
        }
        return (avg/counter);

    };

    void addCar(Car newCar)
    {
        if(counter<maxCars)
        {
            bool found=false;
            for(int i=0; i<counter; i++)
            {
                if(cars[i].getReg()==newCar.getReg())
                {
                    found=true;
                    break;
                }
            };
            if(found)
            {
                cout<<"The Car already exist.";
            }
            else
            {
                cars[counter]=newCar;
                counter++;
            }
        }
        else
        {
            cout<<"No space for car.";
        };
    };

    void addPair(Human newHuman, unsigned int newReg) //add owner for the car with registration number 'newReg'
    {
        if(counterPairs<maxPairs)
        {
            bool foundCar=false;
            for(int i=0; i<counter; i++)
            {
                if(cars[i].getReg()==newReg)
                {
                    foundCar=true;
                    Pair pair(newHuman,newReg);
                    pairs[counterPairs]=pair;
                    counterPairs++;
                    addPeople(newHuman);
                    break;
                }
            }
            if(!foundCar)
            {
                cout<<"No such car.";
            }
        }
        else
        {
            cout<<"No more space for pairs.";
        };
    }

    Car mostPopularCar() //returns the most owner car
    {
        Car mostPopular;
        if(counter!=0)
        {
            mostPopular=cars[0];
            int mostFoundTimes=1;
            for(int i=0; i<counterPairs; i++)
            {
                int foundTimes=getOcurances(pairs,cars[i].getReg());
                if(mostFoundTimes<foundTimes)
                {
                    mostPopular=cars[i];
                }
            }
        }
        return mostPopular;
    };

    double getAvarageOwned(Human human) //gets the average power of the cars owned by 'human'
    {
        double sumPower=0;
        int carsOwned=0;
        for(int j=0; j<counterPairs; j++)
        {
            if(human.getName()==pairs[j].getHuman().getName())
            {
                Car car;
                for(int i=0; i<counter; i++)
                {
                    if(cars[i].getReg()==pairs[j].getReg())
                    {
                        car=cars[i];
                        break;
                    }
                }
                carsOwned++;
                sumPower += car.getPower();
            }
        }
        cout<<"Average power of all cars of this human is: "<< (sumPower/carsOwned)<<endl;
        return (sumPower/carsOwned);
    }

    void generateReport()//report for the database
    {
        Car car=mostPopularCar();
        ofstream outStream("d:/car-report.txt");
        outStream<<"The most popular car is: "<< car.getName() <<endl;
        outStream<<"The average power of all cars is: "<< averagePower()<<endl;
        for(int i=0; i<counterPeople; i++)
        {
            outStream<<"The owner: "<< people[i].getName()<<" have cars with average power: "<< getAvarageOwned(people[i])<<endl;
        }
        outStream.close();
    };

    void backUp()//saves database's info
    {
        ofstream outStream("d:/db-save.dat",ofstream::binary);
        for(int i=0; i<counterPeople; i++)
        {
            outStream<<people[i].getName()<<endl;;
        }
        outStream.close();
    };
    void readUsers()//loads the database from file
    {
        ifstream inpStream("d:/db-save.dat",ifstream::binary);
        string line="";
        Human human;
        while(getline(inpStream,line))
        {
            human.setName(line);
            addPeople(human);

        }

    }

};
int main()
{
    Database db;
    Car car1("Lambordgini Murcielago",0,1000,670);
    Car car2("Mercedes-AMG",1,2000,503);
    Car car3("Pagani Zonda R",2,3000,740);
    Car car4("Bugatti Veyron",3,4000,1020);
    db.addCar(car1);
    db.addCar(car2);
    db.addCar(car3);
    db.addCar(car4);
    Human h1;
    h1.setName("Ivan Ivanov");
    Human h2;
    h2.setName("Todor Petrov");
    Human h3;
    h3.setName("Georgi Vasilev");
    db.addPair(h1,car3.getReg());
    db.addPair(h2,car2.getReg());
    db.addPair(h3,car1.getReg());
    db.addPair(h1,car4.getReg());
    db.addPair(h1,car1.getReg());
    db.printPeople();

    db.generateReport();
    db.backUp();
    db.readUsers();
    db.printPeople();

    return 0;
}


