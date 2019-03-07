
#define SCREEN_MAX_ROWS             3
#define SCREEN_MENU_HEADER_ROWS     1

#define BUTTON_BACK_PIN   2
#define BUTTON_GO_PIN     3
#define BUTTON_PREV_PIN   4
#define BUTTON_NEXT_PIN   5

#define MENU_ID_TOP_CONTROL         10
#define MENU_ID_TOP_SIMULATOR       11
#define MENU_ID_TOP_TRAINER         12
#define MENU_ID_TOP_STUDENT         13
#define MENU_ID_TOP_SETTING         14

#define MENU_ID_CONTROL_AUX         20
#define MENU_ID_CONTROL_TYPR        21
#define MENU_ID_CONTROL_MODE        22
#define MENU_ID_CONTROL_BATTERY     23
#define MENU_ID_CONTROL_SWD         24
#define MENU_ID_CONTROL_RX          25

#define MENU_ID_SETTING_TX          30
#define MENU_ID_SETTING_RX          31
#define MENU_ID_SETTING_DATA_RST    32
#define MENU_ID_SETTING_SOFT_RST    33

#define MENU_ID_RX_0                40
#define MENU_ID_RX_1                41
#define MENU_ID_RX_2                42
#define MENU_ID_RX_3                43
#define MENU_ID_RX_4                44
#define MENU_ID_RX_5                45
#define MENU_ID_RX_6                46
#define MENU_ID_RX_7                47
#define MENU_ID_RX_8                48
#define MENU_ID_RX_9                49

#define MENU_ID_RX_SETTING_SELECT   50
#define MENU_ID_RX_SETTING_RENAME   51
#define MENU_ID_RX_SETTING_BIND     52
#define MENU_ID_RX_SETTING_TOKEN    53
#define MENU_ID_RX_SETTING_CHANNEL  54

#define MENU_ID_RX_RENAME_OK        60

#define RX_NAME_MAX_LEN             13

#define ITEM_EDIT_NOT_SELECTED      100
#define NULL_CHAR                   '\0'


typedef struct menu_node_item {
  uint8_t Id;
  char* Menu;
  struct menu_node* Item;
  void (*LookupFunc)(bool*);
} MenuNodeItem;

typedef struct menu_node {
  char* Title;
  menu_node* Prev;
  MenuNodeItem* Items;
  uint8_t Index;
  uint8_t ScrollIndex;
  uint8_t ItemCount;
  uint8_t LookupItemCount;
  uint8_t ParentId;
  char* ParentMenu;
  void (*ExecFunc)(bool);
} MenuNode;

typedef struct menu_item_edit {
  char Value[RX_NAME_MAX_LEN];
  uint8_t Index;
} MenuItemEdit;


const char allowed_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 -_:*";

// Top menu items
const char menu_top_title[] = "MODE";   // Menu title
const char menu_top_0[] = "CONTROL";
const char menu_top_1[] = "SIMULATOR";
const char menu_top_2[] = "TRAINER";
const char menu_top_3[] = "STUDENT";
const char menu_top_4[] = "SETTING";

// Control menu items
const char menu_control_title[] = "CONTROL";
const char menu_control_0[] = "AUX 1-N";    // when IsTrimming == false
const char menu_control_1[] = "TYPR Rate";  // when IsTrimming == true
const char menu_control_2[] = "MODE";
const char menu_control_3[] = "Battery";
const char menu_control_4[] = "SWD 1-2";
const char menu_control_5[] = "RX";

// Setting menu items
const char menu_setting_title[] = "SETTING";
const char menu_setting_0[] = "TX_UniqueId";
const char menu_setting_1[] = "RX Selection";
const char menu_setting_2[] = "Data Reset";
const char menu_setting_3[] = "Soft Reset/Restart";

// TX_UniqueId menu items


