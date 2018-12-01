//
//  ComposerDB.hpp
//  composerRank
//
//  Created by Shawn An on 2018-11-03.
//  Copyright © 2018 Shawn An. All rights reserved.
//

#ifndef ComposerDB_hpp
#define ComposerDB_hpp

#include <stdio.h>
#include <vector>
#include "Composer.hpp"

using namespace std;

class ComposerDB {
private:
    int composerID;
    vector <Composer> composerDB;
    Composer* addComposer(int,string,string,int,int);
    
public:
    ComposerDB();
    ~ComposerDB();
    Composer* addComposer(string,string,int,int);
    int getID();
    void setID(int);
    void sortByRank();
    void sortByLastName();
    void sortByYOB();
    void sortByCID();
    Composer* searchByID(int);
    void deleteAll();
    void deleteByID(int);
    void load();
    void write();
    void print();

};

#endif /* ComposerDB_hpp */
