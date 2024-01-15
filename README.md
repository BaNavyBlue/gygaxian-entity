# gygaxian-entity

<img src="https://github.com/BaNavyBlue/gygaxian-entity/blob/main/gygax-screen.png" alt="TUI panel" width="1000"/>
<img src="https://github.com/BaNavyBlue/gygaxian-entity/blob/main/gygax2.png" alt="TUI panel 2" width="1000"/>
<img src="https://github.com/BaNavyBlue/gygaxian-entity/blob/main/gygaxian3.png" alt="TUI panel 2" width="1000"/>

This is a stream of conciousness project based on the original Gary Gygax Advanced Dungeons and Dragons first Edition character creation mechanics. There is a mix of c and c++ coding, sometimes just because it was the first thing that popped into my head.

Originally intended this to be an excercise at using inheritance but quickly realized the error of my ways and remembered that inheritance is seldom a good solution for anything. Increasing memory indirection and making code brittle to changes isn't as wonderful for maintainability as OOP guru's would like one to believe.

I couldn't find a compelling reason to extend the "Parent" Entity class into "child" Races nor "child" Char_Classes.  I could extend Entity into races, and extend each race with appropriate char_classes.
But this would be madness when one can just enumerate the races and classes and just allow an Entity to hold the enumeration values.

I did end up creating a racial skills parent class each child race having different skills, and buffs. The Assassin class is a grand child of the main class descending from Thief.

This project has also become a bit about designing a basic Terminal User Interface (TUI).  Currently it's only key stroke driven but it is capable of rescaling the main frame and centering the text.

# Current State of the Code
The primary character creation methods, and character save method is complete.  Basic code for loading character works but now needs to be integrated into the TUI.

TUI has a rough framework created, portions of the TUI code is fairly modular, other portions are somewhat hardcoded and should be refactored.


# Stats:
Stat rolls are first and follows the "Best 3 out of 4" approach.  Stat Rolls show which Class and Race requirements are failed. User has the Option to keep or re-roll. The stat roll also auto rerolls upon what I'm calling cursed rolls (i.e.) when the constitution is so low the only playable class is illusionist and the other stats disqualify character from being an illusionist.
# Sex:
Next user can choose 1 of 5 sex's.  (AD&D 1e only has 2).
# Race:
Race is selected next since race choice can modify stats. Only viable races based on stats will be availble. Modified Stats will also check for edge case stat/class thresholds.  Because some races are not allowed to play certain classes, these races will be pruned from the list of options if they introduce a stat condition that forces them to be a forbiden class, resulting in no class option.
# Class:
Class is limited by Race and Stats. Like race, only viable classes based on race and stats will be shown.
# Alignment:
Following the Player Handbook order alignment is the next choice. Only alignments compatible with chosen class will be available.
# Name:
Moved name until after the primary stats, sex, race, classes and Alignment is specified. User can enter a name based on whatever criteria.  If name already exists one can choose to over-write existing file or not.

Thinking of implementing an auto name generation scheme based on sex, race, classes and alignment, as an option.
# Stat Tables:
Stat Tables are generated and printed.

# Items / Inventory
Using some polymorphism from a parent Item type.
Lists of standard items are currently being specified in .json format and loaded into a class structure.
items/Arms.json is dynamically added into a vector of shared Item pointers. The character has a vector of Items, only the items ID, TYPE and cout are stored in the Character .json since the list of item parameters can get quite large. 

# Character Written.
The current code saves the generated character in the /characters folder as \<chosen name\>.json
it then opens the saved character using the simdjson library. https://github.com/simdjson/simdjson

# ROGUEUTIL
Using https://github.com/sakhmatd/rogueutil as a starting point to create an interactive TUI.
I've been hacking around and modifying some things. I disappled the CPP ifdef flags and cpp code in the rogueutil header as I was observing some things not clearing properly and garbage characters in the example code.

After a bit of searching I figured out how to get the TUI to print utf8 characters so I can use many fun characters if I choose, but I don't appear to have the ability to directly copy and paste them into a string and have them print correctly.  I have to create a utf lookup that takes the values over 127 and performs some bit shifts to covert them from the Unicode U+0000 format "\u0000" or 0x0000 to UTF-8 sequences "\x00\x00\x00". This appears to work I may go back to trying the raw hex codes.

Accidentally painted myself into a monlithic main/UI source file corner using the header file for rogueutil.h since the implementation is in the header I was unable to share the header between modules without creating re-definition errors.  Must refactor the header implementation into a .c file. 

# So What?
These are the initial steps toward creating a fully functional roleplaying game.

The original AD&E 1e mechanics are somewhat jenky and have some non-viable cases which need to be handled and auto re-rolled.
This adds to the charm and challenge of implementing the OG rule system.

Once the character creating system is completed, it will be expanded to have a basic combat system and a method to create npc entities.

The goal is to create something that is easily adaptable into a text based or graphics based role playing game.
