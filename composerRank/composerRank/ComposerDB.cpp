//
//  ComposerDB.cpp
//  composerRank
//
//  Created by Shawn An on 2018-11-03.
//  Copyright © 2018 Shawn An. All rights reserved.
//

#include "ComposerDB.hpp"
#include "Composer.hpp"
#include <algorithm>
#include <fstream>

using namespace std;


bool comparedByRank(Composer a, Composer b) {
    return a.getRank() < b.getRank();
}
bool comparedByLName(Composer a, Composer b) {
    return a.getLastName() < b.getLastName();
}
bool comparedByYOB(Composer a, Composer b) {
    return a.getYOB() < b.getYOB();
}

bool comparedByCID(Composer a, Composer b) {
    return a.getID() < b.getID();
}

Composer* ComposerDB :: addComposer(int ID,string lName, string fName, int yob, int rank) {
    Composer newComposer(ID,fName,lName,yob,rank);
    composerDB.push_back(newComposer);
    return &composerDB[composerDB.size()-1];
}

ComposerDB :: ComposerDB() {
    composerID = 1;
}
Composer* ComposerDB :: addComposer(string lName, string fName, int yob, int rank) {
    Composer newComposer(composerID,fName,lName,yob,rank);
    composerDB.push_back(newComposer);
    composerID++;
    return &composerDB[composerDB.size()-1];
}

ComposerDB:: ~ComposerDB() {
}

int ComposerDB :: getID() {
    return composerID;
}
void ComposerDB :: setID(int ID) {
    composerID = ID;
}

void ComposerDB :: sortByRank() {
    sort(composerDB.begin(),composerDB.end(),comparedByRank);
    cout << "Sorted by Rank Done.\n";
}
void ComposerDB :: sortByLastName() {
    sort(composerDB.begin(),composerDB.end(),comparedByLName);
    cout << "Sorted by LName Done.\n";
}
void ComposerDB :: sortByYOB() {
    sort(composerDB.begin(),composerDB.end(),comparedByYOB);
    cout << "Sorted by YOB Done.\n";
}

void ComposerDB :: sortByCID() {
    sort(composerDB.begin(),composerDB.end(),comparedByCID);
}

Composer* ComposerDB :: searchByID(int id) {
    for (int i = 0; i < composerDB.size(); i++) {
        if(composerDB[i].getID() == id) return &composerDB[i];
    }
    return nullptr;
}

void ComposerDB :: deleteAll() {
    while (!composerDB.empty()) {
        composerDB.pop_back();
    }
}
void ComposerDB :: deleteByID(int id) {
    for (int i = 0 ; i < composerDB.size(); i++) {
        if (composerDB[i].getID() == id) {
            composerDB[i] = composerDB[composerDB.size()-1];
            composerDB.pop_back();
            return;
        }
    }
}

void ComposerDB:: load() {
    ifstream in_stream;
    in_stream.open("session.dat");
    if(in_stream.fail()) {
        cout <<"Input file opening failed.\n";
    } else {
        int id,rank,yob,CID;
        string lName,fName;
        while (in_stream >> id >> rank >> lName >> fName >> yob) {
            addComposer(id,lName,fName,yob,rank);
        }
        CID = id;
        setID(CID);
        in_stream.close();
        cout <<"The session is loaded.\n";
    }
}

void ComposerDB :: write() {
    ofstream out_stream;
    out_stream.open("session.dat");
    if(out_stream.fail()) {
        cout <<"Output file opening failed.\n";
    } else {
        for (int i = 0; i < composerDB.size(); i++) {
            out_stream << composerDB[i].getID() << " "
            << composerDB[i].getRank() << " "
            << composerDB[i].getLastName() << " "
            << composerDB[i].getFirstName() << " "
            << composerDB[i].getYOB()<< "\n";
        }
        out_stream << getID();
        out_stream.close();
        cout <<"The current session is saved.";
    }
}

void ComposerDB :: print() {
    cout << "********************************\n";
    if (composerDB.size()==0) {
        cout <<"DataBase is empty.\n";
    }
    else {
        cout <<"DataBase Information: \n";
        for (auto c : composerDB) {
            c.print();
        }
    }
    cout << "********************************\n";
}
