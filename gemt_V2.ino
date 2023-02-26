#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Menu Declarations
//========================================================================

// Main Menu Options
static Menu MainMenu[] =
{
  {1, "9G Servo Test", dummyMenu}, // Action - Update Menu, Servo
  {2, "ESR Test", dummyTest},  // Action - Test
  {3, "nRF24 Test", dummyTest}, // Action - Test
  {4, "L298N Test", dummyTest}, // Action - Test
  {5, "Ultrasonic Test", dummyTest}, // Action - Test
};
size_t mainMenuLen = sizeof(MainMenu) / sizeof(MainMenu[0]);

// Submenu for servo
static Menu ServoMenu[] =
{
  {1, "Manual Operation Test", dummyTest},
  {2,  "Automatic Operation Test", dummyTest},
  {3, "Back", dummyMenu}, // Action - Update Menu, Main
};
size_t servoMenuLen = sizeof(ServoMenu) / sizeof(ServoMenu[0]);

// Setup a pointer to change which menu is displayed. Start in Main
Menu* CurrentMenuPtr = MainMenu;
size_t* currentMenuLengthPtr = mainMenuLen;

//========================================================================
// Main
//========================================================================

void setup(void)
{
  delay(500);
  Serial.begin(115200);
  startInterface();
}

int main(void) 
{
  // Must intialize the arduino firmware
  init();
  setup();

  while(true)
  {
    //displayDebug(MainMenu, MainMenuLen);
    displayMenu(CurrentMenuPtr, currentMenuLengthPtr);
    delay(3);
  }
  
  return 0;
}