// RX meu items
const char menu_rx_title[] = "RX";
char menu_rx[][RX_NAME_MAX_LEN] = {"RX1 Name", "RX2 Name", "RX3 Name", "RX4 Name", "RX5 Name", "RX6 Name", "RX7 Name", "RX8 Name", "RX9 Name", "RX10 Name"};


// RX setting menu items
const char menu_rx_setting_0[] = "Select";
const char menu_rx_setting_1[] = "Rename";
const char menu_rx_setting_2[] = "Bind";
const char menu_rx_setting_3[] = "(Token)";
const char menu_rx_setting_4[] = "(Channel)";


MenuNode* topMenu;
MenuNode* currentMenu;
MenuNode* rxSettingTemplate;
MenuNode* rxRenameTemplate;
MenuItemEdit itemEdit;
bool IsTrimming = false;
int inputVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUTTON_BACK_PIN, INPUT_PULLUP);
  pinMode(BUTTON_GO_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);

  setupMenu();
  
  showMenu(currentMenu);

//  selectMenu(); // running the currently select menu

//  goBackMenu(); // move back one step in the menu hierarchy
//
//  selectMenu();
//  
//  navigateMenu(currentMenu, 1); // simulating Menu Down button press
//  selectMenu();
//  navigateMenu(currentMenu, 1);
//  navigateMenu(currentMenu, 1);
//  navigateMenu(currentMenu, 1);
//  selectMenu();
//  navigateMenu(currentMenu, 1);
//  selectMenu();
//  navigateMenu(currentMenu, 1);
//  navigateMenu(currentMenu, 1);
//  selectMenu();
//  navigateMenu(currentMenu, 1);
//  selectMenu();
//
//  goBackMenu();
//  goBackMenu();
//
//  selectMenu();
//  navigateMenu(currentMenu, 1);
//  selectMenu();
//
//  goBackMenu();
//  goBackMenu();
//  goBackMenu();
//  goBackMenu();
//  goBackMenu();
  
//  navigateMenu(currentMenu, -1);  // simulating Menu Up button press
//  navigateMenu(currentMenu, -1);
//  selectMenu();
//  navigateMenu(currentMenu, -1);
//  navigateMenu(currentMenu, -1);
//  selectMenu();
//  navigateMenu(currentMenu, -1);
//  navigateMenu(currentMenu, -1);
}

