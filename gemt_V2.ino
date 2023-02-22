#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Menu Declarations
//========================================================================

// Main Menu Options
static Menu mainMenu[] =
{
  {1, "9G Servo Test"}, // Action - Update Menu, Servo
  {2, "ESR Test"},  // Action - Test
  {3, "nRF24 Test"}, // Action - Test
  {4, "L298N Test"}, // Action - Test
  {5, "Ultrasonic Test"}, // Action - Test
};
size_t mainMenuLen = sizeof(mainMenu) / sizeof(mainMenu[0]);

// Submenu for servo
static Menu servoMenu[] =
{
  {1, "Manual Operation Test"},
  {2,  "Automatic Operation Test"},
  {3, "Back"}, // Action - Update Menu, Main
};
size_t servoMenuLen = sizeof(servoMenu) / sizeof(servoMenu[0]);

// Setup a pointer to change which menu is displayed. Start in Main
Menu* currentMenuPtr = mainMenu;
size_t* currentMenuLengthPtr = mainMenuLen;

// Reason for doing like this is that we have some interdependencies of variables in above structs
// So we need to call the functions after those have been initilized
void initMenuActions(void)
{
  // Action - Update Menu, Servo
  mainMenu[0].selectionAction = menuUpdate;
  mainMenu[0].selectionAction(servoMenu, servoMenuLen, currentMenuPtr, currentMenuLengthPtr);

  // Example for other calls
  mainMenu[1].selectionAction = Foo;
  mainMenu[1].selectionAction();

  //...


  //...
  
  // Action - Update Menu, Main
  servoMenu[2].selectionAction = menuUpdate;
  servoMenu[2].selectionAction(mainMenu, mainMenuLen, currentMenuPtr, currentMenuLengthPtr);
}

//========================================================================
// Main
//========================================================================

void setup(void)
{
  delay(500);
  Serial.begin(115200);
  startInterface();
  initMenuActions();
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