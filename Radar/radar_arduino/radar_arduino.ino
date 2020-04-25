#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
#include <Servo.h>

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,11,0,28,0,8,177,0,
  67,4,36,29,20,5,2,26,11,129,
  0,8,29,18,6,17,68,105,115,116,
  97,110,99,101,0 };

struct {
  
  char text_1[11];  // string UTF8 end zero 

  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

const int trigPin = 10;
const int echoPin = 11;
const int buzzer = 8;

long duration;
int distance;
Servo myServo;
void setup() {
  RemoteXY_Init ();
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  myServo.attach(12); 
}
void loop() {
  RemoteXY_Handler ();
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();

  int dist = digitalRead(10);
  delay(100);
  dtostrf(dist, 0, 1, RemoteXY.text_1); // result: distance 
  
  if(distance <= 10){
    digitalWrite(buzzer, HIGH);
   }
   else{
    digitalWrite(buzzer, LOW); 
   }
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();

  int dist = digitalRead(10);
  delay(100);
  dtostrf(dist, 0, 1, RemoteXY.text_1);

  if(distance <= 10){
    digitalWrite(buzzer, HIGH);
   }
   else{
    digitalWrite(buzzer, LOW); 
   }
 
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2; 
  return distance;
}