void setupMenu()  {
  MenuNode* controlMenu;
  MenuNode* settingMenu;
  MenuNode* rxMenu;
  
  // Top menu --------------------
  topMenu = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(topMenu, menu_top_title, 5);
  initMenuNodeItem(topMenu->Items, 0, MENU_ID_TOP_CONTROL, menu_top_0);
  initMenuNodeItem(topMenu->Items, 1, MENU_ID_TOP_SIMULATOR, menu_top_1);
  initMenuNodeItem(topMenu->Items, 2, MENU_ID_TOP_TRAINER, menu_top_2);
  initMenuNodeItem(topMenu->Items, 3, MENU_ID_TOP_STUDENT, menu_top_3);
  initMenuNodeItem(topMenu->Items, 4, MENU_ID_TOP_SETTING, menu_top_4);

  currentMenu = topMenu;  // Top menu is seleted by default

  // Control menu --------------------
  controlMenu = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(controlMenu, menu_control_title, 6);
  initMenuNodeItemWithLookup(controlMenu->Items, 0, MENU_ID_CONTROL_AUX, menu_control_0, funcIsNotTrimming);
  initMenuNodeItemWithLookup(controlMenu->Items, 1, MENU_ID_CONTROL_TYPR, menu_control_1, funcIsTrimming);
  initMenuNodeItem(controlMenu->Items, 2, MENU_ID_CONTROL_MODE, menu_control_2);
  initMenuNodeItem(controlMenu->Items, 3, MENU_ID_CONTROL_BATTERY, menu_control_3);
  initMenuNodeItem(controlMenu->Items, 4, MENU_ID_CONTROL_SWD, menu_control_4);
  initMenuNodeItem(controlMenu->Items, 5, MENU_ID_CONTROL_RX, menu_control_5);
  controlMenu->Prev = topMenu;  // Link back to the previous menu node
  topMenu->Items[0].Item = controlMenu;  // Link with the menu item in the previous menu node

  // Setting menu ---------------------
  settingMenu = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(settingMenu, menu_setting_title, 4);
  initMenuNodeItem(settingMenu->Items, 0, MENU_ID_SETTING_TX, menu_setting_0);
  initMenuNodeItem(settingMenu->Items, 1, MENU_ID_SETTING_RX, menu_setting_1);
  initMenuNodeItem(settingMenu->Items, 2, MENU_ID_SETTING_DATA_RST, menu_setting_2);
  initMenuNodeItem(settingMenu->Items, 3, MENU_ID_SETTING_SOFT_RST, menu_setting_3);
  settingMenu->Prev = topMenu;  // Link back to the previous menu node
  topMenu->Items[4].Item = settingMenu;  // Link with the menu item in the previous menu node

  // RX Selection menu ----------------
  rxMenu = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(rxMenu, menu_rx_title, 10);
  initMenuNodeItem(rxMenu->Items, 0, MENU_ID_RX_0, menu_rx[0]);
  initMenuNodeItem(rxMenu->Items, 1, MENU_ID_RX_1, menu_rx[1]);
  initMenuNodeItem(rxMenu->Items, 2, MENU_ID_RX_2, menu_rx[2]);
  initMenuNodeItem(rxMenu->Items, 3, MENU_ID_RX_3, menu_rx[3]);
  initMenuNodeItem(rxMenu->Items, 4, MENU_ID_RX_4, menu_rx[4]);
  initMenuNodeItem(rxMenu->Items, 5, MENU_ID_RX_5, menu_rx[5]);
  initMenuNodeItem(rxMenu->Items, 6, MENU_ID_RX_6, menu_rx[6]);
  initMenuNodeItem(rxMenu->Items, 7, MENU_ID_RX_7, menu_rx[7]);
  initMenuNodeItem(rxMenu->Items, 8, MENU_ID_RX_8, menu_rx[8]);
  initMenuNodeItem(rxMenu->Items, 9, MENU_ID_RX_9, menu_rx[9]);
  rxMenu->Prev = settingMenu;  // Link back to the previous menu node
  settingMenu->Items[1].Item = rxMenu;  // Link with the menu item in the previous menu node

  // RX Setting template --------------------
  rxSettingTemplate = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(rxSettingTemplate, "", 5);
  initMenuNodeItem(rxSettingTemplate->Items, 0, MENU_ID_RX_SETTING_SELECT, menu_rx_setting_0);
  initMenuNodeItem(rxSettingTemplate->Items, 1, MENU_ID_RX_SETTING_RENAME, menu_rx_setting_1);
  initMenuNodeItem(rxSettingTemplate->Items, 2, MENU_ID_RX_SETTING_BIND, menu_rx_setting_2);
  initMenuNodeItem(rxSettingTemplate->Items, 3, MENU_ID_RX_SETTING_TOKEN, menu_rx_setting_3);
  initMenuNodeItem(rxSettingTemplate->Items, 4, MENU_ID_RX_SETTING_CHANNEL, menu_rx_setting_4);
  rxSettingTemplate->Prev = rxMenu;  // Link back to the previous menu node

  // RX Rename template ---------------------
  rxRenameTemplate = (MenuNode*)malloc(sizeof(MenuNode));
  initMenuNode(rxRenameTemplate, "", 0);
  rxRenameTemplate->ExecFunc = showRxRename;
  rxRenameTemplate->Prev = rxSettingTemplate;  // Link back to the previous menu node

  itemEdit.Index = ITEM_EDIT_NOT_SELECTED;
}

