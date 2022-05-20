/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    //LCDML_UNUSED(param);
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);

    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
    //LCDML.FUNC_setGBA() 

    //
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button or event status change

    // uncomment this line when the screensaver should not be called when this function is running
    // reset screensaver timer
    //LCDML.SCREEN_resetTimer();

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
    // this function is always called when the functions ends.
    // this means when you are calling a jumpTo ore a goRoot function
    // that this part is called before a function is closed
  }
}


 * ===================================================================== *
 */


// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    lcd.setCursor(0, 0);
    lcd.print(F("To close this"));
    lcd.setCursor(0, 1);
    lcd.print(F("function press"));
    lcd.setCursor(0, 2);
    lcd.print(F("any button or use"));
    lcd.setCursor(0, 3);
    lcd.print(F("back button"));
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    lcd.print(F("20 sec wait")); // print some content on first row
    g_func_timer_info = 20;       // reset and set timer
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_1);
  }


  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)) {
      g_func_timer_info--;                // increment the value every second
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(F("  "));
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(g_func_timer_info);       // print the time counter value
    }

    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normally
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("press left or up"));
    lcd.setCursor(0, 1);
    lcd.print(F("count: 0 of 3"));
    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;

        // update LCD content
        // update LCD content
        lcd.setCursor(7, 1); // set cursor
        lcd.print(g_button_value); // print change content
      }
    }

    // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
