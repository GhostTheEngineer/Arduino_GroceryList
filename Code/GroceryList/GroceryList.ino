/******************************************************************************
 * Project: Grocery List
 * File: GroceryList.ino
 * Description:
 *  This file is meant to be used with the Arduino UNO R3 microcontroller, LCD1602, Potentiometer 10k
 *  and 3 buttons (please following wiring diagram included in this repo). This program allows the
 *  user to navigate a predefined finite list with up/down buttons and to remove items using the far-
 *  right button.   
 *
 *  Key Features:
 *  - Up/down navigation.
 *  - List wrapping on traversal.
 *  - Removal of items.
 *  - LCD dimming.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0.0
 * Author: Ghost
 * Created On: 1-23-2025
 * Last Modified: 1-24-2025
 *****************************************************************************/

#include <LiquidCrystal.h> // requires the library to be installed! Search LiquidCrystal by Arduino in library manager and install latest version

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// define button pins
int g_UpBtnPin = 2;
int g_DownBtnPin = 4;
int g_SubmitBtnPin = 5;
bool g_IsBtnPressed = false; // button flag - tells when a button is being pressed(false)

// Checklist data
const char* g_List[15] = { "Apples", "Eggs", "Bread", "Cheese", "Bacon", "Chicken", "Beef", "Milk", "Yogurt", "Ham", "Turkey", "Bagels", "Juice", "Soda", "Coffee" };
int g_Index = 0; // current position in g_List
int g_ListSize = sizeof(g_List) / sizeof(g_List[0]); // virtual size of array - tracks the size of array based on items left, not physical array size in memory
char g_Buffer[20]; // stores item to print to screen - clears once printed


// Misc
long g_PrevMillis = 0; // track time for spam control
const int SPAM_MS_COOLDOWN = 500; // the amount of time in milliseconds to cool down from the last button press (any button)
unsigned char g_ArrowPosition = 1; // track where the arrow is - start on line 2

void clearBuffer() {
  memset(g_Buffer, '\0', sizeof(g_Buffer));
}

void renderItem(int _index, int _line, bool hasArrow) {
  // check if g_List is empty to display message
  if (g_ListSize == 0) {
    lcd.print("List is empty!");
    return;
  }
  
  lcd.setCursor(0, _line); // set line

  //char str[20]; // 20 ensures we have enough room for full string
  sprintf(g_Buffer, "%d", (_index + 1)); // convert index(integer) to cstring - the (+1) shifts due to zero indexing - meant for g_List item number
  strcat(g_Buffer, ". "); // add a period and space between number and item
  strcat(g_Buffer, g_List[_index]); // add the item to the string

  // Add arrow to the line to signify the highlighted item
  if (hasArrow) {
    strcat(g_Buffer, " <");
  }

  lcd.print(g_Buffer); // print to lcd
  clearBuffer(); // clear for next use
}

void removeItem() {
  // Shift elements to the left - the array never shrinks, the element is replaced with empty string and pushed toward back
  for (size_t i = g_Index; i < g_ListSize; i++) {
    if (g_List[i] == "") break; // don't waste time shifting empty elements
    g_List[i] = (i + 1) < g_ListSize ? g_List[i + 1] : "";
  }

  g_ListSize--; // update virtual size of array

  // Incase user removes the last item(end of g_List item) in g_List while the g_List still has more than one item left, we need to update 'index' to previous item
  if(g_ListSize > 0 && g_Index > (g_ListSize - 1)) {
    g_Index--;
  }
}

void setup() {
  // Setup button pins to listen for input
  pinMode(g_UpBtnPin, INPUT_PULLUP); 
  pinMode(g_DownBtnPin, INPUT_PULLUP); 
  pinMode(g_SubmitBtnPin, INPUT_PULLUP); 
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

  lcd.print("Groceries List"); // show message on first line
  renderItem(g_Index, 1, true); // display first item
}

void loop() {

  if (g_ListSize == 0) return; // Prevent further logic if g_List is empty

  long currentMillis = millis();

  // BUTTON PRESS CHECK
  if ((digitalRead(g_UpBtnPin) == LOW || digitalRead(g_DownBtnPin) == LOW || digitalRead(g_SubmitBtnPin) == LOW) && (!g_IsBtnPressed) && (currentMillis - g_PrevMillis) >= SPAM_MS_COOLDOWN) {
    g_IsBtnPressed = true; // update button flag
    g_PrevMillis = currentMillis; // track for spam control
    
    if (digitalRead(g_UpBtnPin) == LOW) { // Up Arrow
      g_Index = (g_Index == 0) ? g_ListSize - 1 : g_Index - 1; // moves one at a time and wraps to last item in g_List when attempting to move to -1
      g_ArrowPosition = 0;
    } else if (digitalRead(g_DownBtnPin) == LOW) { // Down Arrow
      g_Index = (g_Index+1) % g_ListSize; // moves one at a time and wraps to first item in g_List when attempting to move past last item
      g_ArrowPosition = 1;
    } else if (digitalRead(g_SubmitBtnPin) == LOW) { // Submit
      removeItem();
    }

    lcd.clear(); // clear entire lcd screen
    
    // RENDER
    if (g_ListSize > 1) { // only render both lines when there is more than one item left 
      if (g_ArrowPosition == 0) { // moving up
        renderItem(g_Index, 0, true);
        renderItem((g_Index+1) % g_ListSize, 1, false);
      }
      else if (g_ArrowPosition == 1) { // moving down
        renderItem((g_Index == 0) ? g_ListSize - 1 : g_Index - 1, 0, false);
        renderItem(g_Index, 1, true);
      }
      else { // not necessarry but will display if arrow is not at 0 or 1
        lcd.print("Error: arrow!");
      }
    }
    else { // renders only to top line
      renderItem(g_Index, 0, true);
    }
    
  } 

  // Reset button flag if this iteration found a press. Only resets if all buttons are back in up position(unpressed).
  if (g_IsBtnPressed && digitalRead(g_UpBtnPin) == HIGH && digitalRead(g_DownBtnPin) == HIGH && digitalRead(g_SubmitBtnPin) == HIGH) {
    g_IsBtnPressed = false;
  }
  
}
