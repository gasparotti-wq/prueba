#define CS 8
#define INC 10
#define UD 9
#define puls 7
#define VW A0

float voltSelec = 0;
float voltAct = 0;
int lectura;
float tension;
float tolerancia = 0.03;

void setup(){
Serial.begin(115200);
pinMode(CS, OUTPUT);
pinMode(UD, OUTPUT);
pinMode(INC, OUTPUT);
pinMode(puls, INPUT_PULLUP);

digitalWrite(INC, HIGH);
digitalWrite(CS, HIGH);

lectura = analogRead(VW);
voltAct = lectura * 5.11 / 1023;

if(voltAct < 0.00){
voltAct = 0.00;
}

if(voltAct > 5.11){
voltAct = 5.11;
}

Serial.print("Voltaje actual: ");
Serial.println(voltAct);

Serial.println("Escriba el voltaje deseado");
}
void loop() {
if(Serial.available() > 0){
voltSelec = Serial.parseFloat();
while(Serial.available() > 0){
Serial.read();
}
if(voltSelec >= 0.00 and voltSelec <= 5.11){
Serial.print("Voltaje seleccionado: ");
Serial.println(voltSelec);
Serial.println("Presione el boton para comenzar");
}
else{
Serial.println("Voltaje no valida. Seleccione un voltaje entre 0.00 y 5.11");
}
}
if (digitalRead(puls) == LOW) {
digitalWrite(CS, LOW);   
if (voltSelec > voltAct) {
digitalWrite(UD, HIGH);
while (voltSelec > voltAct) {
digitalWrite(INC, LOW);
delay(250);
digitalWrite(INC, HIGH);
delay(250);
lectura = analogRead(VW);
voltAct = lectura * 5.11 / 1023;
Serial.println(voltAct);
}
}
if(voltSelec < voltAct){
digitalWrite(UD, LOW);
while(voltSelec < voltAct){
digitalWrite(INC, LOW);
delay(250);
digitalWrite(INC, HIGH);
delay(250);
lectura = analogRead(VW);
voltAct = lectura * 5.11 / 1023;
Serial.println(voltAct);
}
}
lectura = analogRead(VW);
voltAct = lectura * 5.11 / 1023;
if(voltAct < 0.00){
voltAct = 0.00;
}
if(voltAct > 5.11){
voltAct = 5.11;
}
Serial.print("Voltaje final: ");
Serial.println(voltAct);

digitalWrite(INC, HIGH);
delay(100);
digitalWrite(CS, HIGH);
delay(500);
}
}
