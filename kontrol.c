#include <PS4Controller.h>

/* COMMENT OUT IF NOT NEEDED */
/* Print data to serial monitor */
// #define DEBUGGING_MODE
/* Send data to microcontroller */
#define SEND_DATA

// change ps4 address if needed
#define PS4_ADDR "1C:69:20:A4:E0:FC"

char TransArray[23] = {'K', 'R', 'I'};

const int deadzone = 10;

typedef struct {
  int8_t rX;
  int8_t rY;
  int8_t lX;
  int8_t lY;
  uint8_t r2;
  uint8_t l2;
  bool r1;
  bool l1;
  bool r3;
  bool l3;
  bool crs;
  bool sqr;
  bool tri;
  bool cir;
  bool up;
  bool down;
  bool right;
  bool left;
  bool share;
  bool option;
} Controller;



Controller input = {0};
int dummy = 0;

int applyDeadzone(int value) {
  if (abs(value) < deadzone) {
    return 0; 
  }
  return value;
}

void setup() {
    #ifdef DEBUGGING_MODE
    Serial.begin(115200);
    #endif

    #ifdef SEND_DATA
    Serial.begin(115200);
    #endif

    PS4.begin(PS4_ADDR);
}

void loop() {

    if(PS4.isConnected()) 
    {
      AssignControllerValue();
    }  
    else
    {
      input = {0};
    }

    // Send data to STM32
    #ifdef SEND_DATA
    SendBytes();
    #endif
  
    #ifdef DEBUGGING_MODE
    PrintSerial();
//    delay(50); // Delay for X second before sending the next data
    #endif
}

void PrintSerial()
{
    Serial.print(":");
    Serial.print(dummy);
    Serial.print(";");
    Serial.print(input.lX);
    Serial.print(";");
    Serial.print(input.lY);
    Serial.print(";");
    Serial.print(input.rX);
    Serial.print(";");
    Serial.print(input.rY);
    Serial.print(";");
    Serial.print(input.r1);
    Serial.print(";");
    Serial.print(input.l1);
    Serial.print(";");
    Serial.print(input.r2);
    Serial.print(";");
    Serial.print(input.l2);
    Serial.print(";");
    Serial.print(input.sqr);
    Serial.print(";");
    Serial.print(input.crs);
    Serial.print(";");
    Serial.print(input.tri);
    Serial.print(";");
    Serial.print(input.cir);
    Serial.print(";");
    Serial.print(input.up);
    Serial.print(";");
    Serial.print(input.down);
    Serial.println();
}

void SendBytes()
{
    memcpy(TransArray + 3, &input.lX, 1);
    memcpy(TransArray + 4, &input.lY, 1);
    memcpy(TransArray + 5, &input.rX, 1);
    memcpy(TransArray + 6, &input.rY, 1);
    memcpy(TransArray + 7, &input.r1, 1);
    memcpy(TransArray + 8, &input.l1, 1);
    memcpy(TransArray + 9, &input.r2, 1);
    memcpy(TransArray + 10, &input.l2, 1);
    memcpy(TransArray + 11, &input.sqr, 1);
    memcpy(TransArray + 12, &input.crs, 1);
    memcpy(TransArray + 13, &input.tri, 1);
    memcpy(TransArray + 14, &input.cir, 1);
    memcpy(TransArray + 15, &input.up, 1);
    memcpy(TransArray + 16, &input.down, 1);
    memcpy(TransArray + 17, &input.left, 1);
    memcpy(TransArray + 18, &input.right, 1);
    memcpy(TransArray + 19, &input.share, 1);
    memcpy(TransArray + 20, &input.option, 1);
    
    
    for(int i = 0; i < sizeof(TransArray); i++)
    {
        Serial.write(TransArray[i]);
    }
}

// add more buttons if needed
void AssignControllerValue()
{
    input.lX = applyDeadzone(PS4.LStickX());
    input.lY = applyDeadzone(PS4.LStickY());
    input.rX = applyDeadzone(PS4.RStickX());
    input.rY = applyDeadzone(PS4.RStickY());
    input.r1 = PS4.R1();
    input.l1 = PS4.L1();
    input.r2 = applyDeadzone(PS4.R2Value());
    input.l2 = applyDeadzone(PS4.L2Value());
    input.sqr = PS4.Square();
    input.crs = PS4.Cross();
    input.tri = PS4.Triangle();
    input.cir = PS4.Circle();
    input.up = PS4.Up();
    input.down = PS4.Down();
    input.left = PS4.Left();
    input.right = PS4.Right();
    input.share = PS4.Share();
    input.option = PS4.Options();

}