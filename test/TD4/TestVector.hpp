#ifndef TEST_VECTOR
#define TEST_VECTOR

#define TESTCASE_NUM 9
#define CONCAT(a, b) ((a << 4) + b)

#define ADD_A_IM(im)    CONCAT(OP_ADD_A_IM, im)
#define MOV_A_B         CONCAT(OP_MOV_A_B, 0)
#define IN_A            CONCAT(OP_IN_A, 0)
#define MOV_A_IM(im)    CONCAT(OP_MOV_A_IM, im)
#define MOV_B_A         CONCAT(OP_MOV_B_A, 0)
#define ADD_B_IM(im)    CONCAT(OP_ADD_B_IM, im)
#define IN_B            CONCAT(OP_IN_B, 0)
#define MOV_B_IM(im)    CONCAT(OP_MOV_B_IM, im)
#define OUT_B           CONCAT(OP_OUT_B, 0)
#define OUT_IM(im)      CONCAT(OP_OUT_IM, im)
#define JNC(im)         CONCAT(OP_JNC_IM, im)
#define JMP(im)         CONCAT(OP_JMP_IM, im)

enum OP
{
    OP_ADD_A_IM,   //0b0000
    OP_MOV_A_B,    //0b0001
    OP_IN_A,       //0b0010
    OP_MOV_A_IM,   //0b0011
    OP_MOV_B_A,    //0b0100
    OP_ADD_B_IM,   //0b0101
    OP_IN_B,       //0b0110
    OP_MOV_B_IM,   //0b0111
    OP_NONE0,      //0b1000
    OP_OUT_B,      //0b1001
    OP_NONE1,      //0b1010
    OP_OUT_IM,     //0b1011
    OP_NONE2,      //0b1100
    OP_NONE3,      //0b1101
    OP_JNC_IM,     //0b1110
    OP_JMP_IM,     //0b1111
};

uint8_t testRom[TESTCASE_NUM][5] = {
    {
    // Test Case 1 : OUT Im
        OUT_IM(1),
        OUT_IM(2),
        OUT_IM(3)
    },
    // Test Case 2 : MOV B Im, OUT B
    {
        MOV_B_IM(4),
        OUT_B
    },
    // Test Case 3 : IN B
    {
        IN_B,
        OUT_B
    },
    // Test Case 4 : MOV A Im, MOV B A
    {
        MOV_A_IM(5),
        MOV_B_A,
        OUT_B
    },
    // Test Case 5 : IN A
    {
        IN_A,
        MOV_B_A,
        OUT_B
    },
    // Test Case 6 : ADD B Im
    {
        MOV_B_IM(6),
        ADD_B_IM(1),
        OUT_B
    },
    // Test Case 7 : MOV A B, ADD A Im
    {
        MOV_B_IM(1),
        MOV_A_B,
        ADD_A_IM(2),
        MOV_B_A,
        OUT_B
    },
    // Test Case 8 : JMP Im
    {
        OUT_IM(4),
        OUT_IM(5),
        OUT_IM(6),
        JMP(0)
    },
    // Test Case 9 : JNC Im
    {
        MOV_A_IM(14),
        ADD_A_IM(1),
        JNC(1)
    }
};

struct expectIO
{
    uint8_t pc;
    uint8_t in;
    uint8_t out;
};

expectIO exp_io[TESTCASE_NUM][6] = {
    // Test Case 1 : OUT Im
    {
        {0, 0, 1},
        {1, 0, 2},
        {2, 0, 3},
        {3, 0, 3},
        {4, 0, 3},
        {5, 0, 3}
    },
    // Test Case 2 : MOV B Im, OUT B
    {
        {0, 0, 0},
        {1, 0, 4},
        {2, 0, 4},
        {3, 0, 4},
        {4, 0, 4},
        {5, 0, 4}
    },
    // Test Case 3 : IN B
    {
        {0, 7, 0},
        {1, 0, 7},
        {2, 0, 7},
        {3, 0, 7},
        {4, 0, 7},
        {5, 0, 7}
    },
    // Test Case 4 : MOV A Im, MOV B A
    {
        {0, 0, 0},
        {1, 0, 0},
        {2, 0, 5},
        {3, 0, 5},
        {4, 0, 5},
        {5, 0, 5}
    },
    // Test Case 5 : IN A
    {
        {0, 3, 0},
        {1, 0, 0},
        {2, 0, 3},
        {3, 0, 3},
        {4, 0, 3},
        {5, 0, 3}
    },
    // Test Case 6 : ADD B Im
    {
        {0, 0, 0},
        {1, 0, 0},
        {2, 0, 7},
        {3, 0, 7},
        {4, 0, 7},
        {5, 0, 7}
    },
    // Test Case 7 : MOV A B, ADD A Im
    {
        {0, 0, 0},
        {1, 0, 0},
        {2, 0, 0},
        {3, 0, 0},
        {4, 0, 3},
        {5, 0, 3}
    },
    // Test Case 8 : JMP Im
    {
        {0, 0, 4},
        {1, 0, 5},
        {2, 0, 6},
        {3, 0, 6},
        {0, 0, 4},
        {1, 0, 5}
    },
    // Test Case 9 : JNC Im
    {
        {0, 0, 0},
        {1, 0, 0},
        {2, 0, 0},
        {1, 0, 0},
        {2, 0, 0},
        {3, 0, 0}
    },
};

#endif