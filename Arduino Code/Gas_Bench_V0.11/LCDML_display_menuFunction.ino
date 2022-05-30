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


/*********************************************************************
selGas
//uint8_t g_button_value = 0; // button value counter (global variable)
*********************************************************************/
void selGas(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    int gas = 0;
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    switch(param)
      {
      case 1:
        gas = canal1.gas;
      break;
      case 2:
        gas = canal2.gas;
      break;
      case 3:
        gas = canal3.gas;
      break;
      case 4:
        gas = canal4.gas;
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
      if (gasBak < 3)
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
        gasBak = 3;
    }
    lcd.setCursor(7, 1); // set cursor
    switch(gasBak)
        {
        case 0:
            lcd.print("CO2"); // print change content        
        break;

        case 1:
            lcd.print("SO2"); // print change content        
        break;

        case 2:
            lcd.print("H2S"); // print change content        
        break;
        case 3:
            lcd.print("---"); // print change content        
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
          canal1.gas = gasBak;
//          EEPROM.update(1, gasBak);
        break;
        case 2:
          canal2.gas = gasBak;
//          EEPROM.update(5, gasBak);
        break;
        case 3:
          canal3.gas = gasBak;
//          EEPROM.update(9, gasBak);
        break;
        case 4:
          canal4.gas = gasBak;
//          EEPROM.update(13, gasBak);
        break;
        default:
            // do nothing
        break;
        }      
/*      EEPROM_writeAnything(1, canal1);
      EEPROM_writeAnything(6, canal2);
      EEPROM_writeAnything(11, canal3);
      EEPROM_writeAnything(16, canal4);
*/
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(canal1.gas);
      Serial.println(canal2.gas);
      Serial.println(canal3.gas);
      Serial.println(canal4.gas);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

/*********************************************************************
selRan
//uint8_t g_button_value = 0; // button value counter (global variable)
 *********************************************************************/
void selRan(uint8_t param)
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
        ran = canal1.ran;
      break;
      case 2:
        ran = canal2.ran;
      break;
      case 3:
        ran = canal3.ran;
      break;
      case 4:
        ran = canal4.ran;
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
          canal1.ran = ranBak;
          canal1.rango = rango;
//          EEPROM.update(2, ranBak);
//          EEPROM.update(3, rango);
          break;
        case 2:
          canal2.ran = ranBak;
          canal2.rango = rango;
//          EEPROM.update(6, ranBak);
//          EEPROM.update(7, rango);          
        break;
        case 3:
          canal3.ran = ranBak;
          canal3.rango = rango;
//          EEPROM.update(10, ranBak);
//          EEPROM.update(11, rango);         
        break;
        case 4:
          canal4.ran = ranBak;
          canal4.rango = rango;
//          EEPROM.update(14, ranBak);
//          EEPROM.update(15, rango);        
        break;
        default:
            // do nothing
        break;
        }      
/*      EEPROM_writeAnything(1, canal1);
      EEPROM_writeAnything(6, canal2);
      EEPROM_writeAnything(11, canal3);
      EEPROM_writeAnything(16, canal4);
*/
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(canal1.rango);
      Serial.println(canal2.rango);
      Serial.println(canal3.rango);
      Serial.println(canal4.rango);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}

