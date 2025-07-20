PROGRAM semaforo
  VAR
    rojoc AT %QX0.0 : BOOL;
    amarillo AT %QX0.1 : BOOL;
    verdec AT %QX0.2 : BOOL;
    rojop AT %QX0.3 : BOOL;
    verdep AT %QX0.4 : BOOL;
    cont1 AT %QX0.5 : BOOL;
    cont2 AT %QX0.6 : BOOL;
    parada AT %IX0.0 : BOOL;
  END_VAR
  VAR
    detener : BOOL;
  END_VAR
  VAR
    cambio AT %IX0.1 : BOOL;
  END_VAR
  VAR
    conmutar : BOOL;
    T1 : BOOL;
    T2 : BOOL;
    T3 : BOOL;
    T3aux1 : BOOL;
    T3aux2 : BOOL;
    TON0 : TON;
    TON1 : TON;
    TON2 : TON;
    TON3 : TON;
    TON4 : TON;
    reboot : BOOL;
  END_VAR

  rojoc := (NOT(T3) AND NOT(T2) OR T3 AND T2 AND T1) AND NOT(detener);
  amarillo := NOT(T3) AND NOT(T2) AND (T1 OR T1) AND NOT(detener) OR T3 AND T2 AND T1 AND NOT(detener);
  verdec := NOT(T3) AND T2 AND T1 AND NOT(detener);
  rojop := (NOT(T3) AND T1 OR T2 AND T1) AND NOT(detener);
  verdec := NOT(T3) AND NOT(T2) AND NOT(T1) AND NOT(detener);
  TON0(IN := NOT(reboot) AND NOT(detener), PT := T#6000ms);
  T1 := TON0.Q;
  TON1(IN := T1 AND NOT(detener), PT := T#2000ms);
  T2 := TON1.Q;
  TON3(IN := NOT(conmutar) AND T2 AND NOT(detener), PT := T#6000ms);
  T3aux2 := TON3.Q;
  TON2(IN := conmutar AND T2 AND NOT(detener), PT := T#800ms);
  T3aux1 := TON2.Q;
  T3 := (T3aux1 OR T3aux2) AND NOT(detener);
  TON4(IN := T3 AND NOT(detener), PT := T#2000ms);
  reboot := TON4.Q;
  detener := NOT(cambio) AND (detener OR parada);
  conmutar := NOT(reboot) AND T2 AND (conmutar OR NOT(detener) AND cambio);
  cont1 := NOT(detener);
  cont2 := NOT(detener);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : semaforo;
  END_RESOURCE
END_CONFIGURATION
