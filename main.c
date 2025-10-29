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
void separarAnio(stAlumno *arr, int cant);
void mostrarInversoRecursivo(stAlumno *arr, int i);
void mostrarArchivoInverso(char nombre[], int pos);

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
        printf("7. Separar alumnos por anio y cargarlos en archivos\n");
        printf("8. Mostrar alumnos del arreglo dinamico de manera inversa recursivamente\n");
        printf("9. Mostrar archivo de manera inversa\n");
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
        case 7:
            separarAnio(alumnos, cantidad);
            mostrarArchivo("primer_anio.dat");
            mostrarArchivo("segudno_anio.dat");
            mostrarArchivo("tercer_anio.dat");
            system("pause");
            system("cls");
            break;
        case 8:
            mostrarInversoRecursivo(mayores, cantMay-1);
            system("pause");
            system("cls");
            break;
        case 9:
            mostrarArchivoInverso(archivo, cantidad);
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

/*Ejercicio 7 Separar los alumnos en función del año cursado, y guardar cada grupo en
archivos binarios distintos: primer_anio.dat, segundo_anio.dat y tercer_anio.dat. */
void separarAnio(stAlumno *arr, int cant)
{
    int cont1 = 0, cont2 = 0, cont3 = 0;
    for(int i = 0; i < cant; i++)
    {
        if(arr[i].anio == 1)
        {
            cont1++;
        }
        else if(arr[i].anio == 2)
        {
            cont2++;
        }
        else if(arr[i].anio == 3)
        {
            cont3++;
        }
    }
    stAlumno *primero = (stAlumno*) malloc (cont1 * sizeof(stAlumno));
    stAlumno *segundo = (stAlumno*) malloc (cont2 * sizeof(stAlumno));
    stAlumno *tercero = (stAlumno*) malloc (cont3 * sizeof(stAlumno));

    int p=0, s=0, t=0;
    for(int i = 0; i<cant; i++)
    {
        if(arr[i].anio == 1)
        {
            primero[p] = arr[i];
            p++;
        }
        else if(arr[i].anio == 2)
        {
            segundo[s] = arr[i];
            s++;
        }
        else if(arr[i].anio == 3)
        {
            tercero[t] = arr[i];
            t++;
        }
    }
    FILE *arch = fopen("primer_anio.dat", "wb");
    fwrite(primero, sizeof(stAlumno), cont1, arch);
    fclose(arch);

    arch = fopen("segudno_anio.dat", "wb");
    fwrite(segundo, sizeof(stAlumno), cont2, arch);
    fclose(arch);

    arch = fopen("tercer_anio.dat", "wb");
    fwrite(tercero, sizeof(stAlumno), cont3, arch);
    fclose(arch);

    free(primero);
    free(segundo);
    free(tercero);
}

/* 8 Mostrar alumnos de un arreglo de manera inversa utilizando recursividad */
void mostrarInversoRecursivo(stAlumno *arr, int i)
{
    if (i < 0)
    {
        return;
    }

    printf("Legajo: %d | Nombre: %s | Edad: %d | Año: %d\n",
           arr[i].legajo,
           arr[i].nombreYapellido,
           arr[i].edad,
           arr[i].anio);
    mostrarInversoRecursivo(arr, i-1);
}

/* 9 Leer archivo de manera inversa recursivamente y utilizando fseek */
void mostrarArchivoInverso(char nombre[], int pos)
{
    stAlumno p;

    if(pos<0)
    {
        return;
    }
    FILE *arch = fopen(nombre, "rb");

    if(arch != NULL)
    {
        fseek(arch, pos * sizeof(stAlumno), SEEK_SET);

        if(fread(&p, sizeof(stAlumno), 1, arch) > 0)
        {
            printf("Legajo: %d | Nombre: %s | Edad: %d | Año: %d\n",
                   p.legajo,
                   p.nombreYapellido,
                   p.edad,
                   p.anio);
        }
        fclose(arch);
    }
    mostrarArchivoInverso(nombre, pos-1);
}
