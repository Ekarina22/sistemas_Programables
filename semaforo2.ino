/*  SEMAFORO  -Projecto: Semáforo interactivo para paso de peatones
Semáforo con paso peatón: El semaforo funciona como en la vida actual cuando el semaforo se encuentra en verdeel paso peatonal se encuenta en rojo cuando el
semaforo del carro cambia a rojo el de peaton cambia a verde para seder el paso al peaton. */

/** Definiciones **/
// Semaforo automóviles
int rojo = 13 ;
int amarillo = 12;
int verde = 11;
// Semaforo peatón
int rojoP = 7;
int verdeP = 6;
// Boton
int controlador = 2; // asignación del pin 2 variable botón accionamiento peatones.

/* Variables*/
int SafetyLatence = 1500; // (ms) Tiempo en el que ambos pasos (vehículos y peatón) permanecen en rojo.
int TiempoCruce = 5000; // (ms)tiempo permitido para que el peatón cruce.

unsigned long TimeMinVerdeCar = 5000; // (ms) Tiempo mínimo en el que el paso de vehículos se encuentra en verde.
unsigned long startTime; // variable para guardar el tiempo desde que acaba el paso para peatones y empieza el verde coches.
unsigned long finishTime; // (ms)Tiempo de fin semaforo coches verde inicio del cambio de luces.
int switchState = 0;

/* Programa */
void setup(){
 
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(rojoP, OUTPUT);
  pinMode(verdeP, OUTPUT);
  pinMode(controlador, INPUT);
 // Arranca el ciclo, estados activos (HIGH) de luz verde para vehículos y roja para peatones
  digitalWrite(verde, HIGH);
  digitalWrite(rojoP, HIGH);
}
 
void loop() {
  finishTime = millis ();
  switchState = digitalRead(controlador);
 
 if (switchState == HIGH && (finishTime - startTime) > TimeMinVerdeCar){
   cambioLuces();
  }
 if (switchState == HIGH && (finishTime - startTime) < TimeMinVerdeCar){
   delay (TimeMinVerdeCar);
   cambioLuces();
  } 
}
 
void cambioLuces() {
  delay (2000);
  digitalWrite(verde,LOW);
  digitalWrite(amarillo, HIGH);
  delay(2000);
 
  digitalWrite(amarillo, LOW);
  digitalWrite(rojo, HIGH);
  delay(SafetyLatence);
 
  digitalWrite(rojoP, LOW);
  digitalWrite(verdeP, HIGH);
  delay(TiempoCruce);
 
  for (int x=0; x<10; x++) { // El bucle for enciende el led verde de forma intermitente 9 veces
  digitalWrite(verdeP, HIGH);
  delay(250);
  digitalWrite(verdeP, LOW);
  delay(250);
  }
 
  digitalWrite(rojoP, HIGH);
  delay(500); // Retraso de encendio del semáforo verde del auto con respecto al rojo del peatón
  digitalWrite(rojo, LOW);
  delay(1000);

  digitalWrite(verde, HIGH); 
  startTime = millis();
}
