#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
 
using namespace std;
 
// Estructura para representar un movimiento
struct Movimiento
{
 
};
 
 
struct Pesos{
int pesos_ingresados;
int pesos_retirados;
 
 
};
 
struct Dolares
{
    int dolares_vendidos;
    int dolares_comprados;
 
};
 
// Estructura para representar un plazo fijo
struct PlazoFijo
{
int dinero;
int dias;
int obtenido;
};
 
// Estructura para representar una cuenta bancaria
struct Cuenta
{
    // Datos de la cuenta bancaria
    string nombre;
    int saldo;
    int dolares;
    string contra;
    vector <Dolares> dolare;
    vector <Pesos> peso;
    vector<Movimiento> movimientos;
    vector<PlazoFijo> plazos_fijos;
    vector<int> prestamos= {0,0,0};
    
};
 
 
// Función para mostrar el menú principal
void menu_principal(Cuenta usuario)
{
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nombre << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo << endl;
    cout << "Dólares: USD$ " << usuario.dolares << endl;
    cout << "Plazos fijos armados: " << usuario.plazos_fijos.size() << endl;
    cout << endl;
    cout << "1 - Ingresar efectivo." << endl;
    cout << "2 - Retirar efectivo." << endl;
    cout << "3 - Comprar y/o vender dólares." << endl;
    cout << "4 - Retirar dólares." << endl;
    cout << "5 - Armar plazo fijo." << endl;
    cout << "6 - Cancelar plazo fijo." << endl;
    cout << "7 - Pedir préstamo." << endl;
    cout << "8 - Ver movimientos." << endl;
    cout << "9 - Actualizar datos." << endl;
    cout << "10 - Salir del sistema." << endl;
    cout << endl;
    cout << "Elegir una opcion del menú: " << endl;
}
 
bool registrate(vector<Cuenta> &usuarios) {
    Cuenta usuario;
    cout << "Ingresa tu nombre: ";
    getline(cin, usuario.nombre);
    cout << "Ingresa tu contraseña: ";
    getline(cin, usuario.contra);

    usuario.saldo = 0;
    usuario.dolares = 0;

    usuarios.push_back(usuario);

    ofstream archivo;
    archivo.open("./tpbanco.txt", ios::app); 
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar los datos." << endl;
        return false;
    }

    // Escribir los datos del usuario en el archivo con el formato solicitado
    archivo << usuario.nombre << endl;
    archivo << usuario.contra << endl;
    archivo << "," << usuario.saldo << endl;
    archivo << "," << usuario.dolares << endl;
    archivo << ",0" << endl; // Se asume que no tiene plazos fijos al inicio
    archivo << "." << endl; // Separador entre usuarios
    archivo.close();

    cout << "Registro exitoso. Usuario guardado en el sistema." << endl;
    return true;
}
 

