/*
    FE Q12
    This program controls the LED brightness using the 3 axis accelerometer. 
    Moving the board in x-axis changes the brightness on LED1
    y-axis changes the brightness on LED2
    z-axis changes the brightness on LED3
*/
#include "mbed.h"
#include "LSM6DSLSensor.h"

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); 

PwmOut led_1(LED1);  
PwmOut led_2(LED2); 
PwmOut led_3(LED3); 

void cycleBrigtness( int old[], int now[], char moving[], int sensitivity){
    if(abs(old[0] - now[0]) > sensitivity){ // x axis
        led_1 = led_1 + 0.01;               // increase when moved more that sensitivity value
        old[0] = now[0];
        moving[0] = 'y';                    // display message
    } else {
        led_1 = 0;                          // turn off led when stationary 
        old[0] = now[0];
        moving[0] = 'n';                    // display message
    }

    if(abs(old[1] - now[1]) > sensitivity){ // y axis
        led_2 = led_2 + 0.01;               // increase when moved more that sensitivity value
        old[1] = now[1];
        moving[1] = 'y';                    // display message
    } else {
        led_2 = 0;                          // turn off led when stationary 
        old[1] = now[1];
        moving[1] = 'n';                    // display message
    }

    if(abs(old[2] - now[2]) > sensitivity){ // z axis
        led_3 = led_3 + 0.01;               // increase when moved more that sensitivity value
        old[2] = now[2];
        moving[2] = 'y';                    // display message
    } else {
        led_3 = 0;                          // turn off led when stationary 
        old[2] = now[2];
        moving[2] = 'n';                    // display message
    }
}

int main() {
    uint8_t id;
    int32_t axes_new[3];
    int axes_old[3] = {0,0,0}; // stores the previous location
    int sensitivity = 50;      // change sensitivity for changing led birghtness
    char moving[3] = {'n','n','n'};

    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    acc_gyro.read_id(&id);
    printf("This program will change led brightness in response to moving the board\r\n");

    while(1) {

        acc_gyro.get_x_axes(axes_new);

        cycleBrigtness(axes_old, axes_new, moving, sensitivity);
        
        printf("Movig in axes: x(%c) y(%c) z(%c)\r\n", moving[0],moving[1],moving[2]);

        thread_sleep_for(500);

    }
}

