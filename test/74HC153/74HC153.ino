#include "BusInOut.hpp"

// Declear signal pins of 74HC153.
int a = 0;
int b = 1;
BusInOut selectInput(a, b);
int c0 = 2;
int c1 = 3;
int c2 = 4;
int c3 = 5;
BusInOut dataInputC(c0, c1, c2, c3);
int y = 6;

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

    selectInput.setMode(OUTPUT);
    dataInputC.setMode(OUTPUT);
    pinMode(y, INPUT);
}

void loop() {
    int numOfPass = 0;
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            dataInputC.write(i);
            selectInput.write(j);

            bool out = digitalRead(y);

            if(((i >> j) & 0x01) == out)
            {
                Serial.print("[ PASS ]");
                numOfPass++;
            }
            else
            {
                Serial.print("[ FAIL ]");
            }

            Serial.print("selected signal : ");
            Serial.print((i >> j) & 0x01);
            Serial.print(" output from CUPLIO : ");
            Serial.println(out);
        }
    }
    printResult(16 * 4, numOfPass);
    delay(5000);
}
