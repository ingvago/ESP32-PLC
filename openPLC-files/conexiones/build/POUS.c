void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void CONEXIONES_init__(CONEXIONES *data__, BOOL retain) {
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
  __INIT_VAR(data__->PARDADA,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONMUTAR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CAMBIAR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DETENER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DELTA,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ESTRELLA,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->YON,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->YONAUX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DOSOFF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DOSOFFAUX,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON2,retain);
  TON_init__(&data__->TON3,retain);
}

// Code part
void CONEXIONES_body__(CONEXIONES *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,DETENER,,(!(__GET_VAR(data__->CONMUTAR,)) && (__GET_VAR(data__->DETENER,) || __GET_VAR(data__->PARDADA,))));
  __SET_VAR(data__->TON1.,IN,,(((!(__GET_VAR(data__->DOSOFFAUX,)) && !(__GET_VAR(data__->DOSOFF,))) && !(__GET_VAR(data__->CAMBIAR,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 10000, 0, 0, 0, 0));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,YON,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->TON0.,IN,,(((!(__GET_VAR(data__->DOSOFF,)) && (__GET_VAR(data__->YON,) || __GET_VAR(data__->YONAUX,))) && !(__GET_VAR(data__->CAMBIAR,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 10000, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,DOSOFF,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->,DELTA,,((!(__GET_VAR(data__->YONAUX,)) && !(__GET_VAR(data__->YON,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->,ESTRELLA,,((__GET_VAR(data__->YON,) || __GET_VAR(data__->YONAUX,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON2.,IN,,(((__GET_VAR(data__->CAMBIAR,) && !(__GET_VAR(data__->ESTRELLA,))) || ((!(__GET_VAR(data__->DOSOFFAUX,)) && !(__GET_VAR(data__->DOSOFF,))) && __GET_VAR(data__->YONAUX,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON2.,PT,,__time_to_timespec(1, 500, 0, 0, 0, 0));
  TON_body__(&data__->TON2);
  __SET_VAR(data__->,YONAUX,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->TON3.,IN,,((__GET_VAR(data__->CAMBIAR,) && !(__GET_VAR(data__->DELTA,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON3.,PT,,__time_to_timespec(1, 500, 0, 0, 0, 0));
  TON_body__(&data__->TON3);
  __SET_VAR(data__->,DOSOFFAUX,,__GET_VAR(data__->TON3.Q,));
  __SET_VAR(data__->,CAMBIAR,,((!(__GET_VAR(data__->DOSOFFAUX,)) && !(__GET_VAR(data__->DOSOFF,))) && (__GET_VAR(data__->CAMBIAR,) || (!(__GET_VAR(data__->DETENER,)) && __GET_VAR(data__->CONMUTAR,)))));

  goto __end;

__end:
  return;
} // CONEXIONES_body__() 





