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
// PROGRAM CONEXIONES
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  TON TON0;
  TON TON1;
  __DECLARE_VAR(BOOL,PARDADA)
  __DECLARE_VAR(BOOL,CONMUTAR)
  __DECLARE_VAR(BOOL,CAMBIAR)
  __DECLARE_VAR(BOOL,DETENER)
  __DECLARE_VAR(BOOL,DELTA)
  __DECLARE_VAR(BOOL,ESTRELLA)
  __DECLARE_VAR(BOOL,YON)
  __DECLARE_VAR(BOOL,YONAUX)
  __DECLARE_VAR(BOOL,DOSOFF)
  __DECLARE_VAR(BOOL,DOSOFFAUX)
  TON TON2;
  TON TON3;

} CONEXIONES;

void CONEXIONES_init__(CONEXIONES *data__, BOOL retain);
// Code part
void CONEXIONES_body__(CONEXIONES *data__);
#endif //__POUS_H
