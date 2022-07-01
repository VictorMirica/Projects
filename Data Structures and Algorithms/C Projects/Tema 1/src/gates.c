#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    uint64_t mask = (1 << i);
    if((nr & mask)!=0){
        res = 1;
    }else res = 0;

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    uint64_t mask = ((uint64_t)1 << i);
    res = (nr ^ mask);

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    uint64_t mask = ((uint64_t)1 << i);
    res = (nr | mask);

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    uint64_t mask = ~((uint64_t)1 << i);
    res =(nr & mask);

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    res = nand_gate(nand_gate(a,b), nand_gate(a,b));

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    res = nand_gate(nand_gate(a,a), nand_gate(b,b));

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    res = nand_gate(nand_gate(a,nand_gate(a,b)), nand_gate(b,nand_gate(a,b)));

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    uint8_t sum; 
    uint8_t carry;

    sum = xor_gate(xor_gate(a,b), c);
    carry = or_gate(and_gate(a,b), and_gate(c, xor_gate(a,b)));

    if ((sum == (uint8_t)0) & (carry == (uint8_t)0)){
        res = (uint8_t)0;
    }  
    if ((sum == (uint8_t)1) & (carry == (uint8_t)0)){
        res = (uint8_t)1;
    }
    if ((sum == (uint8_t)1) & (carry == (uint8_t)1)){
        res = (uint8_t)2;
    }
    if ((sum == (uint8_t)0) & (carry == (uint8_t)1)){
        res = (uint8_t)3;
    }

    
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    

    res =(uint64_t)0;
    uint8_t c =(uint8_t)0;

    for(uint64_t i =(uint64_t)0; i <=(uint64_t)63; i++){

        if(res == (a+b)){
            break;
        }

        uint8_t bit1 = get_bit(a, i);
        uint8_t bit2 = get_bit(b, i);
        
        if(full_adder(bit1,bit2,c) == (uint8_t)0){
            c=(uint8_t)0;
            continue;
        }
        if(full_adder(bit1,bit2,c) == (uint8_t)1){
            res = activate_bit(res,i);
            c=(uint8_t)0;
            continue;
        }
        if(full_adder(bit1,bit2,c) == (uint8_t)2){
            res = activate_bit(res,i);
            c=(uint8_t)1;
            continue;
        } 
        if(full_adder(bit1,bit2,c) == (uint8_t)3){
            c=(uint8_t)1;
            continue;
        } 
        
    }

    if (c==(uint8_t)1){
        return 0 ;
    }

    return res;
}

