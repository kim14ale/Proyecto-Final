#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lecturas.h"
#include "Operaciones.h"


#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE_PRODUCTO 50


char nombres_productos[MAX_PRODUCTOS][MAX_NOMBRE_PRODUCTO];
int cantidades_productos[MAX_PRODUCTOS];
float precios_productos[MAX_PRODUCTOS];
int contador_productos = 0;

char cedulas_clientes[MAX_CLIENTES][11];
char nombres_clientes[MAX_CLIENTES][50];
int contador_clientes = 0;

char fechas_facturas[MAX_FACTURAS][11];
char cedulas_facturas[MAX_FACTURAS][11];
char nombres_facturas[MAX_FACTURAS][50];
int cantidades_factura[MAX_FACTURAS][MAX_PRODUCTOS];
float precios_factura[MAX_FACTURAS][MAX_PRODUCTOS];
int cantidad_detalles_factura[MAX_FACTURAS];
float valor_total_factura[MAX_FACTURAS];
int contador_facturas = 0;


void cargarDatos() {
    FILE *archivo;
    char nombre_producto[MAX_NOMBRE_PRODUCTO];
    int cantidad;
    float precio;

    
    archivo = fopen("productos.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %d %f", nombre_producto, &cantidad, &precio) == 3) {
            strcpy(nombres_productos[contador_productos], nombre_producto);
            cantidades_productos[contador_productos] = cantidad;
            precios_productos[contador_productos] = precio;
            contador_productos++;
        }
        fclose(archivo);
    }

    
    archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s", cedulas_clientes[contador_clientes], nombres_clientes[contador_clientes]) == 2) {
            contador_clientes++;
        }
        fclose(archivo);
    }

    
    archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s", fechas_facturas[contador_facturas], cedulas_facturas[contador_facturas], nombres_facturas[contador_facturas]) == 3) {
            int cantidad_detalles;
            fscanf(archivo, "%d", &cantidad_detalles);
            cantidad_detalles_factura[contador_facturas] = cantidad_detalles;
            for (int i = 0; i < cantidad_detalles; i++) {
                fscanf(archivo, "%d %f", &cantidades_factura[contador_facturas][i], &precios_factura[contador_facturas][i]);
            }
            fscanf(archivo, "%f", &valor_total_factura[contador_facturas]);
            contador_facturas++;
        }
        fclose(archivo);
    }
}

void actualizarArchivo(const char* archivoNombre, const char* modo, void (*escribirDatos)()) {
    FILE *archivo = fopen(archivoNombre, modo);
    if (archivo != NULL) {
        escribirDatos(archivo);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo %s\n", archivoNombre);
    }
}

void escribirProductos(FILE* archivo) {
    for (int i = 0; i < contador_productos; i++) {
        fprintf(archivo, "%s %d %.2f\n", nombres_productos[i], cantidades_productos[i], precios_productos[i]);
    }
}

void escribirClientes(FILE* archivo) {
    for (int i = 0; i < contador_clientes; i++) {
        fprintf(archivo, "%s %s\n", cedulas_clientes[i], nombres_clientes[i]);
    }
}

void escribirFacturas(FILE* archivo) {
    for (int i = 0; i < contador_facturas; i++) {
        fprintf(archivo, "%s %s %s\n", fechas_facturas[i], cedulas_facturas[i], nombres_facturas[i]);
        fprintf(archivo, "%d\n", cantidad_detalles_factura[i]);
        for (int j = 0; j < cantidad_detalles_factura[i]; j++) {
            fprintf(archivo, "%d %.2f\n", cantidades_factura[i][j], precios_factura[i][j]);
        }
        fprintf(archivo, "%.2f\n", valor_total_factura[i]);
    }
}


