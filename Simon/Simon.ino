//Simon
#include <stdio.h>
#include <stdlib.h>
#include <LiquidCrystal.h>

// #defines
// The following #defines are used for debugging
#define COMPUTER_LOGIC_OUTPUT   FALSE  //output sequence generating logic
#define PLAYER_TURN_OUTPUT      FALSE  //output player turn logic
#define MULTIPLE_BUTTONS_PUSHED FALSE  //output the multiple button push logic
#define CHECK_BUTTON_PRESS      FALSE  //output button press check logic


// Delays
#define ON_DELAY         200    // LED will stay on for 200 miliseconds
#define OFF_DELAY        200    // LED will go off for 200 miliseconds
#define ROUND_PAUSE      1000   // 1 second pause between rounds


// Game Specific #defines
#define RAND             25001  // Random number for the seed
#define GAME_LENGTH      20     // Max number of flashes per game
#define DEBOUNCE_NUMBER  5      // number of passes that a button is pushed
                                // before registering the push or release.


// Setup #defines
#define MAX_NUM_LEDS     4      //num of LEDS and switches that are in the pattern
#define NUM_WORKING_LEDS 4      //if < 4, then some badly soldered switches
#define MELODY_LENGTH    4      //how long a tone should play
#define NUMBER_OF_TONES  8      //how many tones there are to choose between


// LED Configuration
#define LED_PIN_1        12      // LED connected to digital pin 12
#define LED_PIN_2        11      // LED connected to digital pin 11
#define LED_PIN_3        10      // LED connected to digital pin 10
#define LED_PIN_4        9       // LED connected to digital pin 9


// Push Button Configuration
#define PUSH_BUTTON_4    14      // Pushbutton connected to digital pin 6
#define PUSH_BUTTON_3    15      // Pushbutton connected to digital pin 3
#define PUSH_BUTTON_2    16      // Pushbutton connected to digital pin 4
#define PUSH_BUTTON_1    17       // Pushbutton connected to digital pin 5

//Speaker output
#define SPEAKER_OUT      7       // The speaker is located on digital I/O pin 7

//LCD

#define RS 2
#define Enable 3
#define D4 4
#define D5 5
#define D6 6
#define D7 8
#define filas 2
#define colum 16
LiquidCrystal lcd(RS,Enable,D4,D5,D6,D7);

// Typedefs
typedef enum
{
   TRUE,
   FALSE,
   ERROR
} eBoolean ;

// Global Variables
int game_array[ GAME_LENGTH ] ;  // The sequence of LEDS to light
int led_array[MAX_NUM_LEDS] ;    // an array storing the pin outs for the LEDS
int button_array[MAX_NUM_LEDS] ; // an array storing pushbutton outputs
int current_round ;              // the current game round
char print_output[256] ;         // used for debugging
//The following are used to generate the tones for the lit LEDs.
byte names[] ={ 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = {'a', 'd', 'g', 'C', 'c'} ;


/* ---------------------------------------------------------------------------
 - setup
 - The routine setup is called by the Arduino before main processing has begun.
 - The purpose of setup is to configure the program to use the proper pin outs,
 - initialize variables, and establish serial communication.
   ---------------------------------------------------------------------------*/
void setup()
{
   //initialize serial connection for possible debugging
   Serial.begin(9600) ;
   sprintf( print_output, "Freshly Loaded Program") ;
   Serial.println(print_output) ;

  // set up the LCD's number of columns and rows:
  lcd.begin(colum, filas);
  lcd.setCursor(0,0);
  lcd.print(print_output);

   // Configure the LEDs
   led_array[0] = LED_PIN_1 ;
   led_array[1] = LED_PIN_2 ;
   led_array[2] = LED_PIN_3 ;
   led_array[3] = LED_PIN_4 ;

   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      pinMode( led_array[i], OUTPUT ) ;     // sets the LED pins to output
   }

   // Configure the pushbuttons array
   button_array[0] = PUSH_BUTTON_1 ;
   button_array[1] = PUSH_BUTTON_2 ;
   button_array[2] = PUSH_BUTTON_3 ;
   button_array[3] = PUSH_BUTTON_4 ;

   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      pinMode( button_array[i], INPUT ) ;     // sets pushbutton pins to input
   }

   // setup speaker pin for output
   pinMode(SPEAKER_OUT, OUTPUT) ;

   //Test all the outputs, this flashes the LEDs and plays a sound.
   sprintf( print_output, "Self Test") ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);
   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      digitalWrite(led_array[i], HIGH) ;
   }
   for (int i = 0 ; i < NUMBER_OF_TONES ; i++)
   {
      PlaySound(i) ;
   }

   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      digitalWrite(led_array[i], LOW) ;
   }

   // Set up for new game
   srand(RAND) ;
   new_game() ;
}


