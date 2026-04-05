#include "BusInOut.hpp"

// Declear signal pins of Instruction Decoder.
const int selectB = 0;
const int selectA = 1;
const int _LOAD0 = 2;
const int _LOAD1 = 3;
const int _LOAD2 = 4;
const int _LOAD3 = 5;
BusInOut output(_LOAD3, _LOAD2, _LOAD1, _LOAD0, selectA, selectB);
const int op3 = 6;
const int op2 = 7;
const int op1 = 8;
const int op0 = 9;
const int cFlag = 10;
BusInOut input(cFlag, op0, op1, op2, op3);

#define BITS2BYTE(b5,b4,b3,b2,b1,b0) \
 ((b5<<5)|(b4<<4)|(b3<<3)|(b2<<2)|(b1<<1)|(b0<<0))

#define L 0
#define H 1

const int expValue[32] = {
    BITS2BYTE(L, L, L, H, H, H),  /* ADD A, Im */
    BITS2BYTE(L, L, L, H, H, H),  /* ADD A, Im */
    BITS2BYTE(L, H, L, H, H, H),  /* MOV A, B  */
    BITS2BYTE(L, H, L, H, H, H),  /* MOV A, B  */
    BITS2BYTE(H, L, L, H, H, H),  /* IN  A     */
    BITS2BYTE(H, L, L, H, H, H),  /* IN  A     */
    BITS2BYTE(H, H, L, H, H, H),  /* MOV A, Im */
    BITS2BYTE(H, H, L, H, H, H),  /* MOV A, Im */
    BITS2BYTE(L, L, H, L, H, H),  /* MOV B, A  */
    BITS2BYTE(L, L, H, L, H, H),  /* MOV B, A  */
    BITS2BYTE(L, H, H, L, H, H),  /* ADD B, Im */
    BITS2BYTE(L, H, H, L, H, H),  /* ADD B, Im */
    BITS2BYTE(H, L, H, L, H, H),  /* IN  B     */
    BITS2BYTE(H, L, H, L, H, H),  /* IN  B     */
    BITS2BYTE(H, H, H, L, H, H),  /* MOV B, Im */
    BITS2BYTE(H, H, H, L, H, H),  /* MOV B, Im */
    -1,                           /* N/A       */
    -1,                           /* N/A       */
    BITS2BYTE(L, H, H, H, L, H),  /* OUT B     */
    BITS2BYTE(L, H, H, H, L, H),  /* OUT B     */
    -1,                           /* N/A       */
    -1,                           /* N/A       */
    BITS2BYTE(H, H, H, H, L, H),  /* OUT Im    */
    BITS2BYTE(H, H, H, H, L, H),  /* OUT Im    */
    -1,                           /* N/A       */
    -1,                           /* N/A       */
    -1,                           /* N/A       */
    -1,                           /* N/A       */
    BITS2BYTE(H, H, H, H, H, L),  /* JNC (C=0) */
    BITS2BYTE(H, H, H, H, H, H),  /* JNC (C=1) */
    BITS2BYTE(H, H, H, H, H, L),  /* JMP       */
    BITS2BYTE(H, H, H, H, H, L),  /* JMP       */
};

void printResult(int numOfTest, int numOfPass)
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("Finish all test case.");
    Serial.print("The number of test cases is ");
    Serial.print(numOfTest);
    Serial.print(".\nThe pass rate is ");
    Serial.print(((double)numOfPass/numOfTest) * 100.0);
    Serial.println("\%");
    Serial.println("==============================");
}

void setup() {
    Serial.begin(115200);

    output.setMode(INPUT);
    input.setMode(OUTPUT);
}


void loop() {

    int numOfPass = 0;
    for(int i = 0; i < 32; i++)
    {
        input.write(i);
        int val = output.read();
        if( val == expValue[i] )
        {
            Serial.print("[ PASS ]");
            numOfPass++;
        }
        else if( expValue[i] == -1 )
        {
            Serial.print("[ SKIP ]");
            numOfPass++;
        }
        else
        {
            Serial.print("[ FAIL ]");
        }
        Serial.print(" input signal : ");
        Serial.print(i, BIN);
        Serial.print(" output signal : ");
        Serial.println(val, BIN);
    }
    printResult(32, numOfPass);
    delay(5000);
}