void ingresarProducto() {
    if (contador_productos >= MAX_FACTURAS) {
        printf("No se pueden agregar mas productos.\n");
        return;
    }

    char nombre[MAX_NOMBRE_PRODUCTO];
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);

    // Verifica que no exista otro producto con el mismo nombre
    for (int i = 0; i < contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            printf("El producto ya existe.\n");
            return;
        }
    }

    strcpy(nombres_productos[contador_productos], nombre);
    cantidades_productos[contador_productos] = leerEnteroPositivo("Ingrese la cantidad del producto: ");
    precios_productos[contador_productos] = leerFlotantePositivo("Ingrese el precio del producto: ");

    contador_productos++;
    printf("Producto agregado exitosamente.\n");
    actualizarArchivo("productos.txt", "w", escribirProductos);
}

void modificarProducto() {
    if (contador_productos == 0) {
        printf("No hay productos para modificar.\n");
        return;
    }

    char nombre[MAX_NOMBRE_PRODUCTO];
    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", nombre);

    for (int i = 0; i < contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            cantidades_productos[i] = leerEnteroPositivo("Ingrese la nueva cantidad del producto: ");
            precios_productos[i] = leerFlotantePositivo("Ingrese el nuevo precio del producto: ");
            printf("Producto modificado exitosamente.\n");
            actualizarArchivo("productos.txt", "w", escribirProductos);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    if (contador_productos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    char nombre[MAX_NOMBRE_PRODUCTO];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);

    for (int i = 0; i < contador_productos; i++) {
        if (strcmp(nombres_productos[i], nombre) == 0) {
            for (int j = i; j < contador_productos - 1; j++) {
                strcpy(nombres_productos[j], nombres_productos[j + 1]);
                cantidades_productos[j] = cantidades_productos[j + 1];
                precios_productos[j] = precios_productos[j + 1];
            }
            contador_productos--;
            printf("Producto eliminado exitosamente.\n");
            actualizarArchivo("productos.txt", "w", escribirProductos);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void listarProductos() {
    if (contador_productos == 0) {
        printf("No hay productos para mostrar.\n");
        return;
    }

    for (int i = 0; i < contador_productos; i++) {
        printf("Nombre: %s, Cantidad: %d, Precio: %.2f\n", nombres_productos[i], cantidades_productos[i], precios_productos[i]);
    }
}


void ingresarCliente() {
    if (contador_clientes >= MAX_FACTURAS) {
        printf("No se pueden agregar mas clientes.\n");
        return;
    }

    char cedula[11];
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula);

    
    if (strlen(cedula) != 10) {
        printf("La cedula debe tener 10 digitos.\n");
        return;
    }

    // Verificar que no exista otro cliente con la misma cédula
    for (int i = 0; i < contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula) == 0) {
            printf("El cliente ya existe.\n");
            return;
        }
    }

    strcpy(cedulas_clientes[contador_clientes], cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombres_clientes[contador_clientes]);

    contador_clientes++;
    printf("Cliente agregado exitosamente.\n");
    actualizarArchivo("clientes.txt", "w", escribirClientes);
}

void modificarCliente() {
    if (contador_clientes == 0) {
        printf("No hay clientes para modificar.\n");
        return;
    }

    char cedula[11];
    printf("Ingrese la cedula del cliente a modificar: ");
    scanf("%s", cedula);

    for (int i = 0; i < contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula) == 0) {
            printf("Ingrese el nuevo nombre del cliente: ");
            scanf("%s", nombres_clientes[i]);
            printf("Cliente modificado exitosamente.\n");
            actualizarArchivo("clientes.txt", "w", escribirClientes);
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void listarClientes() {
    if (contador_clientes == 0) {
        printf("No hay clientes para mostrar.\n");
        return;
    }

    for (int i = 0; i < contador_clientes; i++) {
        printf("Cedula: %s, Nombre: %s\n", cedulas_clientes[i], nombres_clientes[i]);
    }
}


void facturar() {
    if (contador_clientes == 0) {
        printf("No hay clientes para facturar.\n");
        return;
    }

    if (contador_productos == 0) {
        printf("No hay productos para facturar.\n");
        return;
    }

    char cedula_cliente[11];
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula_cliente);

    int cliente_encontrado = 0;
    char nombre_cliente[50];
    for (int i = 0; i < contador_clientes; i++) {
        if (strcmp(cedulas_clientes[i], cedula_cliente) == 0) {
            cliente_encontrado = 1;
            strcpy(nombre_cliente, nombres_clientes[i]);
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente no encontrado.\n");
        return;
    }

    char fecha[11];
    printf("Ingrese la fecha de la factura (dd/mm/aaaa): ");
    scanf("%s", fecha);

    if (contador_facturas >= MAX_FACTURAS) {
        printf("No se pueden agregar mas facturas.\n");
        return;
    }

    strcpy(nombres_facturas[contador_facturas], nombre_cliente);
    strcpy(cedulas_facturas[contador_facturas], cedula_cliente);
    strcpy(fechas_facturas[contador_facturas], fecha);

    int cantidad_productos_factura = 0;
    while (1) {
        printf("Desea ingresar un producto a la factura? (1. Si, 2. No): ");
        int continuar = leerEnteroEntre("Opcion: ", 1, 2);

        if (continuar == 2) {
            break;
        }

        if (cantidad_productos_factura >= MAX_PRODUCTOS) {
            printf("No se pueden agregar mas productos a la factura.\n");
            break;
        }

        printf("Ingrese el nombre del producto a facturar: ");
        char nombre_producto[MAX_NOMBRE_PRODUCTO];
        scanf("%s", nombre_producto);

        int producto_encontrado = 0;
        for (int i = 0; i < contador_productos; i++) {
            if (strcmp(nombres_productos[i], nombre_producto) == 0) {
                int cantidad_producto = leerEnteroPositivo("Cantidad: ");

                if (cantidad_producto > cantidades_productos[i]) {
                    printf("La cantidad solicitada supera el stock disponible.\n");
                } else {
                    cantidades_factura[contador_facturas][cantidad_productos_factura] = cantidad_producto;
                    precios_factura[contador_facturas][cantidad_productos_factura] = precios_productos[i];
                    cantidad_detalles_factura[contador_facturas] = cantidad_productos_factura + 1;
                    valor_total_factura[contador_facturas] += cantidad_producto * precios_productos[i];
                    cantidades_productos[i] -= cantidad_producto;
                    cantidad_productos_factura++;
                    producto_encontrado = 1;
                }
                break;
            }
        }

        if (!producto_encontrado) {
            printf("Producto no encontrado.\n");
        }
    }

    if (cantidad_productos_factura == 0) {
        printf("No se ingresaron productos para la factura.\n");
        return;
    }

    contador_facturas++;
    printf("Factura agregada exitosamente.\n");

    int ver_factura;
    printf("Desea ver la factura?\n1. Si\n2. No\nIngrese una opcion: ");
    ver_factura = leerEnteroEntre("Opcion: ", 1, 2);

    if (ver_factura == 1) {
        listarFacturas();
    }
    actualizarArchivo("facturas.txt", "w", escribirFacturas);
}

void listarFacturas() {
    if (contador_facturas == 0) {
        printf("No hay facturas para mostrar.\n");
        return;
    }

    for (int i = 0; i < contador_facturas; i++) {
        printf("\nFactura %d\n", i + 1);
        printf("Fecha: %s\n", fechas_facturas[i]);
        printf("Cedula: %s\n", cedulas_facturas[i]);
        printf("Nombre: %s\n", nombres_facturas[i]);

        
        printf("------------------------------------\n");
        printf("| Cantidad | Descripcion | Precio |\n");
        printf("------------------------------------\n");

        for (int j = 0; j < cantidad_detalles_factura[i]; j++) {
            printf("| %8d | %-10s | %6.2f |\n",
                   cantidades_factura[i][j],
                   nombres_productos[j],
                   precios_factura[i][j]);
        }

        printf("------------------------------------\n");
        printf("| Total           | %6.2f |\n", valor_total_factura[i]);
        printf("------------------------------------\n");
    }
}
