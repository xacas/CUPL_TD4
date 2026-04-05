#include "BusInOut.hpp"
//#include "pwm.h"

enum condition
{
    IGNORE_THEN_IGNORE = 0,
    IGNORE_THEN_LOAD,
    LOAD_THEN_IGNORE,
    LOAD_THEN_LOAD,
    CONDITON_SIZE
};

// Declear signal pins of 74HC161.
const int qa = 0;
const int qb = 1;
const int qc = 2;
const int qd = 3;
BusInOut qOut(qa, qb, qc, qd);
const int a = 4;
const int b = 5;
const int c = 6;
const int d = 7;
BusInOut input(a, b, c, d);
const int _clr = 8;
const int _load = 9;
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

void pulsePin(int pin)
{
    PinStatus op = (digitalRead(pin) == HIGH) ? LOW : HIGH;
    digitalWrite(pin, op);
    delayMicroseconds(50);
    digitalWrite(pin, (op == HIGH) ? LOW : HIGH);
}

void setup() {
    Serial.begin(115200);

    qOut.setMode(INPUT);
    input.setMode(OUTPUT);

    pinMode(_clr, OUTPUT);
    pinMode(_load, OUTPUT);

    digitalWrite(_clr, HIGH);
    digitalWrite(_load, HIGH);

    //74HC161(本物)をテストする場合のクロック入力
    //pwm.begin((float)100000.0,(float)50.0);
}


void loop() {

    int numOfPass = 0;
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            for(int k = 0; k < CONDITON_SIZE; k++)
            {
                do
                {
                    // step 1 : Reset
                    pulsePin(_clr);
                    if(qOut.read() != 0)
                    {
                        Serial.print("[ FAIL ] : Q pins not reset to 0.");
                        break;
                    }

                    // step 2 : Set t0 state
                    input.write(i);
                    if((k == LOAD_THEN_IGNORE) || (k == LOAD_THEN_LOAD))
                    {
                        pulsePin(_load);
                        if(qOut.read() != i)
                        {
                            Serial.print("[ FAIL ] : Q pins not set to ");
                            Serial.print(i);
                            Serial.print(".");
                            break;
                        }
                    }
                    else
                    {
                        if(qOut.read() != 0)
                        {
                            Serial.print("[ FAIL ] : Q pins did not retain their value.");
                            break;
                        }
                    }

                    // step 3 : Set t1 state
                    input.write(j);
                    if((k == IGNORE_THEN_LOAD) || (k == LOAD_THEN_LOAD))
                    {
                        pulsePin(_load);
                        if(qOut.read() != j)
                        {
                            Serial.print("[ FAIL ] : Q pins not set to ");
                            Serial.print(j);
                            Serial.print(".");
                            break;
                        }
                    }
                    else
                    {
                        // k is equal to IGNORE_THEN_IGNORE or LOAD_THEN_IGNORE.
                        if(qOut.read() != ((k == LOAD_THEN_IGNORE) ? i : 0))
                        {
                            Serial.print("[ FAIL ] : Q pins did not retain their value.");
                            break;
                        }
                    }
                    Serial.print("[ PASS ]");
                    numOfPass++;
                } while (0);
                Serial.print(" 1st input signal : ");
                Serial.print(i);
                Serial.print(". 2nd input signal : ");
                Serial.print(j);
                Serial.print(". Test condition : ");
                Serial.print(k);
                Serial.print(". Output : ");
                Serial.println(qOut.read());
            }
            
        }
    }
    printResult(16 * 16 * 4, numOfPass);
    delay(5000);
}