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
    oPokemonDex->existencia = existencia;
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
