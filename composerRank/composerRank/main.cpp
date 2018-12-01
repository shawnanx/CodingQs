//
//  main.cpp
//  composerRank
//
//  Created by Shawn An on 2018-11-03.
//  Copyright © 2018 Shawn An. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Composer.hpp"
#include "ComposerDB.hpp"

void showINSList() {
    cout << "+--------------------------------+\n";
    cout << "|1) Add a new composer           |\n";
    cout << "|2) Retrieve a composer's data   |\n";
    cout << "|3) Modify a composer's info     |\n";
    cout << "|4) List all composers           |\n";
    cout << "|5) List by rank/l_name/b_year   |\n";
    cout << "|6) Load previous session        |\n";
    cout << "|7) Save current session         |\n";
    cout << "|8) Delete a composer            |\n";
    cout << "|9) Reset the database           |\n";
    cout << "|0) Exit the databse             |\n";
    cout << "+--------------------------------+\n";
    cout << "Please choose your task: ";
}

int main(int argc, const char * argv[]) {
    ComposerDB myDB;
    myDB.addComposer("An", "Shawn", 1990, 2);
    myDB.addComposer("Wen", "Emma", 1987, 1);
    myDB.addComposer("A", "B", 2005, 3);
    myDB.addComposer("C", "D", 1960, 4);
    string instruction;
    cout << "Welcome to Composer Database,\n";
    showINSList();
    cin >> instruction;
    while (instruction!="0") {
        if (instruction == "1") {
            string l ;
            string f ;
            int y = 0;
            int r = 0;
            cout << "Enter composer's lastname: ";
            cin >> l;
            cout << "Enter composer's firstname: ";
            cin >> f;
            cout << "Enter the year of birth: ";
            cin >> y;
            cout << "Enter the rank: ";
            cin >> r;
            cout << "Fields has been set\n";
            myDB.addComposer(l, f, y, r);
        }
        else if (instruction == "2") {
            cout << "Enter the C_ID: ";
            int id;
            cin >> id;
            Composer* curr = myDB.searchByID(id);
            if (!curr) cout << "ID does not exist.\n";
            else curr->print();
        }
        else if (instruction == "3") {
            cout << "Enter the C_ID: ";
            int id;
            cin >> id;
            Composer* curr = myDB.searchByID(id);
            if (!curr) cout << "ID does not exist.\n";
            else {
                string flag;
                string tempStr;
                int tempInt;
                cout << "Modify LastName? [1 Yes/0 No] ";
                cin >> flag;
                if (flag == "1") {
                    cout << "LastName: ";
                    cin >> tempStr;
                    curr->setLastName(tempStr);
                }
                cout << "Modify FirstName? [1 Yes/0 No] ";
                cin >> flag;
                if (flag == "1") {
                    cout << "FirstName: ";
                    cin >> tempStr;
                    curr->setFirstName(tempStr);
                }
                cout << "Modify Birth Year? [1 Yes/0 No] ";
                cin >> flag;
                if (flag == "1") {
                    cout << "Birth Year: ";
                    cin >> tempInt;
                    curr->setYOB(tempInt);
                }
                cout << "Modify Rank? [1 Yes/0 No] ";
                cin >> flag;
                if (flag == "1") {
                    cout << "Rank: ";
                    cin >> tempInt;
                    curr->setRank(tempInt);
                }
                cout << "Edit Done.\n";
            }
        }
        else if (instruction == "4") {
            myDB.sortByCID();
            myDB.print();
        }
        else if (instruction == "5") {
            string flag;
            cout << "Sort by Rank_1/LastName_2/Year_3: ";
            cin >> flag;
            if (flag == "1") {
                myDB.sortByRank();
                myDB.print();
            } else if (flag == "2") {
                myDB.sortByLastName();
                myDB.print();
            } else if (flag == "3") {
                myDB.sortByYOB();
                myDB.print();
            } else cout <<" Wrong Command, Retry\n";
        }
        else if (instruction == "6") {
            string flag;
            if (myDB.getID()!=1) {
                cout << "Abort existing session[1 Yes/0 No]: ";
                cin >> flag;
                if (flag == "1") {
                    myDB.deleteAll();
                    myDB.load();
                } else {
                    cout << "Loading cancelled.\n";
                }
            }
        }
        else if (instruction == "7") {
            myDB.write();
        }
        else if (instruction == "8") {
            int id;
            int flag;
            cout << "Enter ID to delete: ";
            cin >> id;
            cout << "Proceed Deletion for ID_" << id << "? [1 Yes/0 No] ";
            cin >> flag;
            if (flag == 1) myDB.deleteByID(id);
            else cout << "Deletion cancelled.\n";
        }
        else if (instruction == "9") {
            int flag;
            cout << "WARNING! PLEASE CONFIRM TO RESET DB! [1 Yes/0 No] ";
            cin >> flag;
            if (flag == 1) {
                myDB.deleteAll();
                cout << "DB reset done.\n";
            }
            else cout << "Reset cancelled.\n";
        }
        else if (instruction == "help") {
            showINSList();
        }
        else {
            break;
        }
        cout << ".. Next[help] :";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        cin.get();
//        showINSList();
        cin >> instruction;
    }
    cout << "You exit the database.\n";
    return 0;
}
