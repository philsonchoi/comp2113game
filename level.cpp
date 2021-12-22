#include <iostream>
#include <fstream>
#include <time.h>
#include "level.h"
#include <stdlib.h>
using namespace std;


string quitUI() // simple function to cout and collect save confirmation
{
    string ans;
    cout << "Do you want to save and quit? (Yes/No)" << endl;
    cin >> ans;
    return ans;
}

void savequit (player& playerone) // once the save is confirmed, the program will create/overwrite a file called save.txt to store player information for later use.
{
    ofstream fout;
    fout.open("save.txt");
    fout << playerone.name << endl;
    fout << playerone.charm << endl;
    fout << playerone.strength << endl;
    fout << playerone.agility << endl;
    fout << playerone.health << endl;
    fout << playerone.mana << endl;
    fout << playerone.levelonechoice << endl; // information like levelchoice will not be shown to the player as it is irrelevant to the player
    fout << playerone.stagelevel << endl;

    fout.close(); // closing the file
    exit (0);
}


void loadgame (player& playerone)
{
    ifstream fin;
    fin.open("save.txt"); // find and open save.txt

    fin >> playerone.name >> playerone.charm >> playerone.strength >> playerone.agility >> playerone.health >> playerone.mana >> playerone.levelonechoice >> playerone.stagelevel;

    // all information will be taken in

    // relevant information will be shown to the player so they can make their decision before committing.
    cout << "Name: " << playerone.name << endl;
    cout << "Charm: " << playerone.charm << " Strength: " << playerone.strength << " Agility: " << playerone.agility << endl;
    cout << "Stage: " << playerone.stagelevel << endl;
    fin.close();
}



void combatUI(player& playerone) // parse the struct object into the function as members such as health and mana need to be displayed.
{
  // a function to contain the combat UI to shorten code, so that it doesn't need to be copy and pasted.

  cout << "What will you do?" << endl;
  cout << "HP: " << playerone.health << "   MP: " << playerone.mana << endl;
  cout << "1. Attack" << endl;
  cout << "2. Ice Magic Attack (cost 2MP)" << endl;
  cout << "3. Fire Magic Attack (cost 2MP)" << endl;
  cout << "4. Guard" << endl;
}

void combatoneUI(player& playerone)
{
  // only for level one, as that the enemy does not need elemental weakness

  cout << "What will you do?" << endl;
  cout << "HP: " << playerone.health << "   MP: " << playerone.mana << endl;
  cout << "1. Attack" << endl;
  cout << "2. Guard" << endl;
}

int attack(int strength, int max, int min)
{
  // randomization of the damage multiplier, which is decided between a minimum and maximum possible damage output

  int finalNum = rand()%(max-min+1)+min;
  return strength * finalNum;
}

int guard (int strength, int max, int min)
{
  // same as attack, but the multiplier is instead used to divide to guard attacks.

  int finalNum = rand()%(max-min+1)+min;
  return strength / finalNum;
}


