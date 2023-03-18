//OUTPUTS  (Alerts)
#define driverRoof 9
#define kitchenArea 10
#define genArea 11
#define transformerArea 12
#define siren 8

#define testPin 2
//INPUTS  {Sensors)
#define sabotage A5   // GreenStrip

#define senseDRoof A4  //Green (near fence)
#define senseKitchen A3 //Brown
#define senseGenArea A2 //BrownStrip (or ChangeOver Room roof)
#define senseTankArea A0 //OrangeStrip
#define sensetransArea A1    //BlueStrip

float DRoof = 0; //Green (near fence)
float Kitchen = 0;  //Brown
float GenArea = 0; //BrownStrip (or ChangeOver Room roof)
float TankArea= 0; //OrangeStrip
float transformer = 0;    //BlueStrip

int val = 150;         // variable to store the read value

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  pinMode(transformerArea, OUTPUT);
  pinMode(genArea, OUTPUT);
  pinMode(kitchenArea, OUTPUT);
  pinMode(driverRoof, OUTPUT);
  pinMode(testPin, OUTPUT);
  pinMode(sabotage, INPUT);
  pinMode(siren, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(testPin, HIGH);
  
  float c = getMagnitude(analogRead(sabotage));
    //("Sabotage:");
    //ln(c);
  if(c>=3){
    raiseAlarm();
    digitalWrite(genArea, HIGH);
    delay(800);
    digitalWrite(driverRoof, HIGH);
    delay(800);
    digitalWrite(kitchenArea, HIGH);
    delay(800);
    digitalWrite(transformerArea, HIGH);
delay(800);
    digitalWrite(genArea, LOW);
    delay(800);
    digitalWrite(driverRoof, LOW);
    delay(800);
    digitalWrite(kitchenArea, LOW);
    delay(800);
    digitalWrite(transformerArea, LOW);
    delay(800);
    //ln("In Sabotage loop");
  }else{
    digitalWrite(siren, LOW);
  }

  DRoof = getMagnitude(analogRead(senseDRoof));
  Kitchen = getMagnitude(analogRead(senseKitchen));  //Brown
  GenArea = getMagnitude(analogRead(senseGenArea)); //BrownStrip (or ChangeOver Room roof)
  TankArea= getMagnitude(analogRead(senseTankArea)); //OrangeStrip
  transformer = getMagnitude(analogRead(sensetransArea));  

    //("DRoof:");
    //ln(DRoof);
  if(DRoof>0.5){
    digitalWrite(driverRoof, HIGH);
    raiseAlarm();
    //("Effect DRoof");
    delay(2000);
  }else{
    digitalWrite(driverRoof, LOW);
    digitalWrite(siren, LOW);
  }

   //("Kitchen:");
    //ln(Kitchen);
  if(Kitchen>0.5){
    digitalWrite(kitchenArea, HIGH);
    raiseAlarm();
     //("Effect Kitchen");
    delay(2000);
  }else{
    digitalWrite(kitchenArea, LOW);
    digitalWrite(siren, LOW);
  }

   //("GenArea:");
    //ln(GenArea);
  if(GenArea>0.5){
    digitalWrite(genArea, HIGH);
    raiseAlarm();
     //("Effect GenArea");
    delay(2000);
  }else{
    digitalWrite(genArea, LOW);
    digitalWrite(siren, LOW);
  }

   //("TankArea:");
    //ln(TankArea);
  if(TankArea>0.5){
   digitalWrite(genArea, HIGH);
   raiseAlarm();
    //("Effect TankArea");
    delay(2000);
  }else{
    digitalWrite(genArea, LOW);
    digitalWrite(siren, LOW);
  }

   //("Transformer:");
    //ln(transformer);
  if(transformer>0.5){
    digitalWrite(transformerArea, HIGH);
    raiseAlarm();
    delay(2000);
  }else{
    digitalWrite(transformerArea, LOW);
    digitalWrite(siren, LOW);
  }
}

void raiseAlarm(){
  for(int x=0; x<5; x++){
    delay(500);
    digitalWrite(siren, HIGH);
    delay(500);
  }
}

int getMagnitude(int sensorValue){
  float voltage= sensorValue * (5.0 / 1023.0);
  return voltage;
}

