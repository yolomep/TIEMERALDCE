
/*
 *--------------------------------------
 * Program Name: Pokemon Emerald Ti CE v 0.0.1 alpha
 * Author: Yolomep Tom
 * License:not MIT
 * Description: Ports my version to Ti 84 plus ce, all from scratch
 *--------------------------------------
*/

#include <tice.h>
#include <stdlib.h>
#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>
#include <string.h>
#include "gfx/gfx.h"
#include <debug.h>
#include <format.h>
#include "includes/extraData.h"
//#include "includes/data.h"
//~screw IFNDEF so include struct, class in .cpp file LOL~
//after watching some videos critizing yandere dev, decided to actually format my files correctly
//jk. Broke clang so revert back to normal. Ahhhh. Still broken 
/* Error message from clang, despite compiling correctly:
fatal error: error in backend: Error while trying to spill UBC from class O24: Cannot scavenge register without an emergency spill slot!
PLEASE submit a bug report to https://bugs.llvm.org/ and include the crash backtrace, preprocessed source, and associated run script.
Stack dump:
0.      Program arguments: C:\\CEdev\\bin\\ez80-clang.exe -S -nostdinc -isystem C:\\CEdev/include -Isrc -Dinterrupt=__attribute__((__interrupt__)) -Wno-main-return-type -Xclang -fforce-mangle-main-argc-argv -mllvm -profile-guided-section-prefix=false -D_EZ80 -DNDEBUG -g0 -Wall -Wextra -Oz -fno-exceptions -fno-rtti -Wall -Wextra -Oz -Wno-reorder-ctor C:/CEdev/examples/TiEmeraldCE/src/testBattle.cpp -o C:/CEdev/examples/TiEmeraldCE/obj/testBattle.cpp.src
1.      <eof> parser at end of file
2.      Code generation
3.      Running pass 'Function Pass Manager' on module 'C:/CEdev/examples/TiEmeraldCE/src/testBattle.cpp'.
4.      Running pass 'Prologue/Epilogue Insertion & Frame Finalization' on function '@_Z10damageCalc7PokemonS_4MovePh'
 #0 0x766fb512 (C:\WINDOWS\System32\KERNELBASE.dll+0x12b512)
 #1 0x00f2e2c6 (C:\CEdev\bin\ez80-clang.exe+0x3ae2c6)
 #2 0x75a73c68 (C:\WINDOWS\System32\ucrtbase.dll+0x33c68)
 #3 0x031402d4 (C:\CEdev\bin\ez80-clang.exe+0x25c02d4)
 #4 0x00b8d867 (C:\CEdev\bin\ez80-clang.exe+0xd867)
 #5 0x00f2e4ee (C:\CEdev\bin\ez80-clang.exe+0x3ae4ee)
 #6 0x01b2fd7f (C:\CEdev\bin\ez80-clang.exe+0xfafd7f)
 #7 0x01b2ff53 (C:\CEdev\bin\ez80-clang.exe+0xfaff53)
 #8 0x01b3021e (C:\CEdev\bin\ez80-clang.exe+0xfb021e)
 #9 0x011658cb (C:\CEdev\bin\ez80-clang.exe+0x5e58cb)
ez80-clang: error: clang frontend command failed with exit code 70 (use -v to see invocation)
clang version 12.0.0 (https://github.com/jacobly0/llvm-project 170be88120e3aa88c20eea5615ba76b8f1d6c647)
Target: ez80
Thread model: posix
InstalledDir: C:\CEdev\bin
ez80-clang: note: diagnostic msg: 
********************

PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
Preprocessed source(s) and associated run script(s) are located at:
ez80-clang: note: diagnostic msg: C:\Users\admin\AppData\Local\Temp\testBattle-5f1a2f.cpp
ez80-clang: note: diagnostic msg: C:\Users\admin\AppData\Local\Temp\testBattle-5f1a2f.sh
ez80-clang: note: diagnostic msg:

********************
*/

//{{ data.h
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

//}}
//global vars for appvars
WildLoc wildloc;
PokeData pokedata;
MoveData movedata;
MoveLearn movelearn;

//{{ move.hpp works fine!
class Move {
public:
    uint16_t index;
    char *name;
    uint8_t power, accuracy;
    uint16_t effect;
    uint8_t type; 
    uint8_t category; //0 spec, 1 status, 2 physic
    uint8_t flags;
    uint8_t secondaryEffectChance;
    uint8_t target;
    int8_t priority;
    //target is combined with flags
    //category is combined with type
    //real priority + 6 = stored priority
    Move(uint16_t index);
    Move() : index{404} {

    }
};

Move::Move(uint16_t index) {
    if(index == 404) {
        this-> index = 404;
        return;
    }
    //effect, power, accuracy, target + flags, category + type, secondaryEffectChance, priority
    char temp[15]; //i think 13 is enough but...
    for(int i = movedata.index[index]; i < movedata.index[index + 1]; i++){
        temp[i - movedata.index[index]] = movedata.index[i];
    }
    index *= 7;
    effect = movedata.data[index];
    power = movedata.data[index + 1];
    accuracy = movedata.data[index + 2];
    //target is last two bits of index + 3
    //category is last two bits of index + 4
    target = movedata.data[index + 3] & ((1 << 2) - 1);
    category = movedata.data[index + 4] & ((1 << 2) - 1);
    flags = movedata.data[index + 3] >> 2;
    type = movedata.data[index + 4] >> 2;
    secondaryEffectChance = movedata.data[index + 5];
    priority = movedata.data[index + 6];
}

//}}

//{{ Pokemon.h
//A pokemon would contain a name, evs, and ivs
class Pokemon {
public:
    char *name; 
    uint8_t evs[6]; //theres a reason why evs are max 255
    uint8_t ivs[6];
    uint8_t base[6];
    int16_t hp; //contains current hp, signed because subtraction
    //This would contain an array regarding status?
    //OK I thought about it. If equals '0' then none, '1' para, '2' poision, '3' burn, '4' freeze, '5' sleep 1 counter etc. '10+' toxic N*?
    char status; 
    //voltaile staus
    //bound, block, confusion, curse, encore, flinch, indenify, infautated, leech seed, nightmare, torment, endure
    bool vol[12];
    //perish song turn, taunt turns
    uint8_t turns[2];
    uint16_t xp;
    uint8_t level;
    uint16_t nextXp;
    Move moves[4];
    bool isShiny;
    uint8_t color;
    uint16_t ability;
    uint8_t nature; //'0'-'15' ish
    uint8_t boosts[6];
    uint8_t dex;
    uint16_t heldItem; //heldItem
    uint8_t type[2]; //1-
    Pokemon(uint8_t dex, uint8_t ivs[], uint8_t base[], uint8_t level, Move moves[], bool isShiny, uint8_t color, uint16_t ability,
        uint8_t nature, char name[], uint8_t type[]); //wildpoke constructor
    Pokemon(uint8_t dex, uint8_t ivs[], uint8_t evs[], uint8_t base[], uint8_t level, uint16_t xp, Move moves[], bool isShiny,
        uint8_t color, uint16_t ability, uint8_t nature, char name[], uint16_t heldItem, uint8_t type[]); //generate from save
    Pokemon() : level(101) {
        
    }
    bool addxp(uint16_t i);
    uint16_t getStat(uint8_t index){
        return 1;
    }
    bool isStab(uint8_t type){
        return (type == this->type[0]) || (type == this->type[1]);
    }
    void prepare();
};

