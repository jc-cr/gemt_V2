
#ifndef GEMT_INTERFACE_H
#define GEMT_INTERFACE_H
#include "Arduino.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EncoderButton.h>
#include <Fonts/Org_01.h>
#include "HardwareSerial.h"

/*========================================================================
 TODO:
  - Info screen
  - Integrate hardware tests
  - Create seperate .h and .cpp   
========================================================================*/

//========================================================================
// Global Definitions
//========================================================================

#define displayRowLimit 8;
#define displayColLimit 21;

/* Use of volatile for variables that:
    - Memormy mapped registers
    - global varchanged by interrupt
    - global var accessed by multithreading
    https://barrgroup.com/embedded-systems/how-to/c-volatile-keyword
*/

// Anon namespace better than static
namespace
{
  volatile uint8_t ebState = 0; // Current state (Position) of the encoder. Max by uint8 is 255
  volatile bool clicked = false; // Updated on encoder "click" case, must reset after use 
  uint8_t clickedItemNumber = 0;
}
//========================================================================
// Initializers
//========================================================================

// Note: If using jumper wires make sure pins are well spaced out.
// rotary encoder is super noisy and registers false clicks among other issues
enum encoderSWPins 
{
  pinA = 19 , // CLK
  pinB = 2, // DT
  pinSW = 38 // SW
};

enum oledDisplayPins
{
  screenWidth = 128,
  screenHeight = 64,
  screenAddress = 0x3C, // i2c Address
  screenReset = -1      // -1 since sharing Arduino reset pin
};

// Display init
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, screenReset);

// EncoderSW init
EncoderButton eb1(pinA, pinB, pinSW);

//========================================================================
// Menu Functions (WIP)
//========================================================================

typedef void (*func)(void);

// Menu screen template
typedef struct Menu
{
  unsigned short int choice;
  const char* menuTextPtr;
  func selectionAction; // Function pointer to Menu selection action
  // At the moment only takes void functions... 
  // Still have not figured out how to set parameters in a general way

  /* Possible CPP solution
  // store the result of a call to std::bind
  <void()> selectionAction = NULL;
  //std::bind(print_num, 31337); // To init you would do
  */

  // Method styling in C https://www.cs.uaf.edu/courses/cs301/2014-fall/notes/methods/index.html
  // Ellipses ref https://www.lemoda.net/c/function-pointer-ellipsis/
} Menu;

// Main Menu Options
Menu MainMenu[] =
{
  {1, "9G Servo Test"}, // Action - Update Menu, Servo
  {2, "ESR Test"},  // Action - Test
  {3, "nRF24 Test"}, // Action - Test
  {4, "L298N Test"}, // Action - Test
  {5, "Ultrasonic Test"}, // Action - Test
};
size_t mainMenuLen = sizeof(MainMenu) / sizeof(MainMenu[0]);

// Submenu for servo
Menu ServoMenu[] =
{
  {1, "Manual Servo Test"},
  {2,  "Auto Servo Test"},
  {3, "Back"}, // Action - Update Menu, Main
};
size_t servoMenuLen = sizeof(ServoMenu) / sizeof(ServoMenu[0]);

// Setup a pointer to change which menu is displayed. Start in Main
Menu* CurrentMenuPtr = MainMenu;
size_t* currentMenuLenPtr = mainMenuLen;

