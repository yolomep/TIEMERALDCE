# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 366 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp" 2
# 17 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/gfx.h" 1




extern "C" {



# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/global_palette.h" 1




extern "C" {



extern unsigned char global_palette[26];


}
# 9 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/gfx.h" 2

# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/logo.h" 1




extern "C" {






extern unsigned char logo_data[402];


}
# 11 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/gfx.h" 2
# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/sprite.h" 1




extern "C" {






extern unsigned char sprite_data[102];


}
# 12 "C:\\CEdev\\examples\\TiEmeraldCE\\src/gfx/gfx.h" 2


}
# 18 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp" 2

# 1 "C:\\CEdev\\examples\\TiEmeraldCE\\src/extraData.h" 1






uint8_t mapBoundary[] = {
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000
};
# 37 "C:\\CEdev\\examples\\TiEmeraldCE\\src/extraData.h"
int8_t wildgrass[][] = {
    {},
}
# 20 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp" 2





struct PokeData{



 uint8_t stats[202*(6 + 2 + 2 + 2)];



    uint8_t evo[202*2];
# 56 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
    uint16_t nameIndex[203];

 char name[];
};


struct MoveLearn{

    uint16_t index[203];

    int16_t data[9614];






};

struct MoveData{
 uint16_t index[359];
    char name[3180];
    int8_t data[2506];
};

struct WildLoc{


 uint16_t index[65*6];
    uint8_t location[1777];
};

struct PlayerSave {

    char name[15];
    uint32_t money;
    uint16_t loc;
    uint16_t x;
    uint16_t y;
    uint8_t badges;
    uint8_t events[36];
    uint8_t pokedex[202];
    uint16_t items[350];
    bool gender;



    uint8_t data8[6*(1 + 6 + 1 + 1 + 1 + 6)];
    uint16_t data16[6*(1 + 1 + 4 + 1 + 1)];
# 114 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
};


WildLoc wildloc;
PokeData pokedata;
MoveData movedata;
MoveLearn movelearn;

class Move {
public:
    uint16_t index;
    char *name;
    uint8_t power, accuracy;
    uint16_t effect;
    uint8_t type;
    uint8_t category;
    uint8_t flags;
    uint8_t secondaryEffectChance;
    uint8_t target;
    int8_t priority;



    Move(uint16_t index);
    Move() : index{404} {

    }
};

Move::Move(uint16_t index) {
    if(index == 404) {
        this-> index = 404;
        return;
    }

    char temp[15];
    for(int i = movedata.index[index]; i < movedata.index[index + 1]; i++){
        temp[i - movedata.index[index]] = movedata.index[i];
    }
    index *= 7;
    effect = movedata.data[index];
    power = movedata.data[index + 1];
    accuracy = movedata.data[index + 2];


    target = movedata.data[index + 3] & ((1 << 2) - 1);
    category = movedata.data[index + 4] & ((1 << 2) - 1);
    flags = movedata.data[index + 3] >> 2;
    type = movedata.data[index + 4] >> 2;
    secondaryEffectChance = movedata.data[index + 5];
    priority = movedata.data[index + 6];
}

class Pokemon {
public:
    char *name;
    uint8_t evs[6];
    uint8_t ivs[6];
    uint8_t base[6];
    int16_t hp;


    char status;


    bool vol[12];

    uint8_t turns[2];
    uint16_t xp;
    uint8_t level;
    uint16_t nextXp;
    Move moves[4];
    bool isShiny;
    uint8_t color;
    uint16_t ability;
    uint8_t nature;
    uint8_t boosts[6];
    uint8_t dex;
    uint16_t heldItem;
    Pokemon(uint8_t dex, uint8_t ivs[], uint8_t base[], uint8_t level, Move moves[], bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[]);
    Pokemon(uint8_t dex, uint8_t ivs[], uint8_t evs[], uint8_t base[], uint8_t level, uint16_t xp, Move moves[], bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[]);
    Pokemon() : level(101) {

    }
    bool addxp(uint16_t i);
};

