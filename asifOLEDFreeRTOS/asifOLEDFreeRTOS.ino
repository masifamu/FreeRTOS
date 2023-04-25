#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <SPI.h>
#include <Adafruit_GFX.h>           //Includes core graphics library
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

  Serial.println("Task being created..");
 BaseType_t created = xTaskCreate(oledDisplayHandler, "OLEDHandler",64,NULL,1,NULL);
 if(created == pdPASS){
  Serial.println("Task Successfully created");
 }else{
  Serial.println("Task not created");

  vTaskStartScheduler();
 }
} // setup

void sendOLEDWelcomeText(){
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F(" masifamu"));
  display.display();
}

void oledDisplayHandler(void *pvParameters){
    // sendOLEDWelcomeText();
    while(1){
        Serial.println("FreeRTOS");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// main code here, to run repeatedly: 
void loop() {
} // loop