void Pokemon::prepare() {
    
}

bool Pokemon::addxp(uint16_t i){
    if(level == 100) return false;
	xp += i;
	if(xp > nextXp) {

    }
    return true;
}

Pokemon::Pokemon(uint8_t dex, uint8_t ivs[], uint8_t evs[], uint8_t base[], uint8_t level, uint16_t xp, Move moves[], bool isShiny,
        uint8_t color, uint16_t ability, uint8_t nature, char name[], uint16_t heldItem, uint8_t type[]) :
	    level(level), xp(xp), isShiny(isShiny), color(color), ability(ability), nature(nature), dex(dex), heldItem(heldItem),
        nextXp(level*level*level) {
	for(int i = 0; i < 6; i++){
		this->ivs[i] = ivs[i];
		this->base[i] = base[i];
        this->evs[i] = evs[i];
	}
	for(int i = 0; i < 4; i++){
		this->moves[i] = moves[i];
	}
    this->type[0] = type[0];
    this->type[1] = type[1];
    this->name = name;
}

Pokemon::Pokemon(uint8_t dex, uint8_t ivs[], uint8_t base[], uint8_t level, Move moves[], bool isShiny, uint8_t color,
    uint16_t ability, uint8_t nature, char name[], uint8_t type[])
: level(level), isShiny(isShiny), color(color), ability(ability), nature(nature), name(name), dex(dex){
	//generate a wild pokemon from these stats
	//ivs, base, moves are arrays
	for(int i = 0; i < 6; i++){
		this->ivs[i] = ivs[i];
		this->base[i] = base[i];
	}
	for(int i = 0; i < 4; i++){
		this->moves[i] = moves[i];
	}
    this->type[0] = type[0];
    this->type[1] = type[1];
    memset(evs, 0, 6);
    this->name = name;
}

//}}

//{{ Trainer.h

class Trainer {
public:
    char *name;
    //Playing style
    uint8_t style;
    Pokemon team[6];
    uint16_t id;
    uint16_t loc = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    bool gender;
    void move(int8_t x, int8_t y);
};


void Trainer::move(int8_t x, int8_t y){
    this->x += 8*x;
    this->y += 8*y;
    //get player background (place will go)
    //gfx_GetSprite(behind_sprite, player.x, player.y);
    //draw player
    //gfx_TransparentSprite(sprite, player.x, player.y); 
}

class Player : public Trainer {
public: 
    unsigned int money = 0;
    uint8_t badges = 0;
    uint8_t events[36];
    Pokemon box[3][40];
    bool pokedex[202]; //checks if caught
    uint16_t items[350]; //number of each item
    void move(int8_t x, int8_t y, gfx_sprite_t *back_sprite);
    uint8_t canMove(int8_t x, int8_t y){
        return 0;
    }
};

void Player::move(int8_t x, int8_t y, gfx_sprite_t *back_sprite){
    this->x += 8*x;
    this->y += 8*y;
    //add rotating animation?
    if(x || y) {
        //dbg_printf("ok??");
        //get player background (place will go)
        gfx_GetSprite(back_sprite, this->x, this->y);
        //draw player
        gfx_TransparentSprite(sprite, this->x, this->y); 
    }
}

//}}


#define print(str, x, y) gfx_PrintStringXY(str, x, y);
#define waitForEnter() while(!os_GetCSC());
#define clearScreen() gfx_FillScreen(255);
//Player variables
gfx_UninitedSprite(behind_sprite, 8, 8);
Player player = Player();

//{{ data.h
//gfx_sprite_t *behind_sprite = gfx_MallocSprite(8, 8);
//begin functions
//draw functions
void printCentered(const char *str, int height) {
    gfx_PrintStringXY(str, (LCD_WIDTH - gfx_GetStringWidth(str)) / 2, height);
}

//void print(str, x, y)
void copy(uint16_t a[], uint16_t b[], int size){
    //copies a into b
    for(int i = 0; i < size; i++) {
        a[i] = b[i];
    }

}

void copy(uint8_t a[], uint8_t b[], int size){
    //copies a into b
    for(int i = 0; i < size; i++) {
        a[i] = b[i];
    }

}

int find(uint16_t a, const uint16_t arr[], uint16_t size) {
    for(int i = 0; i < size; i++){
        if(arr[i] == a) return i;
    }
    return -1;
}
//This is the type checking function
double type(int m, int t){
    //since m and t are supposed to be plus 1, lets subtract 1 from both
    int32_t i = 18 * m + t - 19;
    i = ("UZJZ9N7JZJ;J=JV9;FJJJJAF>F*K:JU:ZKZFJ[F5C]ZJ6JEC;NN8KNZFKZIFJJOFJ&YJEMFUKZ9[JFJHJNN:JJJJZDIJGJZVEVJJKGJJINN9"[i / 3] - 32) >> i % 3 * 2 & 3;
    return (i + i/3)/2.;
}

uint8_t typeCalc(Pokemon p, uint8_t move_type){
    if(p.type[1] == 0) return type(move_type, p.type[0]);
    return type(move_type, p.type[0]) * type(move_type, p.type[1]);
}

