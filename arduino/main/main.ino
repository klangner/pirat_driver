#include <SoftwareSerial.h> // Software Serial Port

#define RxD 2
#define TxD 3

SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
    Serial.begin(9600);
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
    setupBlueToothConnection();

}

void loop()
{
    char recvChar;
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            recvChar = blueToothSerial.read();
            Serial.print(recvChar);
            command(recvChar);
        }
    }
}

void setupBlueToothConnection()
{
    blueToothSerial.begin(38400); // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n"); // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=MyRover\r\n"); // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
    delay(2000); // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n"); // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000); // This delay is required.
    blueToothSerial.flush();
}

//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
int MAX_SPEED = 255;
 
 
 
void stop(void)                    //Stop
{
  digitalWrite(E1,LOW);  
  digitalWrite(E2,LOW);     
}  
void forward()          //Move forward
{
  analogWrite (E1,MAX_SPEED);      //PWM Speed Control
  digitalWrite(M1,HIGH);   
  analogWrite (E2,MAX_SPEED);   
  digitalWrite(M2,HIGH);
} 
void backward()          //Move backward
{
  analogWrite (E1,MAX_SPEED);
  digitalWrite(M1,LOW);  
  analogWrite (E2,MAX_SPEED);   
  digitalWrite(M2,LOW);
}
void turnLeft()             //Turn Left
{
  analogWrite (E1,MAX_SPEED);
  digitalWrite(M1,LOW);   
  analogWrite (E2,MAX_SPEED);   
  digitalWrite(M2,HIGH);
}
void turnRight()             //Turn Right
{
  analogWrite (E1,MAX_SPEED);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,MAX_SPEED);   
  digitalWrite(M2,LOW);
}

void command(char val)
{
  switch(val)
  {
      case 'w'://Move Forward
        forward();   //move forward in max speed
        break;
      case 's'://Move Backward
        backward();   //move back in max speed
        break;
      case 'a'://Turn Left
        turnLeft();
        break;      
      case 'd'://Turn Right
        turnRight();
        break;
      case 'z':
        Serial.println("Hello");
        break;
      case 'x':
        stop();
        break;
  }
}
