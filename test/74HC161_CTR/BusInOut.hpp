#ifndef BUSINOUT_HPP
#define BUSINOUT_HPP

class BusInOut
{
private:
    uint8_t m_bus[8];
    uint8_t m_busNum = 0;
public:
    BusInOut(uint8_t b0 = 0xff, uint8_t b1 = 0xff, uint8_t b2 = 0xff, uint8_t b3 = 0xff, 
        uint8_t b4 = 0xff, uint8_t b5 = 0xff, uint8_t b6 = 0xff, uint8_t b7 = 0xff);
    ~BusInOut();
    uint8_t read(void);
    void write(uint8_t val);
    void setMode(int mode);
};

BusInOut::BusInOut(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, 
        uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7)
{
    m_bus[0] = b0;
    m_bus[1] = b1;
    m_bus[2] = b2;
    m_bus[3] = b3;
    m_bus[4] = b4;
    m_bus[5] = b5;
    m_bus[6] = b6;
    m_bus[7] = b7;

    for(int i = 0; (i < sizeof(m_bus)) && (m_bus[i] != 0xff); i++)
        m_busNum++;
}

BusInOut::~BusInOut()
{
}

uint8_t BusInOut::read(void)
{
    uint8_t val = 0;
    for(int i = m_busNum - 1; 0 <= i; i--)
        val = (val << 1) + digitalRead(m_bus[i]);

    return val;
}

void BusInOut::write(uint8_t val)
{
    for(int i = 0; i < m_busNum; i++)
        digitalWrite(m_bus[i], (val >> i) & 0x01);
}

void BusInOut::setMode(int mode)
{
    for(int i = 0; i < m_busNum; i++)
        pinMode(m_bus[i], mode);
}

#endif