int bisect(int lo, int high, uint8_t a[], int x){
	while(lo < high) {
		int mid = (lo + high)/2;
		if(x < a[mid]) high = mid;
		else lo = mid + 1;
	}
	return lo;
}
//we don't need a move factory, the constructor is enough
Pokemon pokemonFactory(uint8_t pdex, uint8_t level) {
    //create a pokemon with pdex and level
    //0-5 base stats, 6-7 type, 8-9 color-shiny, 10-11 ability
    //uint8_t ivs[], uint8_t base[], uint8_t level, Move moves[], bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[]    uint8_t ivs[6];
    uint8_t ivs[6];
    uint8_t base[6];
    uint8_t evs[6];
    Move moves[4];
    bool isShiny = randInt(0, 2048) <= 1;
    uint16_t location = 12*(pdex - 1);
    memset(evs, 0, 6);
    for(int i = 0; i < 6; i++){
        ivs[i] = randInt(0, 31);
        base[i] = pokedata.stats[location + i];
    }
    uint16_t ability = 0;
    if (pokedata.stats[location + 11]) ability = pokedata.stats[location + 10 + randInt(0, 1)];
    else ability = pokedata.stats[location + 10];
    char name[13];
    for(int i = pokedata.nameIndex[pdex]; i < pokedata.nameIndex[pdex + 1]; i++){
        name[i - pokedata.nameIndex[pdex]] = pokedata.name[i];
    }
    name[pokedata.nameIndex[pdex + 1]] = '\0';
    //get the moves with learn
    //3L1 -> first 7 bits represent level, last 9 bits represent move number  
    //3M -> first 7 bits is 101 (0b1100101), last 9 bits represent move number (hm or tm)
    //3T -> first 7 bits is 102 (0b1100110), last 9 bits represent move number (tutor)
    //3E and 3S go -> first 7 bits is 103 (0b1100111), last 9 bits represent move number (special moves)
    //index[i + 1] = (short) moveLearn.size();
    //add the level up moves, most recent??
    uint8_t shift = 0;
    for(int i = movelearn.index[pdex]; i < movelearn.index[pdex + 1]; i++){
        //scourage the moves...
        //fill up the array...
        if((movelearn.data[i] >> 9) > level) break; //we finished
        //90~% chance to change move
        if(randInt(0, 10) <= 9){
            moves[shift] = Move(movelearn.data[i] & ((1 << 9) - 1));
            //it will cause repetiveness among the movesets, but it is normal  
        }
        
        shift = (shift + 1) % 4;
    }
    uint8_t typed[2];
    typed[0] = pokedata.stats[location + 6];
    typed[1] = pokedata.stats[location + 7];
    return Pokemon(pdex, ivs, base, level, moves, isShiny, pokedata.stats[location + 8 + isShiny],
         ability, randInt(0, 24), name, typed);
}
// void get_data(uint16_t *ret, int data[], uint16_t index){
//     uint8_t curr = 0;
//     while(data[index] != -1){
//         ret[curr] = data[index];
//         curr++;
//         index++;
//     }
// }
//Different data files for different text??
//WILDLOC file should contain locations for each pokemon, two datas
//routes[# of routes]: this should contain the values for each route.
//the route index is ordered by a special index different from the map index, as this index does not include cities? No
//each location with wild pokemon should have this index, stored in a char array.
//what do I mean by this? each should have two short ints, begin index and end index, showing the range of each route. This is inclusive
//data[full size]: this should contain the probability of each location 
//what do we need to pack?
//generates wild pokemon given location
Pokemon genWild(uint8_t loc, uint8_t type = 0) {
//	uint16_t index[65*3]; //index for all values
//	uint8_t location[1777];
	//type: 0 is normal
	//1 is swimming
	//2 is fishing old
	//3 is fishing good
	//4 is fishing new
	//check if player has repel or something
	if(false) return Pokemon();
	if(type < 2) {
        uint16_t beginIndex;
        uint16_t endIndex;
        if(type == 0) {
            //get index from
            beginIndex = wildloc.index[6*loc];
            endIndex = wildloc.index[6*loc + 1];
        }
        else {
            beginIndex = wildloc.index[6*loc + 2];
		    endIndex = wildloc.index[6*loc + 3];
        }
		if(endIndex == 0) {
			//no wild on land
			return Pokemon();
		}
		/*
		 * locations.add(poke.pDex);
					locations.add(poke.minLevel);
					locations.add(poke.maxLevel);
					locations.add(prob);
		 */
		uint8_t number = (endIndex - beginIndex)/4;
		static uint8_t prob[44];
		prob[0] = wildloc.index[beginIndex + 3];
		for(uint8_t i = 1; i < number; i++){
			prob[i] = prob[i - 1] + wildloc.index[beginIndex + 4*i + 3];
		}
		uint8_t rand = randInt(0, 100);
		uint8_t index = bisect(0, number, prob, rand);
		//return the pokemon located at wildloc.index[beginIndex + 4*index] to wildloc.index[beginIndex + 4*index + 2]
		return pokemonFactory(wildloc.index[beginIndex + 4*index], randInt(wildloc.index[beginIndex + 4*index + 1],
		                        wildloc.index[beginIndex + 4*index + 2]));
	}
	else {
		uint16_t beginIndex = wildloc.index[6*loc + 4];
		uint16_t endIndex = wildloc.index[6*loc + 5];
		if(endIndex == 0) {
			return Pokemon();
		}
        /*
        					locations.add(poke.pDex);
					locations.add(poke.minLevel);
					locations.add(poke.maxLevel);
					locations.add(prob.first); //prob
					locations.add(prob.second); //rod
                    */
        //we need to split them into rods...
        uint8_t number = 0;
        static uint8_t rodList[27*4]; //keep the rod type here
        static uint8_t prob[27]; //we keep the probablities here...
        //we loop through and check rod
        
        for(int i = beginIndex; i < endIndex; i += 5){
            //check if corresponds with rod...
            if(type == wildloc.location[i + 4]) {
                
                for(uint8_t j = 0; j < 4; j++){
                    rodList[number*4 + j] = wildloc.location[i + j];
                }
                number++;
            }
        }
        prob[0] = rodList[3];
		for(uint8_t i = 1; i < number; i++){
			prob[i] = prob[i - 1] + rodList[4*i + 3];
		}
		uint8_t rand = randInt(0, 100);
		uint8_t index = bisect(0, number, prob, rand);
		return pokemonFactory(rodList[4*index], randInt(rodList[4*index + 1], rodList[4*index + 2]));
	}
    //print(0, 1, "Read was successful");
	return Pokemon();
}

