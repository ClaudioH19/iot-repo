/*
  TALLER IoT - Arduino UNO, DHT22 y dos LED
  =======================================================
  OBJETIVO: observar un dia FICTICIO de temperatura/humedad.
  El codigo ya funciona: tu tarea es conectar el circuito.

  CONEXIONES POR REALIZAR EN WOKWI (el diagrama se entrega SIN cables):
    DHT22 VCC  -> Arduino 5V
    DHT22 GND  -> Arduino GND
    DHT22 SDA  -> Arduino D2     (NC queda sin conectar)

    Arduino D8 -> resistencia 220 ohm -> A del LED ROJO
    C del LED ROJO -> Arduino GND
    Arduino D9 -> resistencia 220 ohm -> A del LED AZUL
    C del LED AZUL -> Arduino GND

  LED ROJO: alerta si temperatura >= 30 grados Celsius.
  LED AZUL: alerta si humedad relativa >= 80 %.

  DOS MODOS DE TRABAJO:
  true  = DIA AUTOMATICO (valor inicial): usa arreglos de ejemplo;
          NO usa el DHT22 para obtener temperatura/humedad.
  false = SENSOR DHT22: lee la temperatura/humedad del sensor;
          debes haberlo conectado y puedes mover sus controles.

  NOTA: el ciclo de datos ficticios no cambia los controles graficos
  del DHT22. Los datos se observan en el monitor serie y en los LED.
  No hay Wi-Fi, ni simulacion fisica de un invernadero.
*/

#include <DHT.h>                   // Biblioteca para el sensor DHT22.

// ===================== 1. CONFIGURACION =====================
const bool DIA_AUTOMATICO = true; // Pon false para leer el DHT22.

// Pines: los numeros deben coincidir con los cables del diagrama.
const int PIN_DHT = 2;            // Entrada de datos del DHT22 (D2).
const int PIN_LED_ROJO = 8;       // Salida para alerta de calor (D8).
const int PIN_LED_AZUL = 9;       // Salida para alerta de humedad (D9).

// Limites didacticos: no son recomendaciones agronomicas.
const float LIMITE_CALOR = 30.0;  // LED rojo se enciende desde 30 C.
const float LIMITE_HUMEDAD = 80.0;// LED azul se enciende desde 80 %.

DHT sensor(PIN_DHT, DHT22);       // Crea un objeto para leer el DHT22.

// ===================== 2. DIA FICTICIO =====================
// Cada posicion representa un momento. Los tres arreglos deben
// conservar la misma cantidad de elementos y el mismo orden.
const int HORAS[] =      { 0,  3,  6,  9, 12, 15, 18, 21};
const float TEMPS[] =   {20, 18, 17, 23, 28, 33, 29, 24};
const float HUMEDADES[] = {78, 85, 88, 72, 55, 40, 53, 68};
const int CANTIDAD = sizeof(HORAS) / sizeof(HORAS[0]);
int paso = 0;                     // Indice del momento actual (0 a 7).

// ===================== 3. INICIO =====================
// setup() se ejecuta UNA SOLA VEZ al arrancar el Arduino.
void setup() {
  Serial.begin(9600);            // Activa el monitor serie de Wokwi.
  pinMode(PIN_LED_ROJO, OUTPUT);  // Configura D8 como salida.
  pinMode(PIN_LED_AZUL, OUTPUT);  // Configura D9 como salida.
  digitalWrite(PIN_LED_ROJO, LOW); // Empieza con ambos LED apagados.
  digitalWrite(PIN_LED_AZUL, LOW);
  sensor.begin();                // Prepara la biblioteca del DHT22.

  if (DIA_AUTOMATICO) {
    Serial.println("MODO: dia ficticio automatico (sin lectura DHT22)");
  } else {
    Serial.println("MODO: lecturas del sensor DHT22");
  }
}

// ===================== 4. CICLO CONTINUO =====================
// loop() se repite mientras Arduino permanezca encendido.
void loop() {
  float temperatura;             // float almacena numeros decimales.
  float humedad;

  // if / else: selecciona de donde vienen los datos.
  if (DIA_AUTOMATICO) {
    temperatura = TEMPS[paso];   // Lee un valor del arreglo.
    humedad = HUMEDADES[paso];   // Mismo momento, otro arreglo.
    Serial.print("Hora simulada: ");
    if (HORAS[paso] < 10) Serial.print("0");
    Serial.print(HORAS[paso]);
    Serial.println(":00");
  } else {
    temperatura = sensor.readTemperature(); // Medicion DHT22 en C.
    humedad = sensor.readHumidity();        // Medicion DHT22 en %.

    // Si el sensor no esta conectado, la lectura es invalida.
    if (isnan(temperatura) || isnan(humedad)) {
      Serial.println("ERROR DHT22: comprueba 5V, GND y D2.");
      digitalWrite(PIN_LED_ROJO, LOW);
      digitalWrite(PIN_LED_AZUL, LOW);
      delay(2000);               // Espera 2 segundos para reintentar.
      return;                    // Termina ESTA vuelta del loop().
    }
  }

  // print() escribe sin salto; println() agrega salto de linea.
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" C | Humedad relativa: ");
  Serial.print(humedad, 1);
  Serial.println(" %");

  // Compara las mediciones y decide el estado de cada LED.
  if (temperatura >= LIMITE_CALOR) {
    digitalWrite(PIN_LED_ROJO, HIGH); // HIGH enciende el LED rojo.
  } else {
    digitalWrite(PIN_LED_ROJO, LOW);  // LOW apaga el LED rojo.
  }

  if (humedad >= LIMITE_HUMEDAD) {
    digitalWrite(PIN_LED_AZUL, HIGH); // Alerta de humedad alta.
  } else {
    digitalWrite(PIN_LED_AZUL, LOW);
  }

  // En modo automatico, avanza al siguiente momento.
  if (DIA_AUTOMATICO) {
    paso++;                          // Equivale a paso = paso + 1.
    if (paso >= CANTIDAD) paso = 0;  // Vuelve a las 00:00.
    delay(3000);                    // 3 s equivalen a 3 h ficticias.
  } else {
    delay(2000);                    // Lee DHT22 cada 2 segundos.
  }
}
