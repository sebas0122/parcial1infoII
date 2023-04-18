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
    int longitud1;
    while (menu!=2){
        //fout.write(cambiodelinea,1);
        while (solonumeros(codigoc)==false){
            cout<<"ingrese el codigo del curso: ";
            cin>>codigoc;
        }
        while (solonumeros(creditos)==false){
            cout<<"ingrese la cantidad de creditos de esa materia: ";
            cin>>creditos;
        }
        longitud1=longitud(codigoc);
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

void matrizhoras(char a[],bool d[7][24]){
    int i=0;
    int s=0;
    int limite=0;
    int limite2=0;
    int menor=0;
    int mayor=0;
    int clave=0;
    char dia='a';
    char num[3]={};
    while (a[i]!='\0'){
        if (a[i]<=47 || a[i]>=58){
            dia=a[i];
            limite=i+4;
            while (i!=limite){
                i++;
                num[s]=a[i];
                if (s==1 && clave==0){
                    menor=conversorcharint(num);
                    clave=1;
                    s=-1;
                }
                else if (s==1 && clave==1){
                    mayor=conversorcharint(num);
                }
                s++;
            }
            if (dia=='L'){
                limite2=0;
            }
            else if (dia=='M'){
                limite2=1;
            }
            else if (dia=='W'){
                limite2=2;
            }
            else if (dia=='J'){
                limite2=3;
            }
            else if (dia=='V'){
                limite2=4;
            }
            else if (dia=='S'){
                limite2=5;
            }
            else if (dia=='D'){
                limite2=6;
            }
            for (int t=0;t<7;t++){
                if (t==limite2){
                    for (int j=0;j<24;j++){
                        if (j>=menor && j<mayor){
                            if(d[t][j]==false){
                                d[t][j]=true;
                            }
                            else{
                                cout<<"Hay materias que tienen el mismo horario. Por lo tanto lo que matriculo no es valido.";
                                break;
                            }
                        }
                    }
                }
            }
        }
        i++;
        s=0;
        clave=0;
    }
}

bool asignacion(int h,char codi[],bool d[7][24]){
    char dia='a';
    for (int t=0;t<7;t++){
        for (int j=0;j<24;j++){
            if(h>0){
                if (d[t][j]==false){
                    d[t][j]=true;
                    for (int i=0;codi[i]!='\0';i++){
                        cout<<codi[i];
                    }
                    if (t==0){
                        dia='L';
                    }
                    else if (t==1){
                        dia='M';
                    }
                    else if (t==2){
                        dia='W';
                    }
                    else if (t==3){
                        dia='J';
                    }
                    else if (t==4){
                        dia='V';
                    }
                    else if (t==5){
                        dia='S';
                    }
                    else if (t==6){
                        dia='D';
                    }
                    cout<<" : "<<dia<<" "<<j+1<<endl;
                    h-=1;
                }
            }
        }
    }
    if (h==0){
        return true;
    }
    else{
        return false;
    }
}

int horadocente(char a[]){
    int i=0;
    int s=0;
    int limite=0;
    int menor=0;
    int mayor=0;
    int clave=0;
    int horas=0;
    char num[3]={};
    while (a[i]!='\0'){
        if (a[i]<=47 || a[i]>=58){
            limite=i+4;
            while (i!=limite){
                i++;
                num[s]=a[i];
                if (s==1 && clave==0){
                    menor=conversorcharint(num);
                    clave=1;
                    s=-1;
                }
                else if (s==1 && clave==1){
                    mayor=conversorcharint(num);
                }
                s++;
            }
            horas+=(mayor-menor);
            mayor=0;
            menor=0;
        }
        i++;
        s=0;
        clave=0;
    }
    return horas;
}

int horasobrantes(int n, int docente){
    int semanal=n*48;
    semanal=semanal/16;
    semanal=semanal-docente;
    if(semanal<0){
        return 0;
    }
    else{
        return semanal;
    }
}

void horario(){
    //acomodador();
    bool matriz[7][24];
    for (int i=0;i<7;i++){
        for (int j=0;j<24;j++){
            matriz[i][j]=false;
        }
    }
    ifstream fin;
    try{
        fin.open("informacion.txt");
        if(!fin.is_open()){
            throw '2';
        }
    }
    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='2'){
            cout<<"Error al abrir el archivo para lectura.\n";
        }
    }
    int con=0;
    int hprofe[100]={};
    char profe[100]={};
    int p=0;
    while (fin.getline(profe,100)){
        con++;
        if (con==3){
            matrizhoras(profe,matriz);
            con=0;
            hprofe[p]=horadocente(profe);
            p++;
        }
    }
    fin.clear();
    fin.seekg(0);
    char linea[100]={};
    char codigo[100]={};
    char creditos[100]={};
    int creditosint=0;
    int personales=0;
    con=0;
    p=0;
    while (fin.getline(linea,100)){
        con++;
        if (con==1){
            for(int i=0;linea[i]!='\0';i++){
                codigo[i]=linea[i];
            }
        }
        else if(con==2){
            for(int i=0;linea[i]!='\0';i++){
                creditos[i]=linea[i];
            }
            creditosint=conversorcharint(creditos);
            personales=horasobrantes(creditosint,hprofe[p]);
            asignacion(personales,codigo,matriz);
        }
        else if(con==3){
            con=0;
        }
    }
    fin.close();
    cout<<'\n';
    for (int i=0;i<24;i++){
        cout<<" "<<i<<" ";
    }
    cout<<'\n';
    char diasemana[]="LMWJVSD";
    for (int i=0;i<7;i++){
        cout<<'\n'<<diasemana[i];
        for (int j=0;j<24;j++){
            if (matriz[i][j]==false){
                cout<<"  -  ";
            }
            else{
                cout<<"  +  ";
            }
        }
    }
    cout<<'\n';
    cout<<"los espacios con + son los ocupados, los - son los libres.";
}
