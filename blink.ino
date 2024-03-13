//Arduino IO pin numbers
#define LED_PIN 13
#define BTN_PIN 2
//Duration of one time unit in Morse Code
#define TIME_UNIT 132

//Global Variables
constexpr unsigned int nameLength = 3;
const char name[nameLength] = {'s', 'a', 'm'};    //Array that stores the characters of my name
unsigned int currentLetter = 0;

//The setup function runs once at the beginning.
void setup() 
{
  
  Serial.begin(9600);
  
  //Initializes input and output pins
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  //LED is off at the beginning
  digitalWrite(LED_PIN, LOW);

  //Program will only proceed if the infinite loop is exitted.
  while (1)
  {
    //Reads the input associated with the push button.
    bool btnState = digitalRead(BTN_PIN);
    
    //If the button is pressed (LOW), exit the loop to start blinking my name in Morse Code.
    if (btnState == LOW) break;
  }

}

void loop()
{
    //Gets the state of the button input and stores in a variable. Remember, the button is active low.
    bool btnState = digitalRead(BTN_PIN);
    
    //If the button was pressed, reset the system.
    if (btnState == LOW)
    {
      currentLetter = 0;    //Goes back to the first letter of my name
      return;   //restarts the loop
    }

    //Calls the morse code blinking function for the current letter of my name.
    switch(name[currentLetter])
    {
      case 's':
        s();
        break;
      case 'a':
        a();
        break;
      case 'm':
        m();
        break;
    }

    currentLetter++;    //Increments the current letter
    currentLetter %= nameLength;   //When the current letter has an index exceeding the array bounds, it is wrapped back around to 0.
    
    if (currentLetter == 0) mediumGap();    //Delay between the end and start of next sequence
    else shortGap();    //Delay between letters
}

//The functions below are responsible for implementing Morse Code using the in-built LED on pin 13.

void interGap()
{
  digitalWrite(LED_PIN, LOW);
  delay(TIME_UNIT);
}

void shortGap()
{
  digitalWrite(LED_PIN, LOW);
  delay(3 * TIME_UNIT);
}

void mediumGap()
{
  digitalWrite(LED_PIN, LOW);
  delay(7 * TIME_UNIT);
}

void dot()
{
  digitalWrite(LED_PIN, HIGH);
  delay(TIME_UNIT);
}

void dash()
{
  digitalWrite(LED_PIN, HIGH);
  delay(3 * TIME_UNIT);
}

void s()
{
  dot();
  interGap();
  dot();
  interGap();
  dot();
}

void a()
{
  dot();
  interGap();
  dash();
}

void m()
{
  dash();
  interGap();
  dash();
}