//uint8_t g_button_value = 0; // button value counter (global variable)
void selGas(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    int gas = 0;
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    switch(param)
      {
      case 1:
        gas = gasC1;
      break;
      case 2:
        gas = gasC2;
      break;
      case 3:
        gas = gasC3;
      break;
      case 4:
        gas = gasC4;
      break;
      default:
          // do nothing
      break;
      }      
    
    gasBak = gas;
    lcd.setCursor(0, 0);
    lcd.print(F("Seleccione Gas:"));
    lcd.setCursor(0, 2);
    lcd.print(F("OK para confirmar"));
    lcd.setCursor(0, 3);
    lcd.print(F("Can para cancelar"));        
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
// the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkUp()) // check if button left is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      if (gasBak < 2)
      gasBak++;
      else
        gasBak = 0;
    }
    if (LCDML.BT_checkDown()) // check if button down is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      if (gasBak > 0)
        gasBak = gasBak - 1;
      else
        gasBak = 2;
    }
    lcd.setCursor(7, 1); // set cursor
    switch(gasBak)
        {
        case 0:
            lcd.print("0 CO2"); // print change content        
        break;

        case 1:
            lcd.print("1 SO2"); // print change content        
        break;

        case 2:
            lcd.print("2 H2S"); // print change content        
        break;

        default:
            // do nothing
        break;
        }      
    if (LCDML.BT_checkEnter()) // check if button left is pressed
    {
      LCDML.BT_resetEnter(); // reset the left button
      switch(param)
        {
        case 1:
          gasC1 = gasBak;
        break;
        case 2:
          gasC2 = gasBak;
        break;
        case 3:
          gasC3 = gasBak;
        break;
        case 4:
          gasC4 = gasBak;
        break;
        default:
            // do nothing
        break;
        }      
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(gasC1);
      Serial.println(gasC2);
      Serial.println(gasC3);
      Serial.println(gasC4);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

// *********************************************************************
//uint8_t g_button_value = 0; // button value counter (global variable)
void selRan(uint8_t param)
// *********************************************************************
{
  int rango = 0;
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    int ran = 0;

    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    switch(param)
      {
      case 1:
        ran = ranC1;
      break;
      case 2:
        ran = ranC2;
      break;
      case 3:
        ran = ranC3;
      break;
      case 4:
        ran = ranC4;
      break;
      default:
          // do nothing
      break;
      }      
    
    ranBak = ran;
    lcd.setCursor(0, 0);
    lcd.print(F("Seleccione rango:"));
    lcd.setCursor(0, 2);
    lcd.print(F("OK para confirmar"));
    lcd.setCursor(0, 3);
    lcd.print(F("Can para cancelar"));        
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
// the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkUp()) // check if button left is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      if (ranBak < 5)
      ranBak++;
      else
        ranBak = 0;
    }
    if (LCDML.BT_checkDown()) // check if button down is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      if (ranBak > 0)
        ranBak = ranBak - 1;
      else
        ranBak = 5;
    }
    lcd.setCursor(0, 1); // set cursor
    lcd.print("                    ");
    lcd.setCursor(5, 1); // set cursor
    switch(ranBak)
        {
        case 0:
            lcd.print("5 ppm"); // print change content
            rango = 5;
        break;

        case 1:
            lcd.print("50 ppm"); // print change content        
            rango = 50;
        break;

        case 2:
            lcd.print("200 ppm"); // print change content        
            rango = 200;
        break;
        case 3:
            lcd.print("2.000 ppm"); // print change content        
            rango = 2000;
        break;
        case 4:
            lcd.print("5.000 ppm"); // print change content        
            rango = 5000;
        break;
        case 5:
            lcd.print("10.000 ppm"); // print change content        
            rango = 10000;
        break;
        default:
            // do nothing
        break;
        }      
    if (LCDML.BT_checkEnter()) // check if button left is pressed
    {
      LCDML.BT_resetEnter(); // reset the left button
      switch(param)
        {
        case 1:
          ranC1 = ranBak;
          rangoC1 = rango;
        break;
        case 2:
          ranC2 = ranBak;
          rangoC2 = rango;
        break;
        case 3:
          ranC3 = ranBak;
          rangoC3 = rango;
        break;
        case 4:
          ranC4 = ranBak;
          rangoC4 = rango;
        break;
        default:
            // do nothing
        break;
        }      
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(rangoC1);
      Serial.println(rangoC2);
      Serial.println(rangoC3);
      Serial.println(rangoC4);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

// *********************************************************************
//uint8_t g_button_value = 0; // button value counter (global variable)
void selLoop(uint8_t param)
// *********************************************************************
{

  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    boolean loop = false;
    
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    switch(param)
      {
      case 1:
        loop = loopC1;
      break;
      case 2:
        loop = loopC2;
      break;
      case 3:
        loop = loopC3;
      break;
      case 4:
        loop = loopC4;
      break;
      default:
          // do nothing
      break;
      }      
    
    loopBak = loop;
    lcd.setCursor(0, 0);
    lcd.print(F("Seleccione loop Cte:"));
    lcd.setCursor(0, 2);
    lcd.print(F("OK para confirmar"));
    lcd.setCursor(0, 3);
    lcd.print(F("Can para cancelar"));        
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {

// the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkUp() || LCDML.BT_checkDown()) // check if button left is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      LCDML.BT_resetDown(); // reset the left button
      loopBak = !loopBak; //// false = 4-20mA, true = 0-20mA   
    }

    lcd.setCursor(5, 1); // set cursor
    if(loopBak == false)
      lcd.print("4/20mA");
    else
      lcd.print("0/20mA"); // print change content

    if (LCDML.BT_checkEnter()) // check if button left is pressed
    {
      LCDML.BT_resetEnter(); // reset the left button
      switch(param)
        {
        case 1:
          loopC1 = loopBak;
        break;
        case 2:
          loopC2 = loopBak;
        break;
        case 3:
          loopC3 = loopBak;
        break;
        case 4:
          loopC4 = loopBak;
        break;
        default:
            // do nothing
        break;
        }      
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(loopC1);
      Serial.println(loopC2);
      Serial.println(loopC3);
      Serial.println(loopC4);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // update LCD content
    lcd.setCursor(0, 0); // set cursor
    lcd.print(F("screensaver")); // print change content
    lcd.setCursor(0, 1); // set cursor
    lcd.print(F("press any key"));
    lcd.setCursor(0, 2); // set cursor
    lcd.print(F("to leave it"));
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      // remmove compiler warnings when the param variable is not used:
      LCDML_UNUSED(param);

      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    
    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}


// *********************************************************************
void mFunc_para(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {

    char buf[20];
    sprintf (buf, "parameter: %d", param);

    lcd.setCursor(0, 0);
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.print(F("press any key"));
    lcd.setCursor(0, 2);
    lcd.print(F("to leave it"));

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // For example
    switch(param)
    {
      case 10:
        // do something
        break;

      case 20:
        // do something
        break;

      case 30:
        // do something
        break;

      default:
        // do nothing
        break;
    }


    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())        // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
/******************************************************************************
adcs
Salidas 4 -20mA:
adcRead = (MAX/(0.016 * R) * (analogRead(pin) * cteAdc)) - MAX/4
MAX es el valor máximo en ppm del sensor
R es la resistencia de carga, 204,7 ohms
******************************************************************************/
/*
void adcs()
{
float adcRead;
TP4(1);

//H2S de DMNT
dmntCnt = (analogRead(pinDmnt));
// (# de cuentas * (5V/1023) * divisor resistivo)
dmnt = dmntCnt * cteAdc * (1 + 1) / 1;

//H2S de 50ppm
h2sCnt = (analogRead(pinH2S));
adcRead = (50/(0.016 * 204.7) * (h2sCnt * cteAdc)) - 50/4;
if(adcRead < 0)
  h2s = 0;
else
  h2s = adcRead;

//SO2 de 200ppm
so2Cnt = (analogRead(pinSO2));
adcRead = (200/(0.016 * 204.7) * (so2Cnt * cteAdc)) - 200/4;
if(adcRead < 0)
  so2 = 0;
else
  so2 = adcRead;

//CO2 de 10.000ppm
co2Cnt = (analogRead(pinCO2));
adcRead = (co2Cnt * cteAdc) * 10000 / (.02 * 204.7);
//adcRead = (510 * cteAdc) * 10000 / (.02 * 204.7);
if(adcRead < 0)
  co2 = 0;
else
  co2 = adcRead;

// Batería
batCnt = (analogRead(pinBat));
// (# de cuentas * (5V/1023) * divisor resistivo) + caída en diodo de entrada
bat = (batCnt * cteAdc * (120 + 47) / 47) + 0.3;

TP4(0);

Serial.print("\nADCs: ");
Serial.print(dmnt,1);
Serial.print(", ");
Serial.print(h2s,0);
Serial.print(", ");
Serial.print(so2,0);
Serial.print(", ");
Serial.print(co2,0);
Serial.print(", ");
Serial.print(bat,1);
Serial.println();
}
*/