/*********************************************************************
selLoop
//uint8_t g_button_value = 0; // button value counter (global variable)
 *********************************************************************/

 void selLoop(uint8_t param)
{

  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    boolean loop = false;
    
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    switch(param)
      {
      case 1:
        loop = canal1.loop;
      break;
      case 2:
        loop = canal2.loop;
      break;
      case 3:
        loop = canal3.loop;
      break;
      case 4:
        loop = canal4.loop;
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
      lcd.print("4-20mA");
    else
      lcd.print("0-20mA"); // print change content

    if (LCDML.BT_checkEnter()) // check if button left is pressed
    {
      LCDML.BT_resetEnter(); // reset the left button
      switch(param)
        {
        case 1:
          canal1.loop = loopBak;
//          EEPROM.update(5, loopBak);
        break;
        case 2:
          canal2.loop = loopBak;
//          EEPROM.update(9, loopBak);
        break;
        case 3:
          canal3.loop = loopBak;
//          EEPROM.update(13, loopBak);
        break;
        case 4:
          canal4.loop = loopBak;
//          EEPROM.update(17, loopBak);
        break;
        default:
            // do nothing
        break;
        }      
/*      EEPROM_writeAnything(1, canal1);
      EEPROM_writeAnything(6, canal2);
      EEPROM_writeAnything(11, canal3);
      EEPROM_writeAnything(16, canal4);
*/
      LCDML.FUNC_goBackToMenu();      // leave this function
      Serial.println(canal1.loop);
      Serial.println(canal2.loop);
      Serial.println(canal3.loop);
      Serial.println(canal4.loop);
      Serial.println();
    }    
  }
  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    
    // you can here reset some global vars or do nothing
  }
}