/* ---------------------------------------------------------------------------
 - new_game
 - This routine sets up a new game of SIMON.  This means that the
 - current_round is reset to zero, and a new random pattern of LEDs are saved
 - to the game array.
   ---------------------------------------------------------------------------*/
void new_game()
{
   int i ;

   // Fill the game array with a new sequence of LEDs to light.  This is done by
   // setting each round position in the game_array to a random value modded by
   // the number of available LEDs.  This means that the number result (between
   // 0 and (NUM_WORKING_LEDS - 1) is the position in the led_array to light on
   // that turn.
   for (i=0 ; i < GAME_LENGTH ; i++)
   {
      game_array[i] = (rand() % NUM_WORKING_LEDS) ;
   }

   current_round = 0 ;
}


/* ---------------------------------------------------------------------------
 - blink_led
 - This routine blinks a given LED for the designated time.  Used to indicate
 - an LED in the pattern the player must match.
   ---------------------------------------------------------------------------*/
void blink_led(int led_output)
{
   digitalWrite(led_array[led_output], HIGH) ;   // sets the LED on
   PlaySound(led_output) ;
   delay(ON_DELAY) ;                  // waits for a second
   digitalWrite(led_array[led_output], LOW) ;    // sets the LED off
   delay(OFF_DELAY) ;
}


/* ---------------------------------------------------------------------------
 - blink_all
 - This routine blinks all available LEDs.  It is used to signal the end of a
 - game where the player has lost.
   ---------------------------------------------------------------------------*/
void blink_all( void )
{
   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      digitalWrite( led_array[i], HIGH ) ;
   }

   delay( ON_DELAY ) ;

   for (int i = 0 ; i < MAX_NUM_LEDS ; i++)
   {
      digitalWrite( led_array[i], LOW ) ;
   }
   delay( ON_DELAY ) ;
}


/* ---------------------------------------------------------------------------
   CheckForMultipleButtonsPressed
 - Return Values:
 -   TRUE  = Multiple buttons were pressed
 -   FALSE = one or 0 buttons were pressed.
 -
 - This routine checks to see if multiple pushbuttons are pressed at the same
 - time.  This is done by counting the number of pushbuttons that are sending a
 - LOW signal to the Arduino's digital I/O pins
   ---------------------------------------------------------------------------*/
int CheckForMultipleButtonsPressed( int button_1_state,
                                    int button_2_state,
                                    int button_3_state,
                                    int button_4_state )
{
   int return_value = TRUE ;
   int number_of_buttons_held = 0 ;

   if ( TRUE == MULTIPLE_BUTTONS_PUSHED )
   {
//      sprintf( print_output, "Entering CheckForMultipleButtonsPressed\r\n" ) ;
//      Serial.print(print_output) ;
   }

   // count the number of buttons pressed
   if ( button_1_state == LOW )
   {
      number_of_buttons_held++ ;
   }
   if ( button_2_state == LOW )
   {
      number_of_buttons_held++ ;
   }
   if ( button_3_state == LOW )
   {
      number_of_buttons_held++ ;
   }
   if ( button_4_state == LOW )
   {
      number_of_buttons_held++ ;
   }

   // if more than 1 button is pressed return TRUE.
   if ( number_of_buttons_held > 1 )
   {
      return_value = TRUE ;
   }

   // if 1 or no buttons are pressed return false.
   else
   {
      return_value = FALSE ;
   }

   if ( TRUE == MULTIPLE_BUTTONS_PUSHED )
   {
//      sprintf( print_output,
//               "Exiting CheckForMultipleButtonsPressed. Return = %d\r\n",
//               return_value ) ;
      Serial.println(print_output) ;
      lcd.setCursor(0,0);
      lcd.print(print_output);
   }

   return return_value ;
}