bool ingresar_datos(vector<Cuenta>& usuarios) {
    Cuenta usuario;
    ifstream archivo;
    int intentos = 0;
    string linea, nombre, contra;
    bool encontrado = false;

    archivo.open("./tpbanco.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    while (intentos < 4 && !encontrado) { // Intentos hasta 4
        cout << "Intento " << intentos + 1 << " de 4." << endl;

        cout << "Ingrese el nombre del usuario: ";
        getline(cin, nombre);
        cout << "Ingrese su contraseña: ";
        getline(cin, contra);

        // Reiniciar la lectura del archivo
        archivo.clear();
        archivo.seekg(0, ios::beg);

        while (getline(archivo, linea)) {
            if (linea == nombre) {
                getline(archivo, linea);
                if (linea == contra) {
                    encontrado = true;
                    usuario.nombre = nombre;
                    usuario.contra = contra;

                    // Leer saldo
                    getline(archivo, linea);
                    usuario.saldo = stoi(linea.substr(1)); 
                    // Leer dólares
                    getline(archivo, linea);
                    usuario.dolares = stoi(linea.substr(1)); 

                    usuarios.push_back(usuario);

                    cout << "Inicio de sesión exitoso. Bienvenido/a, " << usuario.nombre << "." << endl;
                    break;
                }
            }
        }

        if (!encontrado) {
            intentos++;
            if (intentos < 4) {
                cout << "Usuario o contraseña incorrectos. Intenta de nuevo." << endl;
            } else {
                cout << "Has agotado todos los intentos." << endl;
            }
        }
    }


    if (!encontrado) {
        cout << "Usuario o contraseña incorrectos. Registrate ";
       
            registrate(usuarios);
            return true;
    }
        
     
        archivo.close();

return true;
}
    
 
// 1
void ingresar_efectivo(Cuenta &usuario, int opcion, vector <Pesos> &peso) {
Pesos pesos;
int dinero;
cout<<"Ingrese la cantidad de dinero que quiere depositar: "<<endl;
cin>>dinero;
usuario.saldo+=dinero;
cout<<"El dinero actual en la cuenta es: "<<usuario.saldo<<endl;
pesos.pesos_ingresados=dinero;
usuario.peso.push_back(pesos);

}
// 2
void retirar_efectivo(Cuenta &usuario, int opcion, vector <Pesos> &peso) {
    Pesos pesos;
    int retirar;
    int billetesmil=0;
    int billetesquinientos=0;
    int billetesdoscientos=0;
    int billetescien=0;
    
    cout<<"Ingrese la cantidad de dinero que quiere retirar"<<endl;
    cin>>retirar;
    while(retirar%100!=0 or retirar>usuario.saldo ){
        cout<<"El monto ingresado no es valido,  que sea multiplo de cien, ingrese otro monto "<<endl;
        cin>>retirar;
 
    }
    pesos.pesos_retirados=retirar;
    usuario.peso.push_back(pesos);
    usuario.saldo-=retirar;
    while(retirar>=1000){
        retirar-=1000;
        billetesmil++;
    }
    while(retirar>=500){
        retirar-=500;
        billetesquinientos++;
    }
    while(retirar>=200){
        retirar-=200;
        billetesdoscientos++;
    }
    while(retirar>=100){
        retirar-=100;
        billetescien++;
    }
 
    cout << "Al usuario se le ha dado:" << endl;
    cout << "Billetes de mil: " << billetesmil<< endl;
    cout << "billetes de quinientos: " << billetesquinientos << endl;
    cout << "billetes de doscientos: " << billetesdoscientos << endl;
    cout << "billetes de cien: " << billetescien << endl;
    cout << "-----------------------------" << endl;
    
    
}
// 3
void manejar_dolares(Cuenta &usuario, int opcion, vector <Dolares> dolare) {
    Dolares dolar;
    int op;
    cout<<"ingrese 1 para comprar dolares y 2 para vender"<<endl;
    cout<<"Opcion: ";
    cin>>op;
   
    if(op==1){
        cout<<"ingrese el monto en dolares que quiere comprar en dolares"<<endl;
        int monto_a_comprar;
        cin>>monto_a_comprar;
        monto_a_comprar=monto_a_comprar*1000;
        while(monto_a_comprar>usuario.saldo){
            cout<<"monto invalido, su saldo es insuficiente. Ingrese un monto valido"<<endl;
            cin>>monto_a_comprar;
            monto_a_comprar=monto_a_comprar*1000;
 
        }
 
        usuario.saldo-=monto_a_comprar;
        usuario.dolares+=monto_a_comprar/1000;
        cout<<"saldo en pesos: "<<usuario.saldo<<endl;
        cout<<"saldo en dolares: "<<usuario.dolares<<endl;
        dolar.dolares_comprados=monto_a_comprar/1000;
        usuario.dolare.push_back(dolar);
    }
    
    if(op==2){
        if(usuario.dolares<=10){
            cout<<"usted no puede vender dolares"<<endl;
        }
        int monto_a_vender;
        cout<<"ingrese el monto en dolares que quiere vender"<<endl;
        cin>>monto_a_vender;
         while(monto_a_vender>usuario.dolares){
            cout<<"monto invalido, su saldo es insuficiente. Ingrese un monto valido"<<endl;
            cin>>monto_a_vender;
        }
 
        cout<<"la cantidad de pesos de tu transaccion es de: "<<monto_a_vender*1000<<endl;
        usuario.saldo+=monto_a_vender*1000;
        usuario.dolares-=monto_a_vender;
        dolar.dolares_vendidos=monto_a_vender;
        usuario.dolare.push_back(dolar);
 
    }
}
// 4
void retirar_dolares(Cuenta &usuario, int opcion) {
    int retirar;
    int billetescien=0;
    int billetescincuenta=0;
    int billetesveinte=0;
    int billetesdiez=0;
    
    cout<<"Ingrese la cantidad de dolares que quiere retirar"<<endl;
    cin>>retirar;
    while(retirar%10!=0 or retirar>usuario.dolares ){
        cout<<"El monto ingresado no es valido, ingrese otro monto"<<endl;
        cin>>retirar;
 
    }
    usuario.dolares-=retirar;
    while(retirar>=100){
        retirar-=100;
        billetescien++;
    }
    while(retirar>=50){
        retirar-=50;
        billetescincuenta++;
    }
    while(retirar>=20){
        retirar-=20;
        billetesveinte++;
    }
    while(retirar>=10){
        retirar-=10;
        billetesdiez++;
    }
 
    cout << "Al usuario se le ha dado:" << endl;
    cout << "Billetes de cien: " << billetescien<< endl;
    cout << "billetes de cincuenta: " << billetescincuenta << endl;
    cout << "billetes de veinte: " << billetesveinte << endl;
    cout << "billetes de diez: " << billetesdiez << endl;
    cout << "-----------------------------" << endl;
    
    
    }
 
 