// Logo Bitmap Init
const uint8_t  logo_bmp [] PROGMEM = 
{ 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0x86, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x80, 0x00, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x77, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x38, 0x01, 0xc3, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x0e, 0x07, 0x81, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x87, 0x03, 0x8e, 0x00, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x00, 0xf8, 0x00, 0x70, 0x00, 0x00, 
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x30, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 
  0x00, 0x00, 0xe0, 0x00, 0x3f, 0xfc, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x1c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 
  0x00, 0x03, 0x80, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 
  0x00, 0x07, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 
  0x00, 0x0e, 0x00, 0x00, 0x00, 0x1c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
  0x00, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0x1c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
  0x00, 0x78, 0x00, 0x00, 0x00, 0x1c, 0x0c, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0x87, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xf8, 0x7f, 0xfc, 0x1f, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xc0, 
  0x00, 0x7f, 0xff, 0xe0, 0x7f, 0xff, 0xfc, 0x7f, 0xfc, 0x3f, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x00, 
  0x00, 0x1f, 0xff, 0xf0, 0x3f, 0xff, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xf0, 0x3f, 0xff, 0xfc, 0x00, 
  0x00, 0x07, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xe0, 0x7f, 0xff, 0xf0, 0x00, 
  0x00, 0x03, 0xff, 0xfe, 0x0f, 0xff, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0x07, 0xff, 0xfe, 0x3f, 0xfc, 0x7f, 0xff, 0x81, 0xff, 0xff, 0x80, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0x83, 0xff, 0xfe, 0x3f, 0xf8, 0x7f, 0xff, 0x03, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xc1, 0xff, 0xfe, 0x1f, 0xf8, 0x7f, 0xfe, 0x07, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xe0, 0xff, 0xfe, 0x1f, 0xf8, 0x7f, 0xfe, 0x0f, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xf0, 0x7f, 0xff, 0x1f, 0xf8, 0xff, 0xfc, 0x1f, 0xff, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0xf8, 0x3f, 0xff, 0x1f, 0xf8, 0xff, 0xf8, 0x3f, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xff, 0x1f, 0xf0, 0xff, 0xf0, 0x7f, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xfe, 0x0f, 0xff, 0x8f, 0xf0, 0xff, 0xe0, 0xff, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xff, 0x07, 0xff, 0x8f, 0xf1, 0xff, 0xc1, 0xff, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x83, 0xff, 0x8f, 0xf1, 0xff, 0x83, 0xff, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xe1, 0xff, 0x8f, 0xf1, 0xff, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x7f, 0xcf, 0xe3, 0xfe, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x3f, 0xc7, 0xe3, 0xfc, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x1f, 0xc7, 0xe3, 0xf8, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0xe7, 0xe3, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x07, 0xe7, 0xe7, 0xe1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x83, 0xe7, 0xc7, 0xc3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc1, 0xe3, 0xc7, 0x87, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0xf3, 0xc7, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0xce, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x33, 0xce, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x13, 0x8c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0b, 0x88, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
//========================================================================
// Encoder Handlers (Interrupt functions)
//========================================================================
  
// On click, the global selection variable gets updated with
// value of where it was selcted
void onEb1Clicked(EncoderButton& eb)
{
  // Set selection value to current state
  clicked = true;
  clickedItemNumber = CurrentMenuPtr[ebState].choice;

  // DEBUG - Delete in actua\l proram as Serial printing slows down interrupts
  //Serial.println("CLICKED!");
}

// A function to handle the 'encoder' event
void onEb1Encoder(EncoderButton& eb) 
{
  /*
  // Filter latge spikes from noise
  if(eb.increment() > 4)
  {
    eb.resetPosition(eb.position()); // Reset back to startin pos
  }
  */
  // Reset if encoder goes past active Menu limit
  if (abs(eb.position()) >= currentMenuLenPtr)
  {
    eb.resetPosition(0);
  }

  ebState = abs(eb.position());

  // DEBUG - Delete in actual proram as Serial printing slows down interrupts
  //Serial.println(ebState);
}

//========================================================================
// Helper functions
//========================================================================

// Function to quickly call actions required to prep screen for printing
void displayPrep(void)
{
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
}

// Create function for clarity
void resetClicked(void)
{
  clicked = 0;
}

//========================================================================
// Selection Action Functions
//========================================================================

void goToServoMenu(void)
{
  CurrentMenuPtr = ServoMenu;
  currentMenuLenPtr = servoMenuLen;
  
  // Start at top of page
  ebState = 0;
}

void goToMainMenu(void)
{
  CurrentMenuPtr = MainMenu;
  currentMenuLenPtr = mainMenuLen; 

  // Start at top of page
  ebState = 0;
}

void infoScreen(void)
{
  eb1.update();
  displayPrep();

  // Naive way of identifying whinc menu we are in 
  if (CurrentMenuPtr[0].menuTextPtr == "9G Servo Test")
  {
    switch(clickedItemNumber)
    {
      case 2: // esr
      {

      }
      case 3: // nRF
      {

      }
      case 4: // L298H
      {

      }
      case 5: // Ultrasonic
      {

      }
    }

  }
  else if (CurrentMenuPtr[0].menuTextPtr == "Manual Servo Test")
  {
    switch(clickedItemNumber)
    {
      case 1: // Manual
      {

      }
      case 2: // Auto
      {

      }
    }
  }
}
// Function to set selection action when button pressed
// Currently only accepts void argument functions!
void setSelectionActions(void)
{
  MainMenu[0].selectionAction = goToServoMenu;
  //...

  ServoMenu[2].selectionAction = goToMainMenu;
  //...
}


static const char *confirmOptions[3] = {"OK", "|", "Back"};
static const size_t confirmOptionLen = sizeof(confirmOptions) / sizeof(confirmOptions[0]);

// Reusable function for printing the confirmOptions above
void printConfirmOptions(void)
{
  for (size_t i = 0; i < confirmOptionLen; i++)
  {
     // Highlight line if user is hovering over it
     // Don't highlight the bar though
      if (ebState == i && i != 1)
      {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
      }
      else 
      {
        display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); 
      }
       
       display.print(confirmOptions[i]);
  }
}

