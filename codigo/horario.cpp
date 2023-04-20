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

void inicializador(char a[]){
    int lon=longitud(a);
    for (int i = 0; i < lon; i++) {
        a[i] = '\0';
    }
}

bool comparador(char a[], char b[]){
    int lon1=longitud(a);
    int lon2=longitud(b);
    if(lon1==lon2){
        for (int i=0;i<lon1;i++){
            if (a[i]!=b[i]){
                return false;
            }
        }
    }
    else if(lon1!=lon2){
        return false;
    }
    return true;
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

bool verificadorcodigo(char a[]){
    ifstream fin;
    try{
        fin.open("cursos.txt");
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
    int con=2;
    char l[100]={};
    bool verdad=false;
    while (fin.getline(l,100)){
        con++;
        if (con==3){
            verdad=comparador(l,a);
            if (verdad==true){
                fin.close();
                return true;
            }
            con=0;
            l[100]={};
        }
    }
    fin.close();
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
    char hora1[3]="a";
    char hora2[3]="a";
    char dia[2]="T";
    char cambiodelinea[2]="\n";
    int menu=0;
    int menu2=0;
    int longitud1;
    while (menu!=2){
        while (solonumeros(codigoc)==false || verificadorcodigo(codigoc)==false){
            verificadorcodigo(codigoc);
            cout<<"ingrese el codigo del curso: ";
            cin>>codigoc;
        }
        longitud1=longitud(codigoc);
        fout.write(codigoc,longitud1);
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
        menu2=0;
        cout<<"si desea agregar otra materia marque un numero diferente de 2: ";
        cin>>menu;
    }
    fout.close();
}

void matrizhoras(char a[],int d[7][17]){
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
                    for (int j=0;j<17;j++){
                        if (j>=menor-6 && j<mayor-6){
                            if(d[t][j]==0){
                                d[t][j]=1;
                            }
                            else{
                                cout<<"Hay materias que tienen el mismo horario. Por lo tanto lo que matriculo no es valido. Marque 1 para volver a iniciar el proceso";
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

void getname(char a[],char b[]){
    ifstream fin;
    try{
        fin.open("cursos.txt");
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
    int con=2;
    char l[100]={};
    while (fin.getline(l,100)){
        con++;
        if (con==3){
            if(comparador(l,a)==true){
                fin.getline(l,100);
                int lon=longitud(l);
                for (int s=0;s<lon;s++){
                    b[s]=l[s];
                }
                break;
            }
            con=0;
        }
    }
    fin.close();
}

bool asignacion(int h,char codi[],char n[],int d[7][17]){
    char dia='a';
    for (int t=0;t<7;t++){
        for (int j=0;j<17;j++){
            if(h>0){
                if (d[t][j]==0){
                    d[t][j]=2;
                    getname(codi,n);
                    for (int i=0;n[i]!='\0';i++){
                        cout<<n[i];
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
                    cout<<" : "<<dia<<" "<<j+6<<endl;
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

bool asignacionusuario(int h,char codi[],char n[],int d[7][17]){
    cout<<"\n\n";
    while (h>0){
        getname(codi,n);
        cout<<"curso: ";
        for (int i=0;n[i]!='\0';i++){
            cout<<n[i];
        }
        cout<<"\n\nHoras por asignar: "<<h;
        int limite2=0;
        int j=0;
        char dia='a';
        while (dia!='L' && dia!='M' && dia!='W' && dia!='J' && dia!='V' && dia!='S' && dia!='D'){
            cout<<"\n\ningrese el dia de la semana en el que desea tener la hora de la materia(ponerlo con su inicial mayuscula. Si es miercoles poner 'W'): ";
            cin>>dia;
        }
        while(j<6 || j>24){
            cout<<"ingrese la hora: ";
            cin>>j;
        }
        if(h>0){
            for (int i=0;n[i]!='\0';i++){
                cout<<n[i];
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
            cout<<" : "<<dia<<" "<<j<<endl;
        }
        if (d[limite2][j-6]==0){
            d[limite2][j-6]=2;
            h-=1;
        }
        else{
            cout<<"\n\nEsa hora no se pudo asginar. Hora ocupada.";
        }
        cout<<'\n';
        cout<<"   ";
        for (int i=6;i<23;i++){
            if(i<10){
                cout<<i<<"  ";
            }
            else{
                cout<<i<<" ";
            }
        }
        cout<<'\n';
        char diasemana[]="LMWJVSD";
        for (int i=0;i<7;i++){
            cout<<'\n'<<diasemana[i]<<"  ";
            for (int j=0;j<17;j++){
                if (d[i][j]==0){
                    cout<<"-  ";
                }
                else if(d[i][j]==1){
                    cout<<"+  ";
                }
                else if (d[i][j]==2){
                    cout<<"*  ";
                }
            }
        }
        cout<<'\n';
        cout<<"los espacios con + son los ocupados por horas con profesor,los * son las horas asignadas para estudio independiente, los - son los libres.";
        cout<<"\n\n";
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

void getcredito(char a[],char b[]){
    ifstream fin;
    try{
        fin.open("cursos.txt");
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
    int con=2;
    char l[100]={};
    int i=0;
    while (fin.getline(l,100)){
        con++;
        if (con==3){
            if(comparador(l,a)==true){
                while(i<2){
                    fin.getline(l,100);
                    i++;
                }
                int lon=longitud(l);
                for (int s=0;s<lon;s++){
                    b[s]=l[s];
                }
                fin.close();
                break;
            }
            con=0;
        }
    }
    fin.close();
}

void horario(){
    acomodador();
    int matriz[7][17];
    for (int i=0;i<7;i++){
        for (int j=0;j<17;j++){
            matriz[i][j]=0;
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
    int hprofe[100]={};                  //Esta la utilizo todo el programa. No es necesario ponerla como memoria dinamica
    char *profe;
    profe=new char[100];
    int p=0;
    while (fin.getline(profe,100)){
        con++;
        if (con==2){
            matrizhoras(profe,matriz);
            con=0;
            hprofe[p]=horadocente(profe);
            p++;
        }
    }
    delete[] profe;
    fin.clear();
    fin.seekg(0);
    int matrizcopia[7][17];
    for (int i=0;i<7;i++){
        for (int j=0;j<17;j++){
            matrizcopia[i][j]=matriz[i][j];
        }
    }
    char *linea;
    linea=new char[100];
    for (int i = 0; i < 100; i++) {
        linea[i] = '\0';
    }
    char *codigo;
    codigo=new char[50];
    for (int i = 0; i < 50; i++) {
        codigo[i] = '\0';
    }
    char *name;
    name=new char[100];
    for (int i = 0; i < 100; i++) {
        name[i] = '\0';
    }
    char *creditos;
    creditos=new char[3];
    for (int i = 0; i < 3; i++) {
        creditos[i] = '\0';
    }
    int creditosint=0;
    int personales=0;
    con=0;
    p=0;
    bool poder=false;
    while (fin.getline(linea,100)){
        con++;
        if (con==1){
            for(int i=0;linea[i]!='\0';i++){
                codigo[i]=linea[i];
            }
            getcredito(codigo,creditos);
            creditosint=conversorcharint(creditos);
            personales=horasobrantes(creditosint,hprofe[p]);
            p++;
            poder=asignacion(personales,codigo,name,matriz);
            if (poder==false){
                cout<<"no se pudo asignar mas horas, Se recomienda cancelar materias";
                break;
            }
            inicializador(linea);
            inicializador(codigo);
            inicializador(name);
            inicializador(creditos);
        }
        else if(con==2){
            con=0;
        }
    }
    delete[] linea;
    delete[] codigo;
    delete[] name;
    delete[] creditos;
    cout<<'\n';
    cout<<"   ";
    for (int i=6;i<23;i++){
        if(i<10){
            cout<<i<<"  ";
        }
        else{
            cout<<i<<" ";
        }
    }
    cout<<'\n';
    char diasemana[]="LMWJVSD";
    for (int i=0;i<7;i++){
        cout<<'\n'<<diasemana[i]<<"  ";
        for (int j=0;j<17;j++){
            if (matriz[i][j]==0){
                cout<<"-  ";
            }
            else if(matriz[i][j]==1){
                cout<<"+  ";
            }
            else if (matriz[i][j]==2){
                cout<<"*  ";
            }
        }
    }
    cout<<'\n';
    cout<<"los espacios con + son los ocupados por horas con profesor,los * son las horas asignadas para estudio independiente, los - son los libres.";
    cout<<"\n\n";
    int desicion=0;
    while (desicion<1 || desicion>2){
        cout<<"Si le gusto su horario marque 1. Si no le gusto y desea asignar de forma manual marque 2: ";
        cin>>desicion;
    }
    if (desicion==2){
        cout<<'\n';
        cout<<"   ";
        for (int i=6;i<23;i++){
            if(i<10){
                cout<<i<<"  ";
            }
            else{
                cout<<i<<" ";
            }
        }
        cout<<'\n';
        char diasemana[]="LMWJVSD";
        for (int i=0;i<7;i++){
            cout<<'\n'<<diasemana[i]<<"  ";
            for (int j=0;j<17;j++){
                if (matrizcopia[i][j]==0){
                    cout<<"-  ";
                }
                else if(matrizcopia[i][j]==1){
                    cout<<"+  ";
                }
                else if (matrizcopia[i][j]==2){
                    cout<<"*  ";
                }
            }
        }
        cout<<'\n';
        cout<<"los espacios con + son los ocupados por horas con profesor,los * son las horas asignadas para estudio independiente, los - son los libres.";
        fin.clear();
        fin.seekg(0);
        char *linea;
        linea=new char[100];
        for (int i = 0; i < 100; i++) {
            linea[i] = '\0';
        }
        char *codigo;
        codigo=new char[50];
        for (int i = 0; i < 50; i++) {
            codigo[i] = '\0';
        }
        char *name;
        name=new char[100];
        for (int i = 0; i < 100; i++) {
            name[i] = '\0';
        }
        char *creditos;
        creditos=new char[3];
        for (int i = 0; i < 3; i++) {
            creditos[i] = '\0';
        }
        int creditosint=0;
        int personales=0;
        con=0;
        p=0;
        bool poder2=false;
        while (fin.getline(linea,100)){
            con++;
            if (con==1){
                for(int i=0;linea[i]!='\0';i++){
                    codigo[i]=linea[i];
                }
                getcredito(codigo,creditos);
                creditosint=conversorcharint(creditos);
                personales=horasobrantes(creditosint,hprofe[p]);
                p++;
                poder2=asignacionusuario(personales,codigo,name,matrizcopia);
                if (poder2==false){
                    cout<<"no se pudo asignar mas horas, Se recomienda cancelar materias";
                    break;
                }
                inicializador(linea);
                inicializador(codigo);
                inicializador(name);
                inicializador(creditos);
            }
            else if(con==2){
                con=0;
            }
        }
        delete[] linea;
        delete[] codigo;
        delete[] name;
        delete[] creditos;
    }
    fin.close();
    ofstream fout;
    try{
        fout.open("informacion.txt",std::ios::trunc);
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
    fout.close();
}
