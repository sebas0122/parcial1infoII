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
void matrizhoras(char a[],int d[7][24]);
bool asignacion(int h,char codi[],char n[],int d[7][24]);
void horario();
bool comparador(char a[], char b[]);
bool verificadorcodigo(char a[]);
void getcredito(char a[],char b[]);
void getname(char a[],char b[]);
void inicializador(char a[]);
bool asignacionusuario(int h,char codi[],char n[],int d[7][17]);

#endif // HORARIO_H
