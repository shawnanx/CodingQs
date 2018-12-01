//
//  composer.h
//  composerRank
//
//  Created by Shawn An on 2018-11-03.
//  Copyright © 2018 Shawn An. All rights reserved.
//

#ifndef composer_hpp
#define composer_hpp

#include <iostream>
using namespace std;

class Composer {
private:
    int ID;
    string firstName;
    string lastName;
    int YOB;
    int rank;

public:
    // constructor
    Composer(int);
    Composer(int,string,string,int,int);
    ~Composer();
    // accesssor
    string getFirstName();
    string getLastName();
    int getYOB();
    int getRank();
    int getID();
    // mutator
    void setFirstName(string);
    void setLastName(string);
    void setYOB(int);
    void setRank(int);
    void print();
};

#endif /* composer_h */
