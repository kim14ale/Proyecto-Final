#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE_PRODUCTO 50


void cargarDatos();

void actualizarArchivo(const char* archivoNombre, const char* modo, void (*escribirDatos)());


void escribirProductos();

void escribirClientes();

void escribirFacturas();
void ingresarProducto();

void modificarProducto();

void eliminarProducto();

void listarProductos();
void ingresarCliente();
void modificarCliente();

void listarClientes();
void facturar();
void listarFacturas();