/*******************************************************************************

* Project name:
     Ex1_Afficheur
* Revision History:
       - 20181018 - initial release;
       - 20181030 - modified by Guillaume Terrasson;
* Description:
      Refer to document "CI2A-Sys_micro_ADC".
* Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/en/tools/easypic6/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/en/compilers/mikroc/pro/pic/

*******************************************************************************/

/***************** Global variables and functions declaration ****************/

unsigned ReadADC (void);

/*******************************************************************************
                                 Main Function
*******************************************************************************/

void main() {

/******************************** Initialisation ******************************/

  /***** Declaration and initialisation of variables *****/

  short display = 0;               // 0 = all lamps are OFF - 1 = all lamps are ON
  unsigned res = 0;                // result of analog to digital conversion
  
  /***** Input-Output Configuration *****/

  PORTA = 0;                       // Reset of Input-Output Ports
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;

   /***** Question 5 - à compléter et à commenter *****/

  TRISC.TRISC0 = 0;                // à commenter
  TRISC.TRISC1 = 0;
  TRISC.TRISC2 = 0;                // --> to control lamps L0 to L7
  TRISC.TRISC3 = 0;
  TRISC.TRISC4 = 0;

  TRISA.TRISA0 = _;

  ANSEL = _;
  ANSEL.___ = _;
  ANSELH = 0;

  /***** ADC configuration *****/

  ADCON0.ADCS1 = 1;                // à commenter
  ADCON0.ADCS0 = 0;

  ADCON1.VCFG1 = _;                // à commenter
  ADCON1.VCFG0 = _;                //

  ADCON0.CHS3 = _;                 // à commenter
  ADCON0.CHS2 = _;
  ADCON0.CHS1 = _;
  ADCON0.CHS0 = _;
  ADCON1.ADFM = 1;                 // à commenter

  ADCON0.ADON = 1;                 // à commenter

  /***** Fin Question 5 *****/

  /***** Configuration des comparateurs *****/

  C1ON_bit = 0;                    // Disable all comparators
  C2ON_bit = 0;

/********************************** Main Loop *********************************/

  do {

    /***** PotVal acquisition and treatment *****/

    res = ReadADC();               // Analog to digital conversion of analog voltage in RA0/AN0 pin

    if (res < 205)                 // If 0V <= Vpot < 1V --> only RC0 pin must be set to 1
    {
     display = 0b00000001;
    }
    if (205 <= res && res < 410)   // If 1V <= Vpot < 2V --> only RC1 pin must be set to 1
    {
     display = 0b00000010;
    }
    if (410 <= res && res < 614)   // If 2V <= Vpot < 3V --> only RC2 pin must be set to 1
    {
     display = 0b00000100;
    }
    if (614 <= res && res < 819)   // If 3V <= Vpot < 4V --> only RC3 pin must be set to 1
    {
     display = 0b00001000;
    }
    if (res >= 819)                // If 4V <= Vpot <= 5V --> only RC4 pin must be set to 1
    {
     display = 0b00010000;
    }

    /***** Display control *****/

    PORTC = display;               // RC0, RC1, RC2, RC3, RC4
                                   // are set ON if display_RCi = 1
                                   // are set OFF if display_RCi = 0

  } while(1);
}

/*******************************************************************************
                                 Function ReadADC
*******************************************************************************/

unsigned ReadADC() {
  unsigned result;

  Delay_us(4);

  ADCON0.GO = 1;                   // à commenter
  while(ADCON0.GO);                // à commenter

  result = ADRESH*256 + ADRESL;    // à commenter

  return result;
}