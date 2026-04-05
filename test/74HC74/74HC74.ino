#include "BusInOut.hpp"
//#include "pwm.h"

// Declear signal pins of 74HC74.
const int Q = 0;
const int D = 1;
const int _CLR = 2;
// クロックは CUPIO に取り付けたオシレータで入力するので不要。
//const int ck = 11;
//PwmOut pwm(ck);

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

    pinMode(Q, INPUT);
    pinMode(D, OUTPUT);
    pinMode(_CLR, OUTPUT);

    digitalWrite(_CLR, HIGH);
    //74HC74(本物)をテストする場合のクロック入力
    //pwm.begin((float)100000.0,(float)50.0);
}


void loop() {

    int numOfPass = 0;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                do
                {
                    // step 0 : Set _CLR pin
                    digitalWrite(_CLR, k);
                    // step 1 : Set t0 state
                    digitalWrite(D, i);
                    delayMicroseconds(50);
                    if(digitalRead(Q) != k ? i : 0)
                    {
                        Serial.print("[ FAIL ] : Q pins not set to ");
                        Serial.print(i);
                        Serial.print(".");
                        break;
                    }

                    // step 2 : Set t1 state
                    digitalWrite(D, j);
                    delayMicroseconds(50);
                    if(digitalRead(Q) != k ? j : 0)
                    {
                        Serial.print("[ FAIL ] : Q pins not set to ");
                        Serial.print(j);
                        Serial.print(".");
                        break;
                    }
                    Serial.print("[ PASS ]");
                    numOfPass++;
                } while (0);
                Serial.print(" 1st input signal : ");
                Serial.print(i);
                Serial.print(". 2nd input signal : ");
                Serial.print(j);
                Serial.print(". _CLR signal : ");
                Serial.print(k);
                Serial.print(". Output : ");
                Serial.println(digitalRead(Q));
            }
        }
    }
    printResult(2 * 2 * 2, numOfPass);
    delay(5000);
}