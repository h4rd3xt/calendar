#include <stdio.h>
#include <string.h>

int dia,mes,anio,cuentaDias;
/*************************************************************
FUNCIONES Y PROCEDIMIENTOS PARA CALCULAR LOS DÍAS DE LOS MESES
*************************************************************/
/*Comprueba si un año es bisiesto*/
bool esBisiesto(int anio) {
  if (anio % 4 == 0 && (anio %100 != 0 || anio%400 == 0)) {
    return true;
  }
  return false;
}
/*Calcula el número de días que tiene un mes*/
int numeroDiasMes(int mes, int anio) {
  switch (mes) {
  case 1:
    return 31;
    break;
  case 2:
    if (esBisiesto(anio)) {
      return 29;
    }
    return 28;
    break;
  case 3:
    return 31;
    break;
  case 4:
    return 30;
    break;
  case 5:
    return 31;
    break;
  case 6:
    return 30;
    break;
  case 7:
    return 31;
    break;
  case 8:
    return 31;
    break;
  case 9:
    return 30;
    break;
  case 10:
    return 31;
    break;
  case 11:
    return 30;
    break;
  case 12:
    return 31;
    break;
  }
}
/*Número de días que tiene un año*/
int diasAnio(int anio) {
  if (esBisiesto(anio)) {
    return 366;
  }
  return 365;
}
/*Días entre el 1 enero del año introducido y el 1 de enero de 1601*/
int numeroDiasHasta(int anio) {
  int n = 0;
  for (int i = 1  ; i <= anio-1601 ; i++) {
    n = n + diasAnio(1600+i);
  }
  return n;
}
/*Número de días desde el primer día del año introducido hasta el mes pasado por parámetro*/
int numeroDiasAnio(int mes, int anio) {
  int m = 0; //Días Enero de año nuevo
  for (int i = 1 ; i < mes ; i++) {
    m = m + numeroDiasMes(i,anio);
  }
  return m;
}
/*Día de la semana que cae el año nuevo*/
int diaSemanaAnioNuevo(int anio) {
  int diaSemana;
  int nDias = numeroDiasHasta(anio);
  diaSemana = nDias%7;
  return diaSemana;
}
/*Día de la semana del día 1 de un mes y un año*/
int diaSemanaMes(int mes, int anio) {
  int s = diaSemanaAnioNuevo(anio);
  int d = numeroDiasAnio(mes,anio);
  int r = (s + d)%7;
  return r;
}
/*Día de la semana del último día del mes*/
int diaSemanaUltimoDeMes(int mes, int anio) {
  int s = diaSemanaMes(mes,anio);
  int d = numeroDiasMes(mes,anio);
  int r = (s + d)%7;
  return r;
}
/**********************************
FORMATO DE IMPRESIÓN DEL CALENDARIO
***********************************/
/*Imprime el mes elegido*/
void impCabeceraMes(int mes, int anio) {
  switch (mes) {
  case 1:
    printf("ENERO                  %d",anio);
    break;
  case 2:
    printf("FEBRERO                %d",anio);
    break;
  case 3:
    printf("MARZO                  %d",anio);
    break;
  case 4:
    printf("ABRIL                  %d",anio);
    break;
  case 5:
    printf("MAYO                   %d",anio);
    break;
  case 6:
    printf("JUNIO                  %d",anio);
    break;
  case 7:
    printf("JULIO                  %d",anio);
    break;
  case 8:
    printf("AGOSTO                 %d",anio);
    break;
  case 9:
    printf("SEPTIEMBRE             %d",anio);
    break;
  case 10:
    printf("OCTUBRE                %d",anio);
    break;
  case 11:
    printf("NOVIEMBRE              %d",anio);
    break;
  case 12:
    printf("DICIEMBRE              %d",anio);
    break;
  }
}
/*Imprime la cabecera de la semana*/
void impCabeceraSemana() {
  printf("\n===========================\n");
  printf("LU  MA  MI  JU  VI | SA  DO");
  printf("\n===========================\n");
}
/*Imprime la cabecera del calendario*/
void impCabeceraCalendario(int mes, int anio) {
  impCabeceraMes(mes,anio);
  impCabeceraSemana();
}
/*Imprime los posibles puntos del mes*/
void impPuntos(int mes, int anio) {
  if (cuentaDias == 5 || cuentaDias == 26 || cuentaDias == 33 || cuentaDias == 40) { //Cuando es jueves = cambio de formato
    printf(" . | "); //Unión viernes-sábado
  } else {
    printf(" .  "); //Resto de días
  }
}
/*Imprime el formato correcto en función de los dígitos de los días y de los fines de semana*/
void impFormatoDia(int dia) {
  if (dia > 0 && dia <= 9) { //Día de un dígito
    if (cuentaDias == 5 || cuentaDias == 12 || cuentaDias == 19 || cuentaDias == 26 || cuentaDias == 33) { //Cuando es jueves = cambio de formato
      printf(" %d | ",dia); //Unión viernes-sábado
    } else {
      printf(" %d  ",dia); //Resto de días
    }
  } else {//Día de dos dígito
    if (cuentaDias == 12 || cuentaDias == 19 || cuentaDias == 26 || cuentaDias == 33) { //Cuando es jueves = cambio de formato
      printf("%d | ",dia); //Unión viernes-sábado
    } else {
      printf("%d  ",dia); //Resto de días
    }
  }
}
/********************
IMPRIME EL CALENDARIO
*********************/
void impCalendario(int mes, int anio) {
  int diasMes = numeroDiasMes(mes,anio);
  int primeroMes = diaSemanaMes(mes,anio);
  int ultimoMes = diaSemanaUltimoDeMes(mes,anio);
  cuentaDias = 1;
  for (int puntos = 1 ; puntos <= primeroMes ; puntos++) {
    impPuntos(mes,anio);
    cuentaDias = cuentaDias + 1;
  }
  for (int dia = 1 ; dia <= diasMes ; dia++) {
    impFormatoDia(dia);
    if (cuentaDias%7 == 0) {
      printf("\n");
    }
    cuentaDias = cuentaDias + 1;
  }
  if (ultimoMes != 0) {
    for (int puntos = 1 ; puntos <= 7-ultimoMes ; puntos++) {
      impPuntos(mes,anio);
      cuentaDias = cuentaDias + 1;
    }
  }
}
/*****************
PROGRAMA PRINCIPAL
******************/
int main() {
  printf("%cMes (1..12)%c",168,63);
  scanf("%d",&mes);
  printf("%cA%co (1601..3000)%c",168,164,63);
  scanf("%d",&anio);
  if ((mes >= 1 && mes <= 12) && (anio >= 1601 && anio <= 3000)) {
    impCabeceraCalendario(mes,anio);
    impCalendario(mes,anio);
  }
}
