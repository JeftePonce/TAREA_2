#include "list.h"
#include "funciones.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

void abrirArchivo( char * archivo, Map *pokemonAlm, Map *pokedex ){

    // Se abre el archivo de mundos csv en modo lectura "r"
    FILE *fp = fopen (archivo, "r");

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
    int aparicion=1;
    int contPokALmacenados = 0; //sirve para no pasarnos de los 100 pokemons que se pueden almacenar

    /* sera el tipo de dato que utilizaremos para almacenar los datos del pokemon
    */
    pokemon* oPokemon = NULL;
    pokemondex* oPokemonDex = NULL;

    while (fgets (linea, 1023, fp) != NULL ) { // Se lee la linea incluyendo espacios

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
        oPokemon = crear_pokemon(id, nombre, pc, ps, sexo, tipo);
        oPokemonDex = searchMap(pokedex, nombre);

        if( oPokemonDex == NULL){

            oPokemonDex = crear_pokemonDex(nombre, 0, tipo, evolPrev, evolPost, numPokedex, region, aparicion);
            insertMap(pokedex, oPokemonDex->nombre, oPokemonDex);
            oPokemonDex->existencia = 1;
        }
        else oPokemonDex->existencia++;


        if(contPokALmacenados <= 100){
            insertMap(pokemonAlm,oPokemon->id,oPokemon);
            contPokALmacenados++;
        }

    }

}

pokemon* crear_pokemon(int id, char* nombre, int pc, int ps, char* sexo, char* tipo){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));

    oPokemon->id = id;
    oPokemon->nombre = nombre;
    oPokemon->pc = pc;
    oPokemon->ps = ps;
    oPokemon->sexo = sexo;
    oPokemon->tipo = tipo;

    return oPokemon;
}

pokemondex* crear_pokemonDex(char* nombre, int existencia, char* tipo, char* evolPrev, char* evolPost, int numPokedex, char* region, int aparicion){

   pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));

    oPokemonDex->nombre = nombre;
    oPokemonDex->tipo = tipo;
    oPokemonDex->evolPrev = evolPrev;
    oPokemonDex->evolPost = evolPost;
    oPokemonDex->numPokedex = numPokedex;
    oPokemonDex->region = region;
    oPokemonDex->aparicion = aparicion;


    return oPokemonDex;

}

mostrarMapaAlm(Map* mapa){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon)); //creamos una variable del tipo pokemon

    oPokemon = firstMap(mapa); // nos posicionamos en el incio del mapa

    int i=1;

    while( oPokemon != NULL ){
        //imprimimos los datos del pokemon

        //printf("------%i------\n", i);

        printf("%i \n", oPokemon->id);
        printf("%s \n", oPokemon->nombre);
        printf("%i \n", oPokemon->pc);
        printf("%i \n", oPokemon->ps);
        printf("%s \n", oPokemon->sexo);
        printf("\n");

        i++;

        oPokemon = nextMap(mapa);//avanzamos en el mapa

    }

}

mostrarMapaPokedex(Map* mapa){

    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex)); //creamos una variable del tipo pokemon de la pokedex (pokemondex)

    oPokemonDex = firstMap(mapa); //lo posicionamos en el inicio del mapa

    int i=0;

    while(oPokemonDex != NULL){

        //imprimimos los datos del pokemon de la pokedex

        //printf("------%i------\n", i);

        printf("%s \n", oPokemonDex->nombre);
        printf("%i \n", oPokemonDex->existencia);
        printf("%s \n", oPokemonDex->tipo);
        printf("%s \n", oPokemonDex->evolPrev);
        printf("%s \n", oPokemonDex->evolPost);
        printf("%i \n", oPokemonDex->numPokedex);
        printf("%s \n", oPokemonDex->region);
        printf("\n");
        i++;

        oPokemonDex = nextMap(mapa); //avanzamos en el mapa

    }


}

