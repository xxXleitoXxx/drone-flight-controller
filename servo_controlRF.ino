#include <Wire.h>

// Variables para guardar el estado y tiempos
volatile unsigned long current_time;
volatile unsigned long timer[4]; 
volatile byte previous_state[4];

// Aquí se guardará la duración del pulso (1000 a 2000 us)
// Estos son los valores que realmente te importan
volatile unsigned int pulse_length[4] = {1500, 1500, 1000, 1500};

void setup() {
  Serial.begin(9600);

  // Configuramos los pines 8, 9, 10, 11 como entrada
  // (Aunque la manipulación de registros abajo hace esto, es bueno ser explícito)
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  // --- CONFIGURACIÓN DE INTERRUPCIONES (La parte importante) ---
  // Habilitamos interrupciones para el puerto B (Pines D8 a D13 en Arduino Uno/Nano)
  PCICR  |= (1 << PCIE0);  
  
  // Decimos qué pines específicos activan la interrupción
  PCMSK0 |= (1 << PCINT0); // Pin Digital 8
  PCMSK0 |= (1 << PCINT1); // Pin Digital 9
  PCMSK0 |= (1 << PCINT2); // Pin Digital 10
  PCMSK0 |= (1 << PCINT3); // Pin Digital 11
  
  Serial.println("Sistema iniciado. Mueve los sticks...");
}

void loop() {
  // Imprimimos los valores calculados por la interrupción
  // Usamos una copia local para no interferir con la interrupción mientras imprimimos
  
  Serial.print("CH1: "); Serial.print(pulse_length[0]);
  Serial.print(" | CH2: "); Serial.print(pulse_length[1]);
  Serial.print(" | CH3: "); Serial.print(pulse_length[2]);
  Serial.print(" | CH4: "); Serial.println(pulse_length[3]);
  
  // Un delay pequeño solo para que se pueda leer las interrupciones
  
  // las interrupciones siguen funcionando en el fondo
  delay(100); 
}

// -----------------------------------------------------------------------
// ESTA ES LA RUTINA QUE FALTABA
// Se ejecuta automáticamente cada vez que el pin 8, 9, 10 u 11 cambia de estado
// -----------------------------------------------------------------------
ISR(PCINT0_vect) {
  current_time = micros(); // Marca de tiempo actual

  // --- CANAL 1 (PIN 8) ---
  // Leemos el registro PINB bit 0. Es mucho más rápido que digitalRead(8)
  if (PINB & B00000001) {           // Si el pin 8 está HIGH
    if (previous_state[0] == LOW) { // Y antes estaba LOW (Subida)
      previous_state[0] = HIGH;
      timer[0] = current_time;      // Guardamos cuando empezó el pulso
    }
  } else if (previous_state[0] == HIGH) { // Si el pin está LOW y antes estaba HIGH (Bajada)
    previous_state[0] = LOW;
    pulse_length[0] = current_time - timer[0]; // Calculamos la duración
  }

  // --- CANAL 2 (PIN 9) ---
  if (PINB & B00000010) { 
    if (previous_state[1] == LOW) {
      previous_state[1] = HIGH;
      timer[1] = current_time;
    }
  } else if (previous_state[1] == HIGH) {
    previous_state[1] = LOW;
    pulse_length[1] = current_time - timer[1];
  }

  // --- CANAL 3 (PIN 10) ---
  if (PINB & B00000100) { 
    if (previous_state[2] == LOW) {
      previous_state[2] = HIGH;
      timer[2] = current_time;
    }
  } else if (previous_state[2] == HIGH) {
    previous_state[2] = LOW;
    pulse_length[2] = current_time - timer[2];
  }

  // --- CANAL 4 (PIN 11) ---
  if (PINB & B00001000) { 
    if (previous_state[3] == LOW) {
      previous_state[3] = HIGH;
      timer[3] = current_time;
    }
  } else if (previous_state[3] == HIGH) {
    previous_state[3] = LOW;
    pulse_length[3] = current_time - timer[3];
  }
}
