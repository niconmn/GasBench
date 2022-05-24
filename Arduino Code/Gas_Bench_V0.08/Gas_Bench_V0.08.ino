// ============================================================
// Example:     LCDML_serialmonitor
// ============================================================
// Description:
// This example includes the complete functionality over some
// tabs. All Tabs which are started with "LCDML_display_.."
// generates an output on the display / console / ....
// This example is for the author to test the complete functionality
// ============================================================
// *********************************************************************
// special settings
// *********************************************************************
// enable this line when you are not usigng a standard arduino
// for example when your chip is an ESP or a STM or SAM or something else

//#define _LCDML_cfg_use_ram 

// *********************************************************************
// includes
// *********************************************************************
  #include <LiquidCrystal.h>
  #include <LCDMenuLib2.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  20
  #define _LCDML_DISP_rows  4

  // enable this line (set to 1) to show a header above the first menu element
  // this function can be changed in LCDML_display_menu tab
  #define _LCDML_DSIP_use_header 0

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar

  // LCD object
  // liquid crystal needs (rs, rw, e, dat4, dat5, dat6, dat7)
  LiquidCrystal lcd(12, 11, 6, 5, 4, 3, 2);
  boolean led = false;

  int gasBak = 0;
  int ranBak = 0;
  boolean loopBak = false;
  
  float adcRead;
  float cteAdc = 4.096 / 1023;


  int gasC1 = 0; // nombre para menú lcd
  String nombreGasC1 = " ";
  int ranC1 = 0; // valor entero para menú lcd
  int rangoC1 = 0; // valor máximo del sensor
  boolean loopC1 = false; // false = 4-20mA, true = 0-20mA
  float adcC1 = 0; // lectura adc
  int cntAdcC1 = 0; //cuentas adc

  int gasC2 = 0;
  String nombreGasC2 = " ";  
  int ranC2 = 0;
  int rangoC2 = 0;
  boolean loopC2 = false; // false = 4-20mA, true = 0-20mA
  float adcC2 = 0; // lectura adc
  int cntAdcC2 = 0; //cuentas adc

  int gasC3 = 0;
  String nombreGasC3 = " ";
  int ranC3 = 0;
  int rangoC3 = 0;
  boolean loopC3 = false; // false = 4-20mA, true = 0-20mA
  float adcC3 = 0; // lectura adc
  int cntAdcC3 = 0; //cuentas adc


  int gasC4 = 0;
  String nombreGasC4 = " ";
  int ranC4 = 0;
  int rangoC4 = 0;
  boolean loopC4 = false; // false = 4-20mA, true = 0-20mA
  float adcC4 = 0; // lectura adc
  int cntAdcC4 = 0; //cuentas adc
  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************


// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows-_LCDML_DSIP_use_header, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  // For beginners
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  
  LCDML_add         (0 , LCDML_0     ,1, "Configuracion", NULL);
  LCDML_add         (1 , LCDML_0_1   ,1, "C1", NULL);
  LCDML_addAdvanced (2 , LCDML_0_1_1 ,1, NULL,"Rango de sensor",selRan,1,_LCDML_TYPE_default);
  LCDML_addAdvanced (3 , LCDML_0_1_1 ,2, NULL,"Gas",selGas,1,_LCDML_TYPE_default);
  LCDML_addAdvanced (4 , LCDML_0_1_1 ,3, NULL,"Loop Corriente",selLoop,1,_LCDML_TYPE_default);
  LCDML_add         (5 , LCDML_0_1_1 ,4, "Back",mFunc_back);


  LCDML_add         (6 , LCDML_0_1   ,2, "C2",NULL);
  LCDML_addAdvanced (7 , LCDML_0_1_2 ,1, NULL,"Rango de sensor",selRan,2,_LCDML_TYPE_default);
  LCDML_addAdvanced (8 , LCDML_0_1_2 ,2, NULL,"Gas", selGas,2,_LCDML_TYPE_default);
  LCDML_addAdvanced (9 , LCDML_0_1_2 ,3, NULL,"Loop Corriente",selLoop,2,_LCDML_TYPE_default);
  LCDML_add         (10 ,LCDML_0_1_2 ,4, "Back", mFunc_back);

  LCDML_add         (11 , LCDML_0_1   ,3, "C3",NULL);
  LCDML_addAdvanced (12, LCDML_0_1_3 ,1, NULL,"Rango de sensor",selRan,3,_LCDML_TYPE_default);
  LCDML_addAdvanced (13, LCDML_0_1_3 ,2, NULL,"Gas",selGas,3,_LCDML_TYPE_default);
  LCDML_addAdvanced (14 ,LCDML_0_1_3 ,3, NULL,"Loop Corriente",selLoop,3,_LCDML_TYPE_default);
  LCDML_add         (15, LCDML_0_1_3 ,4, "Back", mFunc_back);

  LCDML_add         (16, LCDML_0_1   ,4, "C4",NULL);
  LCDML_addAdvanced (17, LCDML_0_1_4 ,1, NULL,"Rango de sensor",selRan,4,_LCDML_TYPE_default);
  LCDML_addAdvanced (18, LCDML_0_1_4 ,2, NULL,"Gas",selGas,4,_LCDML_TYPE_default);
  LCDML_addAdvanced (19 ,LCDML_0_1_4 ,3, NULL,"Loop Corriente",selLoop,4,_LCDML_TYPE_default);
  LCDML_add         (20, LCDML_0_1_4 ,4, "Back",mFunc_back);

  LCDML_add         (21, LCDML_0_1   ,5, "Back",mFunc_back);
  LCDML_add         (22, LCDML_0     ,2, "Iniciar Medicion",medicion);
//  LCDML_addAdvanced (22 ,LCDML_0_1   ,2, NULL,"Mediçasao",Mediçasao,3,_LCDML_TYPE_default);

  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    22

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples
    pinMode(A4, OUTPUT);


    // LCD Begin
    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    //LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();   
  }