bool Pokemon::addxp(uint16_t i){
 xp += i;

}

Pokemon::Pokemon(uint8_t dex, uint8_t ivs[], uint8_t evs[], uint8_t base[], uint8_t level, uint16_t xp, Move moves[], bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[], uint16_t heldItem) :
 level(level), xp(xp), isShiny(isShiny), color(color), ability(ability), nature(nature), dex(dex), heldItem(heldItem) {

 for(int i = 0; i < 6; i++){
  this->ivs[i] = ivs[i];
  this->base[i] = base[i];
        this->evs[i] = evs[i];
 }
 for(int i = 0; i < 4; i++){
  this->moves[i] = moves[i];
 }
    this->name = name;
}

Pokemon::Pokemon(uint8_t dex, uint8_t ivs[], uint8_t base[], uint8_t level, Move moves[], bool isShiny, uint8_t color, uint16_t ability, uint8_t nature, char name[])
: level(level), isShiny(isShiny), color(color), ability(ability), nature(nature), name(name), dex(dex){


 for(int i = 0; i < 6; i++){
  this->ivs[i] = ivs[i];
  this->base[i] = base[i];
 }
 for(int i = 0; i < 4; i++){
  this->moves[i] = moves[i];
 }
    memset(evs, 0, 6);
    this->name = name;
}

class Trainer {
public:
    char *name;

    uint8_t style;
    Pokemon team[6];
    uint16_t id;
    uint16_t loc = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    bool gender;
    void move(uin8t_t x, uint8_t y);
};

Trainer::move(int8_t x, int8_t y){
    this->x += 6*x;
    this->y += 6*y;
}

class Player : public Trainer {
public:
    unsigned int money = 0;
    uint8_t badges = 0;
    uint8_t events[36];
    bool pokedex[202];
    uint16_t items[350];

};





Player player = Player();
gfx_sprite_t *behind_sprite = gfx_MallocSprite(6, 6);


void printCentered(const char *str, int height) {
    gfx_PrintStringXY(str, (LCD_WIDTH - gfx_GetStringWidth(str)) / 2, height);
}


void copy(uint16_t a[], uint16_t b[], int size){

    for(int i = 0; i < size; i++) {
        a[i] = b[i];
    }

}

void copy(uint8_t a[], uint8_t b[], int size){

    for(int i = 0; i < size; i++) {
        a[i] = b[i];
    }

}


double type(int m, int t){
    int32_t i = 18 * m + t;
    i = ("J:2JJJ;YQJV>N:;ZIJJ5&ZJZ*[Y;KJVF;KZJ6I6YN>HJNJNFJZ:EYZJ:[UZIJ^J7JI:]9=JIZBJ>IINK:JFBZN:U:KJJ:JJ+FJNJN6NI:IJO"[i / 3] - 32) >> i % 3 * 2 & 3;
    return (i + i/3)/2.;
}

int bisect(int lo, int high, uint8_t a[], int x){
 while(lo < high) {
  int mid = (lo + high)/2;
  if(x < a[mid]) high = mid;
  else lo = mid + 1;
 }
 return lo;
}