/*********************************************************************
Medicion:
*********************************************************************/
unsigned long g_timer_2 = 0;    // timer variable (global variable)
void medicion(uint8_t param)
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_2);
  }

  if(LCDML.FUNC_loop())

    
    if(LCDML.TIMER_ms(g_timer_2, 1000)) 
    {
    impresion();//imprimo por puerto serie info gral
  //******************************************************************************
//C1
  adcRead = (analogRead(A4));
  cntAdcC1 = adcRead;
  if(canal1.loop == false)
    {
      //4-20mA
      adcC1 = (canal1.rango/(0.016 * 204.7) * (adcRead * cteAdc)) - canal1.rango/4;
    }
  else
    {
      //0-20mA
      adcC1 = (adcRead * cteAdc) * canal1.rango / (.02 * 204.7);
    }
  if(adcC1 < 0)
    adcC1 = 0;
  

//C2
  adcRead = (analogRead(A5));
  cntAdcC2 = adcRead;  
  if(canal2.loop == false)
    {
      //4-20mA
      adcC2 = (canal2.rango/(0.016 * 204.7) * (adcRead * cteAdc)) - canal2.rango/4;
    }
  else
    {
      //0-20mA
      adcC2 = (adcRead * cteAdc) * canal2.rango / (.02 * 204.7);
    }
  if(adcC2 < 0)
    adcC2 = 0;
//C3
  adcRead = (analogRead(A6));
  cntAdcC3 = adcRead;  
  if(canal3.loop == false)
    {
      //4-20mA
      adcC3 = (canal3.rango/(0.016 * 204.7) * (adcRead * cteAdc)) - canal3.rango/4;
    }
  else
    {
      //0-20mA
      adcC3 = (adcRead * cteAdc) * canal3.rango / (.02 * 204.7);
    }
  if(adcC3 < 0)
    adcC3 = 0;
//C4
  
  adcRead = (analogRead(A7));
  cntAdcC4 = adcRead;
  if(canal4.loop == false)
    {
      //4-20mA
      adcC4 = (canal4.rango/(0.016 * 204.7) * (adcRead * cteAdc)) - canal4.rango/4;
    }
  else
    {
      //0-20mA
      adcC4 = (adcRead * cteAdc) * canal4.rango / (.02 * 204.7);
    }
  if(adcC4 < 0)
    adcC4 = 0;
 
  //******************************************************************************
      lcd.setCursor(0, 0); // set cursor
      lcd.print(F("1          :     ppm")); // print change content
      lcd.setCursor(2, 0); // set cursor
      switch(canal1.gas)
          {
          case 0:
              lcd.print("CO2"); // print change content 
          break;
          case 1:
              lcd.print("SO2"); // print change content        
          break;
          case 2:
              lcd.print("H2S"); // print change content        
          break;
          case 3:
              lcd.print("---"); // print change content        
          break;
          default:
              // do nothing
          break;
          }      
      if(canal1.gas == 3)
        {
          lcd.setCursor(6, 0); // set cursor
          lcd.print("[---]"); // print change content        
          lcd.setCursor(12, 0); // set cursor
          lcd.print("---- "); // print change content        
        }
      else
        {
        switch(canal1.ran)
            {
            case 0:
                lcd.setCursor(8, 0); // set cursor
                lcd.print("[5]"); // print change content
            break;

            case 1:
                lcd.setCursor(7, 0); // set cursor
                lcd.print("[50]"); // print change content        
            break;

            case 2:
                lcd.setCursor(6, 0); // set cursor
                lcd.print("[200]"); // print change content        
            break;
            case 3:
                lcd.setCursor(7, 0); // set cursor
                lcd.print("[2k]"); // print change content        
            break;
            case 4:
                lcd.setCursor(7, 0); // set cursor
                lcd.print("[5k]"); // print change content        
            break;
            case 5:
                lcd.setCursor(6, 0); // set cursor
                lcd.print("[10k]"); // print change content        
            break;
            default:
                // do nothing
            break;
            }
        if(adcC1 < 1000)
          {
          lcd.setCursor(12, 0); // set cursor
          lcd.print(adcC1,1); // print change content
          }
        else
          {
          lcd.setCursor(12, 0); // set cursor
          lcd.print(adcC1,0); // print change content
          }
        }
//
      lcd.setCursor(0, 1); // set cursor
      lcd.print(F("2          :     ppm")); // print change content
      lcd.setCursor(2, 1); // set cursor
      switch(canal2.gas)
          {
          case 0:
              lcd.print("CO2"); // print change content        
          break;
          case 1:
              lcd.print("SO2"); // print change content        
          break;
          case 2:
              lcd.print("H2S"); // print change content        
          break;
          case 3:
              lcd.print("---"); // print change content        
          break;
          default:
              // do nothing
          break;
          }
      if(canal2.gas == 3)
        {
          lcd.setCursor(6, 1); // set cursor
          lcd.print("[---]"); // print change content        
          lcd.setCursor(12, 1); // set cursor
          lcd.print("---- "); // print change content        
        }
      else
        {
        switch(canal2.ran)
            {
            case 0:
                lcd.setCursor(8, 1); // set cursor
                lcd.print("[5]"); // print change content
            break;

            case 1:
                lcd.setCursor(7, 1); // set cursor
                lcd.print("[50]"); // print change content        
            break;

            case 2:
                lcd.setCursor(6, 1); // set cursor
                lcd.print("[200]"); // print change content        
            break;
            case 3:
                lcd.setCursor(7, 1); // set cursor
                lcd.print("[2k]"); // print change content        
            break;
            case 4:
                lcd.setCursor(7, 1); // set cursor
                lcd.print("[5k]"); // print change content        
            break;
            case 5:
                lcd.setCursor(6, 1); // set cursor
                lcd.print("[10k]"); // print change content        
            break;
            default:
                // do nothing
            break;
            }      
        if(adcC2 < 1000)
          {
          lcd.setCursor(12, 1); // set cursor
          lcd.print(adcC2,1); // print change content
          }
        else
          {
          lcd.setCursor(12, 1); // set cursor
          lcd.print(adcC2,0); // print change content
          }
        }
//
      lcd.setCursor(0, 2); // set cursor
      lcd.print(F("3          :     ppm")); // print change content
      lcd.setCursor(2, 2); // set cursor
      switch(canal3.gas)
          {
          case 0:
              lcd.print("CO2"); // print change content        
          break;

          case 1:
              lcd.print("SO2"); // print change content        
          break;

          case 2:
              lcd.print("H2S"); // print change content        
          break;
          case 3:
              lcd.print("---"); // print change content        
          break;
          default:
              // do nothing
          break;
          }      
      if(canal3.gas == 3)
        {
          lcd.setCursor(6, 2); // set cursor
          lcd.print("[---]"); // print change content        
          lcd.setCursor(12, 2); // set cursor
          lcd.print("---- "); // print change content        
        }
      else
        {
        switch(canal3.ran)
            {
            case 0:
                lcd.setCursor(8, 2); // set cursor
                lcd.print("[5]"); // print change content
            break;

            case 1:
                lcd.setCursor(7, 2); // set cursor
                lcd.print("[50]"); // print change content        
            break;

            case 2:
                lcd.setCursor(6, 2); // set cursor
                lcd.print("[200]"); // print change content        
            break;
            case 3:
                lcd.setCursor(7, 2); // set cursor
                lcd.print("[2k]"); // print change content        
            break;
            case 4:
                lcd.setCursor(7, 2); // set cursor
                lcd.print("[5k]"); // print change content        
            break;
            case 5:
                lcd.setCursor(6, 2); // set cursor
                lcd.print("[10k]"); // print change content        
            break;
            default:
                // do nothing
            break;
            }
        if(adcC3 < 1000)
          {
          lcd.setCursor(12, 2); // set cursor
          lcd.print(adcC3,1); // print change content
          }
        else
          {
          lcd.setCursor(12, 2); // set cursor
          lcd.print(adcC3,0); // print change content
          }
        }
//
      lcd.setCursor(0, 3); // set cursor
      lcd.print(F("4          :     ppm")); // print change content
      lcd.setCursor(2, 3); // set cursor
      switch(canal4.gas)
          {
          case 0:
              lcd.print("CO2"); // print change content        
          break;
          case 1:
              lcd.print("SO2"); // print change content        
          break;
          case 2:
              lcd.print("H2S"); // print change content        
          break;
          case 3:
              lcd.print("---"); // print change content        
          break;
          default:
              // do nothing
          break;
          }      
      if(canal4.gas == 3)
        {
          lcd.setCursor(6, 3); // set cursor
          lcd.print("[---]"); // print change content        
          lcd.setCursor(12, 3); // set cursor
          lcd.print("---- "); // print change content        
        }
      else
        {
        switch(canal4.ran)
            {
            case 0:
                lcd.setCursor(8, 3); // set cursor
                lcd.print("[5]"); // print change content
            break;

            case 1:
                lcd.setCursor(7, 3); // set cursor
                lcd.print("[50]"); // print change content        
            break;

            case 2:
                lcd.setCursor(6, 3); // set cursor
                lcd.print("[200]"); // print change content        
            break;
            case 3:
                lcd.setCursor(7, 3); // set cursor
                lcd.print("[2k]"); // print change content        
            break;
            case 4:
                lcd.setCursor(7, 3); // set cursor
                lcd.print("[5k]"); // print change content        
            break;
            case 5:
                lcd.setCursor(6, 3); // set cursor
                lcd.print("[10k]"); // print change content        
            break;
            default:
                // do nothing
            break;
            }      
        if(adcC4 < 1000)
          {
          lcd.setCursor(12, 3); // set cursor
          lcd.print(adcC4,1); // print change content
          }
        else
          {
          lcd.setCursor(12, 3); // set cursor
          lcd.print(adcC4,0); // print change content
          }
        }
  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}
}

