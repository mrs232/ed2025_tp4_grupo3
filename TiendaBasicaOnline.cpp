//Tienda Basica Online
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- Declaraciones anticipadas ---
// Las clases Cliente, Producto, Pedido y Carrito se declaran aquí para que puedan ser referenciadas entre sí.
class Producto;
class Pedido;

// --- Clase Producto ---
// Define los datos básicos de un producto.
class Producto {
private:
    string nombre;
    float precio;
    string codigo;
    int stock;

public:
    // Constructor
    Producto(string nombre, float precio, string codigo, int stock) {
        this->nombre = nombre;
        this->precio = precio;
        this->codigo = codigo;
        this->stock = stock;
    }

    // Getters
    string getNombre() { return nombre; }
    float getPrecio() { return precio; }
    string getCodigo() { return codigo; }
    int getStock() { return stock; }

    // Setters
    void setNombre(string nombre) { this->nombre = nombre; }
    void setPrecio(float precio) { this->precio = precio; }
    void setCodigo(string codigo) { this->codigo = codigo; }
    void setStock(int stock) { this->stock = stock; }
};
class ProductoFisico : public Producto {
private:
    float peso; // en kilogramos

public:
    ProductoFisico(string nombre, float precio, string codigo, int stock, float peso)
        : Producto(nombre, precio, codigo, stock) {
        this->peso = peso;
    }

    float getPeso() { return peso; }
    void setPeso(float peso) { this->peso = peso; }
};

class ProductoDigital : public Producto {
private:
    float tamanoArchivo; // en MB

public:
    ProductoDigital(string nombre, float precio, string codigo, int stock, float tamanoArchivo)
        : Producto(nombre, precio, codigo, stock) {
        this->tamanoArchivo = tamanoArchivo;
    }

    float getTamanoArchivo() { return tamanoArchivo; }
    void setTamanoArchivo(float tamano) { this->tamanoArchivo = tamano; }
};
// --- Clase Pedido ---
// Define los datos de un pedido realizado.
class Pedido {
private:
    vector<Producto> productosComprados; // Un conjunto de productos.
    float montoTotal;

public:
    // Constructor por defecto
    Pedido() {
        productosComprados = {};
        montoTotal = 0.0;
    }
    // Constructor
    Pedido(vector<Producto> productosComprados, float montoTotal) {
        this->productosComprados = productosComprados;
        this->montoTotal = montoTotal;
    }
    // Mostrar resumen del pedido
    void mostrarResumen() {
        cout << "Resumen del Pedido:" << endl;
        for(int i=0; i<productosComprados.size(); i++) {
            cout << "Producto: " << productosComprados[i].getNombre() << endl;
            cout << "Precio: $" << productosComprados[i].getPrecio() << endl;
            cout << "Codigo: " << productosComprados[i].getCodigo() << endl;
            cout << "Stock: " << productosComprados[i].getStock() << endl;
            cout << "------------------------" << endl;
        }
        cout << "Monto Total: $" << montoTotal << endl;
    }

    // Getters
    vector<Producto> getProductosComprados() { return productosComprados; }
    float getMontoTotal() { return montoTotal; }

    // Setters
    void setProductosComprados(vector<Producto> productos) { this->productosComprados = productos; }
    void setMontoTotal(float monto) { this->montoTotal = monto; }
};

// --- Clase Cliente ---
// Define los datos de un cliente.
class Cliente {
private:
    string nombre;
    string idCliente; // Se usa string por flexibilidad.
    vector<Pedido> historialCompras; // Lista de pedidos anteriores.

public:
    // Constructor
    Cliente(string nombre, string idCliente) {
        this->nombre = nombre;
        this->idCliente = idCliente;
    }

    // Getters
    string getNombre() { return nombre; }
    string getIdCliente() { return idCliente; }
    vector<Pedido> getHistorialCompras() { return historialCompras; }

    // Setters
    void setNombre(string nombre) { this->nombre = nombre; }
    void setIdCliente(string id) { this->idCliente = id; }
    void setHistorialCompras(vector<Pedido> historial) { this->historialCompras = historial; }
};

// --- Clase Carrito ---
// Define los datos del carrito de compras.
class Carrito {
private:
    vector<Producto> productosAnadidos; // Productos que el cliente ha agregado.

public:
    // Constructor
    Carrito(vector<Producto> productosAnadidos) {
        this->productosAnadidos = productosAnadidos;
    }
   // Agregar producto al carrito
    void anadirProducto(Producto producto) {
        productosAnadidos.push_back(producto);
    }

    // Eliminar producto del carrito
    void eliminarProducto(string codigo) {
        for (auto it = productosAnadidos.begin(); it != productosAnadidos.end(); ++it) {
            if (it->getCodigo() == codigo) {
                productosAnadidos.erase(it);
                break;
            }
        }
    }

