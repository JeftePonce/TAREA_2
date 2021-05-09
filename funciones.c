#include "list.h"
#include "funciones.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Funcion dada por el profesor para leer archivos .csv
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

pokemon* crear_pokemon(int id, char* nombre, int pc, int ps, char* sexo){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));

    oPokemon->id = id;
    oPokemon->nombre = nombre;
    oPokemon->pc = pc;
    oPokemon->ps = ps;
    oPokemon->sexo = sexo;

    return oPokemon;
}

pokemondex* crear_pokemonDex(char* nombre, int existencia, char* tipo, char* evolPrev, char* evolPost, int numPokedex, char* region){

   pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));

    oPokemonDex->nombre = nombre;
    oPokemonDex->tipo = tipo;
    oPokemonDex->evolPrev = evolPrev;
    oPokemonDex->evolPost = evolPost;
    oPokemonDex->numPokedex = numPokedex;
    oPokemonDex->region = region;


    return oPokemonDex;

}

mostrarMapaAlm(Map* mapa){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));

    oPokemon = firstMap(mapa);

    int i=1;

    while( oPokemon != NULL ){

        printf("------%i------\n", i);

        printf("%i \n", oPokemon->id);
        printf("%s \n", oPokemon->nombre);
        printf("%i \n", oPokemon->pc);
        printf("%i \n", oPokemon->ps);
        printf("%s \n", oPokemon->sexo);
        printf("\n");

        i++;

        oPokemon = nextMap(mapa);

    }

}

mostrarMapaPokedex(Map* mapa){

    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));

    oPokemonDex = firstMap(mapa);

    int i=0;

    while(oPokemonDex != NULL){

        printf("------%i------\n", i);

        printf("%s \n", oPokemonDex->nombre);
        printf("%i \n", oPokemonDex->existencia);
        printf("%s \n", oPokemonDex->tipo);
        printf("%s \n", oPokemonDex->evolPrev);
        printf("%s \n", oPokemonDex->evolPost);
        printf("%i \n", oPokemonDex->numPokedex);
        printf("%s \n", oPokemonDex->region);
        printf("\n");
        i++;

        oPokemonDex = nextMap(mapa);

    }


}

buscarporNombre(char* name,Map* mapa){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));
    oPokemon = firstMap(mapa);
    int i = 1;

    while( oPokemon != NULL ){

        if (strcmp(oPokemon->nombre,name) == 0){
            printf("------%i------\n", i);

            printf("Nombre: %s \n", oPokemon->nombre);
            printf("ID: %i \n", oPokemon->id);
            printf("PC: %i \n", oPokemon->pc);
            printf("PS: %i \n", oPokemon->ps);
            printf("Sexo: %s \n", oPokemon->sexo);
            printf("\n");

            i++;
        }
        oPokemon = nextMap(mapa);
    }

    if (i == 1){
        printf("No se ha encontrado ningun pokemon con ese nombre en el almacenamiento \n");
    }

}

buscarporNombreDex(char* name,Map* mapa){

    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));
    oPokemonDex = firstMap(mapa);
    int i = 1;

    while( oPokemonDex != NULL ){

        if (strcmp(oPokemonDex->nombre,name) == 0){
            printf("------%i------\n", i);

            printf("Nombre: %s \n", oPokemonDex->nombre);
            printf("Existencia: %i \n", oPokemonDex->existencia);
            printf("Tipo: %s \n", oPokemonDex->tipo);
            printf("Evolucion previa: %s \n", oPokemonDex->evolPrev);
            printf("Evolucion posterior: %s \n", oPokemonDex->evolPost);
            printf("Numero de la pokedex: %i \n", oPokemonDex->numPokedex);
            printf("Region: %s \n", oPokemonDex->region);
            printf("\n");

            i++;
        }
        oPokemonDex = nextMap(mapa);
    }

    if (i == 1){
        printf("No se ha encontrado ningun pokemon con ese nombre en la pokedex \n");
    }

}
