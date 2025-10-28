#include <stdio.h>
#include <stdlib.h>
///Estructura///
typedef struct
{
    int legajo;
    char nombreYapellido[30];
    int edad;
    int anio;
} stAlumno;

///Prototipos///
int contarAlumnosArchivo(char nombreArchivo[]);
stAlumno* cargarAlumnosArreglo(char archivo[], int cantidad);
void  mostrarAlumnosArreglo(stAlumno *arr, int cantidad);
stAlumno* filtrar21(stAlumno *alumnos, int cant, int *cantMay);
stAlumno alumnoNuevo();
stAlumno* agregarFinal(stAlumno *alumnos, int *cant);
stAlumno* redimensionarArreglo(stAlumno *arr, int nuevoTam);
void mostrarArchivo(char nombre[]);
void guardarArchivoEnArreglo(char *nombreArchivo, stAlumno *arr, int cant);
int contarAnio(stAlumno *arr, int cant, int anio);
stAlumno* arregloAnio(stAlumno *arr, int cant, int anio, int *cantanio);

///Main///
int main()
{
    char archivo[] = "alumnos.dat";
    char narchivo[] = "nalumnos.dat";
    int cantidad, cantMay, cantAnio;
    cantidad = contarAlumnosArchivo(archivo);
    stAlumno *alumnos = cargarAlumnosArreglo(archivo, cantidad);
    stAlumno *mayores = NULL;
    stAlumno *anio = NULL;
    int op;

    do
    {
        printf("=== MENU ===\n");
        printf("1. Mostrar alumnos\n");
        printf("2. Mostrar alumnos mayores a 21\n");
        printf("3. Agregar un alumno al arreglo filtrado\n");
        printf("4. Redimensionar arreglo\n");
        printf("5. Guardar en archivo nuevo y mostrar archivo\n");
        printf("6. Filtrar por Anio y mostrar nuevo arreglo\n");
        printf("0. Salir\n");
        scanf("%d", &op);
        switch(op)
        {
        case 1:
            mostrarAlumnosArreglo(alumnos, cantidad);
            system("pause");
            system("cls");
            break;
        case 2:
            mayores = filtrar21(alumnos, cantidad, &cantMay);
            printf("--Alumnos mayores a 21--");
            mostrarAlumnosArreglo(mayores, cantMay);
            system("pause");
            system("cls");
            break;
        case 3:
            mayores = agregarFinal(mayores, &cantMay);
            mostrarAlumnosArreglo(mayores, cantMay);
            system("pause");
            system("cls");
            break;
        case 4:
            mayores = redimensionarArreglo(mayores, 6);
            system("pause");
            system("cls");
            break;
        case 5:
            guardarArchivoEnArreglo(narchivo, mayores, cantMay);
            system("pause");
            mostrarArchivo(narchivo);
            system("pause");
            system("cls");
            break;
        case 6:
            int a;
            printf("\nIngrese el anio que desea filtrar:");
            fflush(stdin);
            scanf("%d", &a);
            anio = arregloAnio(mayores, cantMay, a, &cantAnio);
            system("pause");
            mostrarAlumnosArreglo(anio, cantAnio);
            system("pause");
            system("cls");
            break;
        }
    }
    while(op != 0);

    free(alumnos);
    free(mayores);
    free(anio);
}
///Funciones Auxiliar///
stAlumno alumnoNuevo()
{
    stAlumno nuevo;
    printf("Ingrese legajo: ");
    scanf("%d", &nuevo.legajo);

    printf("Ingrese nombre y apellido: ");
    scanf(" %[^\n]", nuevo.nombreYapellido); // lee con espacios hasta Enter

    printf("Ingrese edad: ");
    scanf("%d", &nuevo.edad);

    printf("Ingrese año: ");
    scanf("%d", &nuevo.anio);

    return nuevo;

}

