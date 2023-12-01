# gygaxian-entity
This is a stream of conciousness project based on the original Gary Gygax Advanced Dungeons and Dragons first Edition character creation mechanics. There is a mix of c and c++ coding, sometimes just because it was the first thing that popped into my head.

Originally intended this to be an excercise at using inheritance but quickly realized the error of my ways and remembered that inheritance is seldom a good solution for anything.
I couldn't find a compelling reason to extend the "Parrent" Entity class into "child" Races nor "child" Char_Classes.  I could extend Entity into races, and extend each race with appropriate char_classes.
But this would be madness when one can just enumerate the races and classes and just allow an Entity to hold the enumeration values.

# Current State of the Code
Currently this code runs in the terminal and allows one to create a character using AD&D 1e calculations.

# Name:
User can enter a name.  If name already exists one can choose to over-write existing file or not.
# Sex:
Next user can choose 1 of 5 sex's.  (AD&D 1e only has 2).
# Alignment:
Alignment is the next choice, each alignment shows compatible Char Classes.
# Stats:
Stat rolls are next follows the "Best 3 out of 4" approach.  Stat Rolls show which Class and Race requirements are failed. User has the Option to keep or re-roll.
# Race:
Race is selected next since race choice can modify stats. Only viable races based on stats will be availble.
# Class:
Class is limited by Race and Stats. Like race, only viable classes based on race and stats will be available.
# Stat Tables:
Stat Tables are generated and printed.

# Character Writen.
The current code saves the generated character in the /characters folder as \<chosen name\>.json
it then opens the saved character using the simdjson library. https://github.com/simdjson/simdjson

# So What?
These is the initial steps toward creating a fully functional roleplaying game.
Once the character creating system is completed, it will be expanded to have a basic combat system and a method to create npc entities.

The goal is to create something that is easily adaptable into a text based or graphics based role playing game.
