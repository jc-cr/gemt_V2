#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Menu Declarations
//========================================================================


// FIXME: Figure out how to make these calls

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
  {3, "Back"}, // Update Menu, Main
};
size_t servoMenuLen = sizeof(servoMenu) / sizeof(servoMenu[0]);

// Setup a pointer to change which menu is displayed
Menu* currentMenuPtr = mainMenu;
size_t* currentMenuLengthPtr = mainMenuLen;



// Reason for doing like this is that we have some interdependencies of variables
// So need to update afterwards
void menuFunctionInit(void)
{
  mainMenu[0].menuUpdateMethod = menuUpdate;
  mainMenu[0].menuUpdateMethod(servoMenu, servoMenuLen, currentMenuPtr, currentMenuLengthPtr);

  // TESTING
  mainMenu[1].menuUpdateMethod = Foo;
  mainMenu[1].menuUpdateMethod();

  //...

}




//========================================================================
// Main
//========================================================================

void setup(void)
{
  delay(500);
  Serial.begin(115200);
  startInterface();
  menuFunctionInit();

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