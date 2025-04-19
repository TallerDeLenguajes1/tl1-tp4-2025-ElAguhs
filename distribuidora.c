#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

typedef struct Tarea
{
    int TareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

typedef struct Producto
{
    int ProductoID;
    int Cantidad;
    char *TipoProducto;
    float PrecioUnitario;
} Producto;

typedef struct Cliente
{
    int ClienteID;
    char *NombreCliente;
    int CantidadProductosAPedir;
    Producto *Productos;
} Clientes;

Nodo *crearListaVacia()
{
    return NULL;
}


void AgregarTarea(Nodo **lista, int *idActual)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));

    nuevo->T.TareaID = (*idActual)++; 
    nuevo->T.Descripcion = (char *)malloc(50 * sizeof(char));

    printf("Ingrese la descripcion de la tarea\n");
    fflush(stdin);
    gets(nuevo->T.Descripcion); 

    nuevo->T.Duracion = 10 + rand() % 91; 
    nuevo->Siguiente = *lista;
    *lista = nuevo;
}
float CostoTotalDeUnProducto(Producto p)
{
    return p.Cantidad * p.PrecioUnitario;
}

int main()
{
    int cantClientes;
    float totalGalletas = 0;
    float totalSnack = 0;
    float totalCigarrillos = 0;
    float totalCaramelos = 0;
    float totalBebidas = 0;

    srand(time(NULL));

    int idActual = 1000;
    Nodo *pendientes = crearListaVacia();

    char respuesta;
    do
    {
        AgregarTarea(&pendientes, &idActual);
        printf("Desea agregar una nueva tarea? (s/n): ");
        scanf(" %c", &respuesta);
    } while (respuesta == 's' || respuesta == 'S');


    printf("Ingrese la cantidad de clientes\n");
    scanf("%d", &cantClientes);

    Clientes *cliente = (Clientes *)malloc(cantClientes * sizeof(Clientes));

    for (int i = 0; i < cantClientes; i++)
    {
        float totalPorCliente = 0;
        cliente[i].ClienteID = i + 1;
        cliente[i].NombreCliente = (char *)malloc(50 * sizeof(char));
        printf("Ingrese el nombre del cliente %d\n", i + 1);
        fflush(stdin);
        gets(cliente[i].NombreCliente);
        fflush(stdin);
        cliente[i].CantidadProductosAPedir = (rand() % 5) + 1;

        cliente[i].Productos = (Producto *)malloc(cliente[i].CantidadProductosAPedir * sizeof(Producto));

        for (int j = 0; j < cliente[i].CantidadProductosAPedir; j++)
        {
            int ProductoRandom = (rand() % 5);
            cliente[i].Productos[j].ProductoID = j + 1;
            cliente[i].Productos[j].Cantidad = (rand() % 10) + 1;
            cliente[i].Productos[j].TipoProducto = TiposProductos[ProductoRandom];
            cliente[i].Productos[j].PrecioUnitario = 10 + rand() % (100 - 10 + 1);

            Producto p = cliente[i].Productos[j];
            float costoTotal = CostoTotalDeUnProducto(p);

            if (strcmp(p.TipoProducto, "Galletas") == 0)
                totalGalletas += costoTotal;
            else if (strcmp(p.TipoProducto, "Snack") == 0)
                totalSnack += costoTotal;
            else if (strcmp(p.TipoProducto, "Cigarrillos") == 0)
                totalCigarrillos += costoTotal;
            else if (strcmp(p.TipoProducto, "Caramelos") == 0)
                totalCaramelos += costoTotal;
            else if (strcmp(p.TipoProducto, "Bebidas") == 0)
                totalBebidas += costoTotal;

            printf("Producto cargado nro. %d\n", cliente[i].Productos[j].ProductoID);
            printf("ProductoID = %d\n", cliente[i].Productos[j].ProductoID);
            printf("Cantidad = %d\n", cliente[i].Productos[j].Cantidad);
            printf("TipoProducto = %s\n", cliente[i].Productos[j].TipoProducto);
            printf("PrecioUnitario = %.2f\n", cliente[i].Productos[j].PrecioUnitario);

            totalPorCliente += costoTotal;
        }
        printf("El total del cliente %d es de %.2f\n", i + 1, totalPorCliente);
    }

    printf("Total por galletas: %.2f\n Total por Snack: %.2f\n Total por Cigarrillos: %.2f\n Total por Caramelos: %.2f\n Total por Bebidas: %.2f\n", totalGalletas, totalSnack, totalCigarrillos, totalCaramelos, totalBebidas);

    for (int i = 0; i < cantClientes; i++)
    {
        free(cliente[i].NombreCliente);
        free(cliente[i].Productos);
    }

    free(cliente);

    return 0;
}