void initMenuNode(MenuNode* node, char* title, uint8_t itemCount) {
  node->Title = title;
  node->Index = 0;
  node->ScrollIndex = 0;
  node->ItemCount = itemCount;
  node->LookupItemCount = itemCount;
  node->ParentId = 0;
  node->ParentMenu = NULL;
  node->Prev = NULL;
  node->ExecFunc = NULL;
  node->Items = (MenuNodeItem*)malloc(itemCount * sizeof(MenuNodeItem));
}

//void initMenuNodeWithParentData(MenuNode* node, char* title, uint8_t itemCount, char *parentMenu, uint8_t parentId) {
//  initMenuNode(node, title, itemCount);
//  node->ParentId = parentId;
//  node->ParentMenu = parentMenu;
//}

void initMenuNodeItem(MenuNodeItem* items, uint8_t index, uint8_t id, char* menu)  {
  MenuNodeItem* nodeItem = &items[index];
  nodeItem->Id = id;
  nodeItem->Menu = menu;
  nodeItem->Item = NULL;
  nodeItem->LookupFunc = NULL;
}

void initMenuNodeItemWithLookup(MenuNodeItem* items, uint8_t index, uint8_t id, char* menu, void (*func)(bool*))  {
  MenuNodeItem* nodeItem = &items[index];
  initMenuNodeItem(items, index, id, menu);
  nodeItem->LookupFunc = func;
}

void showMenu(MenuNode* node)  {
  showMenu(node, true);
}

void showMenu(MenuNode* node, bool printLine)  {
  if (node) {
    int totalLines = node->ItemCount + SCREEN_MENU_HEADER_ROWS;
    int printStartIndex = node->ScrollIndex;
    int printEndIndex = printStartIndex + SCREEN_MAX_ROWS - 1;

//    if (node->Index + SCREEN_MENU_HEADER_ROWS < SCREEN_MAX_ROWS)  {
//      printStartIndex = 0;
//      printEndIndex = printStartIndex + SCREEN_MAX_ROWS - 1;
//    }
//
//    if (printEndIndex >= totalLines)  {
//      printEndIndex = totalLines - SCREEN_MENU_HEADER_ROWS;
//      printStartIndex = printEndIndex - SCREEN_MAX_ROWS + SCREEN_MENU_HEADER_ROWS;
//    }

    if (printStartIndex < 0)  {
      printStartIndex = 0;
    }
    
    if (printStartIndex == 0) {
      Serial.print("== ");
      if (node->ParentMenu) {
        Serial.print(node->ParentMenu);
      }
      else  {
        Serial.print(node->Title);
      }
      Serial.println(" =="); // print Title first
    }
    
    bool lookupData = true;
    int j = 0;
    
    for (int i = 0; i < node->ItemCount; i++) {
//      lookupData = true;
      
//      if (node->Items[i].LookupFunc)  {
//        node->Items[i].LookupFunc(&lookupData);
//      }

//      if (lookupData) {
        if ((i + 1) >= printStartIndex && (i + 1) <= printEndIndex) {
          if (node->Index == j) {
            Serial.print("*");
          }
          else  {
            Serial.print(" ");
          }
          
          Serial.println(node->Items[i].Menu); // print each menu item
        }
        j++;
//      }
    }
    node->LookupItemCount = j;  // Refresh the number of items in a node
  }
  else  {
    Serial.println("Menu not set!");
  }

  if (printLine)  {
    Serial.println(""); // print an empty line
  }
}

void funcIsTrimming(bool* bOutput)  {
  *bOutput = IsTrimming;
}

void funcIsNotTrimming(bool* bOutput) {
  *bOutput = !IsTrimming;
}