//calculates the damage of the move attacker on attacked
//conditions: 0 - weather, 1 - critical, 2 - beat up members
//for weather:
//0 - null, 1 - sun, 2 - rain, 3 - sand, 4 - hail
//plus now increases special attack by x1.5 when it is going against an electric type or minus
//minus now increases special attack by x1.5 when it goes against steel or plus
uint16_t damageCalc(Pokemon attacker, Pokemon attacked, Move move, uint8_t conditions[]) {
    if(move.effect == EFFECT_DRAGON_RAGE) {
        return 40;
    }
    else if(move.effect == EFFECT_OHKO) {
        return 60'000; 
    }
    else if(move.effect == EFFECT_SUPER_FANG) {
        return attacked.hp/2;
    } 
    else if(move.effect == EFFECT_ENDEAVOR) {
        return attacker.hp < attacked.hp ? attacked.hp - attacker.hp : 0;
    }
    //ai should never choose bide -> crappy version of metal burst
    // else if(move.effect == EFFECT_BIDE) {
    //     return 0; //idk??
    // }
    //calculate multihit with multiple calls to damageCalc -> 2,3,4,5 : 3/8, 3/8, 1/8, 1/8 -> 1/8, 1/4, 3/8, 1/4
    //metronome calls a random move to be passed into this function
    else if(move.effect == EFFECT_LEVEL_DAMAGE) {
        return attacker.level;
    }
    else if(move.effect == EFFECT_PSYWAVE) {
        return attacker.level * (10*randInt(5, 10) + 50)/100 + 1; //psywave is now random number from 5 to 10, not 0 to 10
    }
    else if(move.effect == EFFECT_PAIN_SPLIT) {
        return (attacked.hp - attacker.hp)/2;
    }
    
    else if((attacked.ability == ABILITY_FLASH_FIRE && move.type == FIRE_TYPE)||
        (attacked.ability == ABILITY_LIGHTNING_ROD && move.type == ELECTRIC_TYPE) 
        || (attacked.ability == ABILITY_WATER_ABSORB &&move.type == WATER_TYPE)
        || (attacked.ability == ABILITY_VOLT_ABSORB && move.type == ELECTRIC_TYPE) ||
        (attacked.ability == ABILITY_WONDER_GUARD && typeCalc(attacked, move.type) < 2)) {
        return 0;
    }
    else if(attacker.ability == ABILITY_CACOPHONY || attacker.ability == ABILITY_SOUNDPROOF){
        return 0;
    }

    uint16_t attack, defence;
    if(move.category == CATEGORY_PHYSICAL) {
        attack = attacker.getStat(1);
        defence = attacked.getStat(2);
    }
    else {
        attack = attacker.getStat(3);
        defence = attacked.getStat(4);
    }
    if(move.effect == EFFECT_LOW_KICK && randInt(1, 4) > 3) {
        move.power = randInt(60, 150); 
    }
    else if(move.effect == EFFECT_FLAIL) {
        double hpPercentage = attacker.hp*100.0/attacker.getStat(0);
        if(hpPercentage > 68.74) move.power = 20;
        else if(hpPercentage > 55.41) move.power = 40;
        else if(hpPercentage > 30.82) move.power = 80;
        else if(hpPercentage > 10.41) move.power = 100;
        else if(hpPercentage > 4.16) move.power = 150;
        else move.power = 200;
    }
    else if(move.effect == EFFECT_RETURN || move.effect == EFFECT_FRUSTRATION) {
        move.power = move.effect - randInt(0, 30); //121+ - (0, 30)
    }
    else if(move.effect == EFFECT_PRESENT) { //set move.power after use? no, means AI cheating
        if(randInt(0, 10) > 5) {
            move.power = 120;
        }
        else if(randInt(0, 5) > 1) {
            move.power = 100;
        }
        else {
            move.power = 0;
        }
    }
    else if(move.effect == EFFECT_MAGNITUDE) {
        int percent = randInt(0, 100);
        if(percent < 5) {
            move.power = 10;
        }
        else if(percent < 10) {  
            move.power = 30;
        }
        else if(percent < 20) {
            move.power = 50;
        }
        else if(percent < 30) {
            move.power = 90;
        }
        else if(percent < 50) {
            move.power = 110;
        }
        else {
            move.power = 150;
        }
    }
    int16_t damage = (2*attacker.level/5 + 2)*move.power*attacker.getStat(1)/attacked.getStat(2)/50;
    if(2*attacker.hp < attacker.getStat(0)) {
         if((move.type == GRASS_TYPE && attacker.ability == ABILITY_OVERGROW) ||
            (move.type == FIRE_TYPE && attacker.ability == ABILITY_BLAZE) || 
            (move.type == WATER_TYPE && attacker.ability == ABILITY_TORRENT) ||
            (move.type == BUG_TYPE && attacker.ability == ABILITY_SWARM)
            ) {
            damage *= 2;
        }
    }
    if(attacker.ability == ABILITY_HUSTLE && move.category == CATEGORY_PHYSICAL) damage *= 1.5;
    else if((attacker.ability == ABILITY_PURE_POWER || attacker.ability == ABILITY_HUGE_POWER) 
        && move.category == CATEGORY_PHYSICAL) damage *= 2;
    //you can have blaze and eruption
    if(move.effect == EFFECT_ERUPTION) {
        damage *= attacker.hp/attacker.getStat(0);
    }
    else if(move.effect == EFFECT_KNOCK_OFF && attacked.heldItem != 0) {
        damage *= 3/2;
    } 
    // //beat up damage = team damage
    else if(move.effect == EFFECT_BEAT_UP) {
        damage *= conditions[2];
    }
    else if(move.effect == EFFECT_FACADE && attacker.status != '0'){
        damage *= 2;
    }
    if(move.category == CATEGORY_SPECIAL && ((attacker.ability == ABILITY_PLUS && (attacked.ability == ABILITY_MINUS || 
    attacked.type[0] == ELECTRIC_TYPE || attacked.type[1] == ELECTRIC_TYPE))
        || (attacker.ability == ABILITY_MINUS && (attacked.ability == ABILITY_PLUS || attacked.type[0] == STEEL_TYPE || 
        attacked.type[1] == STEEL_TYPE)))) {
        damage *= 1.5;
    }
    //add something about charge
    damage += 2;
    if(conditions[0] == SUN_CONDITION) {
        if(move.effect == EFFECT_WEATHER_BALL) {
            move.type = FIRE_TYPE;
            damage = (damage - 2)*2 + 2;
        }
        if(move.type == FIRE_TYPE) damage *= 3/2;
        else if(move.type == WATER_TYPE) damage *= 2/3;
    }
    else if(conditions[0] == RAIN_CONDITION){
        if(move.effect == EFFECT_WEATHER_BALL) {
            move.type = WATER_TYPE;
            damage = (damage - 2)*2 + 2;
        }
        if(move.type == WATER_TYPE) damage *= 3/2;
        else if(move.type == FIRE_TYPE) damage *= 2/3;
    }
    else if(conditions[0] == HAIL_CONDITION) {
        if(move.effect == EFFECT_WEATHER_BALL) {
            move.type = ICE_TYPE;
            damage = (damage - 2)*2 + 2;
        }
    }
    else if(conditions[0] == SAND_CONDITION) {
        if(move.effect == EFFECT_WEATHER_BALL) {
            move.type = ROCK_TYPE;
            damage = (damage - 2)*2 + 2;
        }
    }
    else {
        if(move.effect == EFFECT_WEATHER_BALL) {
            move.type = NORMAL_TYPE;
        }
    }
    damage *= (1 + conditions[1])*randInt(85, 100)/100*attacker.isStab(move.type)*typeCalc(attacked, move.type); 
    //don't implement randomness before hand to increase randomness
    if(move.category == CATEGORY_PHYSICAL && attacker.status == '3') {
        damage /= 2;
    }
    //other damage...
    if(attacked.ability == ABILITY_MARVEL_SCALE && attacked.status != '0' && move.category == CATEGORY_PHYSICAL){
        damage *= 2/3;
    }

    if(move.effect == EFFECT_FALSE_SWIPE) {
        if(attacked.hp - damage < 1) {
            return attacked.hp - 1;
        }
    }

    if(attacked.ability == ABILITY_THICK_FAT && (move.type == FIRE_TYPE || move.type == ICE_TYPE)) damage /= 2;

    return damage;
}

