#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "funciones.h"
#include "map.h"

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0)return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

int main(){

    // Se crea la lista usando los datos del TDA lista implementado
    //list *lista_pokemon = list_create(lista_pokemon);//almacenamiento pokemon por orden

    //Se crean los mapas para poder agregar los pokemons
    Map* pokemonAlm = createMap(is_equal_int);
    //setSortFunction(pokemonAlm,lower_than_string);

    Map* pokedex = createMap(is_equal_string);
    setSortFunction(pokedex,lower_than_string);

    // Se abre el archivo de mundos csv en modo lectura "r"
    FILE *fp = fopen ("pokemon_Archivo.csv", "r");

    char linea[1024];

    fgets (linea, 1023, fp);

    //Se declaran las variables rut, nombre, dias y ver para ser utilizadas en la funcion crear_bombero
    int id;//int
    char* nombre;
    char* tipo;
    int pc;//int
    int ps;//int
    char* sexo;
    char* evolPrev;
    char* evolPost;
    int numPokedex;//int
    char* region;
    int cont = 0; //sirve para no pasarnos de los 100 pokemons que se pueden almacenar

    /* sera el tipo de dato que utilizaremos para almacenar los datos del pokemon
    */
    pokemon* oPokemon = NULL;
    pokemondex* oPokemonDex = NULL;

    while (fgets (linea, 1023, fp) != NULL /*&& cont <= 100*/ ) { // Se lee la linea incluyendo espacios

        id = (int) strtol(get_csv_field(linea, 0), NULL, 10);
        nombre = get_csv_field(linea,1);
        tipo = get_csv_field(linea, 2);
        pc = (int) strtol(get_csv_field(linea, 3), NULL, 10);
        ps = (int) strtol(get_csv_field(linea, 4), NULL, 10);
        sexo = get_csv_field(linea, 5);
        evolPrev = get_csv_field(linea, 6);
        evolPost = get_csv_field(linea, 7);
        numPokedex = (int) strtol(get_csv_field(linea, 8), NULL, 10);
        region = get_csv_field(linea, 9);

        //Se almacenan los datos dentro de los objetos
        oPokemon = crear_pokemon(id, nombre, pc, ps, sexo);
        oPokemonDex = crear_pokemonDex(nombre, 0, tipo, evolPrev, evolPost, numPokedex, region);

        if( (searchMap(pokemonAlm, oPokemon->nombre)) != NULL ){
            oPokemonDex->existencia++;
        }else{
            oPokemonDex->existencia = 1;
        }

        //Ingresamos el pokemon al mapa correspondiente
        insertMap(pokemonAlm, &oPokemon->id, oPokemon);
        cont++;
        insertMap(pokedex, oPokemonDex->nombre, oPokemonDex);

        if(cont==100) break;

    }

    mostrarMapaAlm(pokemonAlm);

    return 0;
}
