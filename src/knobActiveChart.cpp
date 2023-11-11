#include "ofMain.h"

//bool t=true;
//bool f=false;

/*

[ Channel 2 ]

| o   o | 1
| o   o | 2
| o   o | 3

- - - - -

| o o o |
|       |
| o o o |
  - - -
  4 5 6

*/
#define NUM_KNOB_CHANNEL 5;

array<array<bool, 8>, 8> channel0 = {
    array<bool, 8> {true ,true ,true ,true ,true ,true ,true ,true ,},
    array<bool, 8> {false,false,false,false,false,false,false,false,},
    array<bool, 8> {true ,true ,true ,true ,true ,true ,true ,true ,},
    array<bool, 8> {false,false,false,false,false,false,false,false,},
    array<bool, 8> {true ,true ,true ,true ,true ,true ,true ,true ,},
    array<bool, 8> {false,false,false,false,false,false,false,false,},
    array<bool, 8> {true ,true ,true ,true ,true ,true ,true ,true ,},
    array<bool, 8> {false,false,false,false,false,false,false,false,},
};

array<array<bool, 8>, 8> channel1 = {
    array<bool, 8> {true ,false,false,false,false,false,false,false,},
    array<bool, 8> {false,true ,false,false,false,false,false,false,},
    array<bool, 8> {false,false,true ,false,false,false,false,false,},
    array<bool, 8> {false,false,false,true ,false,false,false,false,},
    array<bool, 8> {false,false,false,false,true ,false,false,false,},
    array<bool, 8> {false,false,false,false,false,true ,false,false,},
    array<bool, 8> {false,false,false,false,false,false,true ,false,},
    array<bool, 8> {false,false,false,false,false,false,false,true ,},
};

array<array<bool, 8>, 8> channel2 = {
    array<bool, 8> {false,false,false,    true ,  true ,    false,false,false,},
    array<bool, 8> {false,false,false,    false,  false,    true ,false,true ,},
    array<bool, 8> {true ,false,false,    false,  false,    true ,false,false,},
    array<bool, 8> {false,true ,false,    false,  false,    false,true ,false,},
    array<bool, 8> {true ,false,true ,    false,  false,    false,false,false,},
    array<bool, 8> {false,false,true ,    false,  false,    false,false,true ,},
    array<bool, 8> {false,false,true ,    true ,  false,    false,false,true ,},
    array<bool, 8> {true ,false,false,    false,  true ,    false,false,false,},
};

array<array<bool, 8>, 8> channel3 = {
    array<bool, 8> {true ,true ,true ,    false,  false,    false,false,false,},
    array<bool, 8> {false,false,true ,    false,  true ,    false,false,true ,},
    array<bool, 8> {false,false,false,    false,  false,    true ,true ,true ,},
    array<bool, 8> {true ,false,false,    true ,  false,    true ,false,false,},// ˆÍ‚Á‚½

    array<bool, 8> {false,false,true ,    true ,  false,    false,true ,false,},
    array<bool, 8> {false,true ,false,    true ,  false,    false,false,true ,},
    array<bool, 8> {false,true ,false,    false,  true ,    true ,false,false,},
    array<bool, 8> {true ,false,false,    false,  true ,    false,true ,false,},
};

array<array<bool, 8>, 8> channel4 = {
    array<bool, 8> {true ,false,true ,    false,  false,    true ,false,true ,},
    array<bool, 8> {false,true ,false,    true ,  true ,    false,true ,false,},

    array<bool, 8> {true ,true ,false,    false,  false,    false,true ,true ,},
    array<bool, 8> {false,false,true ,    true ,  true ,    true ,false,false,},

    array<bool, 8> {true ,false,false,    true ,  false,    true ,true ,false,},
    array<bool, 8> {false,true ,true ,    false,  true ,    false,false,true ,},

    array<bool, 8> {true ,true ,true,     false,  false,    false,true ,false,},
    array<bool, 8> {false,true ,false,    false,  false,    true ,true ,true,},
};
