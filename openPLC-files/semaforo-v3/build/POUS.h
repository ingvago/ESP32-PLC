#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM SEMAFORO
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(BOOL,ROJOC)
  __DECLARE_LOCATED(BOOL,AMARILLO)
  __DECLARE_LOCATED(BOOL,VERDEC)
  __DECLARE_LOCATED(BOOL,ROJOP)
  __DECLARE_LOCATED(BOOL,VERDEP)
  __DECLARE_LOCATED(BOOL,CONT1)
  __DECLARE_LOCATED(BOOL,CONT2)
  __DECLARE_LOCATED(BOOL,PARADA)
  __DECLARE_VAR(BOOL,DETENER)
  __DECLARE_LOCATED(BOOL,CAMBIO)
  __DECLARE_VAR(BOOL,CONMUTAR)
  __DECLARE_VAR(BOOL,T1)
  __DECLARE_VAR(BOOL,T2)
  __DECLARE_VAR(BOOL,T3)
  __DECLARE_VAR(BOOL,T3AUX1)
  __DECLARE_VAR(BOOL,T3AUX2)
  TON TON0;
  TON TON1;
  TON TON2;
  TON TON3;
  TON TON4;
  __DECLARE_VAR(BOOL,REBOOT)

} SEMAFORO;

void SEMAFORO_init__(SEMAFORO *data__, BOOL retain);
// Code part
void SEMAFORO_body__(SEMAFORO *data__);
#endif //__POUS_H
