// #####################################################################
// librerías
// #####################################################################
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// #####################################################################
// constantes:
//  t_min: una cantidad de tiempo para sostener los estados con la
//  menor duración.
//  t_must: cantidad de tiempo para sostener los estados con la 
//  mayor duración.
//  wait: cantidad de tiempo para esperar la entrada de alguno de 
//  los jugadores.
//  ins_number: numero de entradas del sistema.
//  outs_number: numero de salidas del sistema.
//  ins_pins: arreglo con los pines del ESP32 asignados como entradas.
//  outs_pins: arreglo con los pines del ESP32 asignados como salidas.
//  uno, dos, tres,: arreglo para las salidas correspondientes a los
//  estados "en sus marcas", "listos" & "ya".
//  lrojo, lverde: arreglo para las salidas correspondientes a los 
//  estados "jugador verde es ganador" & "jugador rojo es ganador"
// #####################################################################
const long t_min = 200;
const long t_must = 4000;
const long wait = 6000;
const int ins_number = 8;
const int outs_number = 8;
const int ins_pins[ins_number] = {23,22,21,32,27,14,12,13};
const int outs_pins[outs_number] = {19,18,5,17,16,4,2,15};
const int uno[outs_number] = {HIGH, LOW, LOW, LOW, LOW, HIGH, HIGH, LOW};
const int dos[outs_number] = {HIGH, HIGH, LOW, LOW, LOW, HIGH, HIGH, LOW};
const int tres[outs_number] = {LOW, LOW, HIGH, LOW, LOW, HIGH, HIGH, LOW};
const int lrojo[outs_number] = {LOW, LOW, LOW, HIGH, LOW, HIGH, HIGH, LOW};
const int lverde[outs_number] = {LOW, LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW};

// #####################################################################
// variables para interrupciones:
// verde: entrada asignada al jugador verde
// rojo: entrada asignada al jugador rojo
// stop: variable para indicar el inicio de la actividad / juego
// #####################################################################
volatile boolean verde = false;
volatile boolean rojo = false;
volatile boolean stop = true;

// #####################################################################
// funciones para interrupciones:
// cverde: detectar acción del jugador verde
// crojo: detectar acción del jugador rojo
// begin: detectar inicio del juego
// #####################################################################
void cverde() {
  verde = true;
}
void crojo() {
  rojo = true;
}
void begin() {
  stop = false;
}

// #####################################################################
// escritura: escribir mensaje en LCD
// argumentos:
//  str-1: primera linea
//  str-2: segunda linea
// #####################################################################
void escritura(String str_1, String str_2) {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str_1);
  lcd.setCursor(0, 1);
  lcd.print(str_2);
}


// #####################################################################
// state_m: función para establecer los estado
// #####################################################################
void state_m(long t_dur, const int sec[], int l_sec) {
  unsigned long t11 = millis();       // instante de tiempo inicial
  while (true) {       // sostener el estado
    if (millis() - t11 >= t_dur) {  // verificar duración del estado
      // establecer secuencia (salidas) del próximo estado
      for (int i = 0; i < l_sec; i++) digitalWrite(outs_pins[i], sec[i]);
      break;  // romper estado, una vez cumplida la duración
    }
  }
}

// ########################################################################
// configuración inicial
// ########################################################################
void setup() {
  // establecer pines como entradas con resistencia "pull up"
  for (int i = 0; i < ins_number; i++) pinMode(ins_pins[i], INPUT_PULLUP);  
  // estableces pines como salidas
  for (int i = 0; i < outs_number; i++) pinMode(outs_pins[i], OUTPUT);     
  // apagar todas las salidas del sistema
  for (int i = 0; i < outs_number; i++) digitalWrite(outs_pins[i], LOW);
  // LCD
  lcd.clear();
}

// #####################################################################
// ciclo principal
// #####################################################################
void loop() {
  // mensaje inicial
  while (stop == true) {
    attachInterrupt(digitalPinToInterrupt(ins_pins[7]), begin, FALLING);
    escritura("Empezar", "B. Verde");
  }
  stop = true;
  lcd.clear();
  detachInterrupt(ins_pins[7]);   // desactivar interrupción del botón verde
  long trand = random(1000,5000); // tiempo aleatorio para prueba de reflejos
  while (true) {                  // empieza la actividad / juego
    state_m(t_min, uno, outs_number);
    escritura("En sus", "marcas");
    state_m(t_must, dos, outs_number);
    escritura("Listos", "Tiempo: " + String(trand/1000) + "s");
    state_m(trand, tres, outs_number);
    // se habilitan las interrupciones para los botones rojo y verde
    attachInterrupt(digitalPinToInterrupt(ins_pins[7]), cverde, FALLING);
    attachInterrupt(digitalPinToInterrupt(ins_pins[0]), crojo, FALLING);
    // se espera la respuesta de algún jugador
    unsigned long t11 = millis();
    while ((verde == false && rojo == false) && (millis() - t11 <= wait)) {
      escritura("Ya", "!!!");
    }
    // se desactivan las interrupciones para todos
    detachInterrupt(ins_pins[0]);
    detachInterrupt(ins_pins[7]);
    // se determina el ganador de acuerdo a las variables de interrupción
    if (verde == true) {
      verde = false;
      state_m(t_min, lverde, outs_number);
      escritura("Ganador", "Verde");
      delay(5000);
    }
    else if (rojo == true) {
      rojo = false;
      state_m(t_min, lrojo, outs_number);
      escritura("Ganador", "Rojo");
      delay(5000);
    }
    else {
      escritura("Nadie", "Gano");
      for (int i = 0; i < outs_number-3; i++) digitalWrite(outs_pins[i], LOW);
      delay(5000);
    }
    break;
  }
}