/*********************************************************************
impresion
*********************************************************************/
void impresion()
{
        switch(canal1.gas)
          {
          case 0:
              nombreGasC1= "CO2";            
          break;

          case 1:
              nombreGasC1= "SO2";
          break;

          case 2:
              nombreGasC1= "H2S";
          break;
          case 3:
              nombreGasC1= "---";
          break;
          default:
              // do nothing
          break;
          }
          
        switch(canal2.gas)
          {
          case 0:
              nombreGasC2= "CO2";            
          break;

          case 1:
              nombreGasC2= "SO2";
          break;

          case 2:
              nombreGasC2= "H2S";
          break;
          case 3:
              nombreGasC2= "---";
          break;
          default:
              // do nothing
          break;
          }

        switch(canal3.gas)
          {
          case 0:
              nombreGasC3= "CO2";            
          break;

          case 1:
              nombreGasC3= "SO2";
          break;

          case 2:
              nombreGasC3= "H2S";
          break;
          case 3:
              nombreGasC3= "---";
          break;
          default:
              // do nothing
          break;
          }
        switch(canal4.gas)
          {
          case 0:
              nombreGasC4= "CO2";            
          break;

          case 1:
              nombreGasC4= "SO2";
          break;

          case 2:
              nombreGasC4= "H2S";
          break;
          case 3:
              nombreGasC4= "---";
          break;
          default:
              // do nothing
          break;
          }
// CANAL 1
  Serial.print("CANAL 1:");
  Serial.print(" Gas C1: ");
  Serial.print(nombreGasC1);
  Serial.print(" / Rango Max C1[ppm]: ");
  if(nombreGasC1 == "---")
    Serial.print("---");
  else
    Serial.print(canal1.rango);
  Serial.print(" / C1[ppm]: ");
  if(nombreGasC1 == "---")
    Serial.print("---- ");
  else
    Serial.print(adcC1);
  Serial.print(" / C1[cts]: ");
  if(nombreGasC1 == "---")
    Serial.print("----");
  else
    Serial.print(cntAdcC1,1);
  Serial.println();      

// CANAL 2  
  Serial.print("CANAL 2:");
  Serial.print(" Gas C2: ");
  Serial.print(nombreGasC2);  
  Serial.print(" / Rango Max C2[ppm]: ");
  if(nombreGasC2 == "---")
    Serial.print("---");
  else
    Serial.print(canal2.rango);
  Serial.print(" / C2[ppm]: ");
  if(nombreGasC2 == "---")
    Serial.print("---- ");
  else
    Serial.print(adcC2,1);
  Serial.print(" / C2[cts]: ");
  if(nombreGasC2 == "---")
    Serial.print("----");
  else
    Serial.print(cntAdcC2);
  Serial.println();
// CANAL 3  

  Serial.print("CANAL 3:");
  Serial.print(" Gas C3: ");
  Serial.print(nombreGasC3);
  Serial.print(" / Rango Max C3[ppm]: ");
  if(nombreGasC3 == "---")
    Serial.print("---");
  else
    Serial.print(canal3.rango);
  Serial.print(" / C3[ppm]: ");
  if(nombreGasC3 == "---")
    Serial.print("---- ");
  else
    Serial.print(adcC3);
  Serial.print(" / C3[cts]: ");
  if(nombreGasC3 == "---")
    Serial.print("----");
  else
    Serial.print(cntAdcC3,1);
  Serial.println();  
// CANAL 4    
  Serial.print("CANAL 4:");
  Serial.print(" Gas C1: ");
  Serial.print(nombreGasC4);
  Serial.print(" / Rango Max C4[ppm]: ");
  if(nombreGasC4 == "---")
    Serial.print("---");
  else
    Serial.print(canal4.rango);
  Serial.print(" / C4[ppm]: ");
  if(nombreGasC4 == "---")
    Serial.print("---- ");
  else
    Serial.print(adcC4);          
  Serial.print(" / C4[cts]: ");
  if(nombreGasC4 == "---")
    Serial.println("----");
  else
    Serial.println(cntAdcC4,1);
  Serial.println("-------------------------------------------------------------------- ");  
}
/*********************************************************************
guardar
*********************************************************************/
 void guardar(uint8_t param)
{

  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    LCDML_UNUSED(param);
    lcd.setCursor(0, 0);
    lcd.print(F("  Guardar cambios?"));
    lcd.setCursor(0, 2);
    lcd.print(F(" OK para confirmar"));
    lcd.setCursor(0, 3);
    lcd.print(F("  Can para Salir"));        
  }
  if(LCDML.FUNC_loop())           // ****** LOOP *********
    if (LCDML.BT_checkEnter()) // check if button left is pressed
    {
      LCDML.BT_resetEnter(); // reset the left button
      EEPROM_writeAnything(1, canal1);
      EEPROM_writeAnything(6, canal2);
      EEPROM_writeAnything(11, canal3);
      EEPROM_writeAnything(16, canal4);
      Serial.println("- Cambios guardados en EEPROM");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F(" Cambios Guardados!"));
      lcd.setCursor(0, 3);
      lcd.print(F("   Can para Salir"));        
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
//EOF