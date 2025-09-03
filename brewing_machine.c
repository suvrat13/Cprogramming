#include <stdio.h>
#include <time.h>
#include <unistd.h>

/***************************************************************************************************************************************************
Task: Refine requirements, design and code a simple automatic coffee machine control system that meets the following requirements.

The coffee machine control system consists of a brew button, cup sensor, water temperature sensor, brewing pump, water heater, and dispensing valve.

When the brew button is pressed and a cup is detected, the system should wait 10 seconds for water heating and then start brewing at normal pump speed. 
The system should continue brewing as long as the brew button remains pressed.
When the brew button is released, the system should continue brewing for 15 seconds and then stop dispensing.

When the water temperature sensor indicates low temperature, the heater should activate and wait 25 seconds before allowing any brewing operation.
The heater should remain active until optimal temperature is reached.
When the temperature becomes too high, the system should continue the current brewing cycle but prevent new brew cycles from starting.

The system should handle situations when no cup is detected during brewing. If the cup is removed during active brewing, appropriate action should be taken.

For maintenance cleaning cycles, the system operates with different pump speeds and timing sequences.

Note: Show the inputs and outputs as methods defined in the code (no underlying code is needed). Code should be written using C or C++.

***************************************************************************************************************************************************/

/********************************************[  REQUIREMENTS  ]**************************************************************************
1. The system STATE MACHINE shall consist of the following states:
  a. IDLE
  b. BREWING
  c. COMPLETE
  d. EXITED
  c. MAINTENANCE
2. The system shall initialize the STATE MACHINE into IDLE State upon Power up
3. The system shall stay in IDLE state untill all the condition are met for state transition to BREW State
4. The sytem shall enter BREW state iff all the conditions states under at met:
  CONDITION 1: BREW button press is detected and held continuously at 1hz
  CONDITION 2: Cup detected flag is set for > 2 seconds
  CONDITION 3: 10 seconds timer from the time water heating is activated
  CONDITION 4: The temperature of water is within the operating range 25˚C <= Twater <=105˚C
5.The system shall transiton to COMPLETE state when the brew button is release for more than 15 seconds
6. THe system shall transition to EXIT state if a unexpected behavior is observed
7. The system shall inhibit brewing if the temperature > 60˚C


      
******************************************************************************************************************************************/
/********************************************[  SOURCE CODE  ]**************************************************************************/

/*==================[constants]=============================================*/

typedef enum {
  IDLE,
  BREW,
  COMPLETE,
  EXIT,
  MAINTENANCE
}state;

typedef struct {
  state next_state;
  state current_state;
}machine_state;

typedef struct {
  int button_state;
  int cup_detected_state;
  float water_temperature;
}sensor_state;


#define WATER_HEATING_TIMER_DEFAULT (10u)
#define WATER_HEATING_TIMER_EXTEND (25u)
#define WATER_TEMPERATURE_LOW (10.0f)
#define OPTIMAL_WATER_TEMPERATURE (25.0f)
#define WATER_TEMPERATURE_HIGH_INHIBIT_BREW (105.0f)
#define CUP_DETECT_DEBOUNCE 2
/*==================[macros]================================================*/
// void get_button_state(sensor_state *sensor);
// void get_cup_detected_state(sensor_state *sensor);
// void get_next_state(machine_state *brew_state);
// void get_water_temperature(sensor_state *sensor);
// void set_water_heater(int state);

void get_button_state();
void get_cup_detected_state();
void get_next_state();
void get_water_temperature();
void set_water_heater(int state);
/*==================[private type definitions]==============================*/
// Define brew_state and sensor as static/global variables to ensure persistence and accessibility
static machine_state brew_state;
static sensor_state sensor;

void brew_init(){

  brew_state.current_state = IDLE;
  brew_state.next_state = IDLE;
  sensor.button_state = 0;
  sensor.cup_detected_state = 0;
  sensor.water_temperature = 20;
}

