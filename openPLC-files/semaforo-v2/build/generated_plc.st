PROGRAM semaforo
  VAR
    rojoc AT %QX0.0 : BOOL;
    amarillo AT %QX0.1 : BOOL;
    verdec AT %QX0.2 : BOOL;
    rojop AT %QX0.3 : BOOL;
    verdep AT %QX0.4 : BOOL;
    cont1 AT %QX0.5 : BOOL;
    cont2 AT %QX0.6 : BOOL;
    parada AT %IX0.5 : BOOL;
  END_VAR
  VAR
    detener : BOOL;
  END_VAR
  VAR
    cambio AT %IX0.6 : BOOL;
  END_VAR
  VAR
    conmutar : BOOL;
    T1 : BOOL;
    T2 : BOOL;
    T3 : BOOL;
    T4 : BOOL;
    T4aux : BOOL;
    reboot : BOOL;
    TON0 : TON;
    TON1 : TON;
    TON2 : TON;
    TON3 : TON;
    TON4 : TON;
  END_VAR

  rojoc := NOT(T2) AND NOT(detener);
  amarillo := NOT(NOT(T2) AND NOT(detener));
  verdec := NOT(NOT(T2) AND NOT(detener));
  rojop := NOT(NOT(T2) AND NOT(detener));
  verdep := NOT(T2) AND NOT(detener);
  rojoc := NOT(T3) AND T2 AND NOT(detener);
  amarillo := NOT(T3) AND T2 AND NOT(detener);
  verdec := NOT(NOT(T3) AND T2 AND NOT(detener));
  rojoc := NOT(T3) AND T2 AND NOT(detener);
  verdep := NOT(NOT(T3) AND T2 AND NOT(detener));
  rojoc := NOT(NOT(T4) AND NOT(T4aux) AND T3 AND NOT(detener));
  amarillo := NOT(NOT(T4) AND NOT(T4aux) AND T3 AND NOT(detener));
  verdec := NOT(T4) AND NOT(T4aux) AND T3 AND NOT(detener);
  rojoc := NOT(T4) AND NOT(T4aux) AND T3 AND NOT(detener);
  verdep := NOT(NOT(T4) AND NOT(T4aux) AND T3 AND NOT(detener));
  rojoc := NOT(reboot) AND T4 AND NOT(T4aux) AND NOT(detener);
  amarillo := NOT(reboot) AND T4 AND NOT(T4aux) AND NOT(detener);
  verdec := NOT(NOT(reboot) AND T4 AND NOT(T4aux) AND NOT(detener));
  rojoc := NOT(reboot) AND T4 AND NOT(T4aux) AND NOT(detener);
  verdep := NOT(NOT(reboot) AND T4 AND NOT(T4aux) AND NOT(detener));
  TON0(IN := NOT(reboot), PT := T#7000ms);
  T2 := TON0.Q;
  TON1(IN := T2 AND NOT(reboot), PT := T#2000ms);
  T3 := TON1.Q;
  TON2(IN := T3 AND NOT(reboot), PT := T#7000ms);
  T4 := TON2.Q;
  TON3(IN := (T4 OR T4 OR T4aux) AND NOT(reboot), PT := T#2000ms);
  reboot := TON3.Q;
  verdep := NOT(NOT(reboot) AND T4aux AND NOT(T4) AND NOT(detener));
  rojoc := NOT(reboot) AND T4aux AND NOT(T4) AND NOT(detener);
  verdec := NOT(NOT(reboot) AND T4aux AND NOT(T4) AND NOT(detener));
  amarillo := NOT(reboot) AND T4aux AND NOT(T4) AND NOT(detener);
  rojoc := NOT(reboot) AND T4aux AND NOT(T4) AND NOT(detener);
  TON4(IN := conmutar AND T3 AND NOT(reboot), PT := T#800ms);
  T4aux := TON4.Q;
  cont1 := NOT(detener);
  cont2 := NOT(detener);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : semaforo;
  END_RESOURCE
END_CONFIGURATION
