//
//  Composer.cpp
//  composerRank
//
//  Created by Shawn An on 2018-11-03.
//  Copyright © 2018 Shawn An. All rights reserved.
//

#include <iostream>
#include "Composer.hpp"
using namespace std;

Composer:: Composer(int ID){
    this->ID = ID;
    firstName = "Unknown";
    lastName = "Unknown";
    YOB = 9999;
    rank = -1;
}
Composer:: Composer(int ID,string firstName, string lastName, int YOB, int rank){
    this->ID = ID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->YOB = YOB;
    this->rank = rank;
}
Composer:: ~Composer() {
}

string Composer:: getFirstName() {
    return firstName;
}
string Composer:: getLastName() {
    return lastName;
}
int Composer:: getYOB() {
    return YOB;
}
int Composer:: getRank() {
    return rank;
}
int Composer:: getID() {
    return ID;
}

void Composer:: setFirstName(string firstName) {
    this->firstName = firstName;
}
void Composer:: setLastName(string lastName) {
    this->lastName = lastName;
}
void Composer:: setYOB(int YOB) {
    this->YOB = YOB;
}
void Composer:: setRank(int rank) {
    this->rank = rank;
}
void Composer:: print() {
    cout <<"C_ID: " << getID() << "             Rank: "<< getRank()<<
    "\nName: " << getLastName() << ", " << getFirstName() <<
    "\nBorn: " <<  getYOB() << endl;
}
