#include <stdio.h>
#include <string.h>
#include "Lecturas.h"
#include "Operaciones.h"

int main() {
    int opcion;
    cargarDatos();

    do {
        printf("\nBienvenido a InventEdu\n");
        printf("Menu Principal:\n");
        printf("1. Productos\n");
        printf("2. Clientes\n");
        printf("3. Facturar\n");
        printf("0. Salir\n");
        opcion = leerEnteroEntre("Ingrese una opcion: ", 0, 3);

        switch (opcion) {
            case 1: {
                int subopcion;
                do {
                    printf("\nMenu Productos:\n");
                    printf("1. Ingresar Producto\n");
                    printf("2. Modificar Producto\n");
                    printf("3. Eliminar Producto\n");
                    printf("4. Listar Productos\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 4);

                    switch (subopcion) {
                        case 1:
                            ingresarProducto();
                            break;
                        case 2:
                            modificarProducto();
                            break;
                        case 3:
                            eliminarProducto();
                            break;
                        case 4:
                            listarProductos();
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 2: {
                int subopcion;
                do {
                    printf("\nMenu Clientes:\n");
                    printf("1. Ingresar Cliente\n");
                    printf("2. Modificar Cliente\n");
                    printf("3. Listar Clientes\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 3);

                    switch (subopcion) {
                        case 1:
                            ingresarCliente();
                            break;
                        case 2:
                            modificarCliente();
                            break;
                        case 3:
                            listarClientes();
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 3: {
                int subopcion;
                do {
                    printf("\nMenu Facturacion:\n");
                    printf("1. Facturar\n");
                    printf("2. Listar Facturas\n");
                    printf("0. Regresar al Menu Principal\n");
                    subopcion = leerEnteroEntre("Ingrese una opcion: ", 0, 2);

                    switch (subopcion) {
                        case 1:
                            facturar();
                            break;
                        case 2:
                            listarFacturas();
                            break;
                        case 0:
                            printf("Regresando al Menu Principal...\n");
                            break;
                        default:
                            printf("Opcion no valida.\n");
                    }
                } while (subopcion != 0);
                break;
            }
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}