buscarporNombre(char* name,Map* mapa){ //Buscamos por nombre en el almacenamiento

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));
    oPokemon = firstMap(mapa);//Ingresamos al primer elemento del mapa
    int i = 1;//Tenemos una variable para mostrar cuantos pokemones hay en nuestro almacenamiento

    while( oPokemon != NULL ){ //Para recorrer el mapa hasta que este sea nulo

        if (strcmp(oPokemon->nombre,name) == 0){    //Comparamos el nombre del mapa con el nombre ingresado
            printf("------%i------\n", i);

            printf("Nombre: %s \n", oPokemon->nombre);
            printf("ID: %i \n", oPokemon->id);
            printf("PC: %i \n", oPokemon->pc);
            printf("PS: %i \n", oPokemon->ps);
            printf("Sexo: %s \n", oPokemon->sexo);
            printf("\n");

            i++;
        }
        oPokemon = nextMap(mapa); //Pasamos al siguiente
    }

    if (i == 1){ //Si no se encuentra ningun pokemon en el almacenamiento se muestra por pantalla lo siguiente
        printf("No se ha encontrado ningun pokemon con ese nombre en el almacenamiento \n");
    }

}

buscarporNombreDex(char* name,Map* mapa){ //Buscamos por nombre en la pokedex

    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));
    oPokemonDex = firstMap(mapa);//Ingresamos al primer elemento del mapa

    while( oPokemonDex != NULL ){       //Para recorrer el mapa hasta que este sea nulo

        if (strcmp(oPokemonDex->nombre,name) == 0){ //Comparamos el nombre del mapa con el nombre ingresado
            printf("--------------\n");

            printf("Nombre: %s \n", oPokemonDex->nombre);
            printf("Existencia: %i \n", oPokemonDex->existencia);
            printf("Tipo: %s \n", oPokemonDex->tipo);
            printf("Evolucion previa: %s \n", oPokemonDex->evolPrev);
            printf("Evolucion posterior: %s \n", oPokemonDex->evolPost);
            printf("Numero de la pokedex: %i \n", oPokemonDex->numPokedex);
            printf("Region: %s \n", oPokemonDex->region);
            printf("\n");

            return;
        }
        oPokemonDex = nextMap(mapa);
    }

        printf("No se ha encontrado ningun pokemon con ese nombre en la pokedex \n"); //Si no se encuentra que son iguales se muestra por pantalla
}

int mayorID(Map* mapa){     //Busco la mayor ID que tenga un pokemon en el almacenamiento

    int id;
    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));

    oPokemon = firstMap(mapa);
    id = oPokemon->id;          //copio la id del primer pokemon

    while( oPokemon != NULL ){  //se asegura que el pokemon no sea nulo

        oPokemon = nextMap(mapa);
        if (oPokemon == NULL) break;    //comparo las id de los pokemones para quedarme con la mayor y retornarla
        else{
            if (oPokemon->id > id) id = oPokemon->id;
        }

    }
    return id;
}

EvolucionarPokemon(Map *mapaAlm, Map *mapaDex, int id){


    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));
    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));

    oPokemon = firstMap (mapaAlm); //Se le asigna a oPokemon la primera posicion del mapaAlm
    while (oPokemon != NULL){ //Aseguro que el pokemon no sea nulo

        if (oPokemon->id == id) break; //Compruebo que el id que busco este en el almacenamiento

        oPokemon = nextMap(mapaAlm);//Se le asigna a oPokemon la siguiente posicion de mapaAlm
    }
    if (oPokemon == NULL){//Si oPokemon es nulo no se encuentra en el almacenamiento

        printf("No se encuentra en almacenamiento\n");
        return;
    }
    oPokemonDex = searchMap(mapaDex, oPokemon->nombre);//Busca en mapaDex el nombre del pokemon y se le asigna es pokemon a oPokemonDex

    if (strcmp("No tiene",oPokemonDex->evolPost) == 0){//Comparamos si dentro de oPokemonDex, evolPost, tiene la cadena "No tiene" de esta forma sabremos si no tiene evolucion posterior
        printf("Este pokemon no tiene evolucion\n");
        return;
    }else
    if (strcmp(oPokemon->nombre,oPokemonDex->evolPost) == 0){//Compara el nombre del pokemon con su evolucion posterior en la pokedex

        printf("Este pokemon se encuentra en su ultima evolucion\n");
        return;
    }else{//Aca habiendo pasado los casos anteriores y teniendo evolucion se modifican y actualizan los datos de pc, ps y el nombre a su evolucion

        oPokemon->pc = oPokemon->pc * 1.5;
        oPokemon->ps = oPokemon->ps * 1.25;
        oPokemon->nombre = oPokemonDex->evolPost;
        printf("El pokemon ha sido evolucionado");
    }


}

