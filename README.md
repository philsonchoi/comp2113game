# Dragon Quest TEXT

## OPEN IN RAW FORMAT

Dragon Quest is a fantasy Role Playing Game first introduced in 1986, and this fan-made version will adapt its turn based combat mechanics into a text-based adventure game.

Features:

Generation of Random Events - Each turn will have a certain percentage chance of multiplying damage output by 1.5, such odds can be increased by usage of different items used to increase the player's chance, or decrease the enemy's critical chances. Critical chances can also be affected by the initial character skill points, allocated by the player.

Data Structures for Game Status - Character data, such as name, maximum health, maximum magic points, level/EXP will be stored in arrays, vectors and variables in different files so that the information is organized and cohesive.

Dynamic Memory Allocation - Resources such as enemies and levels that are not in use will only be loaded once they are needed in order to make the program less costly on RAM.

File Input/Output - The player can save their progress at a Church (mechanically, this will be a checkpoint), and can load their most recent save data after taking a break. The game allows for multiple playthroughs, and each playthrough, the main character's name will be decided by the player.

Program Codes In Seperate Files - Save/Load game data would be stored in seperate files, and new files will be created as the player wishes.

Visually, the combat will be represented through ASCII art, for example: 

  / \
  | |
  |.|
  |.|
  |:|      __
,_|:|_,   /  )
  (O)    / _I_
   +\ \  || __|
      \ \||___|
        \ /.:.\-\
         |.:. /-----\
         |___|::oOo::|
         /   |:<_T_>:|
        |_____\ ::: /
         | |  \ \:/
         | |   | |
         \ /   | \___
         / |   \_____
                                   人　 　　　　  人　 　　　     人　 　　 　　 人
                           　 　 (　ﾟーﾟ) 　 　 (　ﾟーﾟ) 　 　 (　ﾟーﾟ) 　 　 (　ﾟーﾟ)
                           　　　  ￣￣  　　   　￣￣　　　　    ￣￣　  　　   ￣￣

1. Attack
2. Block
3. Magic
4. Items
5. Run away

Slime monsters courtesy of http://chaos.en.utf8art.com/arc/dragon_quest_7.html
Knight courtesy of https://www.asciiart.eu/people/occupations/knights

The adventure elements of the game will be lines of text, prompting the player to make a decision with branching (albeit small) story paths.

For example:

$MainCharacter has stumbled upon two entrances to the cave, choose the: 
1) darker but shorter path?
2) safer long path?

Input: 1