// 5
void armar_plazo_fijo(Cuenta &usuario, int opcion, vector<PlazoFijo> &plazos_fijos) {
    PlazoFijo plazo;
    int invertir;
    int dias;
    float interes;
    int pesos;
    cout<<"Ingrese la cantidad de dinero que quiere invertir: "<<endl;
    cin>>invertir;
    while(invertir>=usuario.saldo){
        cout<<"El monto ingresado no es valido, ingrese otro monto"<<endl;
        cin>>invertir;
    }
    cout<<"Ingrese la cantidad de dias que va a estar en el plazo fijo: "<<endl;
    cin>>dias;
    while(dias<30){
        cout<<"Ingrese una cantidad de dias correcta (mayor a 30)"<<endl;
        cin>>dias;
    }
 
    interes=(invertir*dias*70)/36500;
    pesos=(invertir+interes);
    usuario.saldo-=invertir;
    cout << "Has invertido: " <<invertir<< endl;
    cout << "Dias ingresado: " << dias<< endl;
    cout << "Vas a obtener: " << pesos << endl;
    cout<<"El dinero actual en la cuenta es: "<<usuario.saldo<<endl;
    cout << "-----------------------------" << endl;
 
    plazo.dinero=invertir;
    plazo.dias=dias;
    plazo.obtenido=pesos;
    usuario.plazos_fijos.push_back(plazo);
 
 
 
}
// 6
void cancelar_plazo_fijo(Cuenta &usuario, int opcion, vector<PlazoFijo> &plazos_fijos) {
    int seleccion;
    while(usuario.plazos_fijos.size()==0)
    {
        cout<<"No tienes ningun plazo fijo armado"<<endl;
        return;
    }
 
 
    cout<<"Tienes "<<usuario.plazos_fijos.size()<<" plazos fijos, a cual quiere ingresar"<<endl;
    cin>>seleccion;
    seleccion--;
   
     while(plazos_fijos.size()>seleccion){
        cout<<"ingrese un numero menor, no tienes tantos plazos fijos"<<endl;
        cin>>seleccion;
    }
    cout<<"En este plazo fijo depositaste "<<usuario.plazos_fijos[seleccion].dinero<<endl;
    cout<<"Este plazo fijo dura "<<usuario.plazos_fijos[seleccion].dias<<" dias"<<endl;
    cout<<"Este plazo fijo te devolvera $"<<usuario.plazos_fijos[seleccion].obtenido<<endl;
 
    string op;
    cout<<"quiere cancelar un plazo fijo? (si/no)"<<endl;
    cin>>op;
    cout<<endl;
    if(op=="si"){
        int seleccion;
        cout<<"cual quiere cancelar?"<<endl;
        cin>>seleccion;
        seleccion--;
        while(plazos_fijos.size()>seleccion){
        cout<<"ingrese un numero menor, no tienes tantos plazos fijos"<<endl;
        cin>>seleccion;
    }
        usuario.saldo+=usuario.plazos_fijos[seleccion].dinero;
        usuario.plazos_fijos.erase(usuario.plazos_fijos.begin()+seleccion);
        return;
    }
    else{
        return;
    }
 
}
// 7
void pedir_prestamo(Cuenta &usuario, int opcion) {
    int op;
    int porciento;
    cout<< "1 - 5%." << endl;
    cout<< "2 - 10%" << endl;
    cout<< "3 - 15%" << endl;
    cout<<"Seleccione la opcion de prestamo"<<endl;
    cin>>op;
    while(op>3 or op<1){
        cout<<"Seleccione una opcion valida"<<endl;
        cin>>op;
    }
 
    switch (op)
    {
        case 1:
            if(usuario.saldo>20000){
                porciento=usuario.saldo*0.05;
                usuario.saldo+=porciento;
                usuario.prestamos[0]++;  
                return;
            }
            else{
                cout<<"No tiene el dinero suficiente"<<endl;
                return;
            }
            break;
        case 2:
            if(usuario.saldo>50000){
                porciento=usuario.saldo*0.10;
                usuario.saldo+=porciento;
                usuario.prestamos[1]++;  
                return;
            }
            else{
                cout<<"No tiene el dinero suficiente"<<endl;
                return;
            }
            break;
        case 3:
            if(usuario.saldo>100000){
                porciento=usuario.saldo*0.15;
                usuario.saldo+=porciento;
                usuario.prestamos[2]++;  
                return;
            }
            else{
                cout<<"No tiene el dinero suficiente"<<endl;
                return;
            }
            break;
    }
}
// 8
void ver_movimientos(Cuenta usuario, int opcion, vector <Dolares> dolare, vector <Pesos> peso, vector<PlazoFijo> &plazos_fijos) {
    cout<<"Menu de movimientos"<<endl;
    cout<<"1 - Prestamos"<<endl;
    cout<<"2 - Movimiento de dolares"<<endl;
    cout<<"3 - Movimiento de pesos "<<endl;
    cout<<"4 - Movimiento de plazo fijo"<<endl;
    
    int op;
    cout<<"seleccione una opcion"<<endl;
    cin>>op;
    switch(op) {
        case 1:
            cout << "Prestamos del 5% realizados: " << usuario.prestamos[0] << endl;
            cout << "Prestamos del 10% realizados: " << usuario.prestamos[1] << endl;
            cout << "Prestamos del 15% realizados: " << usuario.prestamos[2] << endl;
            break;
              
        case 2:
            for (const auto& dolar : usuario.dolare) {
                if (dolar.dolares_comprados > 0) {
                    cout << "Dolares comprados: US$" << dolar.dolares_comprados << endl;
                }
                if (dolar.dolares_vendidos > 0) {
                    cout << "Dolares vendidos: US$" << dolar.dolares_vendidos << endl;
                }
            }
            break;
 
        case 3:
            for (const auto& pesoe : usuario.peso) {
                if (pesoe.pesos_ingresados > 0) {
                    cout << "Pesos ingresados: $" << pesoe.pesos_ingresados << endl;
                }
                if (pesoe.pesos_retirados > 0) {
                    cout << "Pesos retirados: $" << pesoe.pesos_retirados << endl;
                }
            }
            break;
 
        case 4:
            if(usuario.plazos_fijos.empty()) {
                cout<<"No tienes ningun plazo fijo armado"<<endl;
                break;
            }
 
            cout<<"Tienes "<<usuario.plazos_fijos.size()<<" plazos fijos"<<endl;
            for(size_t i = 0; i < usuario.plazos_fijos.size(); ++i) {
                cout << "Plazo fijo " << i+1 << ":" << endl;
                cout << "Dinero depositado: $" << usuario.plazos_fijos[i].dinero << endl;
                cout << "Dias: " << usuario.plazos_fijos[i].dias << endl;
                cout << "Total a obtener: $" << usuario.plazos_fijos[i].obtenido << endl;
                cout << "-----------------------------" << endl;
            }
            break;
 
        default:
            cout << "Opcion invalida" << endl;
            break;
    }
}
 
