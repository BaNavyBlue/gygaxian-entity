# gygaxian-entity
This is a stream of conciousness project based on the original Gary Gygax Advanced Dungeons and Dragons first Edition character creation mechanics. There is a mix of c and c++ coding, sometimes just because it was the first thing that popped into my head.

Originally intended this to be an excercise at using inheritance but quickly realized the error of my ways and remembered that inheritance is seldom a good solution for anything. Increasing memory indirection and making code brittle to changes isn't as wonderful for maintainability as OOP guru's would like one to believe.

I couldn't find a compelling reason to extend the "Parent" Entity class into "child" Races nor "child" Char_Classes.  I could extend Entity into races, and extend each race with appropriate char_classes.
But this would be madness when one can just enumerate the races and classes and just allow an Entity to hold the enumeration values.

I did end up creating a racial skills parent class each child race having different skills, and buffs. The Assassin class is a grand child of the main class descending from Thief.

# Current State of the Code
Currently this code runs in the terminal and allows one to create a character using AD&D 1e calculations.


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

# So What?
These are the initial steps toward creating a fully functional roleplaying game.

The original AD&E 1e mechanics are somewhat jenky and have some non-viable cases which need to be handled and auto re-rolled.
This adds to the charm and challenge of implementing the OG rule system.

Once the character creating system is completed, it will be expanded to have a basic combat system and a method to create npc entities.

The goal is to create something that is easily adaptable into a text based or graphics based role playing game.