void machine_process(){

  get_next_state();

  if(brew_state.next_state == BREW){
    brew_state.current_state = BREW;
    printf("Brewing Coffee...\n");
  }
  else if(brew_state.next_state == COMPLETE){
    brew_state.current_state = COMPLETE;
    printf("Brewing Complete. Please take your cup.\n");
  }
  else if(brew_state.next_state == EXIT){
    brew_state.current_state = EXIT;
    printf("Exiting...\n");
  }
  else if(brew_state.next_state == MAINTENANCE){
    brew_state.current_state = MAINTENANCE;
    printf("Maintenance Mode...\n");
  }
  else{
    brew_state.current_state = IDLE;
    printf("Idle State...\n");
  }

}

void get_next_state(){
  
  static int water_heating_countdown = 0;
  static int set_debounce =0;

  get_button_state();
  get_cup_detected_state();
  get_water_temperature();

  if (brew_state.current_state == IDLE){
    if(sensor.button_state && sensor.cup_detected_state && sensor.water_temperature < WATER_TEMPERATURE_HIGH_INHIBIT_BREW){
      set_water_heater(1);
      if (!set_debounce){
        set_debounce =1; 
        water_heating_countdown = (sensor.water_temperature <= (float)WATER_TEMPERATURE_LOW) ? (int)WATER_HEATING_TIMER_EXTEND : (int)WATER_HEATING_TIMER_DEFAULT;
      }
      if (water_heating_countdown > 0){
        water_heating_countdown--;
        printf("Heating water... Time left: %d seconds\n", water_heating_countdown);
      }
      if (water_heating_countdown == 0 && set_debounce){
        brew_state.next_state = BREW;
        print(f("Water heated to optimal temperature: %.2f˚C\n", sensor.water_temperature));
        set_debounce =0;
      }
    } 
  }
  else if (brew_state.current_state == BREW){
    if (!sensor.button_state){
      brew_state.next_state = COMPLETE;
    }
  }
  else if (brew_state.current_state == COMPLETE){
    if (sensor.button_state){
      brew_state.next_state = BREW;
    }
    else{
      brew_state.next_state = IDLE;
    }
  }
  else if (brew_state.current_state == EXIT){
    brew_state.next_state = EXIT;
  }
  else if (brew_state.current_state == MAINTENANCE){
    brew_state.next_state = MAINTENANCE;
  }
  else{
    brew_state.next_state = IDLE;
  }

}

void get_button_state(){
  // Simulate button press
  static int button_state = 0;
  static int count = 10;
  if (count >0){
    count--;
  }
  else{
    button_state = !button_state; // Toggle state for demonstration
    count = 10; // Reset count
  }
  sensor.button_state = button_state;
}

void get_cup_detected_state(){
  static int cup_state = 0;
  static int debounce_count = 0;
  static int cup_detect_count = 10;
  if (cup_detect_count >0){
    cup_detect_count--;
  }
  else if (debounce_count > CUP_DETECT_DEBOUNCE){
    debounce_count = 0;
    cup_state = !cup_state; // Toggle state for demonstration
    cup_detect_count = 10; // Reset count
  }
  else{
    debounce_count++;
  }
  sensor.cup_detected_state = cup_state;
}

void get_water_temperature(){
  static int temp = 20;

  sensor.water_temperature = temp;
  temp += 0.2;
}

void set_water_heater(int state){
  if (state){
    printf("Water Heater ON\n");
  }
  else{
    printf("Water Heater OFF\n");
  }
}

/*==================[private data]==========================================*/

/*==================[public data]===========================================*/

/*==================[private function declarations]==========================*/
void sys_1000ms_task(void);

/*==================[public function definitions]===========================*/

void sys_1000ms_task(void)
{
    printf("1 second task\n");
    /* Call your code here */
    machine_process();


}


int main() {

    brew_init();
    for(;;)
    {   
      sys_1000ms_task();
        sleep(1);
    }

    return 0;
}