void navigateMenu(MenuNode* node, int8_t upOrDown) {
  bool itemEditMode = false;
  
  if (node) {
    if (itemEdit.Index == ITEM_EDIT_NOT_SELECTED) {
      if (upOrDown == 1)  {
        node->Index++;
        if (node->Index >= node->LookupItemCount) {
          node->Index = 0;
        }
  
        // work out the new ScrollIndex for the pagination
        if (node->Index == 0) {
          node->ScrollIndex = 0;
        }
        else if (node->Index >= (node->ScrollIndex - SCREEN_MENU_HEADER_ROWS) &&
            node->Index < ((node->ScrollIndex - SCREEN_MENU_HEADER_ROWS) + SCREEN_MAX_ROWS)) {
              // do nothing
        }
        else  {
          node->ScrollIndex++;
        }
      }
      else if (upOrDown == -1)  {
        if (node->Index == 0)  {
          node->Index = node->LookupItemCount - 1;
        }
        else  {
          node->Index--;
        }
  
        // work out the new ScrollIndex for the pagination
        if (node->Index == 0) {
          node->ScrollIndex = 0;
        }
        else if (node->Index >= (node->ScrollIndex - SCREEN_MENU_HEADER_ROWS) &&
            node->Index < ((node->ScrollIndex - SCREEN_MENU_HEADER_ROWS) + SCREEN_MAX_ROWS)) {
              // do nothing
        }
        else  {
          if (node->ScrollIndex == 0)  {
            node->ScrollIndex = node->ItemCount - SCREEN_MAX_ROWS + SCREEN_MENU_HEADER_ROWS;
          }
          else  {
            node->ScrollIndex--;
          }
        }
      }
    }
    else  {
      itemEditMode = true;
      itemEdit.Value[itemEdit.Index] = getNextCharValue(itemEdit.Value[itemEdit.Index], upOrDown);
    }
    
    showMenu(node, !itemEditMode);  // print menu

    if (node->ExecFunc) {
      node->ExecFunc(false);
    }
  }
}

uint8_t getNextCharValue(uint8_t ch, int8_t upOrDown) {
  uint8_t len = strlen(allowed_chars);
  char *pch = strchr(allowed_chars, ch);
  uint8_t index = (pch - allowed_chars);
  
  if (upOrDown == 1) { // up
    if (index >= len - 1) {
      index = 0;
    }
    else  {
      index++;
    }
  }
  else  { // down
    if (index == 0)  {
      index = len - 1;
    }
    else  {
      index--;
    }
  }

  return allowed_chars[index];
}

void selectMenu() {
  if (currentMenu) {
    if (itemEdit.Index == ITEM_EDIT_NOT_SELECTED) {
      MenuNode* temp = NULL;
  
      bool lookupData = true;
      int j = 0;
      uint8_t menuId = 0;
      char* title;
      
      for (int i = 0; i < currentMenu->ItemCount; i++) {
  //      lookupData = true;
        
  //      if (currentMenu->Items[i].LookupFunc)  {
  //        currentMenu->Items[i].LookupFunc(&lookupData);
  //      }
  
  //      if (lookupData) {
          if (currentMenu->Index == j)  {
            temp = currentMenu->Items[i].Item;
            menuId = currentMenu->Items[i].Id;
            title = currentMenu->Items[i].Menu;
          }
          j++;
  //      }
      }
      
      if (temp) {
        currentMenu = temp;
        currentMenu->Index = 0;  // resetting use's selection in the previous visit to the menu
        currentMenu->ScrollIndex = 0;
        
        showMenu(currentMenu);  // print menu
      }
      else  { // No more sub-menu. Take action now
  //      Serial.println("No sub-menu found. Handling the menu"); // for testing only
        handleMenu(menuId, title); // Id distinguishes each menu
      }
    }
    else  {
      showMenu(currentMenu, false);  // print menu
      
      itemEdit.Index++;
      if (itemEdit.Index >= RX_NAME_MAX_LEN)  {
        itemEdit.Index = 0;
        // save the data
        if (currentMenu->ExecFunc)  {
          currentMenu->ExecFunc(true);
        }
      }
      else  {
        if (currentMenu->ExecFunc)  {
          currentMenu->ExecFunc(false);
        }
      }
    }
  }
}