/* ---------------------------------------------------------------------------
 - ComputerTurnLogic
 - This routine flashes the sequence of LEDs from game_array up to the index
 - for the current turn.  That means if it is the 3rd turn, the LEDs in indexes
 - 0, 1, and 2 are flased in order so the player can attempt to match them.
   ---------------------------------------------------------------------------*/
void ComputerTurnLogic( void )
{
   int i ;

   if ( TRUE == COMPUTER_LOGIC_OUTPUT )
   {
      sprintf( print_output, "Entering ComputerTurnLogic" ) ;
      Serial.println(print_output) ;
      lcd.setCursor(0,0);
      lcd.print(print_output);
   }

   for ( i=0 ;
         ((i < GAME_LENGTH) && ( i <= current_round)) ;
         i++)
   {
      if ( TRUE == COMPUTER_LOGIC_OUTPUT )
      {
         sprintf( print_output, "  Lighting LED # %d", game_array[i] ) ;
         Serial.println(print_output) ;
         lcd.setCursor(0,0);
         lcd.print(print_output);
      }

      blink_led(game_array[i]) ;
   }
   if ( TRUE == COMPUTER_LOGIC_OUTPUT )
   {
      sprintf( print_output, "Exiting ComputerTurnLogic" ) ;
      Serial.println(print_output) ;
      lcd.setCursor(0,0);
      lcd.print(print_output);
   }
}


/* ---------------------------------------------------------------------------
 - GetKeyPress
 - Return values:
 -  -1 = player error (most likely multiple keys pressed)
 -  1-4 number of the button pressed.
 -
 - This routine processes loops until a keypress passes the debounce period.
 - If there are more than one pushbutton pressed, a -1 return is given.
 - Otherwise a return between 1 annd 4 inclusive is given to signal the button
 - pressed.
   ---------------------------------------------------------------------------*/
int GetKeyPress( void )
{
   int debounce = 0 ;
   int last_button = 0 ;
   int current_button = 0 ;
   int button_1 = HIGH ;
   int button_2 = HIGH ;
   int button_3 = HIGH ;
   int button_4 = HIGH ;
   int multi_press = FALSE ;

//   sprintf( print_output, "Entering GetKeyPress\r\n" ) ;
//   Serial.print(print_output) ;
   while (debounce != DEBOUNCE_NUMBER)
   {
      button_1 = digitalRead( button_array[0] ) ;
      button_2 = digitalRead( button_array[1] ) ;
      button_3 = digitalRead( button_array[2] ) ;
      button_4 = digitalRead( button_array[3] ) ;

      multi_press = CheckForMultipleButtonsPressed( button_1,
                                                    button_2,
                                                    button_3,
                                                    button_4 ) ;

      if ( TRUE == multi_press)
      {
         sprintf( print_output, "Exiting GetKeyPress. Multi-press" ) ;
         Serial.println(print_output) ;
         lcd.setCursor(0,0);
         lcd.print(print_output);
         return -1 ;
      }

      //set current_button to the single low button.
      if (LOW == button_1)
      {
         current_button = 1 ;
      }
      else if (LOW == button_2)
      {
         current_button = 2 ;
      }
      else if (LOW == button_3)
      {
         current_button = 3 ;
      }
      else if (LOW == button_4)
      {
         current_button = 4 ;
      }
      else // no button pressed
      {
         current_button = 0 ;
      }

      if ( (last_button == current_button) && (current_button != 0 ) )
      {
         debounce++ ;
      }
      else
      {
         last_button = current_button ;
         debounce = 0 ;
      }
   }

   sprintf( print_output, "Exiting GetKeyPress. Normal" ) ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);
   return last_button ;
}


