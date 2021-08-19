#include <tice.h>
#include "includes/extraData.h"
#include <stdlib.h>
#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>
#include <string.h>
#include <debug.h>
#include <format.h>
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
    // if(index == 404) {
    //     this-> index = 404;
    //     return;
    // }
    // //effect, power, accuracy, target + flags, category + type, secondaryEffectChance, priority
    // char temp[15]; //i think 13 is enough but...
    // for(int i = movedata.index[index]; i < movedata.index[index + 1]; i++){
    //     temp[i - movedata.index[index]] = movedata.index[i];
    // }
    // index *= 7;
    // effect = movedata.data[index];
    // power = movedata.data[index + 1];
    // accuracy = movedata.data[index + 2];
    // //target is last two bits of index + 3
    // //category is last two bits of index + 4
    // target = movedata.data[index + 3] & ((1 << 2) - 1);
    // category = movedata.data[index + 4] & ((1 << 2) - 1);
    // flags = movedata.data[index + 3] >> 2;
    // type = movedata.data[index + 4] >> 2;
    // secondaryEffectChance = movedata.data[index + 5];
    // priority = movedata.data[index + 6];
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
        //uint8_t te = evs[index]/4 + ivs[index];
        return 1; //te;
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
    // else if(move.effect == EFFECT_LEVEL_DAMAGE) {
    //     return attacker.level;
    // }
    // else if(move.effect == EFFECT_PSYWAVE) {
    //     return attacker.level * (10*randInt(5, 10) + 50)/100 + 1; //psywave is now random number from 5 to 10, not 0 to 10
    // }
    // else if(move.effect == EFFECT_PAIN_SPLIT) {
    //     return (attacked.hp - attacker.hp)/2;
    // }
    
    // else if((attacked.ability == ABILITY_FLASH_FIRE && move.type == FIRE_TYPE)||
    //     (attacked.ability == ABILITY_LIGHTNING_ROD && move.type == ELECTRIC_TYPE) 
    //     || (attacked.ability == ABILITY_WATER_ABSORB &&move.type == WATER_TYPE)
    //     || (attacked.ability == ABILITY_VOLT_ABSORB && move.type == ELECTRIC_TYPE) ||
    //     (attacked.ability == ABILITY_WONDER_GUARD && typeCalc(attacked, move.type) < 2)) {
    //     return 0;
    // }
    // else if(attacker.ability == ABILITY_CACOPHONY || attacker.ability == ABILITY_SOUNDPROOF){
    //     return 0;
    // }

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
    // else if(move.effect == EFFECT_FLAIL) {
    //     double hpPercentage = attacker.hp*100.0/attacker.getStat(0);
    //     if(hpPercentage > 68.74) move.power = 20;
    //     else if(hpPercentage > 55.41) move.power = 40;
    //     else if(hpPercentage > 30.82) move.power = 80;
    //     else if(hpPercentage > 10.41) move.power = 100;
    //     else if(hpPercentage > 4.16) move.power = 150;
    //     else move.power = 200;
    // }
    // else if(move.effect == EFFECT_RETURN || move.effect == EFFECT_FRUSTRATION) {
    //     move.power = move.effect - randInt(0, 30); //121+ - (0, 30)
    // }
    // else if(move.effect == EFFECT_PRESENT) { //set move.power after use? no, means AI cheating
    //     if(randInt(0, 10) > 5) {
    //         move.power = 120;
    //     }
    //     else if(randInt(0, 5) > 1) {
    //         move.power = 100;
    //     }
    //     else {
    //         move.power = 0;
    //     }
    // }
    // else if(move.effect == EFFECT_MAGNITUDE) {
    //     int percent = randInt(0, 100);
    //     if(percent < 5) {
    //         move.power = 10;
    //     }
    //     else if(percent < 10) {  
    //         move.power = 30;
    //     }
    //     else if(percent < 20) {
    //         move.power = 50;
    //     }
    //     else if(percent < 30) {
    //         move.power = 90;
    //     }
    //     else if(percent < 50) {
    //         move.power = 110;
    //     }
    //     else {
    //         move.power = 150;
    //     }
    // }
    int16_t damage = (2*attacker.level/5 + 2)*move.power*attacker.getStat(1)/attacked.getStat(2)/50;
    // if(2*attacker.hp < attacker.getStat(0)) {
    //      if((move.type == GRASS_TYPE && attacker.ability == ABILITY_OVERGROW) ||
    //         (move.type == FIRE_TYPE && attacker.ability == ABILITY_BLAZE) || 
    //         (move.type == WATER_TYPE && attacker.ability == ABILITY_TORRENT) ||
    //         (move.type == BUG_TYPE && attacker.ability == ABILITY_SWARM)
    //         ) {
    //         damage *= 2;
    //     }
    // }
    // if(attacker.ability == ABILITY_HUSTLE && move.category == CATEGORY_PHYSICAL) damage *= 1.5;
    // else if((attacker.ability == ABILITY_PURE_POWER || attacker.ability == ABILITY_HUGE_POWER) 
    //     && move.category == CATEGORY_PHYSICAL) damage *= 2;
    // //you can have blaze and eruption
    // if(move.effect == EFFECT_ERUPTION) {
    //     damage *= attacker.hp/attacker.getStat(0);
    // }
    // else if(move.effect == EFFECT_KNOCK_OFF && attacked.heldItem != 0) {
    //     damage *= 3/2;
    // } 
    // // //beat up damage = team damage
    // else if(move.effect == EFFECT_BEAT_UP) {
    //     damage *= conditions[2];
    // }
    // else if(move.effect == EFFECT_FACADE && attacker.status != '0'){
    //     damage *= 2;
    // }
    // if(move.category == CATEGORY_SPECIAL && ((attacker.ability == ABILITY_PLUS && (attacked.ability == ABILITY_MINUS || 
    // attacked.type[0] == ELECTRIC_TYPE || attacked.type[1] == ELECTRIC_TYPE))
    //     || (attacker.ability == ABILITY_MINUS && (attacked.ability == ABILITY_PLUS || attacked.type[0] == STEEL_TYPE || 
    //     attacked.type[1] == STEEL_TYPE)))) {
    //     damage *= 1.5;
    // }
    // //add something about charge
    // damage += 2;
    // if(conditions[0] == SUN_CONDITION) {
    //     if(move.effect == EFFECT_WEATHER_BALL) {
    //         move.type = FIRE_TYPE;
    //         damage = (damage - 2)*2 + 2;
    //     }
    //     if(move.type == FIRE_TYPE) damage *= 3/2;
    //     else if(move.type == WATER_TYPE) damage *= 2/3;
    // }
    // else if(conditions[0] == RAIN_CONDITION){
    //     if(move.effect == EFFECT_WEATHER_BALL) {
    //         move.type = WATER_TYPE;
    //         damage = (damage - 2)*2 + 2;
    //     }
    //     if(move.type == WATER_TYPE) damage *= 3/2;
    //     else if(move.type == FIRE_TYPE) damage *= 2/3;
    // }
    // else if(conditions[0] == HAIL_CONDITION) {
    //     if(move.effect == EFFECT_WEATHER_BALL) {
    //         move.type = ICE_TYPE;
    //         damage = (damage - 2)*2 + 2;
    //     }
    // }
    // else if(conditions[0] == SAND_CONDITION) {
    //     if(move.effect == EFFECT_WEATHER_BALL) {
    //         move.type = ROCK_TYPE;
    //         damage = (damage - 2)*2 + 2;
    //     }
    // }
    // else {
    //     if(move.effect == EFFECT_WEATHER_BALL) {
    //         move.type = NORMAL_TYPE;
    //     }
    // }
    // damage *= (1 + conditions[1])*randInt(85, 100)/100*attacker.isStab(move.type)*typeCalc(attacked, move.type); 
    // //don't implement randomness before hand to increase randomness
    // if(move.category == CATEGORY_PHYSICAL && attacker.status == '3') {
    //     damage /= 2;
    // }
    // //other damage...
    // if(attacked.ability == ABILITY_MARVEL_SCALE && attacked.status != '0' && move.category == CATEGORY_PHYSICAL){
    //     damage *= 2/3;
    // }

    // if(move.effect == EFFECT_FALSE_SWIPE) {
    //     if(attacked.hp - damage < 1) {
    //         return attacked.hp - 1;
    //     }
    // }

    // if(attacked.ability == ABILITY_THICK_FAT && (move.type == FIRE_TYPE || move.type == ICE_TYPE)) damage /= 2;

    return damage;
}


int main() {

}