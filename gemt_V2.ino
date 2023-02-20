#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Menu Declarations
//========================================================================


// FIXME: Figure out how to make these calls

// Main Menu Options
static const Menu mainMenu[] =
{
  {1, "9G Servo Test", menuUpdate(servoMenu, servoMenuLength, &currentMenuPtr, &currentMneuLengthPtr)},
  {2, "ESR Test"},
  {3, "nRF24 Test"},
  {4, "L298N Test"},
  {5, "Ultrasonic Test"},
};
size_t mainMenuLen = sizeof(mainMenu) / sizeof(mainMenu[0]);

// Submenu for servo
static const Menu servoMenu[] =
{
  {1, "Manual Operation Test"},
  {2,  "Automatic Operation Test"},
  {3, "Back"},
};
size_t servoMenuLen = sizeof(servoMenu) / sizeof(servoMenu[0]);

// Setup a pointer to change which menu is displayed
Menu* currentMenuPtr = mainMenu;
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
    //displayDebug(mainMenu, mainMenuLen);
    displayMenu(currentMenuPtr, currentMenuLengthPtr);

    delay(3);
  }
  
  return 0;
}