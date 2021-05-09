#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "map.h"

typedef struct{

    char* nombre;
    int existencia;
    char* tipo;
    char* evolPrev;
    char* evolPost;
    int numPokedex; //numero del pokemon, unico
    char* region;

}pokemondex;

typedef struct{

    int id; //numero asociado a la posicion en la que entra en pokemon al almacenamiento, independiente de numPokedex
    char* nombre;
    int pc;
    int ps;
    char* sexo;

}pokemon;

const char *get_csv_field (char * tmp, int k);

void abrirArchivo(char* archivo, Map* pokemonAlm, Map* pokedex);

pokemon* crear_pokemon(int id, char* nombre, int pc, int ps, char* sexo);

pokemondex* crear_pokemonDex(char* nombre, int existencia, char* tipo, char* evolPrev, char* evolPost, int numPokedex, char* region);

mostrarMapaAlm(Map* mapa); //muestra todos los pokemones de el mapa almacenamiento

mostrarMapaPokedex(Map* mapa); //muestra todos los pokemones de el mapa pokedex

buscarporNombre(char* name,Map*mapa);

buscarporNombreDex(char* name,Map* mapa);

#endif
