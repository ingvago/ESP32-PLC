// #####################################################################
// librerías
// #####################################################################
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// #####################################################################
// constantes:
//  t_min: tiempo que durara el estado verde carros y rojo para peatón, 
//         en el caso que el peatón solicite cruzar la vía.
//  ins_number: numero de entradas del sistema.
//  outs_number: numero de salidas del sistema.
//  ins_pins: arreglo con los pines del ESP32 asignados como entradas.
//  outs_pins: arreglo con los pines del ESP32 asignados como salidas.
//  rojo_c: arreglo de salidas digitales para obtener la secuencia
//          rojo para carros y verde para peatón.
//  amarillo_c: arreglo de salidas digitales para obtener la secuencia 
//              amarillo carros y rojo para peatón.
//  verde_c: arreglo de salidas digitales para obtener la secuencia 
//           verde carros y rojo para peatón.
// #####################################################################
const long t_min = 800;
const int ins_number = 8;
const int outs_number = 8;
const int ins_pins[ins_number] = {23,22,21,32,27,14,12,13};
const int outs_pins[outs_number] = {19,18,5,17,16,4,2,15};
const int rojo_c[7] = {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH};
const int amarillo_c[7] = {HIGH, HIGH, LOW, HIGH, LOW, HIGH, HIGH};
const int verde_c[7] = {LOW, LOW, HIGH, HIGH, LOW, HIGH, HIGH};

// #####################################################################
// variables para interrupciones:
//  solicitud_peaton: determina el momento en que el peatón solicita 
//                    cruzar la vía. Esta interrupción solo es valida 
//                    cuando el semáforo se encuentra en el estado 
//                    verde carros y rojo peatón.
//  emergencia: determina el momento en que un operario interrumpe el 
//  sistema; con el fin de intervenir el semáforo de forma segura.
// #####################################################################
volatile boolean solicitud_peaton = false;
volatile boolean emergencia = false;

// #####################################################################
// funciones para interrupciones:
//  peaton: espera por la solicitud del peatón. En caso de recibir una 
//          solicitud, establece como verdadero el estado de la 
//          variable solicitud_peaton. Con esta información, el sistema
//          forzara la duración del estado verde carro y rojo peatón al 
//          valor establecido en la variable t_min. Esta interrupción 
//          solo es valida para el estado verde carros y rojo peatón.
//  interr: espera la entrada del operario a través del botón rojo. De 
//          recibirla, se establece como verdadera la variable 
//          emergencia. Con esta información, el sistema cambia el 
//          estado de los conmutadores de la fuente AC y entra en 
//          bloqueo.
//  siga: espera la entrada del operario a través del botón verde. De 
//        recibirla, se pondrá fin al estado de emergencia.
// #####################################################################
void peaton() {
  solicitud_peaton = true;
}
void interr() {
  emergencia = true;
}
void siga() {
  emergencia = false;
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
// blink: semáforo en estado intermitente
// argumentos:
//  luz_vehiculos: bombillo intermitente para vehículos
//  luz_peaton: bombillo intermitente para peatones
//  t_dur: duración, en milisegundos, del estado intermitente
//  t_par: duración, en milisegundos, de la oscilación
// variables:
//  t11: inicio del ciclo
//  t22: instante en que cambia el estado del bombillo
// #####################################################################
void blink(int luz_vehiculos, int luz_peaton, long t_dur, long t_par) {
  escritura("Estado", "Intermitente");
  // encender conmutadores
  for (int i = 5; i < outs_number-1; i++) digitalWrite(outs_pins[i], HIGH);
  unsigned long t11 = millis(); // instante de tiempo inicial
  unsigned long t22 = t11;      // inicio del estado
  // repetir hasta un valor de tiempo
  while((millis() - t11 <= t_dur) && (emergencia == false)) {  
    if (millis() - t22 >= t_par) {  // verificar duración del estado
      t22 = millis();               // actualizar inicio del estado
      digitalWrite(outs_pins[luz_vehiculos], !digitalRead(outs_pins[luz_vehiculos]));
      digitalWrite(outs_pins[luz_peaton], !digitalRead(outs_pins[luz_peaton]));
    }
  }
}

// #####################################################################
// state_m: función para establecer los estados del semáforo
//  argumentos:
//    t_dur: duración del estado inmediatamente anterior
//    sec: vector con el estado a asignar por cada salida
//    l_sec: longitud del vector sec
//  variables: (globales)
//    outs_pins: vector con los pines de salida
//    t_min: tiempo que durara el estado verde carros y rojo para peatón, 
//           en el caso que el peatón solicite cruzar la vía.
//    solicitud_peaton: ver variables de interrupción.
//    emergencia: ver variables de interrupción.
//  variables: (locales)
//    t11: inicio del estado, en milisegundos
// #####################################################################
void state_m(long t_dur, const int sec[], int l_sec) {
  unsigned long t11 = millis();       // instante de tiempo inicial
  while (emergencia == false) {       // sostener el estado
    if (solicitud_peaton  == true) {  // verificar posible interrupción
      t_dur = t_min;            // forzar duración del estado
    }
    if (millis() - t11 >= t_dur) {  // verificar duración del estado
      // establecer secuencia (salidas) del próximo estado
      for (int i = 0; i < l_sec; i++) digitalWrite(outs_pins[i], sec[i]);
      break;  // romper estado, una vez cumplida la duración
    }
  }
}

// #####################################################################
// lights: ciclo principal del semáforo
//  argumentos:
//    t_pv: duración del estado: vía peatones - alto vehículos
//    t_vp: duración del estado: vía vehículos - alto peatones
//    t_inter: duración estados intermedios
// nota: la unidad de tiempo es milisegundos.
// #####################################################################
void lights(long t_pv, long t_vp, long t_inter) {
  // de: estado - rojo carro - para: amarillo intermedio
  state_m(t_pv, amarillo_c, 7);
  // de: amarillo intermedio - para: estado - verde carro
  state_m(t_inter, verde_c, 7);
  // de: estado - verde carro - para: amarillo - intermedio
  // se habilidad la interrupción del peatón, permitiendo solicitar 
  // cruzar la vía
  attachInterrupt(digitalPinToInterrupt(ins_pins[7]), peaton, FALLING);
  state_m(t_vp, amarillo_c, 7);
  // se reinicia la interrupción del peatón para evitar errores en 
  // un próximo ciclo.
  solicitud_peaton = false;
  // se deshabilita la interrupción del peatón
  detachInterrupt(digitalPinToInterrupt(ins_pins[7]));
  // de: amarillo intermedio - para: estado - rojo carro
  state_m(t_inter, rojo_c, 7);
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
}

// #####################################################################
// ciclo principal
// #####################################################################
void loop() {
  // establecer interrupción de emergencia
  attachInterrupt(digitalPinToInterrupt(ins_pins[0]), interr, FALLING);
  // ciclo intermitente con amarillo carro & rojo peatón
  blink(1,3,5000,1000);
  // establecer estado - rojo carro y verde peatón
  for (int i = 0; i<5; i++) digitalWrite(outs_pins[i], rojo_c[i]);
  escritura("Semaforo en", "funcionamiento");
  while (emergencia == false) {
    lights(8000,8000,2000);     // ciclo principal del semáforo
  }
  detachInterrupt(digitalPinToInterrupt(ins_pins[0]));
  attachInterrupt(digitalPinToInterrupt(ins_pins[7]), siga, FALLING);
  while (emergencia == true) {
    // parada de emergencia
    for (int i = 0; i < outs_number; i++) digitalWrite(outs_pins[i], LOW);
    escritura("Parada", "de emergencia");
  }
}
