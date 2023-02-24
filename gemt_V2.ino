#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Menu Declarations
//========================================================================

// Main Menu Options
static Menu MainMenu[] =
{
  {1, "9G Servo Test", menuUpdate}, // Action - Update Menu, Servo
  {2, "ESR Test", Foo},  // Action - Test
  {3, "nRF24 Test", Foo}, // Action - Test
  {4, "L298N Test", Foo}, // Action - Test
  {5, "Ultrasonic Test", Foo}, // Action - Test
};
size_t mainMenuLen = sizeof(MainMenu) / sizeof(MainMenu[0]);

// Submenu for servo
static Menu ServoMenu[] =
{
  {1, "Manual Operation Test"},
  {2,  "Automatic Operation Test"},
  {3, "Back"}, // Action - Update Menu, Main
};
size_t servoMenuLen = sizeof(ServoMenu) / sizeof(ServoMenu[0]);

// Setup a pointer to change which menu is displayed. Start in Main
Menu* CurrentMenuPtr = MainMenu;
size_t* currentMenuLengthPtr = mainMenuLen;

// Reason for doing like this is that we have some interdependencies of variables in above structs
// So we need to call the functions after those have been initilized
void initMenuActions(void)
{
  // Action - Update Menu, Servo

  MainMenu[0].setParams(ServoMenu, servoMenuLen, CurrentMenuPtr, currentMenuLengthPtr);

  // Example for other calls
  MainMenu[1].selectionAction = Foo;
  MainMenu[1].selectionAction();

  //...


  //...
  
  // Action - Update Menu, Main
  ServoMenu[2].selectionAction = menuUpdate;
  ServoMenu[2].selectionAction(MainMenu, mainMenuLen, CurrentMenuPtr, currentMenuLengthPtr);
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
    //displayDebug(MainMenu, MainMenuLen);
    displayMenu(CurrentMenuPtr, currentMenuLengthPtr);
    delay(3);
  }
  
  return 0;
}