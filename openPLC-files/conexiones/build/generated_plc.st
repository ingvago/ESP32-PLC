PROGRAM conexiones
  VAR
    TON0 : TON;
    TON1 : TON;
    Pardada : BOOL;
    Conmutar : BOOL;
    Cambiar : BOOL;
    Detener : BOOL;
    Delta : BOOL;
    Estrella : BOOL;
    YOn : BOOL;
    YOnAux : BOOL;
    DosOff : BOOL;
    DosOffAux : BOOL;
    TON2 : TON;
    TON3 : TON;
  END_VAR

  Detener := NOT(Conmutar) AND (Detener OR Pardada);
  TON1(IN := NOT(DosOffAux) AND NOT(DosOff) AND NOT(Cambiar) AND NOT(Detener), PT := T#10000ms);
  YOn := TON1.Q;
  TON0(IN := NOT(DosOff) AND (YOn OR YOnAux) AND NOT(Cambiar) AND NOT(Detener), PT := T#10000ms);
  DosOff := TON0.Q;
  Delta := NOT(YOnAux) AND NOT(YOn) AND NOT(Detener);
  Estrella := (YOn OR YOnAux) AND NOT(Detener);
  TON2(IN := (Cambiar AND NOT(Estrella) OR NOT(DosOffAux) AND NOT(DosOff) AND YOnAux) AND NOT(Detener), PT := T#500ms);
  YOnAux := TON2.Q;
  TON3(IN := Cambiar AND NOT(Delta) AND NOT(Detener), PT := T#500ms);
  DosOffAux := TON3.Q;
  Cambiar := NOT(DosOffAux) AND NOT(DosOff) AND (Cambiar OR NOT(Detener) AND Conmutar);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : conexiones;
  END_RESOURCE
END_CONFIGURATION