void buscarTipo(char* tipoPok, Map* pokemonAlm){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon)); //creamos una variable del tipo pokemon

    oPokemon = firstMap(pokemonAlm); //la variable del tipo pokemon es ahora el primero del mapa

    list *listaTipoPok = list_create(listaTipoPok); //creamos una lista para almacenar los pokemones con el tipo buscado

    while(oPokemon != NULL){

        if( strstr(oPokemon->tipo, tipoPok) ){ //con esta funcion (strstr) preguntamos si tipoPok esta escrito en el char* de oPokemon->tipo

            list_push_back(listaTipoPok, oPokemon); //y lo añadimos en la lista

        }

        oPokemon = nextMap(pokemonAlm); //avanzamos en el mapa

        //confirmar si el pokemon pertenece al tipo con la funcion que tengo en el otro main y despues cambiar al siguiente, meter el pokemon en una lista y despues imprimir la lista

    }

    oPokemon = list_first(listaTipoPok); //nos posicionamos en el inicio de la lista

    while(oPokemon != NULL){
        //imprimimos los datos del pokemon

        printf("%i\n", oPokemon->id);
        printf("%s\n", oPokemon->nombre);
        printf("%i\n", oPokemon->pc);
        printf("%i\n", oPokemon->ps);
        printf("%s\n", oPokemon->sexo);
        printf("%s\n", oPokemon->tipo);
        printf("\n");

        oPokemon = list_next(listaTipoPok); //nos posicionamos en el siguiente de la lista

    }

    return;

}

MostrarPorRegion(char* region, Map* mapa, Map* mapadex){

    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));
    oPokemon = firstMap(mapa);

    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));

    int cantidad = 0;

    while( oPokemon != NULL ){      //Un while para determinar que el pokemon existe

        oPokemonDex = searchMap(mapadex, oPokemon->nombre);
        if (strcmp(oPokemonDex->region, region) == 0){    //compruebo si es de la region que busco

            cantidad++;
            if (oPokemonDex->aparicion == 1){   //compruebo para no imprimir un pokemon 2 veces

                printf("--------------\n");

                printf("Nombre: %s \n", oPokemonDex->nombre);
                printf("Existencia: %i \n", oPokemonDex->existencia);
                printf("Tipo: %s \n", oPokemonDex->tipo);
                printf("Evolucion previa: %s \n", oPokemonDex->evolPrev);
                printf("Evolucion posterior: %s \n", oPokemonDex->evolPost);
                printf("Numero de la pokedex: %i \n", oPokemonDex->numPokedex);
                printf("\n");

                oPokemonDex->aparicion++;
            }
        }
        oPokemon = nextMap(mapa);  //paso al suiguiente pokemon
    }

    printf("Hay un total de %i pokemones en tu almacenamiento de la region %s\n\n", cantidad, region);

    oPokemon = firstMap(mapa);

    while( oPokemon != NULL ){      //Busco los pokemones de la region buscada y les dejo la aparicion en 1;

        oPokemonDex = searchMap(mapadex, oPokemon->nombre);
        if (strcmp(oPokemonDex->region, region) == 0){

            oPokemonDex->aparicion = 1;
        }
        oPokemon = nextMap(mapa);
    }
}

void liberarPokemon(int idLiberar, Map* pokemonAlm, Map* pokedex){

    //creamos variables para almacenar los tipos de datos correspondientes
    pokemon* oPokemon = (pokemon*) malloc(sizeof(pokemon));
    pokemondex* oPokemonDex = (pokemondex*) malloc(sizeof(pokemondex));

    if(idLiberar > 100){ //si el id a liberar es mayor a 100 entonces nos saldriamos del rango del almacenamiento y se acaba la operacion

        printf("No se encontro el pokemon\n");
        return;

    }

    oPokemon = searchMap(pokemonAlm, idLiberar); //buscamos el pokemon con la id a liberar
    oPokemonDex = searchMap(pokedex, oPokemon->nombre); //buscamos el pokemon que debemos liberar (en la pokedex), para poder bajarle la existencia

    if(oPokemon == NULL) { //verificar si el pokemon es nulo y si lo es, entonces se acaba la operacion

        printf("No se encontro el pokemon\n");
        return;

    }else if( oPokemon->id == idLiberar ){ //si el pokemon id es igual al que buscamos entonces entramos

        eraseMap(pokemonAlm, oPokemon->id); //eliminamos el pokemon
        oPokemonDex->existencia = oPokemonDex->existencia-1; //le restamos una existencia en la pokedex

        printf("El pokemon se elimino correctamente\n");

    }else{ //si no, se printea este mensaje

        printf("No se encontro el pokemon\n");

    }

}
