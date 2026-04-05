#include "BusInOut.hpp"
#include "TestVector.hpp"

// Declear signal pins of TD4.
const int a0 = 0;
const int a1 = 1;
const int a2 = 2;
const int a3 = 3;
BusInOut addr(a0, a1, a2, a3);
const int d0 = 4;
const int d1 = 5;
const int d2 = 6;
const int d3 = 7;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;
BusInOut romData(d0, d1, d2, d3, d4, d5, d6, d7);
// Declear I/O pins.(Only 3 bit)
const int i0 = 14;
const int i1 = 15;
const int i2 = 16;
BusInOut input(i0, i1, i2);
const int o0 = 17;
const int o1 = 18;
const int o2 = 19;
BusInOut output(o0, o1, o2);

// Clock Input
const int td4_clk = 12;
// reset signal pin
const int _reset = 13;

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

void pulsePin(int pin)
{
    PinStatus op = (digitalRead(pin) == HIGH) ? LOW : HIGH;
    digitalWrite(pin, op);
    delayMicroseconds(50);
    digitalWrite(pin, (op == HIGH) ? LOW : HIGH);
}

void setup() {
    Serial.begin(115200);

    addr.setMode(INPUT);
    romData.setMode(OUTPUT);
    input.setMode(OUTPUT);
    output.setMode(INPUT);

    pinMode(td4_clk, OUTPUT);
    pinMode(_reset, OUTPUT);

    digitalWrite(td4_clk, HIGH);
    digitalWrite(_reset, HIGH);
}

void loop() {

    int numOfPass = 0;

    for(int i = 0; i < TESTCASE_NUM; i++)
    {
        // Toggle Reset.
        //pulsePin(_reset);
        digitalWrite(_reset, LOW);
        delayMicroseconds(100);
        digitalWrite(_reset, HIGH);
        for(int j = 0; j < 6; j++)
        {
            // Set input signal.
            uint8_t pc = addr.read();
            if(pc < 5)
            {
                romData.write(testRom[i][pc]);
            }
            input.write(exp_io[i][j].in);
            // Toggle Clock.
            pulsePin(td4_clk);

            // Compare the TD4 Status.
            uint8_t out = output.read();
            if(( pc == exp_io[i][j].pc ) && 
                out == exp_io[i][j].out )
            {
                Serial.print("[ PASS ] : ");
                numOfPass++;
            }
            else
            {
                Serial.print("[ FAIL ] : ");
            }
            Serial.print("exp pc = ");
            Serial.print(exp_io[i][j].pc);
            Serial.print(". act pc = ");
            Serial.print(pc);
            Serial.print(". exp out = ");
            Serial.print(exp_io[i][j].out);
            Serial.print(". act out = ");
            Serial.print(out);
            Serial.print(".\n");
        }
    }

    printResult(TESTCASE_NUM * 6, numOfPass);
    delay(5000);
}