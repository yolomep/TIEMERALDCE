#ifndef _TICE_H
#include <tice.h>
#endif

#ifndef _POKEMON_H
#include "includes/Pokemon.hpp"
#endif

#ifndef _TRAINER_H
#include "includes/trainer.hpp"
#endif

#define _DATA_H

//remember that pdex# = index - 1
//as pdex# 0 is null!
//
struct PokeData{
    //pdex to array
    //(pdex - 1)*12 + n
    //where n is the index you want to access
	uint8_t stats[202*(6 + 2 + 2 + 2)]; //store stuff for all 202, compiler pre computes literals
    //this should contain 
    //first sections (regarding n):
    //0-5 base stats, 6-7 type, 8-9 color-shiny, 10-11 ability
    uint8_t evo[202*2]; // should contain the level of evo. 0 for nothing 
    //special evo dex# ->
    //if max evo, then (101, 0)
    //#13 -> (255, 255) as it can evolve to #15 or #17 randomly
    //#20 -> (102, 21) use item waterstone, evolve to #21
    //#23 -> 103, use leaf stone, evolve to #24
    //#40 -> 30, evolves at level 30 to #41
    //#42 -> 120, evolves to #43, but also #42 if empty space
    //#54 -> 5, evolves at level 5 to #55
    //#58 -> 45, evolves at level 45 to #59
    //#61 -> 105, use moonstone, evolve to #62
    //#64 -> 40, evolves at level 40 to #65
    //#74 -> 45, evolves at level 45 to #75
    //#89 -> 107, evolves to #90 (leaf) #91 (sun)
    //#137 -> 5, evolves at level 5 to #138
    //#138 -> 105, evolve to #139
    //#140 -> 25, evolves at level 25 to #141
    //#143 -> 102 to #144
    //#153 -> 106, use firestone, evolve to #154
    //#155 -> 5, evolves at level 5 to #156
    //#156 -> 104, use thunderstone, evolve to #157
    //#177 -> (254, 177) can evolve to #177 or #178 based on randint(0, sp atk + atk) > atk, then #178 else #177
    //#185 -> 50, evolves at level 50 to #186
    uint16_t nameIndex[203];//beginning of names

	char name[]; //array of names add size!!!!
}; //this should hold data for all pokemon

//use for generating wild?
struct MoveLearn{
    //how would this include all the learned moves?
    uint16_t index[203]; //beginning of all array and end
    //this should include each move, using index
    int16_t data[9614]; //idk how long
    //fixed
    //3L1 -> first 7 bits represent level, last 9 bits represent move number  
    //3M -> first 7 bits is 101 (0b1100101), last 9 bits represent move number (hm or tm)
    //3T -> first 7 bits is 102 (0b1100110), last 9 bits represent move number (tutor)
    //3E and 3S go -> first 7 bits is 103 (0b1100111), last 9 bits represent move number (special moves)
    //index[i + 1] = (short) moveLearn.size();
}; //this should contain data of all learned moves

struct MoveData{
	uint16_t index[359];
    char name[3180]; //array of names
    int8_t data[2506]; //effect, power, accuracy, target + flags, category + type, secondaryEffectChance, priority
}; //this should contain all data of moves

struct WildLoc{
    //where does WildLoc contain?
    //it should have a value
	uint16_t index[65*6]; //index for all values
    uint8_t location[1777];
};

struct PlayerSave {
    //contain data on all 4 of player moves
    char name[15];
    uint32_t money;
    uint16_t loc;
    uint16_t x;
    uint16_t y;
    uint8_t badges;
    uint8_t events[36];
    uint8_t pokedex[202]; //checks if caught, could save more bytes
    uint16_t items[350]; //number of each item
    bool gender;


    //begin pokemon
    uint8_t data8[(6 + 120)*(1 + 6 + 1 + 1 + 1 + 6 + 2)];  //dex, ivs, level, nature, isshiny, evs, type
    uint16_t data16[(6 + 120)*(1 + 1 + 4 + 1 + 1)]; // xp, nextXp, moves, ability, heldItem
    //uint8_t dex[6];
    //uint16_t evs[6*6];
    //uint8_t ivs[6*6];
    //uint16_t xp;
    //uint8_t level;
    //uint16_t nextXp;
    //uint16_t moves[4];
    //bool isShiny;
    //uint8_t nature;
    
};
