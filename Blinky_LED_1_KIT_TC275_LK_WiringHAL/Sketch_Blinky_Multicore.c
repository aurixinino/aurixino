#include "./Libraries/Arduino/Arduino.h"
//****************************************************************************
//                                                             ARDUINO SKETCH
//****************************************************************************
static semaphore_t s_cpuSync;

// set-up function for CPU0
void cpu0_setup() {

    // init semaphore to support CPU0 / CPU1 syncronization
    semaphore_init(s_cpuSync);

    // Take the semaphore and wait till cpu1 give it back
    semaphore_take(s_cpuSync);
    //TO TEST THE DESYNC: semaphore_wait(s_cpuSync);
}

// set-up function for CPU1
void cpu1_setup() {

    // delay to intentionally de-syncronize the two CPU executions
    delay(500);

    //let cpu0 execution to continue
    semaphore_give(s_cpuSync);

    // ... now cpu0 and cpu1 are syncronized and led blinking with be in sync ..
}

// set-up function for CPU2
void cpu2_setup() {

}

// loop function for CPU0
void cpu0_loop() {

    // Create a small delay to permit to observe the LED toggling
    delay(750);

    // Now toggle the LED status
    toggleLED1();
}

// loop function for CPU1
void cpu1_loop() {

    // Create a small delay to permit to observe the LED toggling
    delay(750);

    // Now toggle the LED status
    toggleLED2();
}

// loop function for CPU2
void cpu2_loop() {

}
//****************************************************************************
//                                                             END OF FILE
//****************************************************************************