void mostrarArchivo(char nombre[])
{
    stAlumno a;
    FILE *arch = fopen(nombre, "rb");

    if(arch != NULL)
    {
        while(fread(&a, sizeof(stAlumno), 1, arch) > 0)
        {
            printf("Legajo: %d | Nombre: %s | Edad: %d | Año: %d\n",
                   a.legajo,
                   a.nombreYapellido,
                   a.edad,
                   a.anio);
        }
    }
}
///Funciones///
/*Ejercicio 1*/
int contarAlumnosArchivo(char nombreArchivo[])
{
    int cantidad = 0;
    stAlumno aux;
    FILE *arch = fopen (nombreArchivo, "rb");
    if(arch != NULL)
    {
        while(fread(&aux, sizeof(stAlumno), 1, arch) > 0)
        {
            cantidad++;
        }
    }
    fclose(arch);

    return cantidad;
}

stAlumno* cargarAlumnosArreglo(char archivo[], int cantidad)
{
    stAlumno *arreglo = (stAlumno*) malloc (sizeof(stAlumno) * cantidad);

    if(arreglo == NULL)
    {
        printf("/nNo se pudo reservar la memoria.");
    }

    FILE *arch = fopen(archivo, "rb");

    if(arch != NULL)
    {
        fread(arreglo, sizeof(stAlumno), cantidad, arch);
        fclose(arch);
    }
    else
    {
        free(arreglo);
    }

    return arreglo;
}

void  mostrarAlumnosArreglo(stAlumno *arr, int cantidad)
{
    if(arr != NULL)
    {
        printf("\nListado de alumnos cargados:\n");
        for(int i = 0; i < cantidad; i++)
        {
            printf("Legajo: %d | Nombre: %s | Edad: %d | Año: %d\n",
                   arr[i].legajo,
                   arr[i].nombreYapellido,
                   arr[i].edad,
                   arr[i].anio);
        }
    }
}

/*Ejercicio 2*/
stAlumno* filtrar21(stAlumno *alumnos, int cant, int *cantMay)
{
    *cantMay = 0;
    for(int i = 0; i < cant; i++) //Contamos los mayores a 21 y los sumamos al puntero de cantidad de Mayores
    {
        if(alumnos[i].edad > 21)
        {
            (*cantMay)++;
        }
    }

    stAlumno *mayores = (stAlumno*) malloc (sizeof(stAlumno) * (*cantMay));

    int j = 0;
    for(int i = 0; i < cant; i++) //mayores a 21 lo agregamos al nuevo arreglo dinamico
    {
        if(alumnos[i].edad > 21)
        {
            mayores[j] = alumnos[i];
            j++;
        }
    }
    return mayores;
}

/*Ejercicio 3*/
stAlumno* agregarFinal(stAlumno *alumnos, int *cant)
{
    stAlumno a = alumnoNuevo();

    alumnos = (stAlumno*) realloc(alumnos, (*cant + 1) * sizeof(stAlumno));
    alumnos[*cant] = a;
    (*cant)++;
    return alumnos;
}

/*Ejercicio 4*/
stAlumno* redimensionarArreglo(stAlumno *arr, int nuevoTam)
{
    return (stAlumno *) realloc(arr, nuevoTam * sizeof(stAlumno));
}

/* Ejercicio 5 */
void guardarArchivoEnArreglo(char *nombreArchivo, stAlumno *arr, int cant)
{
    FILE *arch = fopen(nombreArchivo, "wb");

    if(arch != NULL)
    {
        fwrite(arr, sizeof(stAlumno), cant, arch);
        fclose(arch);
    }
}

/*Ejercicio 6*/
int contarAnio(stAlumno *arr, int cant, int anio)
{
    int cont = 0;
    for(int i = 0; i < cant; i++)
    {
        if(arr[i].anio == anio)
        {
            cont++;
        }
    }
    return cont;
}

stAlumno* arregloAnio(stAlumno *arr, int cant, int anio, int *cantanio)
{
    *cantanio = 0;
    *cantanio = contarAnio(arr, cant, anio);

    if(*cantanio == 0)
    {
        return NULL;
    }

    stAlumno *filtrados = (stAlumno*) malloc (*cantanio * sizeof(stAlumno));

    int j = 0;
    for(int i = 0; i < cant; i++)
    {
        if(arr[i].anio == anio)
        {
            filtrados[j] = arr[i];
            j++;
        }
    }
    return filtrados;
}

/*Ejercicio 7*/
void separarAnio(stAlumno *arr, int cant)
{

}
