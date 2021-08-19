#ifndef _TICE_H
#include <tice.h>
#endif

#define _TRAINER_H

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