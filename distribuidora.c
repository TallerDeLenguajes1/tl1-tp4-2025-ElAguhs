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
    gets(nuevo->T.Descripcion);
    fflush(stdin);

    nuevo->T.Duracion = 10 + rand() % 91;
    nuevo->Siguiente = *lista;
    *lista = nuevo;
}

void MostrarLista(Nodo *lista)
{
    while (lista)
    {
        printf("ID: %d | Duracion: %d | Desc: %s\n", lista->T.TareaID, lista->T.Duracion, lista->T.Descripcion);
        lista = lista->Siguiente;
    }
}

void MarcarTareaComoRealizada(Nodo **pendientes, Nodo **realizadas, int id)
{
    Nodo *actual = *pendientes, *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual == NULL)
    {
        printf("Tarea no encontrada.\n");
        return;
    }

    if (anterior == NULL)
    {
        *pendientes = actual->Siguiente;
    }
    else
    {
        anterior->Siguiente = actual->Siguiente;
    }

    actual->Siguiente = *realizadas;
    *realizadas = actual;

    printf("Tarea %d marcada como realizada.\n", id);
}

int esNumero(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

void ConsultarTarea(Nodo *pendientes, Nodo *realizadas)
{
    char palabraID[50];
    printf("Ingrese ID o palabra clave para buscar: ");
    gets(palabraID);
    fflush(stdin);

    Nodo *temp = pendientes;

    if (esNumero(palabraID))
    {
        int id = atoi(palabraID);
        while (temp != NULL)
        {
            if (temp->T.TareaID == id)
            {
                printf("Tarea Pendiente - ID: %d | Descripcion: %s | Duracion: %d\n", temp->T.TareaID, temp->T.Descripcion, temp->T.Duracion);
                return;
            }
            temp = temp->Siguiente;
        }
    }
    else
    {
        while (temp != NULL)
        {
            if (strstr(temp->T.Descripcion, palabraID) != NULL)
            {
                printf("Tarea Pendiente - ID: %d | Descripcion: %s | Duracion: %d\n", temp->T.TareaID, temp->T.Descripcion, temp->T.Duracion);
                return;
            }
            temp = temp->Siguiente;
        }
    }

    temp = realizadas;
    if (esNumero(palabraID))
    {
        int id = atoi(palabraID);
        while (temp != NULL)
        {
            if (temp->T.TareaID == id)
            {
                printf("Tarea Realizada - ID: %d | Descripcion: %s | Duracion: %d\n", temp->T.TareaID, temp->T.Descripcion, temp->T.Duracion);
                return;
            }
            temp = temp->Siguiente;
        }
    }
    else
    {
        while (temp != NULL)
        {
            if (strstr(temp->T.Descripcion, palabraID) != NULL)
            {
                printf("Tarea Realizada - ID: %d | Descripcion: %s | Duracion: %d\n", temp->T.TareaID, temp->T.Descripcion, temp->T.Duracion);
                return;
            }
            temp = temp->Siguiente;
        }
    }

    printf("Tarea no encontrada.\n");
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
    Nodo *realizadas = crearListaVacia();
    int opcion;

    do
    {
        printf("\nMenu:\n");
        printf("1. Agregar tarea\n");
        printf("2. Ver tareas pendientes\n");
        printf("3. Ver tareas realizadas\n");
        printf("4. Marcar tarea como realizada\n");
        printf("5. Consultar tarea por ID o palabra clave\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            AgregarTarea(&pendientes, &idActual); 
            break;
        case 2:
            printf("Tareas pendientes:\n");
            MostrarLista(pendientes); 
            break;
        case 3:
            printf("Tareas realizadas:\n");
            MostrarLista(realizadas); 
            break;
        case 4:
        {
            int id;
            printf("Ingrese el ID de la tarea a marcar como realizada: ");
            scanf("%d", &id);
            MarcarTareaComoRealizada(&pendientes, &realizadas, id); 
            break;
        }
        case 5:
            ConsultarTarea(pendientes, realizadas); 
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida.\n");
            break;
        }
    } while (opcion != 0);

    
    Nodo *aux;
    while (pendientes != NULL)
    {
        aux = pendientes;
        pendientes = pendientes->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }

    while (realizadas != NULL)
    {
        aux = realizadas;
        realizadas = realizadas->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }

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