// 9
void actualizar_datos(Cuenta &usuario, int opcion) {
    int op;
    string cambio;
    string nueva;
    string vieja;
    string nueva2;
    string contra;
    cout<<"Ingrese el dato que quiere modificar"<<endl;
    cout<<"1- Contraseña"<<endl;
    cout<<"2- Nombre"<<endl;
    cin>>op;
    while(op>2 or op<1){
        cout<<"Ingrese una opcion valida"<<endl;
        cin>>op;
    }
 
     switch (op)
        {
        case 1:
            cout<<"Ingrese la contraseña actual"<<endl;
            cin>>vieja;
            while(vieja!=usuario.contra){
                cout<<"Incorrecta, vuelva a ingresarla"<<endl;
                cin>>vieja;
            }
            cout<<"Correcto, ponga la nueva contraseña"<<endl;
            cin>>nueva;
                
            cout<<"Repita la contraseña"<<endl;
            cin>>nueva2;
            while(nueva2!=nueva){
                cout<<"No son iguales, vuelva a copiarla"<<endl;
                cin>>nueva2;
            }
                usuario.contra=nueva;
                cout<<"Contraseña restablecida"<<endl;
            break;
            
           
        case 2:
            cout<<"Ingrese la contraseña"<<endl;
            cin>>contra;
            while(contra!=usuario.contra){
                cout<<"Contraseña incorrecta, ingresela de nuevo"<<endl;
                cin>>contra;
            }
            cout<<"Ingrese el nuevo nombre"<<endl;
            cin>>cambio;
            usuario.nombre=cambio;
            cout<<"Nombre reestablecido"<<endl;
            break;
}
}
 


