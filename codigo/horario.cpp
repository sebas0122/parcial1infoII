#include "horario.h"

int potencia(int a, int b){
    int i=2;
    int pot=a;
    if (b==0){
        return 1;
    }
    while (i<=b){
        pot*=a;
        i++;
    }
    return pot;
}

bool solonumeros(char a[]){
    for (int i=0;a[i]!='\0';i++){
        if (a[i]<=47 || a[i]>=58){
            return false;
        }
    }
    return true;
}

int longitud(char a[]){
    int i = 0;
    int con;
    for (i=0;a[i] != '\0';i++){
        con++;
    }
    return i;
}

int conversorcharint(char num[]){
    int lon=longitud(num);
    int mult=lon-1;
    int mult2=0;
    int numero=0;
    int numint=0;
    for (int i=0; i<lon;i++){
        numero=static_cast<int>(num[i]) - 48;
        mult2=potencia(10,mult);
        numint+=numero*mult2;
        mult--;
    }
    return numint;
}

bool semana(char a[]){
    char sem[]="LMWJVSD";
    for (int i=0;sem[i]!='\0';i++){
        if (sem[i]==a[0]){
            return true;
        }
    }
    return false;
}

void acomodador(){
    ofstream fout;
    try{
        fout.open("informacion.txt",ios::app);
        if(!fout.is_open()){
            throw '2';
        }
    }
    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='2'){
            cout<<"Error al abrir el archivo para lectura.\n";
        }
    }
    char codigoc[10]="a";
    char creditos[3]="a";
    char hora1[3]="a";
    char hora2[3]="a";
    char dia[2]="T";
    char cambiodelinea[2]="\n";
    int menu=0;
    int menu2=0;
    while (menu!=2){
        while (solonumeros(codigoc)==false){
            cout<<"ingrese el codigo del curso: ";
            cin>>codigoc;
        }
        while (solonumeros(creditos)==false){
            cout<<"ingrese la cantidad de creditos de esa materia: ";
            cin>>creditos;
        }
        int longitud1=longitud(codigoc);
        fout.write(codigoc,longitud1);
        fout.write(cambiodelinea,1);
        longitud1=longitud(creditos);
        fout.write(creditos,longitud1);
        fout.write(cambiodelinea,1);
        while (menu2!=2){
            while (semana(dia)==false){
                cout<<"ingrese el dia de la semana en la que ve la materia(ponerlo con su inicial mayuscula. Si es miercoles poner 'W'): ";
                cin>>dia;
            }
            fout.write(dia,1);
            while (solonumeros(hora1)==false){
                cout<<"ingrese la primera hora de esa materia que tiene en ese dia que registró: ";
                cin>>hora1;
            }
            longitud1=longitud(hora1);
            if (longitud1==1){
                hora1[1]=hora1[0];
                hora1[0]='0';
            }
            fout.write(hora1,2);
            while (solonumeros(hora2)==false){
                cout<<"ingrese la ultima hora de esa materia que tiene en ese dia que registró: ";
                cin>>hora2;
                int hora1int=conversorcharint(hora1);
                int hora2int=conversorcharint(hora2);
                if (hora1int>hora2int){
                    cout<<"no tiene sentido que la ultima hora sea menor que la primera hora: ";
                    hora2[0]='a';
                }
            }
            longitud1=longitud(hora2);
            if (longitud1==1){
                hora2[1]=hora2[0];
                hora2[0]='0';
            }
            fout.write(hora2,longitud1);
            cout<<"si esta materia la ve otro dia de la semana marque un numero diferente de 2: ";
            cin>>menu2;
            dia[0]='T';
            hora1[0]='a';
            hora2[0]='a';
        }
        fout.write(cambiodelinea,1);
        codigoc[0]='a';
        creditos[0]='a';
        menu2=0;
        cout<<"si desea agregar otra materia marque un numero diferente de 2: ";
        cin>>menu;
    }
    fout.close();
}