//draws the battle
//+---------+
//| f    e  |
//|      dat|
//| u   cxxx|
//+---------+
//conditions: 0 - weather, 1 - critical, 2 - beat up members
void displayBattle(Pokemon user, Pokemon enemy, uint8_t conditions[]){
    const char* weather_name = weatherString[conditions[0]];
    gfx_SetTextBGColor(COLOR_WHITE);
    gfx_SetTextFGColor(COLOR_BLACK);
    print(weather_name, 10, 10);
    
    //makes the rectangle
    gfx_Rectangle(100, 100, 150, 150);
    //display options



    //display player first

}

void battleTrainer(Trainer trainer){

}

void battleWild(Pokemon wildmon){
    //how is the battle organized?

}

/*
use map.png not test.png
12*x
Notes about the maps:
Oldale town: Free potion has been moved to the pokemart, first encounter will give free potion
Petalburg town: Wally's house exists, just like how may's house exists (HM surf will be avaliable after norman is defeated)
route 104a: the black just shows the "hitbox" of the dock, which will trigger the boat stuff
    same with the black lining the bottom. Deferentiates the different sections. Black can still be walked on
route 114a: meteor falls cave entrance is a light brown square.
route 106: both down and right go to dewford, but if you go right you spawn in the water (edge)
Dewford town: the dock is the same as route 104a's dock
route 104b: berry patch 3 of them with dark brown, type of berry is stored in event[34-36] -> use mod + divide
Rustoburo city: the brown patch is devon corp... no space to put above center so... 
    Entering the building first time, player recieve quick claw
Fallabor town: basically empty. No locations of interest. Changed location of mart and center 
Rusturf tunnel: can't cross black line until rock smash
route 109: light yellow for the sand
route 111: sand can only be traveled if equipped item
route 113: traveling on grass adds soot. Go to house to trade soot.
"black", "blue", "brown", "dark brown", "dark green", "dark red", "green", "grey",
				"light blue", "light brown", "light gray", "light green", "light orange", "light yellow",
				"magenta", "medgray", "navy", "orange", "orange red", "pink", "purple", "red", "yellow"
*/

void drawMap(uint8_t location){
    //location begins on 0
    switch(location){
        case 0:
            
            break;
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
    }
}
//returns menu choice
uint8_t menu(const char *title, const char* choices[], uint8_t size, uint8_t bgColor){
    //should display:
    /*
    menu("Menu", ["select 1", "select 2", "select 3"])
    Menu
     >  [0]  select 1
        [1]  select 2
        [2]  select 3
        [3]

        [9]  select 9
        [10] select 10
    */
    gfx_SetTextScale(1, 2);
    printCentered(title, 10);
    uint8_t loc = 0; //we are selecting 0
    for(uint8_t i = 0; i < size; i++){
        char text[45];
        sprintf(text, "[%d] ", i);
        strcat(text, choices[i]);
        print(text, 40, 20*i + 30);
    }
    gfx_SetColor(bgColor);
    print(">", 20, 30);
    //bool key, prevKey;
    do{
        // key = kb_Data[1] == kb_2nd;
        // //(kb_Data[6] & kb_Clear) is the clear key
        // if (key && !prevkey) {
        //     // ...
        // }
        // prevkey = key;
        kb_Scan();
        //slow down the key input thing
        //too fast, enters like 3 keystrokes per key
        while (!os_GetCSC());
        // gfx_SetTextXY(180, 200);
        // gfx_PrintInt(kb_Data[6] != kb_Enter, 1);
        // <erase length
        if(kb_Data[7] & kb_Down){
            //go down, press 
            //remove at current loc
            //print("  ", 20, 30 + loc*20);
            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);
            //then add loc
            loc++;
            if (loc == size){
                loc = 0;
            }
            //then redraw
            print(">", 20, 30 + loc*20);
        }
        else if(kb_Data[7] & kb_Up){
            //remove at current loc
            //print("  ", 20, 30 + loc*20);
            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);
            //then add loc
            loc--;
            if(loc < 0){
                loc = size - 1;
            }
            //then redraw
            print(">", 20, 30 + loc*20);
            
        }
        else if(kb_Data[3] & kb_0){
            //print("hahaha", 0, 0);
            loc = 0;
            break;
        }
        else if(kb_Data[3] & kb_1) {

            loc = 1;
            break;
        }
        else if((kb_Data[3] & kb_4) && size >= 5){
            loc = 4;
            break;
        }
        else if((kb_Data[3] & kb_7) && size >= 8){
            loc = 7;
            break;
        }
        else if((kb_Data[4] & kb_2) && size >= 3){
            loc = 2;
            break;
        }
        else if((kb_Data[4] & kb_5) && size >= 6){
            loc = 5;
            break;
        }
        else if((kb_Data[4] & kb_8) && size >= 9){
            loc = 8;
            break;
        }
        else if((kb_Data[5] & kb_3) && size >= 4){
            loc = 3;
            break;
        }
        else if((kb_Data[5] & kb_6) && size >= 7){
            loc = 6;
            break;
        }
        else if((kb_Data[5] & kb_9) && size == 10){
            loc = 9;
            break;
        }
        // gfx_SetTextXY(200, 200);
        // gfx_PrintInt(kb_Data[6] != kb_Enter, 1);
    } while(kb_Data[6] != kb_Enter);
    // gfx_PrintInt(i, 2);
    gfx_SetTextScale(1, 1);
    return loc;
    
}


uint8_t menu(const char *title, const char* choices[], uint8_t size){
    return menu(title, choices, size, 255);
}
//HP = (2*base + iv + ev/4)*level/100 + level + 10
//other = ((2*base + iv + ev/4)*level/100 + 5)*nature
//3/9	3/8	3/7	3/6	3/5	3/4	3/3	4/3	5/3	6/3	7/3	8/3	9/3
//2/8	2/7	2/6	2/5	2/4	2/3	2/2	3/2	4/2	5/2	6/2	7/2	8/2

//}}

