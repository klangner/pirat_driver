#include <SoftwareSerial.h> // Software Serial Port

#define RxD 2
#define TxD 3

//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
int MAX_SPEED = 255;

// Bluetooth connection
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
    String cmd = "";
    while(blueToothSerial.available()){
      char recvChar = blueToothSerial.read();
      cmd += recvChar;
    }
    
    if(cmd.length() > 0){
      Serial.print(cmd);
      runCommand(cmd);
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


void runCommand(String cmd)
{
    if(cmd.startsWith("f")){
        forward(MAX_SPEED); 
    } else if(cmd.startsWith("b")){
        backward(MAX_SPEED);   
    } else if(cmd.startsWith("l")){
        turnLeft(MAX_SPEED);
    } else if(cmd.startsWith("r")){
        turnRight(MAX_SPEED);
    } else if(cmd.startsWith("s")){
        stop();
    }
}

 
// Stop 
void stop(void)               
{
  digitalWrite(E1,LOW);  
  digitalWrite(E2,LOW);     
}  

// Move forward with speed in m/s
void forward(int speed)
{
  analogWrite (E1,speed);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,speed);   
  digitalWrite(M2,HIGH);
} 

// Move backward with speed in m/s
void backward(int speed)
{
  analogWrite (E1,speed);
  digitalWrite(M1,LOW);  
  analogWrite (E2,speed);   
  digitalWrite(M2,LOW);
}

// Turn left with given angular speed
void turnLeft(int speed)
{
  analogWrite (E1,speed);
  digitalWrite(M1,LOW);   
  analogWrite (E2,speed);   
  digitalWrite(M2,HIGH);
}

// Turn right with given angular speed
void turnRight(int speed)
{
  analogWrite (E1,speed);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,speed);   
  digitalWrite(M2,LOW);
}