/* ---------------------------------------------------------------------------
 - GetKeyRelease
 - Return values:
 -  -1 = player error (most likely multiple keys pressed)
 -  1-4 number of the button pressed.
 -
 - This routine processes loops until a key release passes the debounce period.
 - If there are more than one pushbutton pressed, a -1 return is given.
 - Otherwise a return between 1 annd 4 inclusive is given to signal the button
 - released.
   ---------------------------------------------------------------------------*/
int GetKeyRelease(int orig_button)
{
   int return_value = orig_button ;
   int released_button = 0 ;
   int debounce = 0 ;
   int button_1 = LOW ;
   int button_2 = LOW ;
   int button_3 = LOW ;
   int button_4 = LOW ;
   int multi_press = TRUE ;
   int button_read = 0 ;


//   sprintf( print_output, "Entering GetKeyRelease\r\n" ) ;
//   Serial.print(print_output) ;
   while ( debounce != DEBOUNCE_NUMBER )
   {
      button_1 = digitalRead( PUSH_BUTTON_1 ) ;
      button_2 = digitalRead( PUSH_BUTTON_2 ) ;
      button_3 = digitalRead( PUSH_BUTTON_3 ) ;
      button_4 = digitalRead( PUSH_BUTTON_4 ) ;

      multi_press = CheckForMultipleButtonsPressed( button_1,
                                                    button_2,
                                                    button_3,
                                                    button_4 ) ;

      if ( TRUE == multi_press)
      {
         sprintf( print_output, "Exiting GetKeyRelease. multi-press" ) ;
         Serial.println(print_output) ;
         lcd.setCursor(0,0);
         lcd.print(print_output);
         return -1 ;
      }

      switch (orig_button)
      {
         case 1:
            button_read = button_1 ;
            break ;
         case 2:
            button_read = button_2 ;
            break ;
         case 3:
            button_read = button_3 ;
            break ;
         case 4:
            button_read = button_4 ;
            break ;
         default:
 //           sprintf( print_output, "Exiting GetKeyRelease. orig_button unknown\r\n" ) ;
 //           Serial.print(print_output) ;
            return -1 ;
            break ;
      }

      if (button_read == HIGH)
      {
         debounce++ ;
      }
   } //end loop

   sprintf( print_output, "Exiting GetKeyRelease. Normally" ) ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);
   return return_value ;
}


/* ---------------------------------------------------------------------------
 - ProcessKeyEntered
 - Return values:
 -  TRUE player input is correct for the present sequence index
 -  FALSE player inputed the incorrect answer
 -
 - This routine checks the input received from the player against the LED in
 - the current sequence.  If they match, a TRUE response is returned, if they
 - differ a FALSE response is returned.
   ---------------------------------------------------------------------------*/
int ProcessKeyEntered(int button_registered, int player_round)
{
   int return_value = TRUE ;


//   sprintf( print_output, "Entering ProcessKeyEntered\r\n" ) ;
//   Serial.print(print_output) ;

   if ( (button_registered -1) == game_array[player_round])
   {
      return_value = TRUE ;
   }
   else
   {
      return_value = FALSE ;
   }

   sprintf( print_output,
            "Exiting ProcessKeyEntered with value = %d",return_value ) ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);
   return return_value ;
}


/* ---------------------------------------------------------------------------
 - PlayerTurnLogic
 - Return values:
 -  TRUE player input is correct for the present sequence index
 -  FALSE player inputed the incorrect answer
 -  -1 means an unexpected error occured durin processing.
 -
 - This routine handles the full player turn.  Each turn for the player
 - consists of pressing a single button to represent the LED in the sequence
 - that should be lit to match the given pattern.  To process a single input
 - three steps are taken.  First a key press must be registered, then the
 - key release must be registered, lastly the button that was just pressed and
 - released must be checked against the expected answer.  If the player input
 - the worng answer or pressed more than one pushbutton, then the players
 - turn ends and the game is over.
   ---------------------------------------------------------------------------*/
