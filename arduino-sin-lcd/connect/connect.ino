// #####################################################################
// constantes:
//  t_min: tiempo que tomara la transición entre estado si el usuario 
//  solicita un cambio antes del tiempo obligatorio.
//  t_must: tiempo obligatorio que tomara la transición entre estados.
//  ins_number: numero de entradas del sistema.
//  outs_number: numero de salidas del sistema.
//  ins_pins: arreglo con los pines del ESP32 asignados como entradas.
//  outs_pins: arreglo con los pines del ESP32 asignados como salidas.
//  triangulo, estrella: arreglo con las salidas correspondientes a 
//  los estados "conexión delta" & "conexión estrella" respectivamente.
// #####################################################################
const long t_min = 500;
const long t_must = 8000;
const int ins_number = 8;
const int outs_number = 8;
const int ins_pins[ins_number] = {23,22,21,32,27,14,12,13};
const int outs_pins[outs_number] = {19,18,5,17,16,4,2,15};
const int triangulo[outs_number] = {HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW, LOW};
const int estrella[outs_number] = {LOW, LOW, LOW, HIGH, HIGH, LOW, HIGH, LOW};

// #####################################################################
// variables para interrupciones:
// cambio: determina el cambio de conexión por el usuario.
// stop: determina una parada por el usuario.
// #####################################################################
volatile boolean cambio = false;
volatile boolean stop = false;

// #####################################################################
// funciones para interrupciones:
// change: detecta una solicitud de cambio por el usuario & el fin 
// de un ciclo de parada
// parada: detecta una solicitud de parada por el usuario
// #####################################################################
void change() {
  cambio = true;
  stop = false;
}
void parada() {
  stop = true;
}

// #####################################################################
// state_m: función para establecer los estado
// #####################################################################
void state_m(long t_dur, const int sec[], int l_sec) {
  unsigned long t11 = millis();       // instante de tiempo inicial
  while (stop == false) {       // sostener el estado
    if (cambio  == true) {  // verificar posible interrupción
      t_dur = t_min;        // forzar duración del estado
    }
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
}

// #####################################################################
// ciclo principal
// #####################################################################
void loop() {
  // se inicial el sistema en conexión delta
  state_m(t_must, triangulo, 7);
  // se habilita la interrupción de parada
  attachInterrupt(digitalPinToInterrupt(ins_pins[0]), parada, FALLING);
  // operación normal del sistema
  while (stop == false) {
    // se habilita interrupción para cambiar conexión y se establece 
    // conexión estrella
    attachInterrupt(digitalPinToInterrupt(ins_pins[7]), change, FALLING);
    state_m(t_must, estrella, 7);
    cambio = false;
    detachInterrupt(ins_pins[7]);
    // se habilita interrupción para cambiar conexión y se establece 
    // conexión delta
    attachInterrupt(digitalPinToInterrupt(ins_pins[7]), change, FALLING);
    state_m(t_must, triangulo, 7);
    cambio = false;
    detachInterrupt(ins_pins[7]);
  }
  // operación en caso de parada
  while (stop == true) {
    // se habilita interrupción para reiniciar el sistema
    attachInterrupt(digitalPinToInterrupt(ins_pins[7]), change, FALLING);
    for (int i = 0; i < outs_number; i++) digitalWrite(outs_pins[i], LOW);
  }
  cambio = false;
  detachInterrupt(ins_pins[7]);
  detachInterrupt(ins_pins[0]);
}
