#include "gemt_interface.h"
#include "Arduino.h"

//========================================================================
// Main
//========================================================================

void setup(void)
{
  delay(500);
  Serial.begin(115200); // DEBUGGING
  startInterface();
  setSelectionActions();
}

int main(void) 
{
  // Must intialize the arduino firmware
  init();
  setup();

  while(true)
  {
    //displayDebug(MainMenu, MainMenuLen);
    displayMenuDriver(CurrentMenuPtr, currentMenuLenPtr);
    delay(3);
  }
  
  return 0;
}