void sobrescribir_datos_usuario(Cuenta usuario) {
    ifstream archivo_entrada("./tpbanco.txt");
    ofstream archivo_temporal("./tpbanco_temp.txt");

    if (!archivo_entrada.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!archivo_temporal.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivo_entrada, linea)) {
        if (linea == usuario.nombre) {
            archivo_temporal << usuario.nombre << endl;
            archivo_temporal << usuario.contra << endl;
            archivo_temporal << "," << usuario.saldo << endl;
            archivo_temporal << "," << usuario.dolares << endl;
            archivo_temporal << "," <<usuario.plazos_fijos.size()<< endl; 
            archivo_temporal << "." << endl;

            // Saltamos las siguientes 5 líneas del archivo original (datos del usuario actual)
            for (int i = 0; i < 5; ++i) {
                getline(archivo_entrada, linea);
            }

            encontrado = true;
        } else {
            // Escribimos la línea tal cual en el archivo temporal
            archivo_temporal << linea << endl;
        }
    }

    archivo_entrada.close();
    archivo_temporal.close();

    if (encontrado) {
        // Reemplazamos el archivo original con el temporal
        remove("./tpbanco.txt");
        rename("./tpbanco_temp.txt", "./tpbanco.txt");
        cout << "Datos del usuario actualizados con éxito." << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("./tpbanco_temp.txt");
        cout << "Usuario no encontrado." << endl;
    }
}

int main()
 
{
    ifstream archivo;
    vector <Pesos> peso;
    vector <Dolares> dolare;
    vector <Cuenta> usuarios;
    vector <PlazoFijo> plazos_fijos;
    Cuenta usuario;
    int opcion = 0;
 
    if(ingresar_datos(usuarios) or registrate(usuarios)){
    while (opcion != 10)
    {
        menu_principal(usuarios[0]);
        cin >> opcion;
 
        switch (opcion)
        {
        case 1:
            ingresar_efectivo(usuarios[0], opcion, peso);
            break;
        case 2:
            retirar_efectivo(usuarios[0], opcion, peso);
            break;
        case 3:
            manejar_dolares(usuarios[0], opcion,dolare);
            break;
        case 4:
            retirar_dolares(usuarios[0], opcion);
            break;
        case 5:
            armar_plazo_fijo(usuarios[0], opcion,plazos_fijos);
            break;
        case 6:
            cancelar_plazo_fijo(usuarios[0], opcion, plazos_fijos);
            break;
        case 7:
            pedir_prestamo(usuarios[0], opcion);
            break;
        case 8:
            ver_movimientos(usuarios[0], opcion, dolare, peso,plazos_fijos);
            break;
        case 9:
            actualizar_datos(usuarios[0], opcion);
            break;
        case 10:
            cout << "Gracias por utilizar nuestro sistema " << usuario.nombre << ", vuelva pronto." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    }
    }
  
    sobrescribir_datos_usuario(usuarios[0]);


    return 0;
}