int PlayerTurnLogic( void )
{
   /* Notes
    - Pressed push button == LOW, released button == HIGH
   */
   int button = 0 ;
   int return_value = -1 ;
   int player_round = 0 ;

   while ( (player_round <= current_round) &&
           (return_value != FALSE) )
   {
      button = GetKeyPress() ;
      if ( -1 == button )
      {
         return FALSE ;
      }

      //turn on appropriate light and sound
      digitalWrite( led_array[(button-1)], HIGH ) ;

      PlaySound(button-1) ;
      button = GetKeyRelease(button) ;
      if ( -1 == button )
      {
         //turn off appropriate light and sound
         digitalWrite( led_array[(button-1)], LOW ) ;
         return FALSE ;
      }

      //turn off appropriate light and sound
      digitalWrite( led_array[(button-1)], LOW ) ;

      if ( TRUE == ProcessKeyEntered(button, player_round) )
      {
         player_round++ ;
      }
      else
      {
          return_value = FALSE ;
      }
   } // end loop

   if ((player_round - 1) == current_round)
   {
      return_value = TRUE ;
   }
   else
   {
      return_value = FALSE ;
   }

   sprintf( print_output,
            "Exiting PlayerTurnLogic with value = %d",return_value ) ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);

   return return_value ;
}


/* ---------------------------------------------------------------------------
 - PlaySound
 - This routine is used to play the desired note from the Arduino's speaker
 - by turning the input for the speaker on and off a given number of times
 - per interva.
   ---------------------------------------------------------------------------*/
void PlaySound( int melody_note )
{
   int count = 0 ;
   byte tone = 0 ;

   tone = melody[melody_note] ;

   for ( count = 0 ; count <= NUMBER_OF_TONES ; count++ )
   {
      if ( names[count] == tone )
      {
         for ( int i=0 ; i < 100 ; i++ )
         {
            digitalWrite(SPEAKER_OUT, HIGH);
            delayMicroseconds(tones[count]);
            digitalWrite(SPEAKER_OUT, LOW);
            delayMicroseconds(tones[count]);
         }
      }
   }
}


/* ---------------------------------------------------------------------------
 - loop
 - The routine loop is called by the Arduino constantly after the setup
 - routine.  This means that everytime loop finishes processing, it is called
 - again and starts processing again from the beginning of the routine.  The
 - game SIMON has been designed with this in mind.
   ---------------------------------------------------------------------------*/
void loop()
{
   int i ;
   int player_passed_round = FALSE ;
   int mistake = FALSE ;

   sprintf( print_output, "Starting Round %d", current_round) ;
   Serial.println(print_output) ;
   lcd.setCursor(0,0);
   lcd.print(print_output);

   ComputerTurnLogic() ;

//   delay( ROUND_PAUSE ) ;

   player_passed_round = PlayerTurnLogic() ;
   if ( TRUE == player_passed_round )
   {
      mistake = FALSE ;
   }
   else //if ( FALSE == player_passed_round )
   {
      mistake = TRUE ;
   }


   if ( mistake == TRUE )
   {
      sprintf( print_output, "Game Over.") ;
      Serial.println(print_output) ;
      lcd.setCursor(0,0);
      lcd.print(print_output);

      for (i=0 ; i < 10 ; i++)
      {
         PlaySound(4) ;
         blink_all() ;
      }

      mistake = FALSE ;
      new_game() ;
   }
   else if  ( current_round == GAME_LENGTH )
   {
      for (i=0 ; i < 5 ; i++)
      {
         for (int j = 0 ; j < MAX_NUM_LEDS ; j++)
         {
            digitalWrite(led_array[j], HIGH) ;
            delay(100) ;
         }
         PlaySound(0) ;
         for (int j = 0 ; j < MAX_NUM_LEDS ; j++)
         {
            digitalWrite(led_array[j], LOW) ;
            delay(100) ;
         }
      }

      mistake = FALSE ;
      new_game() ;
   }
   else
   {
      current_round++ ;
   }

   delay(1000) ;
}
