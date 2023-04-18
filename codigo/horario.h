#ifndef HORARIO_H
#define HORARIO_H
#include <iostream>
#include <fstream>

using namespace std;

void acomodador();
int potencia(int a, int b);
bool solonumeros(char a[]);
int conversorcharint(char num[]);
int longitud(char a[]);
bool semana(char a);
int horadocente(char a[]);
int horasobrantes(int n, int docente);
void matrizhoras(char a[],bool d[7][24]);
bool asignacion(int h,char codi[],bool d[7][24]);
void horario();

#endif // HORARIO_H