Pokemon pokemonFactory(uint8_t pdex, uint8_t level) {



    uint8_t ivs[6];
    uint8_t base[6];
    uint8_t evs[6];
    Move moves[4];
    bool isShiny = randInt(0, 2048) <= 1;
    uint16_t location = 12*pdex;
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







    uint8_t shift = 0;
    for(int i = movelearn.index[pdex]; i < movelearn.index[pdex + 1]; i++){


        if((movelearn.data[i] >> 9) > level) break;

        if(randInt(0, 10) <= 9){
            moves[shift] = Move(movelearn.data[i] & ((1 << 9) - 1));

        }

        shift = (shift + 1) % 4;
    }

    return Pokemon(pdex, ivs, base, level, moves, isShiny, pokedata.stats[location + 8 + isShiny], ability, randInt(0, 24), name);
}
# 372 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
Pokemon genWild(uint8_t loc, uint8_t type = 0) {
# 381 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
 if(false) return Pokemon();
 if(type < 2) {
        uint16_t beginIndex;
        uint16_t endIndex;
        if(type == 0) {

            beginIndex = wildloc.index[6*loc];
            endIndex = wildloc.index[6*loc + 1];
        }
        else {
            beginIndex = wildloc.index[6*loc + 2];
      endIndex = wildloc.index[6*loc + 3];
        }
  if(endIndex == 0) {

   return Pokemon();
  }






  uint8_t number = (endIndex - beginIndex)/4;
  static uint8_t prob[44];
  prob[0] = wildloc.index[beginIndex + 3];
  for(uint8_t i = 1; i < number; i++){
   prob[i] = prob[i - 1] + wildloc.index[beginIndex + 4*i + 3];
  }
  uint8_t rand = randInt(0, 100);
  uint8_t index = bisect(0, number, prob, rand);

  return pokemonFactory(wildloc.index[beginIndex + 4*index], randInt(wildloc.index[beginIndex + 4*index + 1],
                          wildloc.index[beginIndex + 4*index + 2]));
 }
 else {
  uint16_t beginIndex = wildloc.index[6*loc + 4];
  uint16_t endIndex = wildloc.index[6*loc + 5];
  if(endIndex == 0) {
   return Pokemon();
  }
# 430 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
        uint8_t number = 0;
        static uint8_t rodList[27*4];
        static uint8_t prob[27];


        for(int i = beginIndex; i < endIndex; i += 5){

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

 return Pokemon();
}

void battleTrainer(Trainer trainer){

}

void battleWild(Pokemon wildmon){

}
# 481 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
void drawMap(uint8_t location){
    gfx_ZeroScreen();

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

uint8_t menu(const char *title, const char* choices[], uint8_t size){
# 516 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
    gfx_SetTextScale(1, 2);
    printCentered(title, 10);
    uint8_t loc = 0;
    for(uint8_t i = 0; i < size; i++){
        char text[45];
        sprintf(text, "[%d] ", i);
        strcat(text, choices[i]);
        gfx_PrintStringXY(text, 40, 20*i + 30);;
    }
    gfx_SetColor(255);
    gfx_PrintStringXY(">", 20, 30);;

    do{






        kb_Scan();


        while (!os_GetCSC());



        if(kb_Data[7] & kb_Down){



            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);

            loc++;
            if (loc == size){
                loc = 0;
            }

            gfx_PrintStringXY(">", 20, 30 + loc*20);;
        }
        else if(kb_Data[7] & kb_Up){


            gfx_FillRectangle_NoClip(20, 30 + loc*20, 10, 20);

            loc--;
            if(loc < 0){
                loc = size - 1;
            }

            gfx_PrintStringXY(">", 20, 30 + loc*20);;

        }
        else if(kb_Data[3] & kb_0){

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


    } while(kb_Data[6] != kb_Enter);

    gfx_SetTextScale(1, 1);
    return loc;

}





int main(void) {



 ti_var_t wildLoc = ti_Open("WildLoc", "r");
 ti_var_t pokeData = ti_Open("PokeData", "r");
 ti_var_t moveData = ti_Open("MoveData", "r");
    ti_var_t moveLearn = ti_Open("MoveLearn", "r");
 if(!wildLoc || !pokeData || !moveData || !moveLearn) {
  if(!wildLoc) {
   os_PutStrFull("Could not find or locate WildLoc.8xv");
  }
  if(!pokeData) {
   os_PutStrFull("Could not find or locate PokeData.8xv");
  }
  if(!moveData) {
   os_PutStrFull("Could not find or locate MoveData.8xv");
  }
        if(!moveLearn) {
            os_PutStrFull("Could not find or locate MoveLearn.8xv");
        }
  while(!os_GetCSC());
  return 1;
 }
    ti_Read(&wildloc, sizeof(WildLoc), 1, wildLoc);
    ti_Read(&pokedata, sizeof(PokeData), 1, pokeData);
    ti_Read(&movedata, sizeof(MoveData), 1, moveData);
    ti_Read(&movelearn, sizeof(MoveLearn), 1, moveLearn);
    gfx_Begin();


    uint8_t char_data2[] = {0x00, 0x00, 0x08, 0x1C, 0x26, 0x43, 0x81, 0xFF};
    uint8_t char_data3[] = {0x3A, 0x7E, 0xC4, 0xC4, 0xC4, 0xCD, 0x7F, 0x32};

    gfx_SetCharData(2, char_data2);
    gfx_SetCharData(3, char_data3);


    gfx_FillScreen(0);
    gfx_SetTextFGColor(9);
    gfx_SetTextBGColor(0);





    gfx_SetPalette(global_palette, 26, 0);
    goto skip;

    while(!os_GetCSC());




    printCentered("\x03 V 0.02", 80);
    printCentered("(C) 1995-2005 GAMEFREAK inc.", 90);
    printCentered("(C) 2005 POKeMON", 100);
    printCentered("(C) 1995-2005 Nintendo", 110);
    printCentered("(C) 2020-2021 T.J. CODES", 120);
    printCentered("ALL RIGHTS RESERVED", 130);
    printCentered("PRESENTS", 140);





    while (!os_GetCSC());

    gfx_FillScreen(255);
    gfx_ScaledTransparentSprite_NoClip(((gfx_sprite_t*)logo_data), 15, 15, 8, 8);


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
    printCentered("This is supposed to be the opening scene, but I", 60);
    printCentered("realized it cost too much memory. There are no", 70);
    printCentered("sprites in this game because there is no", 80);
    printCentered("memory for all the sprites. For more:", 90);
    printCentered("yolomep.github.io/EmeraldDeltaTi84pce", 100);
    gfx_SetTextBGColor(253);
    gfx_PrintStringXY("Quick overview of controls:", 10, 130);;
    gfx_PrintStringXY("Up is the up arrow. Down is the down", 10, 140);;
    gfx_PrintStringXY("arrow, etc. 2nd is the B button and Enter", 10, 150);;
    gfx_PrintStringXY("is the A button Other buttons (Mode, Alpha,", 10, 160);;
    gfx_PrintStringXY("y=, etc.) will represent start and select,", 10, 170);;
    gfx_PrintStringXY(" but they will be explained before use.", 10, 180);;
# 742 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
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
    timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
    uint32_t x = timer_Get(1);

    while(!os_GetCSC()) {
        uint32_t y = timer_Get(1);
        dbg_sprintf(dbgout, "timer %u\n", (y % 32768));
        if((y - x) % 32768 >= 17000){

            dbg_sprintf(dbgout, "he\n");
            gfx_FillRectangle_NoClip(60, 130, 100, 10);

        }
        else if((y - x) % 32768 >= 0) {
            dbg_sprintf(dbgout, "ha\n");
            printCentered("Press Enter to Start", 130);
        }
    }
    gfx_SetTextTransparentColor(255);
    uint8_t val = 0;
    {

        static const char* temp[] {"New", "Load", "Exit"};
        val = menu("Save or load game?", temp, 3);
    }
    if(val == 0) {
        printCentered("Remember to save by using the menu.", 30);
        printCentered("Press any button to continue.", 70);
        while (!os_GetCSC());
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



            for(int i = 0; i < 6; i++){
                uint8_t temp = 16*i;
                uint8_t pdex = saveFile.data8[temp];






                uint8_t tivs[6];
                uint8_t tevs[6];
                uint8_t tbase[6];
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


                player.team[i] = Pokemon(pdex, tivs, tevs, tbase, saveFile.data8[temp + 7], saveFile.data16[8*i], tmove,
                    saveFile.data8[temp + 9], (saveFile.data8[temp + 9] ? pokedata.stats[12*pdex + 9] : pokedata.stats[12*pdex + 8]),
                    saveFile.data16[8*i + 6], saveFile.data8[temp + 8], tname, saveFile.data16[8*i + 7]);
            }
            printCentered("Save Loaded Successfully!", 40);
        }
        else {
            printCentered("No Save Detected. Creating new game...", 30);

        }
        printCentered("Press any button to continue.", 70);
        while (!os_GetCSC());
    }
    else if(val == 2) {
        gfx_End();
        return 0;
    }

    bool backgroundDrawn = false;
    bool playerFirstDrawn = false;
    while(true){
# 861 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
        if(!backgroundDrawn) {
            drawMap(player.loc);
            backgroundDrawn = true;
        }

        gfx_GetSprite(behind_sprite, player.x, player.y);
        gfx_TransparentSprite(((gfx_sprite_t*)sprite_data), player.x, player.y);
        if(!playerFirstDrawn) {

            gfx_Sprite(behind_sprite, player.x, player.y);
            playerFirstDrawn = true;
        }



        kb_Scan();


        while (!os_GetCSC());

        if(kb_Data[1] & kb_2nd) {
            static const char* temp[] {"Back", "Quit", "Save", "Team", "Bag", "Fly"};
            uint8_t option = menu("Menu", temp, 6);
# 893 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
            switch(option) {
                case 0:
                break;
                case 1:
                    gfx_End();
                    return 0;
                case 2:
                    gfx_ZeroScreen();
                    printCentered("Saving...", 20);
                    PlayerSave saveFile;
                    saveFile.badges = player.badges;
                    saveFile.badges = player.badges;
                    saveFile.money = player.money;
                    saveFile.loc = player.loc;
                    saveFile.x = player.x;
                    saveFile.y = player.y;
                    saveFile.name = player.name;
                    copy(saveFile.events, player.events, 36);
                    copy(saveFile.items, player.items, 350);
                    for(int i = 0; i < 202; i++){
                        saveFile.pokedex[i] = player.pokedex[i];
                    }
                    for(int i = 0; i < 6; i++){
                        uint8_t temp = 16*i;
                        Pokemon pktemp = player.team[i];

                        saveFile.data8[temp] = pktemp.dex;
                        for(int j = 0; j < 6; j++) {
                            saveFile.data8[temp + j + 1] = pktemp.ivs[j];
                            saveFile.data8[temp + j + 10] = pktemp.evs[j];
                        }
                        for(int j = 0; j < 4; j++){
                            saveFile.data16[8*i + 2 + j] = pktemp.moves[j].index;
                        }
                        saveFile.data8[temp + 7] = pktemp.level;
                        saveFile.data8[temp + 9] = pktemp.isShiny;
                        saveFile.data8[temp + 8] = pktemp.nature;
                        saveFile.data16[8*i] = pktemp.xp;
                        saveFile.data16[8*i + 6] = pktemp.ability;
                        saveFile.data16[8*i + 7] = pktemp.heldItem;
                    }
                    printCentered("Save Successfully!", 40);
                    while(!os_GetCSC());;
                    break;
                case 3:
                    gfx_ZeroScreen();

            }


            backgroundDrawn = false;
            playerFirstDrawn = false;
            continue;
        }




        player.move((kb_Data[7] & kb_Down) - (kb_Data[7] & kb_Up), (kb_Data[7] & kb_Right) - (kb_Data[7] & kb_Left));
# 960 "C:\\CEdev\\examples\\TiEmeraldCE\\src\\main.cpp"
        gfx_Sprite(behind_sprite, player.x, player.y);

    }



    gfx_End();
    return 0;



}