void handleMenu(uint8_t menuId, char* title) {
  if (menuId >= MENU_ID_RX_0 && menuId <= MENU_ID_RX_9) { // RX Name item has been selected
    rxSettingTemplate->ParentId = menuId;
    rxSettingTemplate->ParentMenu = title;
    currentMenu = rxSettingTemplate;
    currentMenu->Index = 0;  // resetting use's selection in the previous visit to the menu
    currentMenu->ScrollIndex = 0;  // resetting use's selection in the previous visit to the menu
    
    showMenu(currentMenu);  // print menu
  }
  else if (menuId == MENU_ID_RX_SETTING_RENAME) {
    rxRenameTemplate->ParentId = rxRenameTemplate->ParentId;
    rxRenameTemplate->ParentMenu = rxSettingTemplate->ParentMenu;
    currentMenu = rxRenameTemplate;
    currentMenu->Index = 0;  // resetting use's selection in the previous visit to the menu
    currentMenu->ScrollIndex = 0;  // resetting use's selection in the previous visit to the menu
    
    showMenu(currentMenu, false);  // print menu

    if (itemEdit.Index == ITEM_EDIT_NOT_SELECTED) {
      strcpy(itemEdit.Value, rxRenameTemplate->ParentMenu);
      itemEdit.Index = 0;
    }

    showRxRename(false);
  }
  else  {
    switch (menuId) {
      case MENU_ID_CONTROL_AUX:
//        Serial.println("Action: Control -> AUX");
        break;
      case MENU_ID_CONTROL_TYPR:
//        Serial.println("Action: Control -> TYPR");
        break;
      case MENU_ID_CONTROL_MODE:
//        Serial.println("Action: Control -> MODE");
        break;
      case MENU_ID_CONTROL_BATTERY:
//        Serial.println("Action: Control -> BATTERY");
        break;
      case MENU_ID_CONTROL_SWD:
//        Serial.println("Action: Control -> SWD");
        break;
      case MENU_ID_CONTROL_RX:
//        Serial.println("Action: Control -> RX");
        break;
      case MENU_ID_RX_RENAME_OK:
        strcpy(rxRenameTemplate->ParentMenu, title);
        break;
    }
  }
  Serial.println(""); // print an empty line
}

void showRxRename(bool saveMode) {
  if (saveMode) {
    handleMenu(MENU_ID_RX_RENAME_OK, itemEdit.Value);  // save the RX name from the user
    goBackMenu();
  }
  else  {
    Serial.println(itemEdit.Value);
  
    uint8_t i = 0;
  
    while (i < itemEdit.Index)  {
      Serial.print(" ");
      i++;
    }
  
    Serial.println("-");
  }
}

void goBackMenu() {
  if (currentMenu) {
    itemEdit.Index = ITEM_EDIT_NOT_SELECTED;
    
    if (currentMenu->Prev) {
      currentMenu = currentMenu->Prev;
    }
    showMenu(currentMenu);  // print menu
  }
}

void SerialWriteNum(uint32_t num, bool newLine) {
  char str[10];
  ltoa(num, str, 10);

  if (newLine)  {
    Serial.println(str);
  }
  else  {
    Serial.print(str);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  bool pressed = false;
  
  inputVal = digitalRead(BUTTON_BACK_PIN);
  if (inputVal == LOW) {
    pressed = true;
    goBackMenu();
  }
  
  inputVal = digitalRead(BUTTON_GO_PIN);
  if (inputVal == LOW) {
    pressed = true;
    selectMenu();
  }
  
  inputVal = digitalRead(BUTTON_PREV_PIN);
  if (inputVal == LOW) {
    pressed = true;
    navigateMenu(currentMenu, -1);
  }
  
  inputVal = digitalRead(BUTTON_NEXT_PIN);
  if (inputVal == LOW) {
    pressed = true;
    navigateMenu(currentMenu, 1);
  }

  if (pressed)  {
    delay(500);
  }
}