void combatthree(player& playerone, enemy& firedragon)
{
    // functions are ordered from level 3 to 1, as that 3 depends on 2, and 2 depends on 1.

    int combatresponse;
    combatUI(playerone);

      while (playerone.health > 0 && firedragon.health > 0) // while either enemy or player is still alive, keep the combat function running.
     {
      cin >> combatresponse;
      string attacktype;

      switch (combatresponse) // combat function is controlled by 4 cases, the player enters numbers decide their actions.
    {
      case 1:
        int damage;
        damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
        cout << "Your attack was " << damage << " points" << endl;
        firedragon.health -= damage;
        cout << "Enemy Health is currently " << firedragon.health << "/80" << endl;

        if (firedragon.health > 0)
        {
         int damage;
         damage = attack(firedragon.strength, firedragon.maxdamage, firedragon.mindamage);
        cout << "Fire Dragon attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break; // each case needs a break or else all cases will run.

      case 2:
        attacktype = "ice";

        if (firedragon.weakness == attacktype) // if the weakness is the attack type, then strength is increased to give bonus damage
        {                                      // as the name of the Fire Dragon suggests, it is weak to ice, so it receives greater damage if the player uses ice attacks.
          playerone.strength += 1;
          int damage;
          damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage); // damage output, after randomization has to be set to a variable, or else the damage displayed, and the damage occured will be random and different
          cout << "Your Ice Magic Attack was " << damage << " points" << endl;
          playerone.mana -= 2;
          firedragon.health -= damage;
          cout << "Enemy Health is currently " << firedragon.health << "/80" << endl;
          cout << "It's very effective!" << endl; // this gives a hint to the player as to if it is a good decision or not
          playerone.strength -= 1;
        }
          if (firedragon.resist == attacktype) // this will never happen, but this function is still kept as it is useful for reuse.
          {
            playerone.strength -= 1;
            int damage;
            damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage); // again, damage has to be placed in a variable to prevent multiple randomizations in this scope.
            cout << "Your Ice Magic Attack was " << damage << " points" << endl;
            playerone.mana -= 2;
            firedragon.health -= damage;
            cout << "Enemy Health is currently " << firedragon.health << "/80" << endl;
            cout << "It's not very effective..." << endl;
            playerone.strength += 1;

          }

        if (firedragon.health > 0)
        {
        int damage;
        damage = attack(firedragon.strength, firedragon.maxdamage, firedragon.mindamage);
        cout << "Fire Dragon attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }

        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;

      case 3:

        attacktype = "fire";

        if (firedragon.weakness == attacktype) // the fire dragon is fire based, so it is not weak to fire.
        {
          playerone.strength += 1;
          int damage;
          damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
          cout << "Your Fire Magic Attack was " << damage << " points" << endl;
          firedragon.health -= damage;
          cout << "Enemy Health is currently " << firedragon.health << "/80" << endl;
          cout << "It's very effective!" << endl;
          playerone.strength -= 1;
        }
          if (firedragon.resist == attacktype)
          {
            playerone.strength -= 1;
            int damage;
            damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
            cout << "Your Fire Magic Attack was " << damage << " points" << endl;
            playerone.mana -= 2;
            firedragon.health -= damage;
            cout << "Enemy Health is currently " << firedragon.health << "/80" << endl;
            cout << "It's not very effective..." << endl;
            playerone.strength += 1;
          }

        if (firedragon.health > 0)
        {
        int damage;
        damage = attack(firedragon.strength, firedragon.maxdamage, firedragon.mindamage);
        cout << "Fire Dragon attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;


      case 4:       // guarding minimizes incoming damage, in case the player believes that the incoming damage will be particularly high.
        int guarding;
        guarding = guard(firedragon.strength, firedragon.maxdamage, firedragon.mindamage);
        cout << "You guarded Fire Dragon's attack, only inflicting " << guarding << " HP." << endl;
        playerone.health -= guarding;
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;


    }

    }
}


void level3(player& playerone)
{
    struct enemy firedragon; // initialize the enemy's stats and information
    firedragon.health = 80;
    firedragon.strength = 1;
    firedragon.weakness = "ice";
    firedragon.resist = "fire";
    firedragon.mindamage = 8;
    firedragon.maxdamage = 14;
    int response;

    // story narrative here.

    cout << "Days pass as " << playerone.name << " journeys through the forrest." << endl;
    cout << playerone.name << " finds an apple tree and fully replenishes his health." << endl;

    playerone.health = 100;

    cout << "Your health is now " << playerone.health << endl;

    cout << "For every passing hour, the skies turn cloudier and cloudier, an red ominous aura fills the forest" << endl;
    cout << playerone.name << " feels a weighty vibration emenating from the ground." << endl;
    cout << "A red dragon is in a deep state of slumber,  " << playerone.name << " treads carefully to make sure he doesn't wake the beast." << endl;
    cout << "A golden gleam shines past the dragon's fiery tail, revealing the Treasure of Truth" << endl;

    cout << playerone.name << " has to defeat the Fire Dragon to reach the treasure." << endl;
    cout << "What shall you do?" << endl;
    cout << "1. Sneak and ambush the dragon!" << endl;
    cout << "2. Throw a rock to distract the dragon, and then attack." << endl;
    cout << "3. Moonwalk your way to the treasure, disregarding all reason." << endl;

    // narrative/tactical decisions to be made here, instead of a combat information
    // each decision could have different outcomes depending on their stats

    cin >> response;

    if (response == 1)
      if (playerone.agility >= 2) // skillchecks are used here to see if a player qualifies for this decision/bonuses
        {
          cout << "Ambush successful! Extra damage and your turn first." << endl;
          firedragon.health -= 10;
          cout << "Fire Dragon HP: " << firedragon.health << endl;
          playerone.strength += 1;
          combatthree(playerone, firedragon);
        }

      else
        { // if the player does not satisfy the condition, this route will not be allowed. in this case, if the strength is too high, the player will not be able to make this choice.
          cout << "Ambush unsuccessful, damage remains normal!" << endl;
          combatthree(playerone,firedragon);
        }

    if (response == 2)
      if (playerone.strength >2)
        {
          cout << "You are too strong and threw the rock too far away, the dragon is still sleeping and not distracted." << endl;
          cout << "What shall you do?" << endl;
          cout << "1. Sneak and ambush the dragon!" << endl;
          cout << "2. Throw a rock to distract the dragon, and then attack." << endl;
          cout << "3. Moonwalk your way to the treasure, disregarding all reason." << endl;
          cin >> response;
        }

      else
        {
          cout << "The dragon is distracted! Your turn first!" << endl;
          firedragon.health -= 10;
          playerone.strength += 1;

          cout << "Fire Dragon HP: " << firedragon.health << endl;
          combatthree(playerone, firedragon);
        }


    if (response == 3)
    {
      cout << "The dragon is a fan of Michael Jackson and is entranced by your moonwalk! Extra damage for our hero!" << endl;
      playerone.strength += 2;
      combatthree(playerone, firedragon);
    }


    if (firedragon.health <= 0)
    { // game ends once the fire dragon is killed
      cout << "You have defeated the Fire Dragon and have completed the game!" << endl;
      cout << "Thank you for playing" << endl;
      exit (0);
//      gamestatethree = "Deactive";
    }


    if (playerone.health <= 0)
    {
      cout << "You lose!" << endl;
      exit(0);
    }

}

void combattwo(player& playerone, enemy& icegoblin)
{
      // the functionality of combattwo is the same as combatthree.
      // combattwo and combatthree could be the same function, but some bugs occurred so I split them to be safe.
      int combatresponse;
    combatUI(playerone);

      while (playerone.health > 0 && icegoblin.health > 0)
     {
      cin >> combatresponse;
      string attacktype;

      switch (combatresponse)
    {
      case 1:
        int damage;
        damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
        cout << "Your attack was " << damage << " points" << endl;
        icegoblin.health -= damage;
        cout << "Enemy Health is currently " << icegoblin.health << "/40" << endl;

        if (icegoblin.health > 0)
        {
         int damage;
         damage = attack(icegoblin.strength, icegoblin.maxdamage, icegoblin.mindamage);
        cout << "Ice Goblin attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;

      case 2:
        attacktype = "ice";

        if (icegoblin.weakness == attacktype)
        {
          playerone.strength += 1;
          int damage;
          damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
          cout << "Your Ice Magic Attack was " << damage << " points" << endl;
          playerone.mana -= 2;
          icegoblin.health -= damage;
          cout << "Enemy Health is currently " << icegoblin.health << "/40" << endl;
          cout << "It's very effective!" << endl;
          playerone.strength -= 1;
        }
          if (icegoblin.resist == attacktype)
          {
            playerone.strength -= 1;
            int damage;
            damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
            cout << "Your Ice Magic Attack was " << damage << " points" << endl;
            playerone.mana -= 2;
            icegoblin.health -= damage;
            cout << "Enemy Health is currently " << icegoblin.health << "/40" << endl;
            cout << "It's not very effective..." << endl;
            playerone.strength += 1;

          }

        if (icegoblin.health > 0)
        {
        int damage;
        damage = attack(icegoblin.strength, icegoblin.maxdamage, icegoblin.mindamage);
        cout << "Ice Goblin attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }

        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;

      case 3:

        attacktype = "fire";

        if (icegoblin.weakness == attacktype)
        {
          playerone.strength += 1;
          int damage;
          damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
          cout << "Your Fire Magic Attack was " << damage << " points" << endl;
          icegoblin.health -= damage;
          cout << "Enemy Health is currently " << icegoblin.health << "/40" << endl;
          cout << "It's very effective!" << endl;
          playerone.strength -= 1;
        }
          if (icegoblin.resist == attacktype)
          {
            playerone.strength -= 1;
            int damage;
            damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
            cout << "Your Fire Magic Attack was " << damage << " points" << endl;
            playerone.mana -= 2;
            icegoblin.health -= damage;
            cout << "Enemy Health is currently " << icegoblin.health << "/40" << endl;
            cout << "It's not very effective..." << endl;
            playerone.strength += 1;
          }

        if (icegoblin.health > 0)
        {
        int damage;
        damage = attack(icegoblin.strength, icegoblin.maxdamage, icegoblin.mindamage);
        cout << "Ice Goblin attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
        }
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;


      case 4:
        int guarding;
        guarding = guard(icegoblin.strength, icegoblin.maxdamage, icegoblin.mindamage);
        cout << "You guarded Ice Goblin's attack, only inflicting " << guarding << " HP." << endl;
        playerone.health -= guarding;
        cout << "Your health is currently " << playerone.health << "/100." << endl;
        break;


    }

    }
}

void level2 (player& playerone)
{

  struct enemy icegoblin;
  icegoblin.health = 40;
  icegoblin.strength = 3;
  icegoblin.weakness = "fire";
  icegoblin.resist = "ice";
  icegoblin.mindamage = 3;
  icegoblin.maxdamage = 8;
  string gamestatetwo;

    // the game acknowledges the choice the player made in level 1, if he or she chose to fight the Drunk Man or avoid combat.

    if (playerone.levelonechoice == "escape")
    {
      cout << "As " << playerone.name << " cunningly evades danger, the sun begins to rise. Our hero begins to realize he spent the whole night at the Tavern." << endl;
    }
    if (playerone.levelonechoice == "fight")
    {
      cout << "Perhaps emblematic of what is more to come, " << playerone.name << " did not back away from a challenge, and for that, his strength is increased by one." << endl;
      playerone.strength +=1;
    }

    cout << "In a hungover state, the rising sun shines upon " << playerone.name;

    cout <<  ". Dusting off his jacket, he heads off to the Forest of Lies" << endl;

    cout << "Hours pass as " << playerone.name << " bravely ventures through the depths of the forest." << endl;
    cout << "Birds chirp in the distance as tree leaves crunch on each step." << endl;
    cout << "An uncomfortable aura encapsulates " << playerone.name << endl;
    cout << "An ice goblin appears!" << endl;
    cout << "Ice Goblin: You're not getting any further into this forrest. This is King Dragon's domain, and you shall pay with your life!" << endl;
    cout << "It doesn't look like you can escape, it's time to get rid of the Ice Goblin."<< endl;

    combattwo(playerone, icegoblin);


  if (icegoblin.health <= 0)
  {
    gamestatetwo = "Deactive";
    cout << "You have defeated the Ice Goblin!" << endl;
    cout << "Now entering level 3" << endl;
    playerone.stagelevel = 3;
    string ans;
    bool saveconfirm = false;

    // the save and quit feature, if the player gets to choose between continuing, or quitting and saving.
    // this is as ofstream only occurs once the execution is completed, so program cannot write to save.txt without the program finishing.
    // the information is already continually stored while the program is running, but once it stops running, it will require a save.txt file to know the player's progress

    while (saveconfirm == false)
    {
      ans = quitUI();

    if (ans == "Yes")
    {
      saveconfirm = true;
      savequit(playerone);
    }

    else if (ans == "No")
    {
      saveconfirm = true;
      level3(playerone);
    }

    else // control invalid input
    {
     cout << "Invalid response!" << endl;
    }

    }

  }


  if (playerone.health <= 0)
  {
    string tryagain;
    gamestatetwo = "Deactive";
    cout << "You lose!" << endl;
    cout << "Try again? (Yes / No)" << endl;
    cin >> tryagain;

      if (tryagain == "Yes")
      {
      playerone.health = 100;
      icegoblin.health = 40;
      gamestatetwo = "Active";
      }

      else (tryagain == "No");
      {
      cout << "Thank you for playing!";
      }
  }
}

void combatone(player& playerone, enemy& drunkman)
{

  combatoneUI(playerone);
  int combatresponse;

    while (playerone.health > 0 && drunkman.health > 0)
    {
    cin >> combatresponse;
    int damage;

    switch (combatresponse)
    {

  case 1:
    damage = attack(playerone.strength, playerone.mindamage, playerone.maxdamage);
    cout << "Your attack was " << damage << " points" << endl;
    drunkman.health -= damage;
    cout << "Enemy Health is currently " << drunkman.health << "/30" << endl;
    if (drunkman.health > 0)
    {
        damage = attack(drunkman.strength, drunkman.maxdamage, drunkman.mindamage);
        cout << "Drunk Man attacks, dealing " << damage << " points" << endl;
        playerone.health -= damage;
    }
    cout << "Your health is currently " << playerone.health << "/100." << endl;
    break;

  case 2:
    damage = guard(drunkman.strength, drunkman.maxdamage, drunkman.mindamage);
    cout << "You guarded Drunk Man's attack, only inflicting " << damage << "HP." << endl;
    playerone.health -= damage;
    cout << "Your health is currently " << playerone.health << "/100." << endl;
    break;
    }

    }

}

void level1(player& playerone)
{

  enemy drunkman;
  drunkman.health = 30;
  drunkman.strength = 1;
  drunkman.mindamage = 1;
  drunkman.maxdamage = 5;

  int combatresponse = 0;
  int response = 0;
  string gamestateone = "Active";

  string tryagain;

while (gamestateone == "Active")
{
  cout << "There is a myth, that there is the Treasure of Truth, past the Forest of Lies." << endl;
  cout << "Our hero, " << playerone.name << ", is tasked with obtaining the treasure for whatever reason." << endl;
  cout << "But first, " << playerone.name << " feels the need to prepare at a nearby tavern." << endl;
  cout << "After a couple of drinks, the hero is vitalized for his journey" << endl;
  cout << "While waiting for his turn in the small bathroom, a shifty-looking man accuses the hero of staring while using the communal urinal" << endl;
  cout << " \"What are you looking at?! \" the man drunkenly says." << playerone.name << " is feeling an unwholesome intent." << endl;
  cout << "Pick your response:" << endl;
  cout << "1. Sorry I don't know what you're talking about. [Escape]" << endl;
  cout << "2. [Kick the man] " << endl;
  cout << "3. Nice banana." << endl;
  cin >> response;

  // narrative choices here. there are skillchecks for certain decisions.

  if (response == 1)
    {
      cout << "Drunk man: \"Come back here!\" " << endl;
      cout << "You managed to escape." << endl;
      playerone.levelonechoice = "escape";
      playerone.stagelevel = 2;
      gamestateone = "Deactive";

      // the player gets to choose to save and quit at the end of every level not including the final level.

        string ans;
        bool saveconfirm = false;

        while (saveconfirm == false)
        {
          ans = quitUI();

        if (ans == "Yes")
        {
          saveconfirm = true;
          savequit(playerone);
        }

        else if (ans == "No")
        {
          saveconfirm = true;
          level2(playerone);
        }

        else
        {
         cout << "Invalid response!" << endl;
        }

        }

    }

  if (response == 2)
  {
    drunkman.health -= 5;
    cout << "Drunk man takes 5HP damage" << endl;
    cout << "It's super effective!" << endl;
    cout << "Drunk man: HP = " << drunkman.health << "/30" << endl;
    playerone.levelonechoice = "escape";
    combatone(playerone, drunkman);
    gamestateone = "Deactive";

  }

  if (response == 3)
  {
  cout << playerone.name << " looks at the man's right hand, which, indeed was holding a banana." << endl;

  if (playerone.charm > 1)
  {
      gamestateone = "Deactive";
      cout << "Drunk man:  \"Oh thanks, why didn't you say so sooner?\" " << endl;
      cout << "The fight was avoided" << endl;
      playerone.levelonechoice = "escape";
      playerone.stagelevel = 2;
      string ans;
        bool saveconfirm = false;

        while (saveconfirm == false)
        {
          ans = quitUI();

        if (ans == "Yes")
        {
          saveconfirm = true;
          savequit(playerone);
        }

        else if (ans == "No")
        {
          saveconfirm = true;
          level2(playerone);
        }

        else
        {
         cout << "Invalid response!" << endl;
        }

        }

  }
  else {
    cout << "Drunk man:  \"Don't mock me!\" " << endl;
    cout << "Charm failed! A fight begins!" << endl;
    cout << "Drunk man: HP = " << drunkman.health << "/30" << endl;

    combatone(playerone, drunkman);
    gamestateone = "Deactive";
    }

}

}

if (drunkman.health <= 0)
{
  gamestateone = "Deactive";
  cout << "You have defeated the Drunk Man!" << endl;
  cout << "Now entering level 2" << endl;
  playerone.levelonechoice = "fight";
  playerone.stagelevel = 2;
  string ans;
  bool saveconfirm = false;

    while (saveconfirm == false)
    {
      ans = quitUI();

    if (ans == "Yes")
    {
      saveconfirm = true;
      savequit(playerone);
    }

    else if (ans == "No")
    {
      saveconfirm = true;
      level2(playerone);
    }

    else
    {
     cout << "Invalid response!" << endl;
    }

    }
      level2(playerone);
    }


if (playerone.health <= 0)
{
  gamestateone = "Deactive";
  cout << "You lose!" << endl;

}

}
