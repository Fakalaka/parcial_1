#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "entidad1.h"
#include "utn.h"
#include "entidad2.h"

static int proximoId(void);
static int buscarLibre(Cliente* array,int limite);
static int cantidadPublicaciones(int id,Publicacion* arrayC,int limiteC);
static float promedioAlgo(Cliente* array,int limite);

int cliente_init(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            array[i].isEmpty=1;
        }
    }
    return retorno;
}

int cliente_altaForzada(Cliente* array,int limite,char* nombre,char* apellido,int cuit)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            retorno=0;
            strcpy(array[i].nombre,nombre);
            strcpy(array[i].apellido,apellido);
            array[i].cuit=cuit;
            array[i].id=proximoId();
            array[i].isEmpty=0;
        }
            else retorno=-3;
    }
        else{
            retorno=-2;
        }
    return retorno;
}

int cliente_alta(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    int cuit;
    char nombre[50];
    char apellido[50];
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            if(!getValidString("\nNombre: ","\nEso no es un nombre\n","\n50 caracteres maximo\n",nombre,50,2)){
                if(!getValidString("\nApellido: ","\nEso no es un apellido\n","\n50 caracteres maximo\n",apellido,50,2)){
                    if(!getValidInt("\nCUIT: ","\nIngresar solo los digitos\n",&cuit,0,99999999,2)){
                        retorno=0;
                        strcpy(array[i].nombre,nombre);
                        strcpy(array[i].apellido,apellido);
                        array[i].cuit=cuit;
                        array[i].id=proximoId();
                        array[i].isEmpty=0;
                        printf("\nID: %d\n", array[i].id);
                    }
                }
            }
            else retorno=-3;
        }
        else{
            retorno=-2;
        }
    }
    return retorno;
}

int cliente_baja(Cliente* array,int limite, int id)
{
    int retorno=-1;
    int indice=cliente_buscarId(array,limite,id);
    if(indice>=0){
        array[indice].isEmpty=1;
        retorno=0;
    }
    return retorno;
}

int cliente_modificacion(Cliente* array,int limite,int id)
{
    int retorno=-1;
    char nombre[50];
    char apellido[50];
    int cuit;
    int indice=cliente_buscarId(array,limite,id);
    if(indice>=0){
        retorno=-2;
        if(!getValidString("\nNombre: ","\nEso no es un nombre\n","\n50 caracteres maximo\n",nombre,50,2)){
            if(!getValidString("\nApellido: ","\nEso no es un apellido\n","\n50 caracteres maximo\n",apellido,50,2)){
                if(!getValidInt("\nCUIT: ","\nIngresar solo los digitos\n",&cuit,0,99999999,2)){
                    retorno=0;
                    strcpy(array[indice].nombre,nombre);
                    strcpy(array[indice].apellido,apellido);
                    array[indice].cuit=cuit;
                }
            }
        }
    }
    return retorno;
}

int cliente_ordenar(Cliente* array,int limite,int orden)
{
    int retorno=-1;
    int i;
    int flagSwap;
    Cliente auxiliarEstructura;
    if(limite>0&&array!=NULL){
        do{
            flagSwap=0;
            for(i=0;i<limite-1;i++){
                if(!array[i].isEmpty && !array[i+1].isEmpty){
                    if((strcmp(array[i].nombre,array[i+1].nombre)>0 && orden) || (strcmp(array[i].nombre,array[i+1].nombre)<0 && orden)){
                        auxiliarEstructura=array[i];
                        array[i]=array[i+1];
                        array[i+1]=auxiliarEstructura;
                        flagSwap=1;
                    }
                }
           }
        }while(flagSwap);
    }
    return retorno;
}

int buscarLibre(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        for(i=0;i<limite;i++){
            if(array[i].isEmpty){
            retorno=i;
            break;
            }
        }
    }
    return retorno;
}

int proximoId(void)
{
    static int proximoId=-1;
    proximoId++;
    return proximoId;
}

int cliente_mostrar(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int retorno=-1;
    int i;
    int avisos;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty){
                avisos=cliente_contarAvisos(arrayP,limiteP,array[i].id);
                printf("ID: %d - Nombre: %s - Apellido: %.s - CUIT: %d - Avisos activos: %d\n",array[i].id,array[i].nombre,array[i].apellido,array[i].cuit,avisos);
            }
        }
    }
    return retorno;
}

int cliente_buscarId(Cliente* array,int limite,int id)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=-2;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty && array[i].id==id){
                retorno=i;
                break;
            }
        }
    }
    return retorno;
}

int cantidadPublicaciones(int id,Publicacion* arrayC,int limiteC)
{
    int i;
    int contador=0;
    if(limiteC > 0 && arrayC != NULL)
    {
        for(i=0;i<limiteC;i++)
        {
            if(!arrayC[i].isEmpty && arrayC[i].idCliente==id)
                contador++;
        }
    }
    return contador;
}

int cliente_maxPublicaciones(Cliente* array,int limite,Publicacion* arrayC,int limiteC)
{
    int retorno = -1;
    int i;
    int aux;
    int max=0;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty){
                aux=cantidadPublicaciones(array[i].id,arrayC,limiteC);
                if(max==0 || max<aux) max=aux;
            }
        }
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty && cantidadPublicaciones(array[i].id,arrayC,limiteC)==max)
            printf("\nMayor cantidad de contrataciones: %s",array[i].nombre);
        }
    }
    return retorno;
}

float promedioAlgo(Cliente* array,int limite)
{
    int i;
    float suma=0;
    int cantidad=0;
    if(limite > 0 && array != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty){
                suma+=array[i].calificacion;
                cantidad++;
            }
        }
    }
    return suma/cantidad;
}

int pantalla_mostrarPorPrecio(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    float promedio = promedioAlgo(array,limite);
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].calificacion>promedio)
                printf("\n");
                //printf("%d - %s - %d\n",array[i].idPantalla, array[i].nombre, array[i].isEmpty);
        }
    }
    return retorno;
}

int cliente_mostrarPorId(Cliente* array,int limite,int id)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty && array[i].id==id){
                printf("Nombre: %s - Apellido: %.s - CUIT: %d\n",array[i].nombre,array[i].apellido,array[i].cuit);
                retorno=0;
            }
        }
    }
    return retorno;
}

int cliente_contarAvisos(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && !array[i].isPaused)
            retorno++;
    }
    return retorno;
}

int cliente_contarAvisosActivos(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && !array[i].isPaused)
            retorno++;
    }
    return retorno;
}

int cliente_contarAvisosPausados(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && array[i].isPaused)
            retorno++;
    }
    return retorno;
}

int cliente_maximoAvisos(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisos(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

int cliente_maximoAvisosActivos(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisosActivos(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

int cliente_maximoAvisosPausados(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisosPausados(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

int cliente_informar(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=cliente_maximoAvisosActivos(array,limite,arrayP,limiteP);
    printf("\n*Cliente(s) con mas avisos activos*\n");
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisos(arrayP,limiteP,array[i].id)==max) && !max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    printf("\n*Cliente(s) con mas avisos pausados*\n");
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisosPausados(arrayP,limiteP,array[i].id)==max) && !max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    printf("\n*Cliente(s) con mas avisos*\n");
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisos(arrayP,limiteP,array[i].id)==max) && !max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    return 0;
}
