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





void SEMAFORO_init__(SEMAFORO *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__QX0_0,data__->ROJOC,retain)
  __INIT_LOCATED_VALUE(data__->ROJOC,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_1,data__->AMARILLO,retain)
  __INIT_LOCATED_VALUE(data__->AMARILLO,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_2,data__->VERDEC,retain)
  __INIT_LOCATED_VALUE(data__->VERDEC,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_3,data__->ROJOP,retain)
  __INIT_LOCATED_VALUE(data__->ROJOP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_4,data__->VERDEP,retain)
  __INIT_LOCATED_VALUE(data__->VERDEP,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_5,data__->CONT1,retain)
  __INIT_LOCATED_VALUE(data__->CONT1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_6,data__->CONT2,retain)
  __INIT_LOCATED_VALUE(data__->CONT2,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_0,data__->PARADA,retain)
  __INIT_LOCATED_VALUE(data__->PARADA,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->DETENER,__BOOL_LITERAL(FALSE),retain)
  __INIT_LOCATED(BOOL,__IX0_1,data__->CAMBIO,retain)
  __INIT_LOCATED_VALUE(data__->CAMBIO,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->CONMUTAR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T3,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T3AUX1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T3AUX2,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
  TON_init__(&data__->TON2,retain);
  TON_init__(&data__->TON3,retain);
  TON_init__(&data__->TON4,retain);
  __INIT_VAR(data__->REBOOT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void SEMAFORO_body__(SEMAFORO *data__) {
  // Initialise TEMP variables

  __SET_LOCATED(data__->,ROJOC,,(((!(__GET_VAR(data__->T3,)) && !(__GET_VAR(data__->T2,))) || ((__GET_VAR(data__->T3,) && __GET_VAR(data__->T2,)) && __GET_VAR(data__->T1,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_LOCATED(data__->,AMARILLO,,((((!(__GET_VAR(data__->T3,)) && !(__GET_VAR(data__->T2,))) && (__GET_VAR(data__->T1,) || __GET_VAR(data__->T1,))) && !(__GET_VAR(data__->DETENER,))) || (((__GET_VAR(data__->T3,) && __GET_VAR(data__->T2,)) && __GET_VAR(data__->T1,)) && !(__GET_VAR(data__->DETENER,)))));
  __SET_LOCATED(data__->,VERDEC,,(((!(__GET_VAR(data__->T3,)) && __GET_VAR(data__->T2,)) && __GET_VAR(data__->T1,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_LOCATED(data__->,ROJOP,,(((!(__GET_VAR(data__->T3,)) && __GET_VAR(data__->T1,)) || (__GET_VAR(data__->T2,) && __GET_VAR(data__->T1,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_LOCATED(data__->,VERDEC,,(((!(__GET_VAR(data__->T3,)) && !(__GET_VAR(data__->T2,))) && !(__GET_VAR(data__->T1,))) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON0.,IN,,(!(__GET_VAR(data__->REBOOT,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 6000, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,T1,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,IN,,(__GET_VAR(data__->T1,) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 2000, 0, 0, 0, 0));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,T2,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->TON3.,IN,,((!(__GET_VAR(data__->CONMUTAR,)) && __GET_VAR(data__->T2,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON3.,PT,,__time_to_timespec(1, 6000, 0, 0, 0, 0));
  TON_body__(&data__->TON3);
  __SET_VAR(data__->,T3AUX2,,__GET_VAR(data__->TON3.Q,));
  __SET_VAR(data__->TON2.,IN,,((__GET_VAR(data__->CONMUTAR,) && __GET_VAR(data__->T2,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON2.,PT,,__time_to_timespec(1, 800, 0, 0, 0, 0));
  TON_body__(&data__->TON2);
  __SET_VAR(data__->,T3AUX1,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->,T3,,((__GET_VAR(data__->T3AUX1,) || __GET_VAR(data__->T3AUX2,)) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON4.,IN,,(__GET_VAR(data__->T3,) && !(__GET_VAR(data__->DETENER,))));
  __SET_VAR(data__->TON4.,PT,,__time_to_timespec(1, 2000, 0, 0, 0, 0));
  TON_body__(&data__->TON4);
  __SET_VAR(data__->,REBOOT,,__GET_VAR(data__->TON4.Q,));
  __SET_VAR(data__->,DETENER,,(!(__GET_LOCATED(data__->CAMBIO,)) && (__GET_VAR(data__->DETENER,) || __GET_LOCATED(data__->PARADA,))));
  __SET_VAR(data__->,CONMUTAR,,((!(__GET_VAR(data__->REBOOT,)) && __GET_VAR(data__->T2,)) && (__GET_VAR(data__->CONMUTAR,) || (!(__GET_VAR(data__->DETENER,)) && __GET_LOCATED(data__->CAMBIO,)))));
  __SET_LOCATED(data__->,CONT1,,!(__GET_VAR(data__->DETENER,)));
  __SET_LOCATED(data__->,CONT2,,!(__GET_VAR(data__->DETENER,)));

  goto __end;

__end:
  return;
} // SEMAFORO_body__() 