//========================================================================
// Screen Display Functions
//========================================================================

// Bootup fucnction for display
void startInterface(void) 
{ 
  if(!display.begin(SSD1306_SWITCHCAPVCC, screenAddress)) {
    display.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //Link the event(s) to your function
  eb1.setClickHandler(onEb1Clicked);
  eb1.setEncoderHandler(onEb1Encoder);

  // Create mapping to selection action fuunctions
  setSelectionActions();

  // Display logo for 2 sec
  display.clearDisplay();
  display.drawBitmap(0, 0, logo_bmp, screenWidth, screenHeight - 5, WHITE); // -5, bc getting some weird stuff at bottom of screen
  display.display();
  delay(2000);
  
  display.clearDisplay();  
  display.display();
}

// Display driver code: Outputs current menu items line by-line,
// Highlights and selects based on encoder-button readings
void displayMenuDriver(void)
{
  // Condition for executing users selections based on 'clicked' bool
  if (clicked)
  {
    clickedItemNumber = CurrentMenuPtr[ebState].choice;
    resetClicked(); // Reset before proceeding to function
    CurrentMenuPtr[ebState].selectionAction();
  }

  //Display the previous Menu state
  else
  {
    char buffer[50]; // init buffer of 50 bytes to hold expected string size

    // Setup
    eb1.update();
    displayPrep();
    
    // Printing header line
    display.println("Select module test:");
    // Display all current Menu options
    for (size_t i = 0; i < (currentMenuLenPtr); ++i)
    {
      // Highlight line if user is hovering over it
      if (ebState == i)
      {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
      }
      else 
      {
        display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); 
      }
      
      // Print out in int and Text format
      sprintf(buffer, "%d. %s", CurrentMenuPtr[i].choice, CurrentMenuPtr[i].menuTextPtr);
      display.println(buffer);
    }
    
    display.display();
  }
}

//========================================================================
// Functions for debugging
//========================================================================

void dummyInfo(void)
{
  eb1.update();

  displayPrep();
  display.println("Test Information:");
  display.println();
  display.println("This is a demo of an info screen"); display.println("for a test.");
  display.println();

  printConfirmOptions();

  display.display();
}

// Demo of test screen functionality
void dummyTest(void)
{
  while(clicked == 0)
  { 
    dummyInfo();
    delay(3);
  }
  resetClicked();

  while(clicked == 0)
  {
    eb1.update();

    displayPrep();
    display.println("This is a screen for the actual test");
    display.println();

    printConfirmOptions();

    display.display();
    delay(3);
  }
  resetClicked();
}


//========================================================================
// Stuff to implement later...
//========================================================================

/*
// Changes Menu pointer to point to selected Menu screen
void menuUpdate(Menu NewMenu[], size_t newMenuLength, Menu* OldMenuPtr, size_t* oldMenuLengthPtr)
{
  OldMenuPtr = NewMenu;
  oldMenuLengthPtr = newMenuLength;
}

*/
#endif 