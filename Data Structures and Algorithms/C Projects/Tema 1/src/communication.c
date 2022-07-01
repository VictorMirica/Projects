#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch(18);
    send_squanch(9);
    send_squanch(3);
    send_squanch(11);
}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
   for(int i = 0; i < 5; i++){
       uint8_t encodedChar =recv_squanch();
       for(int j = 1; j < 27 ;j++){
           if (encodedChar == j){
            char c ='A';
            fprintf(stdout, "%c",(c+(j-1)));
           }
       }
   }
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
    uint8_t v[10];
    int i;
    int j;
    for (i=0;i<10;i++){
        v[i] = recv_squanch();
    }
    for(i=0;i<10;i++){
        for(j=0;j<2;j++){
            send_squanch(v[i]);
        }
    }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
    send_squanch(232); 

    /*
    * length = 10 -> 10 in baza 2 = 1010, codificat 11(1010)00 = 232
    */

    send_squanch(8);
    send_squanch(5);
    send_squanch(12);
    send_squanch(12);
    send_squanch(15);
    send_squanch(20);
    send_squanch(8);
    send_squanch(5);
    send_squanch(18);
    send_squanch(5);


}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
    uint8_t decoded_len = 0;
    int i;
    uint8_t len = recv_squanch();

    len = len << 2;
    len = len >> 4;
    for(i=0; i<4; i++){
        uint8_t mask = (1 << i);
        if((len & mask) == 0){
            continue;
        }
        if(i==0){
            decoded_len += 1;
            continue;
        }
        int pow = 1;
        for(int j=1; j<=i ;j++){
        pow = pow * 2;
        }
        decoded_len += pow;
    }

    char length[2];
    sprintf(length, "%d", decoded_len);
    for(i=0; i<=1; i++){
        fprintf(stdout, "%c", length[i]);
    }


    for(int i = 0; i < decoded_len; i++){
       uint8_t encodedChar =recv_squanch();
       for(int j = 1; j < 27 ;j++){
           if (encodedChar == j){
            char c ='A';
            fprintf(stdout, "%c", (c+(j-1)) );
           }
       }
   }
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    uint8_t decoded_len = 0;
    uint8_t len = recv_squanch();

    len = len << 2;
    len = len >> 4;
    for(int i=0; i<4; i++){
        uint8_t mask = (1 << i);
        if((len & mask) == 0){
            continue;
        }
        if(i==0){
            decoded_len += 1;
            continue;
        }
        int pow = 1;
        for(int j=1; j<=i ;j++){
        pow = pow * 2;
        }
        decoded_len += pow;
    }
    
    for (int i = 0; i<(decoded_len-1);i++){
        uint8_t ignoredLetter = recv_squanch();
    }
    char lastLetter = recv_squanch();
    char decodedLastLetter;

    for(int j = 1; j < 27 ;j++){
           if (lastLetter == j){
            char c ='A';
            decodedLastLetter = (c+(j-1));
           }
    }

    if((decodedLastLetter) == 'P'){
        send_squanch(232);
        /*
        * length = 10 -> 10 in baza 2 = 1010, codificat 11(1010)00 = 232
        */
        send_squanch(16);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);
        send_squanch(12);
        send_squanch(5);
        send_squanch(18);
        send_squanch(9);
        send_squanch(3);
        send_squanch(11);

    }else{
        send_squanch(236);
        /*
        *   length = 11 -> 11 in baza 2 = 1011, codificat 11(1011)00 = 236
        */
        send_squanch(22);
        send_squanch(9);
        send_squanch(14);
        send_squanch(4);
        send_squanch(9);
        send_squanch(3);
        send_squanch(1);
        send_squanch(20);
        send_squanch(15);
        send_squanch(18);
        send_squanch(19);

    }
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t newByte = 0;
    for (int i=3; i>=0; i--){
        if((c1 & (1 << i)) != 0){
            newByte = (newByte | (1<<((2*i)+1)));    
        }

        if((c2 & (1 << i)) != 0){
            newByte = (newByte | (1<<(2*i)));
        }
    }
    send_squanch(newByte);
}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */

    res =0;

    for(int i =7; i>0; i=i-2){
        if((c & (1 << i)) != 0 ){
            switch (i)
            {
            case 7:
                res = (res | (1 << 7));
                break;
            case 5:
                res = (res | (1 << 6));
                break;
            case 3:
                res = (res | (1 << 5));
                break;
            case 1:
                res = (res | (1 << 4));
                break;
            default:
                break;
            }
        }
    }

    for(int i=6; i>=0; i=i-2){
        if((c & (1  << i)) != 0){
            res = (res | (1 << (i/2)));
        }
    }

    return res;
}
