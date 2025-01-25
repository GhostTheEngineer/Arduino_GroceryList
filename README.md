# Grocery List

An Arduino-based project that allows users to navigate and manage a predefined grocery list using an **Arduino UNO R3**, **LCD1602**, **3 buttons**, and a **10k potentiometer**.

---

## Features

- **List Navigation with Wrapping Support**:
  - Use the **leftmost button** to move up the list.
  - Use the **next button** to move down the list.
  - Wrapping support ensures that navigating past the last item returns to the first item, and vice versa.
  
- **Item Removal**:
  - Use the **rightmost button** to remove the currently highlighted item.
  - The list automatically updates to show the next available items. If the list is empty, a `List is empty` message is displayed.

- **Display**:
  - The **LCD1602** shows **2 items** at a time.
  - An arrow (`<`) indicates the currently highlighted item.
  - When only one item remains, it is displayed on the first line.

- **Challenge**:
  - Currently, there is no way to add new items to the list. This is left as a challenge for anyone who downloads the repository to try!

---

## Components Used

1. **Arduino UNO R3**
2. **LCD1602 Display**
3. **3 Buttons**
4. **10k Potentiometer**

---

## Wiring

A **wiring diagram** in JPG format is included in the repository to help set up the components correctly.

---

## Software Requirements

- **Arduino IDE**
  - Install the **LiquidCrystal** library through the Library Manager.

---

## Repository Contents

- `Code/GroceryList/GroceryList.ino` – The Arduino code for the project.
- `wiring_diagram.jpg` – A wiring diagram to assist with hardware setup.

---

## How It Works

1. **Navigate the List**:
   - Use the **Up** and **Down** buttons to move through the list.
   - The display wraps around when you reach the top or bottom of the list.

2. **Remove an Item**:
   - Highlight an item with the arrow (`<`).
   - Press the **Remove** button to delete it from the list.
   - The list updates automatically.

3. **List Behavior**:
   - If the last item is removed, the display shows `List is empty`.

---

## Challenge

Feel free to enhance this project by adding the ability to **add new items to the list**!

---

## Contributions

This project does not accept contributions. It is designed as a standalone challenge for individuals interested in Arduino projects.

---

## License

This project is license under MIT. Read [here](/LICENSE).

---

Happy coding!
