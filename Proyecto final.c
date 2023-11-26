/*Sistema bancario*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char nombre[30];
    char ap[30];
    char am[15];
    char telefono[15];
    char direccion[150];
    char usuario[20];
    char contra[20];
    int no_cuenta;
    long int saldo;
}datos;
typedef struct
{
    datos d;
}usuario;

void registro(usuario u[100],int *c,int *cuenta,int cuentas[100]);
void consulta(usuario u[100],int c,int);
void transacciones(usuario u[100],int c,int);
void bajas(usuario u[100],int *c,int);
void modificacion(usuario u[100],int c,int);
void imprime(usuario u[100],int,int);
int buscar(usuario u[100],int c);
void dep_transfer(usuario u[100],int c,int);
double calculadora(double inversion,double tasa,int meses);
void entrada(usuario u[100],int c);
int busqueda_binaria(int cuentas[100],int c);
void impresion_bin(usuario u[100],int f);

int main()
{
    //system("clear");
    usuario u[100];
    int c=0,opc2;
    int cuenta = 800;
    int cuentas[100];
    int f;
    
    do
    {
        puts("SISTEMA BANCARIO");
        puts("Selecciona el numero de la opcion que desees realizar");
        printf("1.Crear cuenta bancaria\n2.Ya eres usuario?Identificate..\n3.Busqueda Binaria\n4.Salir\n");
        scanf("%d",&opc2);
        getchar();
        
        switch(opc2)
        {
            case 1://REGISTRO
                registro(u,&c,&cuenta,cuentas);
                system("clear");
                break;
            case 2:
                if(c==0)
                    {
                        system("clear");
                        puts("ERROR!..No day registros disponibles!!");
                    }
                else
                    entrada(u,c);
                break;
            case 3:
                 if(c==0)
                    {
                        system("clear");
                        puts("ERROR!..No day registros disponibles!!");
                    }
                else
                    f = busqueda_binaria(cuentas,c);
                    if( f = -1)
                        printf("No se encontro el numero buscado");
                    else
                        impresion_bin(u,f);
                break;
            /*default:
                printf("No selecciono alguna opcion correcta");
                break;*/
        }
    }while(opc2!=4);
    return 0;
}
void registro(usuario u[100],int *c,int *cuenta,int cuentas[100])
{
    printf("Nombre: ");
    gets(u[*c].d.nombre);
    printf("Apellido paterno: ");
    gets(u[*c].d.ap);
    printf("Apellido materno: ");
    gets(u[*c].d.am);
    printf("Telefono: ");
    gets(u[*c].d.telefono);
    //getchar();
    printf("Direccion:");
    gets(u[*c].d.direccion);
    printf("Usuario:");
    gets(u[*c].d.usuario);
    printf("Contraseña:");
    gets(u[*c].d.contra);
    
    cuentas[*c] = *cuenta; 
    
    u[*c].d.no_cuenta = *cuenta;
    (*cuenta)++;
    (*c)++;
    system("clear");
    
    //entrada(u,c);
}
void entrada(usuario u[100],int c)
{
    system("clear");
    int opc;
    char auxusuario[20],auxcontra[20];
    int posno,bandera=0;
    int meses;
    double tasa=(.08/12),cf,inversion;
    a:
    printf("Usuario:");
    gets(auxusuario);
    printf("Contraseña:");
    gets(auxcontra);
    //printf("%s\n",auxusuario);
    //printf("%s\n",u[0].d.usuario);
    system("clear");
    for(int x=0;x<c;x++)
    {
        if(strcmp(auxusuario,u[x].d.usuario)==0)
        {    
            bandera++;
            if(strcmp(auxcontra,u[x].d.contra)==0)
            {
                bandera++;
                posno=x;
            }
            else
            {
                //system("clear");
                puts("Error, usuario o contraseña no encontrada1");
                goto a;
                
            }
        }
    }
    
    if(bandera==2)
        
                    do
                        {
                            puts("Bienvenido");
                            printf("1.Consulta Saldo\n2.Transacciones\n3.Inversiones\n4.Bajas\n5.Modificaciones\n6.Busqueda Binaria\n7.Salir\n");
                            printf("Elije una opcion:");
                            scanf("%d",&opc);
                            getchar();
                            switch(opc)
                            {
                                case 1://CONSULTAS
                                    consulta(u,c,posno);
                                    break;
                                case 2://TRANSACCIONES
                                    transacciones(u,c,posno);
                                    break;
                                case 3://INVERSIONES
                                    
                                    puts("Actualmente la tasa de interes se encuentra a 8 por ciento anual");
                                    puts("Cuanto te gustaria invertir:");
                                    scanf("%lf",&inversion);
                                    puts("A cuantos meses te gustaria invertir");
                                    scanf("%d",&meses);
                                    cf=calculadora(inversion,tasa,meses);
                                    printf("Tu capital final seria de: %.2lf\n",cf);
                                    break;
                                case 4://BAJAS
                                    bajas(u,&c,posno);
                                    break;
                                case 5:
                                    modificacion(u,c,posno);
                                    break;
                                case 6:
                                    //busqueda_binaria(cuentas);
                            }   
                        }while(opc!=7);
}
void consulta(usuario u[100],int c,int posno)
{
    system("clear");
    int opc;
    puts("Menu de opciones");
    printf("1.Consulta general\n2.Consulta particular\n");
    scanf("%d",&opc);
    switch(opc)
    {
        case 1:
            system("clear");
            printf("No. cuenta\tSaldo\n");
            for(int y=0;y<c;y++)
                imprime(u,y,opc);
            break;
        case 2:
            system("clear");
            imprime(u,posno,opc);
            break;
    }
}
void imprime(usuario u[100],int c,int opc)
{
    //system("clear");
    //puts("TUS DATOS SON");
    switch(opc)
    {
        case 1:
            printf("%d\t\t %ld\n",u[c].d.no_cuenta,u[c].d.saldo);
            break;
        case 2:
            printf("Numero de cuenta: %d\n",u[c].d.no_cuenta);
            printf("Nombre: %s\n",u[c].d.nombre);
            printf("Direccion: %s\n",u[c].d.direccion);
            printf("Telefono: %s\n",u[c].d.telefono);
            printf("Saldo: %ld\n",u[c].d.saldo);
            break;
    }
}
int buscar(usuario u[100],int c)
{
    int opc,pos=-1;
    int auxno;
    char auxcontra[20];
    
    puts("Elije que dato usaras para acceder a los datos de tu cuenta");
    puts("1.Numero de cuenta");
    puts("2.Contraseña");
    scanf("%d",&opc);
    switch(opc)
    {
        case 1:
            printf("Por favor proporcione su numero de cuenta:");
            scanf("%d",&auxno);
            for(int x=0;x<c;x++)
                if(auxno==u[x].d.no_cuenta)
                    {
                        pos=x;
                        break;
                    }
            if(pos==-1)
            {
                system("clear");
                puts("El numero de cuenta no existe");
                //buscar(u,c);
            }
            break;
        case 2:
            printf("Por favor proporcione su contraseña:");
            scanf("%s",auxcontra);
            for(int x=0;x<c;x++)
                if(strcmp(auxcontra,u[x].d.contra)==0)
                    {
                        pos=x;
                        break;
                    }
            if(pos==-1)
            {
                system("clear");
                puts("Contraseña no existe");
                //buscar(u,c);
            }
            break;
    }
    return pos;
        
}
void transacciones(usuario u[100],int c,int posno)
{
    int opc;
    do
    {
        puts("Que deseas realizar.");
        puts("1.Depositos");
        puts("2.Retiro");
        puts("3.Salir");
        scanf("%d",&opc);
        switch(opc)
        {
            case 1:
                dep_transfer(u,posno,opc);
                
                break;
            case 2:
                dep_transfer(u,posno,opc);
                break;
        }
    }while(opc!=3);
    system("clear");
}
void dep_transfer(usuario u[100],int c,int opc)
{
    char salir;
    int pos=-1;
    int auxdep,auxtransfer;
    /*do
    {
        pos=buscar(u,c);
    }while(pos<0);*/
    
    if(opc == 1)
    {
        printf("Cuanto deseas depositar:");
        scanf("%d",&auxdep);
        (u[c].d.saldo)+=auxdep;
    }
    else if(opc == 2)
    {
        if(u[c].d.saldo == 0)
            printf("No cuentas con saldo suficiente");
        else
            printf("Cuanto deseas retirar:");
            scanf("%d",&auxtransfer);
            if(u[c].d.saldo-auxtransfer<0)
            {
                puts("No cuentas con saldo suficiente para realizar toda la transaccion");
                printf("Solo puedes transferir %ld\n",u[c].d.saldo);
            }
            else
                (u[c].d.saldo)-=auxtransfer;
    }
}
double calculadora(double inversion,double tasa,int meses)//Matematicas Discretas recursion
{
    if(meses == 0)
        return inversion;
    else
        return calculadora(inversion*(1+tasa),tasa,meses - 1);
}
void bajas(usuario u[100],int *c,int posno)
{
    int pos=-1;
    char eliminacion;
    printf("Quieres eliminar tu numero de cuenta[S/N]");
    eliminacion=toupper(getchar());
    if(eliminacion=='S')
    {
        for(int x=posno; x<*c;x++)
            u[x]=u[x + 1];
        (*c)--;    
    }
}
void modificacion(usuario u[100],int c,int posno)
{
    int opc;
    do
    {
        puts("Opciones a modificar");
        puts("1.Nombre");
        puts("2.Telefono");
        puts("3.Direccion");
        puts("4.Salir");
        scanf("%d",&opc);
        getchar();
        switch(opc)
        {
            case 1:
                puts("Nombre");
                scanf("%s",u[posno].d.nombre);
                puts("Apellido paterno");
                scanf("%s",u[posno].d.ap);
                puts("Apellido materno");
                scanf("%s",u[posno].d.am);
                break;
            case 2:
                puts("Telefono");
                scanf("%s",u[posno].d.telefono);
                getchar();
                break;
            case 3:
                puts("Direccion");
                gets(u[posno].d.direccion);
                break;
            
        }
    }while(opc!=4);
}

