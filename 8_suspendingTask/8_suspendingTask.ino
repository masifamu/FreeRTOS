/**
 * Task will be suspeded one by one, at the end only red task will running.
 * you can add vTaskDelay() function in eash task to see a delayed suspending over serial
*/



#include <Arduino_FreeRTOS.h>

#define YELLOW    6
#define GREEN     7
#define BLUE      8
#define WHITE     4
#define RED       5

#define RED_BUTTON    2
#define GREEN_BUTTON  3


#define SET(digitalPin) digitalWrite(digitalPin, HIGH)
#define RESET(digitalPin) digitalWrite(digitalPin, LOW)
#define TOGGLE(digitalPin) digitalWrite(digitalPin, digitalRead(digitalPin)^1)

//you can add profiler to check the task working as well

TaskHandle_t yellowTaskHandle;
TaskHandle_t greenTaskHandle;
TaskHandle_t blueTaskHandle;
TaskHandle_t whiteTaskHandle;
TaskHandle_t redTaskHandle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(yellowLedControllerTask, "YellowLED",100,NULL,1,&yellowTaskHandle);
  xTaskCreate(greenLedControllerTask, "greenLED",100,NULL,1,&greenTaskHandle);
  xTaskCreate(blueLedControllerTask, "blueLED",100,NULL,1,&blueTaskHandle);
  xTaskCreate(whiteLedControllerTask, "whiteLED",100,NULL,1,&whiteTaskHandle);
  xTaskCreate(redLedControllerTask, "redLED",100,NULL,1,&redTaskHandle);

   xTaskCreate(suspendMonitoringTask, "suspendMonitoring",100,NULL,1,NULL);
}

void suspendMonitoringTask(void *pvParameters){
    static uint16_t suspendMonitor;
    while(1){
        suspendMonitor++;
        if(suspendMonitor == 10000){
            vTaskSuspend(yellowTaskHandle);
        }else if(suspendMonitor == 20000){
            vTaskSuspend(greenTaskHandle);
        }else if(suspendMonitor == 50000){
            vTaskSuspend(blueTaskHandle);
        }else if(suspendMonitor == 60000){
            vTaskSuspend(whiteTaskHandle);
        }else if(suspendMonitor == 65000){
            vTaskResume(yellowTaskHandle);
        }

    vTaskDelay(pdMS_TO_TICKS(100));
    }

}
void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    TOGGLE(YELLOW);
    Serial.println("yellow controller Task");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    TOGGLE(GREEN);
    Serial.println("green controller Task");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    TOGGLE(BLUE);
    Serial.println("blue controller Task");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void whiteLedControllerTask(void *pvParameters){
  pinMode(WHITE, OUTPUT);
  while(1){
    TOGGLE(WHITE);
    Serial.println("white controller Task");
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void redLedControllerTask(void *pvParameters){
  pinMode(RED, OUTPUT);
  while(1){
    TOGGLE(RED);
    Serial.println("red controller Task");
    vTaskDelay(pdMS_TO_TICKS(100));

  }
}
void loop() {
}
