#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define ADC_PIN A0

// queue to send ADC data from read task to display task
QueueHandle_t xQueue;


/* Function to monitor task stack and heap usage */
// void prvMonitorTaskStackHeapUsage(void)
// {
//     TaskStatus_t task_status;
    
//     // get task status
//     vTaskGetInfo(xTaskGetCurrentTaskHandle(), &task_status, pdTRUE, eInvalid);
    
//     // print task stack and heap usage
//     Serial.print(task_status.pcTaskName);
//     Serial.print(": Stack high water mark = ");
//     Serial.print(task_status.uxStackHighWaterMark);
//     Serial.print(", Free heap = ");
//     Serial.println(xPortGetFreeHeapSize());
// }

/* Task to read ADC data */
void vADCTask(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // read every 100ms
    uint16_t adc_value;
    
    xLastWakeTime = xTaskGetTickCount();
    
    for (;;)
    {
        // read ADC data
        adc_value = analogRead(ADC_PIN);
        
        // send ADC data to OLED task
        xQueueSend(xQueue, &adc_value, 0);
        
        // monitor stack and heap usage
        // prvMonitorTaskStackHeapUsage();
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/* Task to display ADC data on OLED display */
void vOLEDDisplayTask(void *pvParameters)
{
    uint16_t adc_value;
    char str[16];
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    
    for (;;)
    {
        // wait for ADC data
        xQueueReceive(xQueue, &adc_value, portMAX_DELAY);
        
        // format ADC data as a string
        sprintf(str, "ADC value: %d", adc_value);
        
        // display ADC data on OLED display
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(str);
        display.display();
        
        // monitor stack and heap usage
        // prvMonitorTaskStackHeapUsage();
    }
}

void setup() 
{
    Serial.begin(9600);
    
    // create queue for ADC data
    xQueue = xQueueCreate(5, sizeof(uint16_t));
    
    // create tasks
    xTaskCreate(vADCTask, "ADC Task", 128, NULL, 1, NULL);
    xTaskCreate(vOLEDDisplayTask, "OLED Task", 128, NULL, 2, NULL);
    
    // start scheduler
    vTaskStartScheduler();
}

void loop() 
{
    // this should never be called
}
