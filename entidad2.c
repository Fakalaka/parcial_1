#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "entidad1.h"
#include "entidad2.h"
#include "utn.h"

static int proximoId(void);
static int buscarId(Publicacion* array,int limite,int id);
static int buscarLibre(Publicacion* array,int limite);

int publicacion_init(Publicacion* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            array[i].isEmpty=1;
            array[i].ventas=0;
        }
    }
    return retorno;
}

int publicacion_contratar(Publicacion* array,Cliente* arrayC,int limite,int limiteP)
{
    int retorno=-1;
    int i;
    char aviso[64];
    int rubro;
    int id;
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            if(!getValidString("\nAviso: ","\nEso no es un aviso\n","\n64 caracteres maximo\n",aviso,64,2)){
                if(!getValidInt("\nRubro: ","\nEso no es un rubro\n",&rubro,0,999,2)){
                    if(!getValidInt("\nID Cliente: ","\nDe 1 a 19999\n",&id,0,100,2)){
                        if(cliente_buscarId(arrayC,limiteP,id)>=0){
                            retorno=0;
                            strcpy(array[i].aviso,aviso);
                            array[i].rubro=rubro;
                            array[i].id=proximoId();
                            array[i].idCliente=id;
                            array[i].isPaused=0;
                            array[i].isEmpty=0;
                        }
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
/*
int publicacion_modificacion(Publicacion* array,int limite,int id)
{
    int retorno=-1;
    char aviso[50];
    int rubro;
    int idCliente;
    int indice=buscarId(array,limite,id);
    if(indice>=0){
        retorno=-2;
        if(!getValidString("\nAviso: ","\nEso no es un aviso\n","\n64 caracteres maximo\n",aviso,64,2)){
                if(!getValidInt("\nRubro: ","\nEso no es un rubro\n",&rubro,0,999,2)){
                    if(!getValidInt("\nID Cliente: ","\nDe 1 a 19999\n",&id,0,100,2)){
                        if(cliente_buscarId(arrayC,limiteP,id)>=0){
                            retorno=0;
                            strcpy(array[i].aviso,aviso);
                            array[i].rubro=rubro;
                            array[i].idCliente=id;
                        }
                    }
                }
            }
    }
    return retorno;
}
*/
int publicacion_mostrarPorCliente(Publicacion* array,int limite, int idCliente)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty&&array[i].idCliente==idCliente){
                //printf("ID: %d - Producto: %s - Rubro: %.2f - Cantidad Vendida: %d - ID Cliente: %d\n",array[i].id,array[i].aviso,array[i].rubro,array[i].ventas,array[i].idCliente);
                retorno=0;
            }
        }
    }
    return retorno;
}

int publicacion_baja(Publicacion* array,int limite, int id)
{
    int retorno=-1;
    int indice=buscarId(array,limite,id);
    if(indice>=0){
        array[indice].isEmpty=1;
        retorno=0;
    }
    return retorno;
}

static int buscarLibre(Publicacion* array,int limite)
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

static int proximoId(void)
{
    static int proximoId=-1;
    proximoId++;
    return proximoId;
}

static int buscarId(Publicacion* array,int limite,int id)
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


int publicacion_mostrar(Publicacion* array,int limite,Cliente* arrayC)
{
    int retorno=-1;
    int i;
    int userindex;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty){
                    userindex=cliente_buscarId(arrayC,limite,array[i].idCliente);
                    printf("\nID: %d - Aviso: %s - Rubro: %d - CUIT Cliente: %d\n",array[i].id,array[i].aviso,array[i].rubro,arrayC[userindex].cuit);
            }
        }
    }
    return retorno;
}

int publicacion_comprar(Publicacion* array,int limite,Cliente* Clientes,int id)
{
    int retorno=-1;
    int indice=buscarId(array,limite,id);
    int userindex=cliente_buscarId(Clientes,limite,array[indice].idCliente);
    int calificacion;
    if(indice>=0&&(!array[indice].isEmpty&&array[indice].idCliente>0)){
        retorno=0;
        array[indice].idCliente--;
        array[indice].ventas++;
        getValidInt("Calificacion (1 - 5): ","Por favor ingresar un numero entero de 1 a 5",&calificacion,1,5,3);
        Clientes[userindex].cantidadCalif++;
        Clientes[userindex].calificacion+=calificacion;
    }
    return retorno;
}

int publicacion_pausar(Publicacion* array,int limite,Cliente* arrayC,int limiteC)
{
    int id;
    int index;
    int choice;
    int idCliente;
    int retorno=-1;
    if(!getValidInt("\nID Publicacion: ","\nPublicacion no encontrada\n",&id,0,1000,2)){
        index=buscarId(array,limite,id);
        idCliente=cliente_buscarId(arrayC,limiteC,array[index].idCliente);
        if(cliente_mostrarPorId(arrayC,limiteC,idCliente)>=0){
            getValidInt("Cambiar estado? [1]SI - [0]NO ","Por favor, marcar 1 o 0",&choice,0,1,2);
            if(choice){
                array[index].isPaused=1;
                retorno=0;
            }
        }
    }
    return retorno;
}

int publicacion_reanudar(Publicacion* array,int limite,Cliente* arrayC,int limiteC)
{
    int id;
    int index;
    int choice;
    int idCliente;
    int retorno=-1;
    if(!getValidInt("\nID Publicacion: ","\nPublicacion no encontrada\n",&id,0,1000,2)){
        index=buscarId(array,limite,id);
        idCliente=cliente_buscarId(arrayC,limiteC,array[index].idCliente);
        if(cliente_mostrarPorId(arrayC,limiteC,idCliente)>=0){
            getValidInt("Cambiar estado? [1]SI - [0]NO ","Por favor, marcar 1 o 0",&choice,0,1,2);
            if(choice){
                array[index].isPaused=0;
                retorno=0;
            }
        }
    }
    return retorno;
}
