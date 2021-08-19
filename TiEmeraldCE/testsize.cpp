#include <tice.h>

#include <iostream>

using namespace std;

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
//A pokemon would contain a name, evs, and ivs
class Pokemon {
public:
    char *name; 
    uint8_t evs[6]; //theres a reason why evs are masx 255
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
    uint8_t type[2];
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
};

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

int main() {
    cout << sizeof(Pokemon);
}