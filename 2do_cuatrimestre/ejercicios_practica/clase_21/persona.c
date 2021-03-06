#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "persona.h"
#define TAM_BUFFER 32

//Pido al usuario
int pedirCadenaLetras(char* mensaje, char* cadena)
{
    int flag=0;
    char auxiliar[50];

    if(cadena!=NULL)
    {


        cargarCadena(mensaje, auxiliar);

        while(esLetra(auxiliar)!=1)
        {
            printf("Error. No es valido.\n");
            cargarCadena(mensaje, auxiliar);
        }

        strcpy(cadena, auxiliar);

        if(stricmp(cadena, auxiliar)==0)
        {
            flag=1;
        }

    }

    return flag;

}

int pedirCadenaInt(char* mensaje, int minimo, int maximo)
{
    int flag=0;//No esta cargado
    char auxiliar[50]={};
    int numeroAuxiliar;

    do
    {
        cargarCadena(mensaje, auxiliar);

        while(esNumero(auxiliar)!=1)
        {
            printf("Error. No es un numero valido.\n");
            cargarCadena(mensaje, auxiliar);
        }

        numeroAuxiliar=atoi(auxiliar);//*Tomo el valor

        if(numeroAuxiliar>=minimo && numeroAuxiliar<=maximo)
        {
            flag=1;//Cumple con las condiciones. Sale de la iteracion.
        }
        else
        {
            printf("Fuera de rango.\n");
        }


    }while(flag==0);


    return numeroAuxiliar;

}

int cargarCadena(char* mensaje, char* cadena)
{
    int flag=0;//No est� cargada

    if(cadena!=NULL)
    {

        printf("%s: ", mensaje);
        fflush(stdin);

        //Para no escribir de m�s en memoria uso fgets
        //(limita lo que se puede ingresar)
        fgets(cadena,sizeof(char)*TAM_BUFFER,stdin);

        //Agregar '\0' al final cuando cadena < al buffer
        //para que pueda validar (porque fgets escribe '\n' al final)
        if(strlen(cadena)<TAM_BUFFER-1)
        {
            *(cadena+(strlen(cadena)-1))='\0';
        }


        if(strlen(cadena)>0)
        {
            flag=1;
        }
    }

    return flag;
}

//Comprobaciones
int esLetra(char auxiliar[])
{
    int i;
    int flag=1;//1 es char

    for(i=0;i<strlen(auxiliar);i++)
    {
        if((auxiliar[i]!=' ') && (auxiliar[i]<'A' || auxiliar[i]>'Z') && (auxiliar[i]<'a' || auxiliar[i]>'z')) //Si hay espacio tambien es valido como letra
        {
            flag=0;//0 no es char
            break;
        }
    }

    return flag;
}

int esNumero (char auxiliar[])
{
    int i;
    int flag=1;//1 es entero

    for(i=0; i<strlen(auxiliar); i++)
    {
        if(auxiliar[i]<'0' || auxiliar[i]>'9')
        {
            flag=0;
            break;
        }
    }

    return flag;
}

//Setters
void persona_setName(ePersona* persona, char* nombre)
{
    if(persona!=NULL)
    {
        strcpy(persona->nombre, nombre);
    }

}

void persona_setAge(ePersona* persona, int edad)
{
    if(persona!=NULL)
    {
        persona->edad=edad;
    }
}

//Getters
int persona_getAge(ePersona* persona)
{
    int retorno=-1;

    if(persona!=NULL)
    {
        retorno= persona->edad;
    }

    return retorno;

}

char* persona_getName(ePersona* persona)
{
    return persona->nombre;
}

//Mostrar
void mostrarPersona(ePersona* persona)
{
    if(persona!=NULL)
    {
        printf("-----------------------------------\n");
        printf("Nombre:%s\nEdad:%d\n", persona_getName(persona), persona_getAge(persona));

    }
}

//Constructores
eListaPersonas* persona_inicializarArrayList(void)
{
    eListaPersonas* listaPersonas;

    //Asigno memoria para 1 lista
    listaPersonas= (eListaPersonas*) malloc(sizeof(eListaPersonas));

    listaPersonas->index=0;//Indice de personas en la lista
    listaPersonas->totalLista=2; //Tama�o total de personas en la lista
    //Creo la lista asignando memoria din�mica;
    listaPersonas->lista= persona_crearLista(listaPersonas->totalLista);

    return listaPersonas;
}

ePersona** persona_crearLista(int totalPersonas)
{
    ePersona** listaPersonas;

    //Array din�mico
    listaPersonas=(ePersona**)malloc( totalPersonas * sizeof(ePersona*));

    return listaPersonas;

}

ePersona* persona_crearPersona()
{
    ePersona* persona;

    persona=(ePersona*)malloc(sizeof(ePersona));

    return persona;
}

int persona_addPersona(eListaPersonas* listaPersonas, ePersona* persona)
{
    ePersona** auxLista;
    int flag=0;//No hay espacio

    //Compruebo que los punteros no vengan nulos
    if(listaPersonas!=NULL && persona!=NULL)
    {

        if(listaPersonas->lista[listaPersonas->index]!=NULL)
        {
            //Cargo la persona en la posici�n index de la lista
            *(listaPersonas->lista+listaPersonas->index)=persona; //Usar aritm�tica de punteros
            //Sumo 1 al indice (paso a la siguiente posici�n)
            listaPersonas->index++;

            //Compruebo que la lista no est� completa
            if(listaPersonas->index >= listaPersonas->totalLista)//Llegu� al final, lista completa
            {
                //Asigno m�s memoria a la lista
                listaPersonas->totalLista+=5;
                printf("\nRedefino array. Total personas:%d\n",listaPersonas->totalLista);
                //uso aux por si devuelve NULL
                auxLista=(ePersona**) realloc(listaPersonas->lista, listaPersonas->totalLista * sizeof(ePersona*));

                if(auxLista!=NULL)
                {
                    listaPersonas->lista=auxLista;
                    flag=1;//hay espacio
                }
                else
                {
                    printf("No hay memoria.");
                }

            }
        }
    }
    else
    {
        printf("Puntero nulo.");
    }

    return flag;

}


