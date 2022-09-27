#include <stdio.h>
#include <string.h>

int dia,mes,anio,cuentaDias;
/*************************************************************
FUNCIONES Y PROCEDIMIENTOS PARA CALCULAR LOS D�AS DE LOS MESES
*************************************************************/
/*Comprueba si un a�o es bisiesto*/
bool esBisiesto(int anio) {
  if (anio % 4 == 0 && (anio %100 != 0 || anio%400 == 0)) {
    return true;
  }
  return false;
}
/*Calcula el n�mero de d�as que tiene un mes*/
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
/*N�mero de d�as que tiene un a�o*/
int diasAnio(int anio) {
  if (esBisiesto(anio)) {
    return 366;
  }
  return 365;
}
/*D�as entre el 1 enero del a�o introducido y el 1 de enero de 1601*/
int numeroDiasHasta(int anio) {
  int n = 0;
  for (int i = 1  ; i <= anio-1601 ; i++) {
    n = n + diasAnio(1600+i);
  }
  return n;
}
/*N�mero de d�as desde el primer d�a del a�o introducido hasta el mes pasado por par�metro*/
int numeroDiasAnio(int mes, int anio) {
  int m = 0; //D�as Enero de a�o nuevo
  for (int i = 1 ; i < mes ; i++) {
    m = m + numeroDiasMes(i,anio);
  }
  return m;
}
/*D�a de la semana que cae el a�o nuevo*/
int diaSemanaAnioNuevo(int anio) {
  int diaSemana;
  int nDias = numeroDiasHasta(anio);
  diaSemana = nDias%7;
  return diaSemana;
}
/*D�a de la semana del d�a 1 de un mes y un a�o*/
int diaSemanaMes(int mes, int anio) {
  int s = diaSemanaAnioNuevo(anio);
  int d = numeroDiasAnio(mes,anio);
  int r = (s + d)%7;
  return r;
}
/*D�a de la semana del �ltimo d�a del mes*/
int diaSemanaUltimoDeMes(int mes, int anio) {
  int s = diaSemanaMes(mes,anio);
  int d = numeroDiasMes(mes,anio);
  int r = (s + d)%7;
  return r;
}
/**********************************
FORMATO DE IMPRESI�N DEL CALENDARIO
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
    printf(" . | "); //Uni�n viernes-s�bado
  } else {
    printf(" .  "); //Resto de d�as
  }
}
/*Imprime el formato correcto en funci�n de los d�gitos de los d�as y de los fines de semana*/
void impFormatoDia(int dia) {
  if (dia > 0 && dia <= 9) { //D�a de un d�gito
    if (cuentaDias == 5 || cuentaDias == 12 || cuentaDias == 19 || cuentaDias == 26 || cuentaDias == 33) { //Cuando es jueves = cambio de formato
      printf(" %d | ",dia); //Uni�n viernes-s�bado
    } else {
      printf(" %d  ",dia); //Resto de d�as
    }
  } else {//D�a de dos d�gito
    if (cuentaDias == 12 || cuentaDias == 19 || cuentaDias == 26 || cuentaDias == 33) { //Cuando es jueves = cambio de formato
      printf("%d | ",dia); //Uni�n viernes-s�bado
    } else {
      printf("%d  ",dia); //Resto de d�as
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