int main(void) {
    uint8_t tems[] = {1, 2};
    damageCalc(Pokemon(), Pokemon(), Move(), tems);
	//dbg_sprintf(dbgout, "%d\n", sizeof(Pokemon)); //119
    //set everything
    ti_CloseAll();
    //open wildLoc
	ti_var_t wildLoc = ti_Open("WildLoc", "r");
	ti_var_t pokeData = ti_Open("PokeData", "r");
	ti_var_t moveData = ti_Open("MoveData", "r");
    ti_var_t moveLearn = ti_Open("MoveLear", "r");
    //dbg_sprintf(dbgout, "%d\n", wildLoc);
	if(!wildLoc || !pokeData || !moveData || !moveLearn) {
        os_ClrHome();
        //probably try to shorten
		if(!wildLoc) {
			os_PutStrFull("Could not find or locate: WildLoc.8xv");
            os_NewLine();
		}
		if(!pokeData) {
			os_PutStrFull("Could not find or locate: PokeData.8xv");
            os_NewLine();
		}
		if(!moveData) {
			os_PutStrFull("Could not find or locate: MoveData.8xv");
            os_NewLine();
		}
        if(!moveLearn) {
            os_PutStrFull("Could not find or locate: MoveLearn.8xv");
            os_NewLine();
        }
		while(!os_GetCSC());
		return 1;
	}
    ti_Read(&wildloc, sizeof(WildLoc), 1, wildLoc);
    ti_Read(&pokedata, sizeof(PokeData), 1, pokeData);
    ti_Read(&movedata, sizeof(MoveData), 1, moveData);
    ti_Read(&movelearn, sizeof(MoveLearn), 1, moveLearn);
    gfx_Begin();
    //Call PKMNSET2
    //uint8_t char_data[] = {0x39, 0x45, 0x82, 0x82, 0x82, 0x83, 0x45, 0x39}; // Bitmap for "alpha"
    uint8_t char_data2[] = {0x00, 0x00, 0x08, 0x1C, 0x26, 0x43, 0x81, 0xFF}; //delta
    uint8_t char_data3[] = {0x3A, 0x7E, 0xC4, 0xC4, 0xC4, 0xCD, 0x7F, 0x32}; //alpha2
    //gfx_SetCharData(1, char_data);
    gfx_SetCharData(2, char_data2);
    gfx_SetCharData(3, char_data3);


    gfx_FillScreen(0);
    gfx_SetTextFGColor(9);
    gfx_SetTextBGColor(0);

/*
0x39, 0x45, 0x82, 0x82, 0x82, 0x83, 0x45, 0x39,	// Char 000 (.)
	0x00, 0x00, 0x08, 0x1C, 0x26, 0x43, 0x81, 0xFF,	// Char 001 (.)
    */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    goto skip; //================================================================================SKIP==============
    //printCentered("\x01       \x03", 80);
    while(!os_GetCSC());
    
    /* Print some scaled text */
    //gfx_SetTextScale(1, 2);
    //set start screen
    printCentered("\x03 V 0.02", 80);
    printCentered("(C) 1995-2005 GAMEFREAK inc.", 90);
    printCentered("(C) 2005 POKeMON", 100);
    printCentered("(C) 1995-2005 Nintendo", 110);
    printCentered("(C) 2020-2021 T.J. CODES", 120);
    printCentered("ALL RIGHTS RESERVED", 130);
    printCentered("PRESENTS", 140);
   
    //set coordinates
    //print("ABCDEFGHIJKLMNOPQRSTUVXYZABCDEFGHIJKLMNOPQ", 0, 0);
    //print("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 0, 10);
    //print("Ha!", 10, 20);
    while (!os_GetCSC());
    //gfx_sprite_t *behind_sprite = gfx_MallocSprite(30, 60);
    gfx_FillScreen(255);
    gfx_ScaledTransparentSprite_NoClip(logo, 15, 15, 8, 8);
    //delay(2000);
    
    gfx_FillScreen(255);
    gfx_SetTextFGColor(0);
    gfx_SetColor(5);
    gfx_FillRectangle_NoClip(0, 140, 320, 100);
    gfx_SetColor(127);
    gfx_FillRectangle_NoClip(0, 0, 320, 50);
    gfx_SetColor(74);
    gfx_FillRectangle_NoClip(0, 50, 320, 90);
    gfx_SetColor(7);
    gfx_SetTextBGColor(254);
    printCentered("This is supposed to be the opening scene, but I", 60); //max 47
    printCentered("realized it cost too much memory. There are no", 70);
    printCentered("sprites in this game because there is no", 80);
    printCentered("memory for all the sprites. For more:", 90);
    printCentered("yolomep.github.io/EmeraldDeltaTi84pce", 100);
    gfx_SetTextBGColor(253);
    print("Quick overview of controls:", 10, 130);
    print("Up is the up arrow. Down is the down", 10, 140);
    print("arrow, etc. 2nd is the B button and Enter", 10, 150);
    print("is the A button Other buttons (Mode, Alpha,", 10, 160);
    print("y=, etc.) will represent start and select,", 10, 170);
    print(" but they will be explained before use.", 10, 180);
    // //gfx_GetSprite(behind_sprite, x, y);
    // // gfx_TransparentSprite(sprite, x, y);
    // for(int i = 0; i < 200; i++){
    //     gfx_FillScreen(255);
    //     gfx_SetTextFGColor(0);
    //     gfx_SetColor(5);
    //     gfx_FillRectangle_NoClip(0, 140, 320, 100);
    //     gfx_SetColor(127);
    //     gfx_FillRectangle_NoClip(0, 0, 320, 50);
    //     gfx_SetColor(74);
    //     gfx_FillRectangle_NoClip(0, 50, 320, 90);
    //     gfx_SetColor(7);
    //     delay(100);
    //     gfx_FillTriangle(i, 140, i + 30, 140, i + 15, 60);
    //     gfx_FillTriangle(i + 100, 140, i + 140, 140, i + 120, 40);
    //     gfx_FillTriangle(i + 200, 140, i + 230, 140, i + 210, 50);
    //     delay(100);
    // }
    // char* choices[] = {"option 1", "option 2", "haefs"};
    // x = menu("Pause", choices, 3);
    
    // char work[10] = "hehe";
    // sprintf(work, "crap %d", x);
    // // puts(work);
    // print(work, 1, 130);
    skip: 
        while (!os_GetCSC());
        gfx_SetTextBGColor(253);
    
    gfx_FillScreen(71);
    gfx_SetTextScale(2, 4);
    gfx_SetTextFGColor(231);
    printCentered("Pokemon", 60);
    gfx_SetTextScale(1, 1);
    gfx_SetTextFGColor(255);
    printCentered("Delta Emerald", 90);
    printCentered("TI-84 C Edition (Abridged)", 100);
    printCentered("(C) 2020 Yolomep Codes", 200);
    printCentered("Press Enter to Start", 130);
    //timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    //uint32_t x = timer_Get(1);
    //15 ticks transparent, 17 ticks visible
    // while(!os_GetCSC()) {
    //     uint32_t y = timer_Get(1);
    //     dbg_sprintf(dbgout, "timer %u\n", (y % 32768));
    //     if((y - x) % 32768 >= 17000){
    //         //blink
    //         dbg_sprintf(dbgout, "he\n");
    //         gfx_FillRectangle_NoClip(60, 130, 100, 10);
            
    //     }
    //     else if((y - x) % 32768 >= 0) {
    //         dbg_sprintf(dbgout, "ha\n");
    //         printCentered("Press Enter to Start", 130);
    //     }
    // }
    gfx_SetTextTransparentColor(255);
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_FillScreen(255);
    uint8_t val = 0;
    {
        //load game+scope hack:
        const char* temp[] {"New", "Load", "Exit"};
        val = menu("Save or load game?", temp, 3);
    }
    gfx_FillScreen(255);
    //dbg_sprintf(dbgerr, "bruh");
    if(val == 0) {
        printCentered("Remember to save by using the menu.", 30);
        printCentered("Press any button to continue.", 70);
        player.x = 120;
        player.y = 120;
        waitForEnter();
    }
    else if(val == 1) {
        ti_var_t save = ti_Open("EmerDSav", "r");
        if(save) {
            printCentered("Loading Save...", 30);
            PlayerSave saveFile;
            ti_Read(&saveFile, sizeof(PlayerSave), 1, save);
           
            copy(player.events, saveFile.events, 36);
            copy(player.items, saveFile.items, 350);
            player.badges = saveFile.badges;
            player.gender = saveFile.gender;
            player.money = saveFile.money;
            player.loc = saveFile.loc;
            player.x = saveFile.x;
            player.y = saveFile.y;
            player.name = saveFile.name;
            for(int i = 0; i < 202; i++) {
                player.pokedex[i] = saveFile.pokedex[i];
            }
            //copy(player.pokedex, saveFile.pokedex, 202);

            //do stuff with data8 and data16
            for(int i = 0; i < 6 + 120; i++){
                uint8_t temp = 18*i;
                if(i > 5 && saveFile.data8[temp + 7] == 101) i = ((i + 34)/40)*40; //probably works
                uint8_t pdex = saveFile.data8[temp];
                //create pokemon
                
                 /*
            uint8_t data8[6*(1 + 6 + 1 + 1 + 1 + 6)];  //dex, ivs, level, nature, isshiny, evs
    uint16_t data16[6*(1 + 1 + 4 + 1)]; // xp, nextXp, moves, ability*/
                //copy ivs and evs into temp
                uint8_t tivs[6];
                uint8_t tevs[6];
                uint8_t tbase[6]; //0-5 base stats, 6-7 type, 8-9 color-shiny, 10-11 ability
                Move tmove[4];
                char tname[15];
                for(int j = 0; j < 6; j++) {
                    tivs[j] = saveFile.data8[temp + j + 1];
                    tevs[j] = saveFile.data8[temp + j + 10];
                    tbase[j] = pokedata.stats[12*pdex + j];
                }
                for(int j = 0; j < 4; j++){
                    tmove[j] = Move(saveFile.data16[8*i + 2 + j]);
                }
                //uint8_t dex, uint8_t ivs[], uint8_t evs[], uint8_t base[], uint8_t level, uint16_t xp, Move moves[]
                // bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[]
                uint8_t ttype[2];
                ttype[0] = saveFile.data8[temp + 16];
                ttype[1] = saveFile.data8[temp + 17];
                Pokemon tempPoke1 = Pokemon(pdex, tivs, tevs, tbase, saveFile.data8[temp + 7], saveFile.data16[8*i], tmove, 
                    saveFile.data8[temp + 9], (saveFile.data8[temp + 9] ? pokedata.stats[12*pdex + 9] : pokedata.stats[12*pdex + 8]),
                    saveFile.data16[8*i + 6], saveFile.data8[temp + 8], tname, saveFile.data16[8*i + 7], ttype);
                if(i < 6) {
                    player.team[i] = tempPoke1;
                }
                else {
                    player.box[(i - 6)/40][(i - 6)%40] = tempPoke1;
                }
            //-Wno-xxxx
            }
            printCentered("Save Loaded Successfully!", 40);
        }
        else {
            player.x = 120;
            player.y = 120;
            printCentered("No Save Detected. Creating new game...", 30);
            
        }
        printCentered("Press any button to continue.", 70);
        waitForEnter();
    }
    else if(val == 2) {
        gfx_End();
        return 0;
    }
    //dbg_printf(dbgerr, "bru2h");
    //dbg_printf("bruh2");
    bool backgroundDrawn = false;
    //bool replaceBackground = true;
    behind_sprite->width = 8;
    behind_sprite->height = 8;
    //dbg_printf(dbgerr, "bruh");
    gfx_FillScreen(255);
    
    while(true){
        //game loop
        
    /*
    Logic behind game loop
    draw background if not drawn
    getKey()
    if(menu): handle menu
    when menu exit: redraw background, handle movement?
    */
        if(!backgroundDrawn) {
            drawMap(player.loc);
            backgroundDrawn = true;
            gfx_GetSprite(behind_sprite, player.x, player.y);
            gfx_TransparentSprite(sprite, player.x, player.y);
            
        }
        //dbg_printf("gay");
        //get background before handle movement! 
        //whelp null pointer error. 
        dbg_printf("%u %u\n", player.x, player.y);
        
        //dbg_printf("gay\n");
        
        //dbg_printf("gay\n");
        //check if we need to draw player
        // if(!playerFirstDrawn) {
        //     //draw previous background
        //     gfx_Sprite(behind_sprite, player.x, player.y);
        //     //dbg_printf("gay\n");
        //     playerFirstDrawn = true;
        // }
        
        //dbg_sprintf(dbgerr, "gay1");
        //handle movement code check...
        //1 check if key press
        //check if player can move there
        kb_Scan();
        //since this is technically event driven, we can just use getCSC?
        //uses get csc so I don't need to write my own lol. 
        //continuous key meh
        waitForEnter();
        //check for menu key:
        if(kb_Data[1] & kb_2nd) {
            gfx_FillScreen(255);
            static const char* temp[] {"Back", "Quit", "Save", "Team", "Bag", "Fly", "Trainer"};
            uint8_t option = menu("Menu", temp, 7);
            gfx_FillScreen(255);
            /*
            Menu
            [0] Back
            [1] Quit
            [2] Save
            [3] Team
            [4] Bag
            [5] Fly
            [6] Trainer
            */
            switch(option) {
                case 0: //do nothing
                break;
                case 1:
                    gfx_End();
                    return 0;
                case 2: {
                    gfx_ZeroScreen();
                    printCentered("Saving...", 20);
                    printCentered("Do not turn off your calc", 30);
                    PlayerSave saveFile;
                    saveFile.badges = player.badges;
                    saveFile.badges = player.badges;
                    saveFile.money = player.money;
                    saveFile.loc = player.loc;
                    saveFile.x = player.x;
                    saveFile.y = player.y;
                    strcpy(saveFile.name, player.name);
                    copy(saveFile.events, player.events, 36);
                    copy(saveFile.items, player.items, 350);
                    for(int i = 0; i < 202; i++){
                        saveFile.pokedex[i] = player.pokedex[i];
                    }
                    for(int i = 0; i < 6 + 120; i++){
                        uint8_t temp = 18*i;

                        Pokemon pktemp;
                        if(i < 6) pktemp = player.team[i];
                        else pktemp = player.box[(i - 6)/40][(i - 6) % 40];
                        saveFile.data8[temp + 7] = pktemp.level;
                        if(pktemp.level == 101) {
                            continue; //might take a while? idk but i know branch helps
                        }
                        //Pokemon te = player.team[i];
                        saveFile.data8[temp] = pktemp.dex;
                        for(int j = 0; j < 6; j++) {
                            saveFile.data8[temp + j + 1] = pktemp.ivs[j];
                            saveFile.data8[temp + j + 10] = pktemp.evs[j];
                        }
                        for(int j = 0; j < 4; j++){
                            saveFile.data16[8*i + 2 + j] = pktemp.moves[j].index;
                        }

                        saveFile.data8[temp + 9] = pktemp.isShiny;
                        saveFile.data8[temp + 8] = pktemp.nature;
                        saveFile.data16[8*i] = pktemp.xp;
                        saveFile.data16[8*i + 6] = pktemp.ability;
                        saveFile.data16[8*i + 7] = pktemp.heldItem;
                        saveFile.data8[temp + 16] = pktemp.type[0];
                        saveFile.data8[temp + 17] = pktemp.type[1];
                    }
                    ti_var_t save = ti_Open("EmerDSav", "w");
                    ti_Write(&saveFile, sizeof(PlayerSave), 1, save);
                    printCentered("Save Successfully!", 50);
                    waitForEnter();
                    break;
                }
                case 3: {
                    gfx_ZeroScreen();
                    printCentered("Pokemon", 10);
                    uint8_t loc = 0; //currenlty hovering over zero
                    //First should be lead
                    /*n^3 experience
                        Pokemon
                    Sceptile L300 300/400 HP [Status] 
                        1000000/2000000 xp
                    */
                    uint8_t size = 0;
                    for(uint8_t i = 0; i < 6; i++){
                        if(player.team[i].level != 101) size++;
                        else break;
                    }
                    for(uint8_t i = 0; i < size; i++){
                        char text[45];
                        strcat(text, player.team[i].name);
                        char tes[8];
                        sprintf(tes, " L%d ", player.team[i].level);
                        strcat(text, tes);
                        memset(tes, 0, 6);
                        sprintf(tes, "%d/", player.team[i].hp);
                        strcat(text, tes);
                        memset(tes, 0, 8);
                        sprintf(tes, "%d HP", player.team[i].getStat(0));
                        strcat(text, tes);
                        if(player.team[i].status) {
                            switch (player.team[i].status) {
                                case 1:
                                    strcat(text, " [Confused]");
                                break;
                            }
                            
                        }
                        //_u_ustoa(10);
                        // sprintf(text, "[%d] ", i);
                        // strcat(text, choices[i]);
                        print(text, 40, 20*i + 30);
                        memset(text, 0, 42);
                        //100,00,00 100**3
                        sprintf(tes, "%d/", player.team[i].level);
                        strcat(text, tes);
                    }
                    gfx_SetColor(255);
                    print("->", 18, 30);
                    //bool key, prevKey;
                    do{
                        // key = kb_Data[1] == kb_2nd;
                        // //(kb_Data[6] & kb_Clear) is the clear key
                        // if (key && !prevkey) {
                        //     // ...
                        // }
                        // prevkey = key;
                        kb_Scan();
                        //slow down the key input thing
                        //too fast, enters like 3 keystrokes per key
                        while (!os_GetCSC());
                        // gfx_SetTextXY(180, 200);
                        // gfx_PrintInt(kb_Data[6] != kb_Enter, 1);
                        // <erase length
                        if(kb_Data[7] & kb_Down){
                            //go down, press 
                            //remove at current loc
                            //print("  ", 20, 30 + loc*20);
                            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);
                            //then add loc
                            loc++;
                            if (loc == size){
                                loc = 0;
                            }
                            //then redraw
                            print("->", 18, 30 + loc*20);
                        }
                        else if(kb_Data[7] & kb_Up){
                            //remove at current loc
                            //print("  ", 20, 30 + loc*20);
                            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);
                            //then add loc
                            loc--;
                            if(loc < 0){
                                loc = size - 1;
                            }
                            //then redraw
                            print("->", 18, 30 + loc*20);
                            
                        }
                        else if(kb_Data[3] & kb_0){
                            //print("hahaha", 0, 0);
                            loc = 0;
                            break;
                        }
                        else if(kb_Data[3] & kb_1) {
                            loc = 1;
                            break;
                        }
                        else if((kb_Data[3] & kb_4) && size >= 5){
                            loc = 4;
                            break;
                        }
                        else if((kb_Data[4] & kb_2) && size >= 3){
                            loc = 2;
                            break;
                        }
                        else if((kb_Data[4] & kb_5) && size >= 6){
                            loc = 5;
                            break;
                        }
                        else if((kb_Data[5] & kb_3) && size >= 4){
                            loc = 3;
                            break;
                        }
                        // gfx_SetTextXY(200, 200);
                        // gfx_PrintInt(kb_Data[6] != kb_Enter, 1);
                    } while(kb_Data[6] != kb_Enter);
                    // gfx_PrintInt(i, 2);
                }
            }
            //pressed menu, no need to update
            //triggers whenever there is a scene change 
            backgroundDrawn = false;
            
            continue;
        }
        /* Check if any arrows are pressed */
        else if (kb_Data[7]) {
            //check if player has crossed border, if so, prepare to update stuff
            //my head hurts and I'm losing my sanity
            //cases: check for border
            //then check based off of each map... (include map data in custom array)
            
            //create player test move function, return values:
            //0 if can move
            //1 if hit top wall
            //2 if hit bottom wall
            //3 if hit left wall
            //4 if hit right wall
            //5 if hit border
            uint8_t checkMove = player.canMove(((kb_Data[7] & kb_Right) != 0) - ((kb_Data[7] & kb_Left) != 0), ((kb_Data[7] & kb_Down) != 0) - ((kb_Data[7] & kb_Up) != 0));
            switch(checkMove) {
                case 0:
                break;
                case 1:

                break;
                case 2:

                break;
                case 3:

                break;
                case 4:

                break;
                case 5:
                continue;
            }
            gfx_Sprite(behind_sprite, player.x, player.y);
            //handle movement, update xy
            //check for move technically allows for diagonal movement (sorta)
            //dbg_printf("%u\n", (kb_Data[7] & kb_Up));
            //move x, y
            //down +y 
            //up -y
            //
            player.move(((kb_Data[7] & kb_Right) != 0) - ((kb_Data[7] & kb_Left) != 0), ((kb_Data[7] & kb_Down) != 0) - ((kb_Data[7] & kb_Up) != 0),
            behind_sprite);

            /* Render the sprite */
            //playerFirstDrawn = false;
        }
        
        //region
        //do special event:
        switch(player.loc) {
            case 0:
            
            break;
            case 1:
            
            break;
            case 2:
            
            break;
            case 3:
            
            break;
            case 4:
            
            break;
            case 5:
            
            break;
            case 6:
            
            break;
            case 7:
            
            break;
            case 8:
            
            break;
        }
        //endregion
        //Draw player sprite (only if not move)...
        //no need to check if player has moved here as checks will be done above (use continue if found that player cannot move.); 
        //gfx_Sprite(behind_sprite, player.x, player.y); why is this here???????

    }
    //player coordinates are updated based on the top left corner...

    /* End graphics drawing */
    gfx_End();
    return 0;
    //rgb(220,220,220)
    //grey
    
}
//Last line is (320, 240)
