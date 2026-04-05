#include "BusInOut.hpp"

BusInOut outPin(0,1,2,3);
BusInOut inA(5,6,7,8);
BusInOut inB(9,10,11,12);

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

    outPin.setMode(INPUT);
    inA.setMode(OUTPUT);
    inB.setMode(OUTPUT);
    pinMode(4, INPUT);
}

void loop() {
    int numOfPass = 0;
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            inA.write(i);
            inB.write(j);

            if((((i + j) % 16) == outPin.read())
                 && ((0 < ((i + j) / 16)) == digitalRead(4)))
            {
                Serial.print("[ PASS ]");
                numOfPass++;
            }
            else
            {
                Serial.print("[ FAIL ]");
            }

            Serial.print(i);
            Serial.print(" + ");
            Serial.print(j);
            Serial.print(" = ");
            Serial.println(outPin.read());
        }
    }
    printResult(16 * 16, numOfPass);
    delay(5000);
}
