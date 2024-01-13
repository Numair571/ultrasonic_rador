#include <Servo.h>
#include <ThingSpeak.h>

int trig = D8; 
int echo = D9;

long duration;
int distance;

Servo myservo;

char thingSpeakAPIKey[] = "";
int channelID =;

int calculateDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myservo.attach(D11);
  Serial.begin(9600);
  ThingSpeak.begin(client);
}

void loop()
{
  int i;
  for (i = 15; i <= 100; i++)
  {
    myservo.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    updateThingSpeak(i, distance);
  }
  for (i = 100; i >= 15; i--)
  {
    myservo.write(i);
    delay(15);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    updateThingSpeak(i, distance);
  }
}

void updateThingSpeak(int servoPosition, int distance)
{
  String data = String("field1=") + String(servoPosition) +
                String("&field2=") + String(distance);
  int status = ThingSpeak.writeFields(channelID, data, thingSpeakAPIKey);
  Serial.print("ThingSpeak Update: ");
  if (status == 200)
    Serial.println("Success");
  else
    Serial.println("Failed");

  delay(2000); 
}
