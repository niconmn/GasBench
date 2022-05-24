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
            lcd.print("CO2"); // print change content        
        break;

        case 1:
            lcd.print("SO2"); // print change content        
        break;

        case 2:
            lcd.print("H2S"); // print change content        
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
      lcd.print("4-20mA");
    else
      lcd.print("0-20mA"); // print change content

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

/*********************************************************************
medicion
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
  if(loopC1 == false)
    {
      //4-20mA
      adcC1 = (rangoC1/(0.016 * 204.7) * (adcRead * cteAdc)) - rangoC1/4;
    }
  else
    {
      //0-20mA
      adcC1 = (adcRead * cteAdc) * rangoC1 / (.02 * 204.7);
    }
  if(adcC1 < 0)
    adcC1 = 0;
  

//C2
  adcRead = (analogRead(A5));
  if(loopC2 == false)
    {
      //4-20mA
      adcC2 = (rangoC2/(0.016 * 204.7) * (adcRead * cteAdc)) - rangoC2/4;
    }
  else
    {
      //0-20mA
      adcC2 = (adcRead * cteAdc) * rangoC2 / (.02 * 204.7);
    }
  if(adcC2 < 0)
    adcC2 = 0;
//C3
  adcRead = (analogRead(A6));
  if(loopC3 == false)
    {
      //4-20mA
      adcC3 = (rangoC3/(0.016 * 204.7) * (adcRead * cteAdc)) - rangoC3/4;
    }
  else
    {
      //0-20mA
      adcC3 = (adcRead * cteAdc) * rangoC3 / (.02 * 204.7);
    }
  if(adcC3 < 0)
    adcC3 = 0;
//C4
  
  adcRead = (analogRead(A7));

  if(loopC4 == false)
    {
      //4-20mA
      adcC4 = (rangoC4/(0.016 * 204.7) * (adcRead * cteAdc)) - rangoC4/4;
    }
  else
    {
      //0-20mA
      adcC4 = (adcRead * cteAdc) * rangoC4 / (.02 * 204.7);
    }
  if(adcC4 < 0)
    adcC4 = 0;
 
  //******************************************************************************
      lcd.setCursor(0, 0); // set cursor
      lcd.print(F("1          :     ppm")); // print change content
      lcd.setCursor(2, 0); // set cursor
      switch(gasC1)
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
          default:
              // do nothing
          break;
          }      
      switch(ranC1)
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
      
      lcd.setCursor(0, 1); // set cursor
      lcd.print(F("2          :     ppm")); // print change content
      lcd.setCursor(2, 1); // set cursor
      switch(gasC2)
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
          default:
              // do nothing
          break;
          }      
      switch(ranC2)
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
      
      lcd.setCursor(0, 2); // set cursor
      lcd.print(F("3          :     ppm")); // print change content
      lcd.setCursor(2, 2); // set cursor
      switch(gasC3)
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
          default:
              // do nothing
          break;
          }      
      switch(ranC3)
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
      
      lcd.setCursor(0, 3); // set cursor
      lcd.print(F("4          :     ppm")); // print change content
      lcd.setCursor(2, 3); // set cursor
      switch(gasC4)
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
          default:
              // do nothing
          break;
          }      
      switch(ranC4)
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


/*********************************************************************
impresion
*********************************************************************/
void impresion()
{
        switch(gasC1)
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
          default:
              // do nothing
          break;
          }
          
        switch(gasC2)
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
          default:
              // do nothing
          break;
          }

        switch(gasC3)
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
          default:
              // do nothing
          break;
          }
        switch(gasC4)
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
          default:
              // do nothing
          break;
          }
// CANAL 1
  Serial.print("CANAL 1:");
  Serial.print(" Gas C1: ");
  Serial.print(nombreGasC1);
  Serial.print(" / Rango Max C1[ppm]: ");  
  Serial.print(rangoC1);
  Serial.print(" / C1[ppm]: ");
  Serial.print(adcC1);
  Serial.print(" / C1[cts]: ");
  Serial.print(cntAdcC1);
  Serial.println();      

// CANAL 2  
  Serial.print("CANAL 2:");
  Serial.print(" Gas C2: ");
  Serial.print(nombreGasC2);  
  Serial.print(" / Rango Max C2[ppm]: ");
  Serial.print(rangoC2);
  Serial.print(" / C2[ppm]: ");
  Serial.print(adcC2);
  Serial.print(" / C2[cts]: ");
  Serial.print(cntAdcC2);
  Serial.println();
// CANAL 3  

  Serial.print("CANAL 3:");
  Serial.print(" Gas C3: ");
  Serial.print(nombreGasC3);
  Serial.print(" / Rango Max C3[ppm]: ");
  Serial.print(rangoC3);
  Serial.print(" / C3[ppm]: ");
  Serial.print(adcC3);
  Serial.print(" / C3[cts]: ");
  Serial.print(cntAdcC3);
  Serial.println();  
// CANAL 4    
  Serial.print("CANAL 4:");
  Serial.print(" Gas C1: ");
  Serial.print(nombreGasC4);
  Serial.print(" / Rango Max C4[ppm]: ");
  Serial.print(rangoC4);
  Serial.print(" / C4[ppm]: ");
  Serial.print(adcC4);          
  Serial.print(" / C4[cts]: ");
  Serial.println(cntAdcC4);
  Serial.println("-------------------------------------------------------------------- ");  
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