void setup() {
  Serial.begin(9600);
 // pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ref1=0;
  int mag1=0;
  int phs1=0;
  int ref2=0;
  int mag2=0;
  int phs2=0;

 // ref=analogRead(A0);
  phs1=analogRead(A1);
  mag1=analogRead(A2);
  phs2=analogRead(A3);
  mag2=analogRead(A4);
 
 //float vref = ref*(5.0 / 1023.0);
 float vphs1 = phs1*(5.0 / 1023.0);
 float vmag1 = mag1*(5.0 / 1023.0);
 float vphs2 = phs2*(5.0 / 1023.0);
 float vmag2 = mag2*(5.0 / 1023.0);
 
 float magniRatio1 = -30.0 + vmag1*(100.0 / 3.0);
 float phsDiff1 = 190.0 - 100.0*vphs1;
 float magniRatio2 = -30.0 + vmag2*(100.0 / 3.0);
 float phsDiff2 = 190.0 - 100.0*vphs2;

 float cliMag1 = magniRatio1  - 11.54-5.85;
 float cliMag2 = magniRatio2 - 3.68;
 float cliPhs1 = phsDiff1 - 100.0 + 29.9 - 7.0-40.0-0.5;
 float cliPhs2 = phsDiff2 - 35.48+9.0;

 
 //if(phsDiff > 0.0){
 // phsDiff = 180.0 - 100.0*vphs
 //}
 
  Serial.print(" !");
  Serial.print(phsDiff1);
  Serial.println();
  Serial.print(" @");
  Serial.print(magniRatio1);
  Serial.println();
  Serial.print(" #");
  Serial.print(phsDiff2);
  Serial.println();
  Serial.print(" %");
  Serial.print(magniRatio2);
  Serial.println();
  Serial.print("<");
  
  Serial.print(" ^");
  Serial.print(cliPhs1);
  Serial.println();
  Serial.print(" ?");
  Serial.print(cliMag1);
  Serial.println();
  Serial.print(" &");
  Serial.print(cliPhs2);
  Serial.println();
  Serial.print(" *");
  Serial.print(cliMag2);
  Serial.println();
  Serial.print(">");
  delay(1000);
  
}
