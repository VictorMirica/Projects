#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    /* TODO */
    res = (uint16_t)0;
    int count = 0;

    for(uint64_t i = (uint64_t)0; i <= (uint64_t)63; i++){
        uint64_t mask = ((uint64_t)1 << i);
        if((memory & mask)!=0){
        count++;
        }else (count = 0);

        if(count == 5){
            for (uint16_t j = (uint16_t)1; j <= (uint16_t)16; j++){
                uint64_t mask2 = ((uint64_t)1 << (i+j));

                if((memory & mask2)!=0){
                    res = (res | ((uint16_t)1 << (j-1)));
                }
            }
            break;
        }
    }
    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    /* TODO */
    res = (uint16_t)0;
    int count = 0;

    for(uint64_t i = (uint64_t)63; i >= (uint64_t)0; i--){
        uint64_t mask = ((uint64_t)1 << i);
        if((memory & mask)!=0){
        count++;
        }else (count = 0);

        if(count == 3){
            for (uint16_t j = (uint16_t)1; j <= (uint16_t)16; j++){
                uint64_t mask2 = ((uint64_t)1 << (i-j));

                if((memory & mask2)!=0){
                    res = (res | ((uint16_t)1 << (16-j)));
                }
            }
            break;
        }
    }

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    /* TODO */
    
    res = (uint16_t)0;

     for(uint16_t i = (uint16_t)0; i <= (uint16_t)15; i++){
        uint16_t mask = ((uint16_t)1 << i);
        if((spell & mask)!=0){
    
            if((key & mask)!=0){
                continue;
            }else (res = (res | mask));

        }else{

            if((key & mask)!=0){
                res = (res | mask);
            }else continue;
        }
    }
    
    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */

    res =(uint32_t)0;
    int human=0;
    int monster=0;
    int count=0;
    

    for(uint16_t i=(uint16_t)0; i<=(uint16_t)15;i++){

        uint16_t mask = ((uint16_t)1 << i);
        if((enemy & mask)!=0){
        count++;
        }
    }

    if(count%2==0){
        monster=1;
    }else {
        human=1;
    }

    

    if(monster){   
        res = (res | ((uint32_t)1 << (uint32_t)31));
        res = (res | ((uint32_t)1 << (uint32_t)28));
            
        }

    if(human){
        res = (res | ((uint32_t)1 << (uint32_t)30));
        res = (res | ((uint32_t)1 << (uint32_t)29));
        }


    uint16_t value=(uint16_t)0;


    if(human){
        value = (~(enemy) + (uint16_t)1);
    }

    if(monster){
        uint16_t oneMinusEnemy=(uint16_t)0;

        oneMinusEnemy = (~(enemy) + (uint16_t)1 + (uint16_t)1);

        value = (enemy & oneMinusEnemy);
    }

    for(uint16_t i=(uint16_t)0; i<=(uint16_t)15;i++){
        uint16_t mask = ((uint16_t)1 << i);
        if((value & mask)!=0){
            res = (res | mask);
        }

    }

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    /* TODO */

    uint16_t highAntibodies;
    res= (uint16_t)0;

    highAntibodies = cocktail;
    
    for(uint32_t i=(uint32_t)31; i>=(uint32_t)16; i--){
        uint32_t mask = ((uint32_t)1<< (i-16));

        if((mask & highAntibodies) != 0){
            res = (res | (uint32_t)1 << i);
        }
    }
    


    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;

    /* TODO */

    if (map == UINT64_MAX){

        return 2;
    }

    int count = 0;
    int flag = 0;
    for(uint64_t i=0; i<64; i++){

        uint64_t mask = ((uint64_t)1 << i);
        if((map & mask) != 0){
            count++;
            if(count>4){
                flag = 1;
                break;
            }
        }else{
            if((count != 4) && (count != 0)){
                flag =1;
                break;
            }
            count = 0;
        }

    }
    if(!flag){
        return 0;
    }


    if(map == ((uint64_t)6442450944)){
        return 1;
    }

    return 3;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */

    int indexWitcher = -1;
    int indexPortal = -1;

    for(uint32_t i=0; i<32; i++){
        uint32_t mask = ((uint32_t)1 << i);
        if((map & mask)!=0){
            if(indexWitcher != -1){
                indexPortal = i;
                break;
           }

            indexWitcher = i;
            continue;
        }

    }

    res = (indexPortal - indexWitcher);
    return res;
}
