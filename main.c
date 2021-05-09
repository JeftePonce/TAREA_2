#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "funciones.h"
#include "map.h"

/*
  funci�n para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0)return 1;
    return 0;
}

/*
  funci�n para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  funci�n para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if((int*)key1 == (int*)key2) return 1;
    return 0;
}

/*
  funci�n para comparar claves de tipo int
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
    int contPokALmacenados = 0; //sirve para no pasarnos de los 100 pokemons que se pueden almacenar
    char* name;
    int aparicion=1;
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

        //Ingresamos el pokemon al mapa correspondiente


        //insertMap(pokedex, oPokemonDex->nombre, oPokemonDex);



    }

    //int op;//variable para el menu

    //Limpiamos variables
    //Almacenamiento
    id = (int) malloc(sizeof(id));//
    nombre = (char*) malloc(sizeof(nombre));//
    pc = (int) malloc(sizeof(pc));//
    ps = (int) malloc(sizeof(ps));//
    sexo = (char*) malloc(sizeof(sexo));//

    //Pokedex
    tipo = (char*) malloc(sizeof(tipo));
    evolPrev = (char*) malloc(sizeof(evolPrev));
    evolPost = (char*) malloc(sizeof(evolPost));
    numPokedex = (int) malloc(sizeof(numPokedex));
    region = (char*) malloc(sizeof(region));

    char* archivo;
    char* tipoPokBus;
    int idLiberar;

    //mostrarMapaPokedex(pokedex);

    int op;

    while(1){


        printf("Seleccione una opcion:\n");
        printf("1. Importar archivo CSV \n");
        printf("2. Agregar un Pokemon al Almacenamiento \n");
        printf("3. Evolucionar Pokemon \n");
        printf("4. Buscar Pokemon por Tipo en Almacenamiento \n");
        printf("5. Buscar Pokemon por Nombre en Almacenamiento \n");
        printf("6. Buscar Pokemon por Nombre en Pokedex \n");
        printf("7. Mostrar todos los Pokemons en la Pokedex \n");
        printf("8. Mostrar Pokemons del Almacenamiento ordenados por PC \n");
        printf("9. Liberar Pokemon del Almacenamiento \n");
        printf("10. Mostrar Pokemon del Almacenamiento por Region \n");
        printf("0. Salir \n");
        printf("Escriba el numero de la opcion: ");
        scanf("%i", &op);

        switch (op){
        //case 0 es para salir del programa
        case 0:

            return 0;

        case 1:

            archivo = (char*) malloc(sizeof(char));

            printf("Importar archivo CSV\n");

            printf("Importar ubicacion del archivo\n");
            scanf("%s", archivo);

            FILE *doc = fopen(archivo, "r");

            if(!doc){
                printf("No se encontro el archivo\n");
            }
            abrirArchivo(archivo, pokemonAlm, pokedex);

            break;

        case 2:

            id = (int) malloc(sizeof(id));//
            nombre = (char*) malloc(sizeof(nombre));//
            pc = (int) malloc(sizeof(pc));//
            ps = (int) malloc(sizeof(ps));//
            sexo = (char*) malloc(sizeof(sexo));//

            tipo = (char*) malloc(sizeof(tipo));
            evolPrev = (char*) malloc(sizeof(evolPrev));
            evolPost = (char*) malloc(sizeof(evolPost));
            numPokedex = (int) malloc(sizeof(numPokedex));
            region = (char*) malloc(sizeof(region));

            printf("2. Agregar un Pokemon al Almacenamiento \n");

            if(contPokALmacenados==100){

                printf("El almacenamiento esta lleno. \n");
                break;
            }

            printf("Ingrese los datos del Pokemon que desea agregar: \n");
            //printf("ID: ");
            //scanf("%i", &id);

            printf("NOMBRE: \n");
            scanf("%s", nombre);

            printf("TIPO: separados por una coma en caso de ser 2\n");
            scanf("%s", tipo);

            printf("PC: \n");
            scanf("%i", &pc);

            printf("PS: \n");
            scanf("%i", &ps);

            printf("SEXO: \n");
            scanf("%s", sexo);
            getchar();

            printf("Evolucion Previa: \n");
            gets(evolPrev);

            printf("Evolucion Posterior: \n");
            gets(evolPost);

            printf("Numero Pokedex: \n");
            scanf("%i", &numPokedex);

            printf("REGION: \n");
            scanf("%s", region);

            id = mayorID(pokemonAlm);
            //printf("%i \n", id);
            id++;

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

            //mostrarMapaAlm(pokemonAlm);
            //printf("%s %s %i %i %s %s %s %i %s\n",nombre,tipo,pc,ps,sexo,evolPrev,evolPost,numPokedex,region);


            break;

        case 3:

            printf("3. Evolucionar Pokemon \n");

            int ide;
            printf("Ingrese id del Pokemon: ");
            scanf("%d", &ide);
            EvolucionarPokemon(pokemonAlm, pokedex, ide);



            break;

        case 4:

            tipoPokBus = (char*) malloc(sizeof(char));

            printf("4. Buscar Pokemon por Tipo en Almacenamiento\n");
            printf("Ingrese el Tipo que desea buscar:\n");
            scanf("%s", tipoPokBus);
            printf("\n");

            buscarTipo(tipoPokBus, pokemonAlm);

            break;

        case 5:

            name = (char*) malloc(sizeof(name));
            printf("5. Buscar Pokemon por Nombre en Almacenamiento \n");
            printf("Ingrese el nombre a buscar \n");
            scanf("%s",name);

            buscarporNombre(name,pokemonAlm);

            break;

        case 6:

            name = (char*) malloc(sizeof(name));
            printf("6. Buscar Pokemon por Nombre en Pokedex \n");
            printf("Ingrese el nombre a buscar \n");
            scanf("%s",name);

            buscarporNombreDex(name,pokedex);

            break;

        case 7:

            printf("7. Mostrar todos los Pokemons en la Pokedex \n");

            mostrarMapaPokedex(pokedex);

            break;

        case 8:

            printf("8. Mostrar Pokemons del Almacenamiento ordenados por PC \n");

            break;

        case 9:

            printf("9. Liberar Pokemon del Almacenamiento \n");

            printf("Ingrese id del pokemon que desea liberar\n");
            scanf("%i", &idLiberar);

            liberarPokemon(idLiberar, pokemonAlm, pokedex);

            break;

        case 10:

            printf("10. Mostrar Pokemon del Almacenamiento por Region \n");

            region = (char*) malloc(sizeof(region));
            printf("Ingrese la region que quiera buscar: ");
            scanf("%s", region);
            printf("\nPokemones de la region de %s \n", region);

            //Muestro por pantalla la informacion de la pokedex de los pokemones del almacenamiento
            MostrarPorRegion(region, pokemonAlm, pokedex);

            break;


        default:

            break;


        }


    }

    return 0;
}
