#include "gemt_interface.h"
#include "Arduino.h"



//========================================================================
// Menu Declarations
//========================================================================

// Main Menu Options
static const Menu mainMenu[] =
{
  {1, "9G Servo Test"},
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
    displayDebug(mainMenu, mainMenuLen);
    delay(10000);
    /*
    // Main Menu switch    
    // Get user Serial input for desired main menu test
    display.clearDisplay();
    display.setTextSize(1); 
    display.println("\n\nPlease set Serial Inputs to \'No Line Ending\'");
    unsigned short int mainSel = menuSelection("Main Menu", mainMenu); 
                             
    switch (mainSel)
    {
      case 1: // 9G
      {

        break;
      }
      case 2:  // ESR
      { 
        
        break;
      }
      case 3: // nRF
      {
        
        break;
      }
      case 4: // L298N
      {

        break;
      }
      case 5: // Ultrasonic
      {
        
        break;
      }
      default:
      {
        display.println("Error: Invalid inputs should be caught by getSerrialInput()!");
        break;
      }
    }  
  */
    delay(50);
  }
  
  return 0;
}