int busqueda_binaria(int cuentas[100],int c)
{
    int x;
    int mitad,valor_medio;
    int longitud = c;
    int busqueda;
    printf("longitud: %d\n",longitud);
    int izq = 0, der = longitud - 1;
    
    for(int y=0;y<c;y++)
        printf("%d\n",cuentas[y]);
    printf("Que numero de cuentas deseas buscar:");
    scanf("%d",&busqueda);
    getchar();
    do
    {
        mitad = (izq + der) / 2;
        printf("%d\n",mitad);
        valor_medio = cuentas[mitad];
        
        if(busqueda == valor_medio)
        {
            return mitad;
        }
        else if(busqueda < valor_medio)
        {
            der = mitad - 1;
        }
        else
            izq = mitad + 1;
    }while(izq <= der);
    return -1;
}
void impresion_bin(usuario u[100],int f)
{
    printf("Numero de cuenta: %d\n",u[f].d.no_cuenta);
    printf("Nombre: %s\n",u[f].d.nombre);
    printf("Direccion: %s\n",u[f].d.direccion);
    printf("Telefono: %s\n",u[f].d.telefono);
    printf("Saldo: %ld\n",u[f].d.saldo);
    printf("Usuario: %s\n",u[f].d.usuario);
    printf("Contraseña: %s\n",u[f].d.contra);
}