    // Getters
    vector<Producto> getProductosAnadidos() { return productosAnadidos; }

    // Setters
    void setProductosAnadidos(vector<Producto> productos) { this->productosAnadidos = productos; }
};

//Cosas marcos,franco y victor

// --- TDA Cola para pedidos ---
class NodoPedido {
public:
    Pedido pedido;
    NodoPedido* siguiente;

    NodoPedido(Pedido pedido) {
        this->pedido = pedido;
        this->siguiente = nullptr;
    }
};

class ColaPedidos {
private:
    NodoPedido* frente;
    NodoPedido* final;

public:
    ColaPedidos() {
        frente = nullptr;
        final = nullptr;
    }

    void encolar(Pedido pedido) {
        NodoPedido* nuevo = new NodoPedido(pedido);
        if (final == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    void mostrarPedidos() {
        NodoPedido* actual = frente;
        int i = 1;
        while (actual != nullptr) {
            cout << "\nPedido #" << i++ << ":" << endl;
            actual->pedido.mostrarResumen();
            actual = actual->siguiente;
        }
        if (frente == nullptr) {
            cout << "No hay pedidos en la cola." << endl;
        }
    }
};

//main
int main() {
    ProductoFisico libro("Libro C++", 30.0, "P001", 10, 1.2);
    ProductoDigital curso("Curso C++ Online", 20.0, "P002", 100, 500);
    ProductoFisico mouse("Mouse Gamer", 25.0, "P003", 8, 0.3);
    ProductoDigital app("App Premium", 15.0, "P004", 50, 150);

    vector<Producto> catalogo = {libro, curso, mouse, app};
    Cliente cliente("Juan", "C001");
    Carrito carrito(vector<Producto>{});
    ColaPedidos cola;

    int opcion;
    do {
        cout << "\n--- MENU TIENDA ONLINE ---" << endl;
        cout << "1. Ver productos" << endl;
        cout << "2. Agregar producto al carrito" << endl;
        cout << "3. Eliminar producto del carrito" << endl;
        cout << "4. Ver carrito" << endl;
        cout << "5. Confirmar pedido" << endl;
        cout << "6. Ver historial de pedidos" << endl;
        cout << "0. Salir" << endl;
        cout << "OpciÃ³n: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n--- Productos Disponibles ---" << endl;
            for (Producto& p : catalogo) {
                cout << "Nombre: " << p.getNombre()
                     << " | CÃ³digo: " << p.getCodigo()
                     << " | Precio: $" << p.getPrecio()
                     << " | Stock: " << p.getStock() << endl;
            }
        } else if (opcion == 2) {
            string cod;
            cout << "CÃ³digo del producto a agregar: ";
            cin >> cod;
            bool encontrado = false;
            for (Producto& p : catalogo) {
                if (p.getCodigo() == cod) {
                    carrito.anadirProducto(p);
                    cout << "Producto agregado." << endl;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) cout << "CÃ³digo no encontrado." << endl;
        } else if (opcion == 3) {
            string cod;
            cout << "CÃ³digo del producto a eliminar: ";
            cin >> cod;
            carrito.eliminarProducto(cod);
            cout << "Producto eliminado (si estaba)." << endl;
        } else if (opcion == 4) {
            vector<Producto> productos = carrito.getProductosAnadidos();
            cout << "\n--- Carrito Actual ---" << endl;
            if (productos.empty()) {
                cout << "El carrito estÃ¡ vacÃ­o." << endl;
            } else {
                for (Producto& p : productos) {
                    cout << "Producto: " << p.getNombre()
                         << " | CÃ³digo: " << p.getCodigo()
                         << " | Precio: $" << p.getPrecio() << endl;
                }
            }
        } else if (opcion == 5) {
            vector<Producto> productos = carrito.getProductosAnadidos();
            if (productos.empty()) {
                cout << "El carrito estÃ¡ vacÃ­o. No se puede confirmar." << endl;
            } else {
                float total = 0;
                for (Producto& p : productos) {
                    total += p.getPrecio();
                }
                Pedido nuevoPedido(productos, total);
                cliente.getHistorialCompras().push_back(nuevoPedido);
                cola.encolar(nuevoPedido);
                cout << "\nPedido confirmado. Detalles:" << endl;
                nuevoPedido.mostrarResumen();
                carrito.setProductosAnadidos({});
            }
        } else if (opcion == 6) {
            cout << "\n--- Pedidos realizados (en cola) ---" << endl;
            cola.mostrarPedidos();
        } else if (opcion == 0) {
            cout << "Saliendo del sistema." << endl;
        } else {
            cout << "OpciÃ³n invÃ¡lida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
