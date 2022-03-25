// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// ReRe-writed by Mikolaj OstryJR Ostrowski 
// Mail: mikolaj.p.ostrowski@gmail.com
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 2022.03.25
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int filterLen = 50;
const int maxValue = 350;//max value of measurement, if distance will be more than this or below 0, this measurement will be deleted;
int lastResults[filterLen];
int i=0;
bool maxValueErrorForDebug = false;

float calculateRound(int filter[filterLen]){
  float sum=0;
  int addedValuesNum=0;
  for(i=0;i<filterLen-1;i++){
    if(i>filterLen-(filterLen/10)){
      sum = sum + filter[i];
      addedValuesNum = addedValuesNum + 1;
    }
    sum = sum + filter[i];
  }
  sum = sum/(filterLen+addedValuesNum);
  return sum;
}

void speedStart(){
  for(i=0;i<5;i++){
    makeMeasurement();
  }
  int distance = makeMeasurement();
  for(i=0;i<(filterLen/1)-1;i++){
    lastResults[i] = distance;
  }
}

int makeMeasurement(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2; // Calculating the distance, Speed of sound wave divided by 2 (go and back)
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("distance filterDistance valueError");
  speedStart();
}
void loop() {
  makeMeasurement();
  maxValueErrorForDebug = false;
  if(distance<maxValue && distance>0){
    for(i=0;i<filterLen-1;i++)
    {
        lastResults[i]=lastResults[i+1];
    }
    lastResults[filterLen-1] = distance;

    Serial.print(distance);
    Serial.print(" ");
    Serial.println(calculateRound(lastResults));
    //Serial.print(" ");
    //Serial.println(100);
  }else{
    maxValueErrorForDebug = true;
    Serial.print(lastResults[filterLen-1]);
    Serial.print(" ");
    Serial.print(calculateRound(lastResults));
    //Serial.print(" ");
    //Serial.println(200);
  }
  delay(40);
}