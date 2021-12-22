#include <iostream>
#include <fstream> // for creating and reading files
#include <time.h> // for pseudo-random number generation
#include "level.h" // inclusion of external header file to declare functions
#include <stdlib.h>
using namespace std;

int main()
{
  string startscreen;
  string finalconfirm = "No";
  cout << "Welcome to Dragon Quest Text!" << endl;      // starting screen
  cout << "Enter S to create new save, or L to load pre-existing save file." << endl;

  cin >> startscreen;

  if (startscreen == "S") // create new save
  {
    while (finalconfirm == "No")
    {
    player playerone; // initialize player object
    string nameconfirm = "No";
    while (nameconfirm != "Yes" || nameconfirm == "No")
    {
        cout << "Enter your hero's name: ";
        cin >> playerone.name; // insert name information
        cout << "Your name will be " << playerone.name << ". Type Yes to confirm, No to retry." << endl; // di
        cin >> nameconfirm;
    }

    string pointsconfirm = "No";

    while (pointsconfirm != "Yes" || pointsconfirm == "No")
    {
        cout << "Please allocate your 6 skill points, each skill has a minimum of 1 and maximum of 3: " << endl;
        cout << "Charm: ";
        cin >> playerone.charm;
        cout << "Strength: ";
        cin >> playerone.strength;
        cout << "Agility: ";
        cin >> playerone.agility;

        int total = playerone.charm + playerone.strength + playerone.agility;

        // this checks if the points adhere to the points between 1-3.

        if (playerone.charm > 3 || playerone.strength > 3 || playerone.agility > 3 || playerone.charm < 1 || playerone.strength < 1 || playerone.agility < 1)
        {
            cout << "Invalid points assignment. Please make sure to allocate 6 points." << endl;

        }

        // check if the player has used more than 6 points

        if (total > 6)
        {
            cout << "Invalid points assignment. Please make sure to allocate 6 points." << endl;
        }

        // final confirmation is checked here

        else
        {
        cout << "Please confirm this is your desired allocation. Type Yes to confirm, No to retry." << endl;
        cin >> pointsconfirm;
        }

    }

    // final confirmation screen

    cout << "Name: " << playerone.name << endl;
    cout << "Charm: " << playerone.charm << " Strength: " << playerone.strength << " Agility: " << playerone.agility << endl;

    cout << "Is this acceptable? (Yes/No)" << endl;

    cin >> finalconfirm;

    if (finalconfirm == "Yes")
    {
        level1(playerone);
    }

    }


  }



if (startscreen == "L")
{
    player playerone;
    loadgame(playerone); // loadgame function is in level.cpp, declared in level.h

    string commit;

    cout << "Would you like to use this profile and continue your adventure at stage level " << playerone.stagelevel << "? (Yes/No), No will lead to starting a brand new save" << endl;

    cin >> commit; // let the player look at his/her profile before continuing

    if (commit == "Yes")
    {
        if (playerone.stagelevel == 2) // the player will start at their corresponding checkpoints
        {
            level2(playerone);
        }

        if (playerone.stagelevel == 3)
        {
            level3(playerone);
        }
    }

    else if (commit == "No")
    {
        exit (0);
    }

}


return 0;

}
