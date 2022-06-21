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
  //#include <EEPROM.h>
  #include "EEPROMAnything.h"
  #include <LiquidCrystal_I2C.h> // LCD
//  #include <LiquidCrystal.h>
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
  int Aux1= 0;
  int aux;
  // LCD object
  // liquid crystal needs (rs, rw, e, dat4, dat5, dat6, dat7)
  LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//  LiquidCrystal lcd(12, 11, 6, 5, 4, 3, 2);
  bool led = false;
  bool cambios = false; // Sin cambios de config = false

  int temp = 0;
  byte gasBak = 0;
  byte ranBak = 0;
  byte loopBak = false;

  const int pinSensores = 33; // Salida para manejo de sensores
  byte pinBomba = 12;
  bool swBomba = false;
  byte pinSwBomba = 45;

  
  float adcRead;
  float cteAdc = 4.096 / 1023;

  struct canalEeprom
  {
    byte gas;
    byte ran;
    int rango;
    byte loop;
  };

  canalEeprom canal1;
  String nombreGasC1 = " ";
//  byte gasC1 = 0; // nombre para menú lcd
//  byte ranC1 = 0; // rango sensor expresado en valor entero para menú lcd (0-5)
//  int rangoC1 = 0; // valor máximo del sensor (5 a 10k)
//  bool loopC1 = false; // false = 4-20mA, true = 0-20mA
  float adcC1 = 0; // lectura adc
  int cntAdcC1 = 0; //cuentas adc

  canalEeprom canal2;
  String nombreGasC2 = " ";  
//  byte gasC2 = 0;
//  byte ranC2 = 0;
//  int rangoC2 = 0;
//  bool loopC2 = false; // false = 4-20mA, true = 0-20mA
  float adcC2 = 0; // lectura adc
  int cntAdcC2 = 0; //cuentas adc

  canalEeprom canal3;
  String nombreGasC3 = " ";
//  byte gasC3 = 0;
//  byte ranC3 = 0;
//  int rangoC3 = 0;
//  bool loopC3 = false; // false = 4-20mA, true = 0-20mA
  float adcC3 = 0; // lectura adc
  int cntAdcC3 = 0; //cuentas adc


  canalEeprom canal4;
  String nombreGasC4 = " ";
//  byte gasC4 = 0;
//  byte ranC4 = 0;
//  int rangoC4 = 0;
//  bool loopC4 = false; // false = 4-20mA, true = 0-20mA
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
  
  LCDML_add         (0 ,LCDML_0     ,1,"Iniciar medicion",medicion);
  LCDML_add         (1 ,LCDML_0     ,2,"Configurar canales",NULL);


  LCDML_add         (2 ,LCDML_0_2   ,1,"Canal 1", NULL);
  LCDML_addAdvanced (3 ,LCDML_0_2_1 ,1,NULL,"Rango de sensor",selRan,1,_LCDML_TYPE_default);
  LCDML_addAdvanced (4 ,LCDML_0_2_1 ,2,NULL,"Gas",selGas,1,_LCDML_TYPE_default);
  LCDML_addAdvanced (5 ,LCDML_0_2_1 ,3,NULL,"Loop Corriente",selLoop,1,_LCDML_TYPE_default);
  LCDML_add         (6 ,LCDML_0_2_1 ,4,"Salir",mFunc_back);


  LCDML_add         (7 ,LCDML_0_2   ,2,"Canal 2",NULL);
  LCDML_addAdvanced (8 ,LCDML_0_2_2 ,1,NULL,"Rango de sensor",selRan,2,_LCDML_TYPE_default);
  LCDML_addAdvanced (9 ,LCDML_0_2_2 ,2,NULL,"Gas", selGas,2,_LCDML_TYPE_default);
  LCDML_addAdvanced (10,LCDML_0_2_2 ,3,NULL,"Loop Corriente",selLoop,2,_LCDML_TYPE_default);
  LCDML_add         (11,LCDML_0_2_2 ,4,"Salir", mFunc_back);

  LCDML_add         (12,LCDML_0_2   ,3,"Canal 3",NULL);
  LCDML_addAdvanced (13,LCDML_0_2_3 ,1,NULL,"Rango de sensor",selRan,3,_LCDML_TYPE_default);
  LCDML_addAdvanced (14,LCDML_0_2_3 ,2,NULL,"Gas",selGas,3,_LCDML_TYPE_default);
  LCDML_addAdvanced (15,LCDML_0_2_3 ,3,NULL,"Loop Corriente",selLoop,3,_LCDML_TYPE_default);
  LCDML_add         (16,LCDML_0_2_3 ,4,"Salir", mFunc_back);

  LCDML_add         (17,LCDML_0_2   ,4,"Canal 4",NULL);
  LCDML_addAdvanced (18,LCDML_0_2_4 ,1,NULL,"Rango de sensor",selRan,4,_LCDML_TYPE_default);
  LCDML_addAdvanced (19,LCDML_0_2_4 ,2,NULL,"Gas",selGas,4,_LCDML_TYPE_default);
  LCDML_addAdvanced (20,LCDML_0_2_4 ,3,NULL,"Loop Corriente",selLoop,4,_LCDML_TYPE_default);
  LCDML_add         (21,LCDML_0_2_4 ,4,"Salir",mFunc_back);

  LCDML_add         (22 ,LCDML_0_2  ,5,"Salir",mFunc_back);

  LCDML_add         (23,LCDML_0     ,3,"Guardar config.",guardar);

//  LCDML_addAdvanced (22 ,LCDML_0_1   ,2, NULL,"Mediçasao",Mediçasao,3,_LCDML_TYPE_default);

  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    23

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
//    Serial.println(F(_LCDML_VERSION)); // only for examples

    analogReference(EXTERNAL); // Referencia ADC
  //analogReference(INTERNAL1V1); // Referencia ADC
//  analogReference(INTERNAL2V56); // Referencia ADC

	pinMode(pinBomba, OUTPUT);
	digitalWrite(pinBomba,LOW);
	pinMode(pinSwBomba, INPUT);
	digitalWrite(pinSwBomba,HIGH);
	pinMode(pinSensores, OUTPUT);
	
    // LCD Begin
    lcd.init(); // initialize the lcd 
    lcd.backlight();
    bienvenida();
  
    EEPROM_readAnything(1, canal1);
    EEPROM_readAnything(6, canal2);
    EEPROM_readAnything(11, canal3);
    EEPROM_readAnything(16, canal4);

    Serial.println(canal1.gas);
    Serial.println(canal1.ran);
    Serial.println(canal1.rango);
    Serial.println(canal1.loop);
    Serial.println("*******");
    
    Serial.println(canal2.gas);
    Serial.println(canal2.ran);
    Serial.println(canal2.rango);
    Serial.println(canal2.loop);
    Serial.println("*******");
    
    Serial.println(canal3.gas);
    Serial.println(canal3.ran);
    Serial.println(canal3.rango);
    Serial.println(canal3.loop);
    Serial.println("*******");
    
    Serial.println(canal4.gas);
    Serial.println(canal4.ran);
    Serial.println(canal4.rango);
    Serial.println(canal4.loop);
    Serial.println("*******");


//    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);

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
	controlBomba();
  }
