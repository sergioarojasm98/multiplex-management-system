#include <iostream>
#include <stdlib.h>
#include "compat.h"  // Cross-platform getch() + CLEAR_SCREEN()

using namespace std;

string fechaVenta[100000];
string fechaPersonas[100000];
int valorVenta[100000];
int numPersonas[100000];
int nVentas = 0;
int nPersonas = 0;

struct Sala
{
	int nfp, nfg, ncol;
	void imprimir()
	{
		cout << "Numero de filas preferenciales: " << nfp << endl;
		cout << "Numero de filas generales: " << nfg << endl;
		cout << "Numero de columnas: " << ncol << endl;
	}
};

struct Sillas
{
	int nfp, nfg, ncol;
	bool esReservada[200][200];
	void imprimir()
	{
		cout << "    ";
		for (int j = 1; j < ncol + 1; j++)
			if (j < 10)
				cout << " ";
			else
				cout << j / 10;
		cout << endl;
		cout << "    ";
		for (int j = 1; j < ncol + 1; j++)
			cout << j % 10;
		cout << endl;
		cout << "   +";
		for (int j = 1; j < ncol + 1; j++)
			cout << "-";
		cout << "+" << endl;
		for (int i = 1; i < nfp + 1; i++)
		{
			cout << (i < 10 ? " " : "") << i << " ";
			cout << "|";
			for (int j = 1; j < ncol + 1; j++)
				if (esReservada[i][j])
					cout << "X";
				else
					cout << ".";
			cout << "|" << endl;
		}
		cout << "   +";
		for (int j = 1; j < ncol + 1; j++)
			cout << "-";
		cout << "+" << endl;
		for (int i = 1; i < nfg + 1; i++)
		{
			cout << (i + nfp < 10 ? " " : "") << i + nfp << " ";
			cout << "|";
			for (int j = 1; j < ncol + 1; j++)
				if (esReservada[i + nfp][j])
					cout << "X";
				else
					cout << ".";
			cout << "|" << endl;
		}
		cout << "   +";
		for (int j = 1; j < ncol + 1; j++)
			cout << "-";
		cout << "+" << endl;

		cout << "    ";
		for (int j = 1; j <= (ncol - 8) / 2; j++)
			cout << " ";
		cout << "Pantalla" << endl;
	}
};

struct Peli
{
	string nombre;
	int duracion;
	string director;
	void imprimir()
	{

		cout << "Nombre: " << nombre << endl;
		cout << "Duracion: " << duracion << " minutos" << endl;
		cout << "Director: " << director << endl;
	}
};

struct Funcion
{
	string hora;
	int idSala;
	int idPeli;
	string formato;
	Sillas sillas;
	void imprimir()
	{
		cout << endl
			 << "Sala #: " << idSala + 1 << endl;
		cout << "---------" << endl;
		cout << "Pelicula # " << idPeli + 1 << endl;
		cout << "Hora: " << hora << endl;
		cout << "Formato: " << formato << endl;
	}
};

void mostrarPelis(Peli *peliculas, int &npelis)
{
	for (int i = 0; i < npelis; i++)
	{
		cout << endl
			 << "Pelicula #" << i + 1 << ": " << endl;
		cout << "------------" << endl;
		peliculas[i].imprimir();
	}
	cout << endl;
}

void mostrarPeliYFuncion1(Peli *peliculas, Funcion *funciones, int &nfunc, int &npelis)
{
	mostrarPelis(peliculas, npelis);
	int idPeli;
	bool a = true;
	while (a == true)
	{
		cout << "* Ingrese el numero de la pelicula que desea ver: ";
		cin >> idPeli;
		if (idPeli > 0 && idPeli <= npelis)
			a = false;
		else
			cout << "El numero de la pelicula debe estar entre 1 y " << npelis << "**" << endl;
	}
	idPeli--;
	for (int j = 0; j < nfunc; j++)
	{
		if (idPeli == funciones[j].idPeli)
		{
			cout << endl
				 << " >> FUNCION " << j + 1 << endl;
			cout << " ============" << endl;
			cout << "Pelicula #" << funciones[j].idPeli + 1 << " : " << peliculas[funciones[j].idPeli].nombre << endl;
			cout << "Sala #" << funciones[j].idSala + 1 << endl;
			cout << "Hora : " << funciones[j].hora << endl;
			cout << "Formato : " << funciones[j].formato << endl;
		}
	}
}
void mostrarPeliYFuncion2(Peli *peliculas, Funcion *funciones, int &nfunc, int &npelis)
{
	for (int j = 0; j < nfunc; j++)
	{
		cout << endl
			 << " >> FUNCION " << j + 1 << endl;
		cout << " ============" << endl;
		cout << "Pelicula #" << funciones[j].idPeli + 1 << " : " << peliculas[funciones[j].idPeli].nombre << endl;
		cout << "Sala #" << funciones[j].idSala + 1 << endl;
		cout << "Hora : " << funciones[j].hora << endl;
		cout << "Formato : " << funciones[j].formato << endl;
	}
}

void mostrarSalas(Sala *salas, int &nsalas)
{
	for (int i = 0; i < nsalas; i++)
	{
		cout << endl
			 << "Sala #" << i + 1 << ": " << endl;
		cout << "--------" << endl;
		salas[i].imprimir();
		cout << endl;
	}
}

void addSala(Sala *salas, int &nsalas)
{
	Sala s;
	cout << "Ingrese el numero de filas preferenciales: ";
	cin >> s.nfp;
	cout << "Ingrese el numero de filas generales: ";
	cin >> s.nfg;
	cout << "Ingrese el numero de columnas: ";
	cin >> s.ncol;
	salas[nsalas] = s;
	nsalas++;
	cout << endl
		 << " Sala agregada correctamente !! " << endl;
}

void remSala(Sala *salas, int &nsalas, Funcion *funciones, int &nfunc)
{

	mostrarSalas(salas, nsalas);
	int i, intentos = 0;
	bool a = true;
	while (a == true)
	{
		cout << endl
			 << "Ingrese la sala que quiere eliminar: ";
		cin >> i;
		i--;
		if (i < 0 || i >= nsalas)
		{
			if (intentos == 3)
				a = false;
			else
				cout << "**Esa sala no existe. Intentelo de nuevo**" << endl;
			intentos++;
		}
		else
			a = false;
	}
	for (int j = 0; j < nfunc; j++)
		if (funciones[j].idSala == i)
		{
			cout << endl
				 << "**NO se puede quitar la sala. Elimine primero la(s) funcion(es)**" << endl;
			return;
		}
	for (int j = i; j < nsalas - 1; j++)
		salas[j] = salas[j + 1];
	nsalas--;

	for (int j = 0; j < nfunc; j++)
		if (funciones[j].idSala > i)
			funciones[j].idSala--;
	cout << endl
		 << " Sala eliminada correctamente !! " << endl;
}

void ediSala(Sala *salas, int &nsalas, Funcion *funciones, int &nfunc)
{
	int idSala;
	bool a = true;
	mostrarSalas(salas, nsalas);
	while (a == true)
	{
		cout << endl
			 << "Ingrese el numero de la sala a editar: ";
		cin >> idSala;
		idSala--;
		if (idSala >= 0 && idSala < nsalas)
			a = false;
		else
			cout << endl
				 << "**El numero de la sala debe estar entre 1 y " << nsalas << "**" << endl
				 << endl;
	}
	int op;
	cout << endl
		 << "OPCIONES: " << endl;
	cout << "1. Modificar el numero de filas preferenciales de la sala #" << idSala + 1 << endl;
	cout << "2. Modificar el numero de filas generales de la sala #" << idSala + 1 << endl;
	cout << "3. Modificar el numero de columnas de la sala #" << idSala + 1 << endl;
	cout << "4. Volver" << endl
		 << endl;
	cout << "> Opcion: ";
	cin >> op;
	cout << endl;
	int num;
	if (op == 1)
	{
		cout << " >> Numero actual de filas preferenciales: " << salas[idSala].nfp << endl
			 << endl;
		cout << "Ingrese el nuevo numero de filas preferenciales: ";
		cin >> num;
		salas[idSala].nfp = num;
	}
	else if (op == 2)
	{
		cout << " >> Numero actual de filas generales: " << salas[idSala].nfg << endl
			 << endl;
		cout << "Ingrese el nuevo numero de filas generales: ";
		cin >> num;
		salas[idSala].nfg = num;
	}
	else if (op == 3)
	{
		cout << " >> Numero actual de columnas: " << salas[idSala].ncol << endl
			 << endl;
		cout << "Ingrese el nuevo numero de columnas: ";
		cin >> num;
		salas[idSala].ncol = num;
	}
	for (int j = 0; j < nfunc; j++)
		if (funciones[j].idSala == idSala)
		{
			funciones[j].sillas.nfg = salas[j].nfg;
			funciones[j].sillas.nfp = salas[j].nfp;
			funciones[j].sillas.ncol = salas[j].ncol;
		}
	cout << endl
		 << "Sala editada correctamente !! " << endl;
}
void addFuncion(Funcion *funciones, int &nfunc, Peli *peliculas, int &npelis, Sala *salas, int &nsalas)
{
	Funcion f;
	mostrarPelis(peliculas, npelis);
	bool a = true;
	while (a == true)
	{
		cout << "Ingrese el # de la pelicula a la que agregara una funcion: ";
		cin >> f.idPeli;
		f.idPeli--;
		if (0 <= f.idPeli && f.idPeli < npelis)
			a = false;
		else
			cout << "El numero de la pelicula debe estar entre 1 y " << npelis << "**" << endl;
	}
	mostrarSalas(salas, nsalas);
	cout << "Ingrese el # de la sala escogida: ";
	cin >> f.idSala;
	f.idSala--;
	a = true;
	bool b = true;
	while (a == true)
	{
		cout << "Ingrese la hora de la nueva funcion: ";
		cin >> f.hora;
		if (f.hora.size() == 5)
			a = false;
		else
			cout << "**Hora invalida**" << endl;
	}
	cout << "Ingrese el formato de la pelicula: ";
	cin >> f.formato;
	cout << endl
		 << " Funcion agregada correctamente !! " << endl;
	f.sillas.nfg = salas[f.idSala].nfg;
	f.sillas.nfp = salas[f.idSala].nfp;
	f.sillas.ncol = salas[f.idSala].ncol;
	for (int i = 0; i < f.sillas.nfg + f.sillas.nfp; i++)
		for (int j = 0; j < f.sillas.ncol; j++)
			f.sillas.esReservada[i][j] = false;
	funciones[nfunc] = f;
	nfunc++;
}

void remFuncion(Funcion *funciones, int &nfunc, Peli *peliculas, int &npelis)
{
	int idfunc;
	mostrarPeliYFuncion2(peliculas, funciones, nfunc, npelis);
	bool a = true;
	while (a == true)
	{
		cout << endl
			 << "* Ingrese el numero de la funcion a eliminar: ";
		cin >> idfunc;
		idfunc--;
		if (idfunc < nfunc)
			a = false;
		else
			cout << "**La funcion debe estar entre 1 y " << nfunc << "**" << endl
				 << endl;
	}
	for (int i = idfunc; i < nfunc - 1; i++)
		funciones[i] = funciones[i + 1];
	nfunc--;
	cout << endl
		 << " Funcion eliminada correctamente !! " << endl;
}

void addPeli(Peli *peliculas, int &npelis)
{
	Peli p;
	cout << "Ingrese el nombre de la pelicula: ";
	getline(cin, p.nombre);
	getline(cin, p.nombre);
	cout << "Ingrese el nombre del director: ";
	getline(cin, p.director);
	cout << "Ingrese la duracion de la pelicula en minutos: ";
	cin >> p.duracion;
	peliculas[npelis] = p;
	npelis++;
	cout << "La pelicula " << p.nombre << " se ha agregado correctamente !!" << endl;
}

void remPeli(Peli *peliculas, int &npelis, Funcion *funciones, int &nfunc)
{
	mostrarPelis(peliculas, npelis);
	cout << "Ingrese la pelicula que quiere eliminar: ";
	int i;
	cin >> i;
	i--;
	if (i < 0 || i >= npelis)
	{
		cout << "**La pelicula no existe**" << endl;
		return;
	}
	for (int j = 0; j < nfunc; j++)
		if (funciones[j].idPeli == i)
		{
			cout << endl
				 << "**NO se puede quitar la pelicula. Elimine primero la(s) funcion(es)**" << endl;
			return;
		}

	for (int j = i; j + 1 < npelis; j++)
		peliculas[j] = peliculas[j + 1];
	npelis--;

	for (int j = 0; j < nfunc; j++)
		if (funciones[j].idPeli > i)
			funciones[j].idPeli--;
	cout << endl
		 << " Pelicula eliminada correctamente !! " << endl;
}

void buscarEntreFechas1()
{
	string fecha1, fecha2;
	bool a = true;
	while (a == true)
	{
		cout << endl
			 << "Digite la fecha inicial (AAAAMMDD): ";
		cin >> fecha1;
		if (fecha1.size() == 8)
			a = false;
		else
			cout << "**Fecha invalida**" << endl;
	}
	a = true;
	while (a == true)
	{
		cout << "Digite la fecha final (AAAAMMDD): ";
		cin >> fecha2;
		if (fecha2.size() == 8 && fecha1 <= fecha2)
			a = false;
		else
			cout << "**Fecha invalida**" << endl;
	}
	int valorTotal = 0;
	for (int i = 0; i < nVentas; i++)
		if (fecha1 <= fechaVenta[i] && fechaVenta[i] <= fecha2)
		{
			cout << "Venta de " << valorVenta[i] << " el " << fechaVenta[i] << endl;
			valorTotal += valorVenta[i];
		}
	cout << endl
		 << "El dinero recaudado en el rango este rango de fechas es de: " << valorTotal << endl;
}

void buscarEntreFechas2()
{
	string fecha1, fecha2;
	bool a = true;
	while (a == true)
	{
		cout << endl
			 << "Digite la fecha inicial (AAAAMMDD): ";
		cin >> fecha1;
		if (fecha1.size() == 8)
			a = false;
		else
			cout << "**Fecha invalida**" << endl;
	}
	a = true;
	while (a == true)
	{
		cout << "Digite la fecha final (AAAAMMDD): ";
		cin >> fecha2;
		if (fecha2.size() == 8 && fecha1 <= fecha2)
			a = false;
		else
			cout << "**Fecha invalida**" << endl;
	}
	int numTotal = 0;
	cout << endl;
	for (int i = 0; i <= nPersonas; i++)
		if (fecha1 <= fechaPersonas[i] && fechaPersonas[i] <= fecha2)
		{
			cout << "Ingresaron " << numPersonas[i] << " persona(s) el " << fechaPersonas[i] << endl;
			numTotal += numPersonas[i];
		}
	cout << endl
		 << "En este rango de fechas ingresaron  " << numTotal << " persona(s)" << endl;
}

void consPeli(Funcion *funciones, int &nfunc, Peli *peliculas, int &npelis)
{
	string pregunta;
	bool estado = false;
	getline(cin, pregunta);
	for (int i = 0; i < 4; i++)
	{
		cout << endl
			 << "* Ingrese el nombre de la pelicula que quiere consultar: ";
		getline(cin, pregunta);
		cout << endl
			 << endl;
		for (int i = 0; i < nfunc; i++)
		{
			if (peliculas[funciones[i].idPeli].nombre == pregunta)
			{
				cout << " >> FUNCION " << i + 1 << endl;
				cout << " ============" << endl;
				cout << "Sala #" << funciones[i].idSala + 1 << endl;
				cout << "Horario: " << funciones[i].hora << endl;
				estado = true;
			}
		}
		if (estado == false)
			cout << "No se encontro la pelicula, intentelo de nuevo " << endl
				 << endl;
		else
			return;
		if (i == 3)
			cout << endl
				 << "**Intentos completados**" << endl;
	}
}
void vender(int opcion, Funcion *funciones, int &nfunc, int &np, int &dtr, int &preciop, int &preciog, Peli *peliculas, int &npelis, int &excedente3D, int &aux, string &temp)
{
	int idFunc, fila, col;
	mostrarPeliYFuncion1(peliculas, funciones, nfunc, npelis);
	bool a = true;
	while (a == true)
	{
		cout << endl
			 << "* Ingresar la funcion que quieren ver [o -1 para salir]: ";
		cin >> idFunc;
		if (idFunc == -1)
			return;
		idFunc--;
		if (0 <= idFunc && idFunc < nfunc)
			a = false;
		else
			cout << endl
				 << "**El numero de la funcion debe estar entre 1 y " << nfunc << "**" << endl;
	}
	a = true;
	string fecha;
	while (a == true)
	{
		cout << endl
			 << endl
			 << "Fecha de la venta (AAAAMMDD): ";
		cin >> fecha;
		cout << endl;
		if (fecha.size() == 8 && fecha > temp)
			a = false;
		else
			cout << "**Fecha invalida**" << endl;
	}
	if (aux == 0)
	{
		fechaPersonas[nPersonas] = fecha;
		funciones[idFunc].sillas.imprimir();
	}
	if (fechaPersonas[nPersonas] < fecha && aux == 1)
	{
		nPersonas++;
		fechaPersonas[nPersonas] = fecha;
		for (int i = 0; i < funciones[idFunc].sillas.nfg + funciones[idFunc].sillas.nfp; i++)
			for (int j = 0; j < funciones[idFunc].sillas.ncol; j++)
				funciones[idFunc].sillas.esReservada[i][j] = false;
		funciones[idFunc].sillas.imprimir();
	}
	else if (fechaPersonas[nPersonas] == fecha && aux == 1)
	{
		nPersonas++;
		fechaPersonas[nPersonas] = fecha;
		funciones[idFunc].sillas.imprimir();
	}
	aux = 1;
	a = true;
	while (a == true)
	{
		cout << endl
			 << "Ingrese la fila: ";
		cin >> fila;
		cout << "Ingrese la columna: ";
		cin >> col;
		if (funciones[idFunc].sillas.esReservada[fila][col] == false)
		{
			funciones[idFunc].sillas.esReservada[fila][col] = true;
			a = false;
		}
		else
			cout << endl
				 << "**El asiento escogido ya esta ocupado**" << endl;
	}
	numPersonas[nPersonas] = 1;
	np++;
	if (fila < funciones[idFunc].sillas.nfp)
	{
		if (funciones[idFunc].formato == "3D")
		{
			cout << "Pagar $" << preciop + excedente3D << endl;
			valorVenta[nVentas] = preciop + excedente3D;
			dtr = dtr + preciop + excedente3D;
		}
		else
		{
			cout << "Pagar $" << preciop << endl;
			valorVenta[nVentas] = preciop;
			dtr = dtr + preciop;
		}
	}
	else
	{
		if (funciones[idFunc].formato == "3D")
		{
			cout << "Pagar $" << preciog + excedente3D << endl;
			valorVenta[nVentas] = preciog + excedente3D;
			dtr = dtr + preciog + excedente3D;
		}
		else
		{
			cout << "Pagar $" << preciog << endl;
			valorVenta[nVentas] = preciog;
			dtr = dtr + preciog;
		}
	}
	cout << endl
		 << "Venta Exitosa!!" << endl;

	fechaVenta[nVentas] = fecha;
	nVentas++;
	cout << endl
		 << "**De enter para continuar**";
	getch();
}

void consultar(int opcion, Funcion *funciones, int nfunc, Peli *peliculas, int npelis, int np, int dtr)
{
	cout << endl
		 << "1. Horarios de las peliculas" << endl;
	cout << "2. Numero total de personas que han ingresado" << endl;
	cout << "3. Numero de personas que han ingresado en un lapso de tiempo" << endl;
	cout << "4. Cantidad total de dinero recaudado" << endl;
	cout << "5. Cantidad de dinero recaudado en un lapso de tiempo" << endl;
	cout << "6. Volver" << endl
		 << endl;
	bool a = true;
	while (a == true)
	{
		cout << "> Opcion: ";
		cin >> opcion;
		if (opcion >= 1 && opcion <= 6)
			a = false;
		else
			cout << "Opcion Incorrecta" << endl;
	}

	if (opcion == 1)
	{
		consPeli(funciones, nfunc, peliculas, npelis);
	}
	else if (opcion == 2)
	{
		cout << endl
			 << "A la fecha han ingresado " << np << " personas" << endl;
	}
	else if (opcion == 3)
	{
		buscarEntreFechas2();
	}
	else if (opcion == 4)
	{
		cout << endl
			 << "A la fecha se ha recaudado $" << dtr << endl;
	}
	else if (opcion == 5)
	{
		buscarEntreFechas1();
	}
	cout << endl
		 << "**De enter para continuar**";
	getch();
}

void configurar(int opcion, Peli *peliculas, int &npelis, Funcion *funciones, int &nfunc, Sala *salas, int &nsalas, int &preciop, int &preciog, int &excedente3D)
{
	cout << endl
		 << "1. Configuracion de salas" << endl;
	cout << "2. Configuracion de peliculas" << endl;
	cout << "3. Configuracion de funciones" << endl;
	cout << "4. Configurar los precios" << endl;
	cout << "5. volver" << endl
		 << endl;
	bool a = true;
	while (a == true)
	{
		cout << "> Opcion: ";
		cin >> opcion;
		if (opcion >= 1 && opcion <= 5)
			a = false;
		else
			cout << endl
				 << "**Opcion Incorrecta**" << endl;
	}

	if (opcion == 1)
	{
		cout << endl
			 << "  1. Agregar sala" << endl;
		cout << "  2. Eliminar sala" << endl;
		cout << "  3. Editar sala" << endl
			 << endl;
		cout << "> Opcion: ";
		cin >> opcion;
		if (opcion == 1)
			addSala(salas, nsalas);
		else if (opcion == 2)
			remSala(salas, nsalas, funciones, nfunc);
		else if (opcion == 3)
			ediSala(salas, nsalas, funciones, nfunc);
	}
	else if (opcion == 2)
	{
		cout << endl
			 << "  1. Agregar peliculas" << endl;
		cout << "  2. Eliminar peliculas" << endl
			 << endl;
		cout << "> Opcion: ";
		cin >> opcion;

		if (opcion == 1)
			addPeli(peliculas, npelis);
		else if (opcion == 2)
			remPeli(peliculas, npelis, funciones, nfunc);
	}
	else if (opcion == 3)
	{
		cout << endl
			 << "  1. Agregar funciones" << endl;
		cout << "  2. Eliminar funciones" << endl
			 << endl;
		cout << "> Opcion: ";
		cin >> opcion;
		if (opcion == 1)
			addFuncion(funciones, nfunc, peliculas, npelis, salas, nsalas);
		else if (opcion == 2)
			remFuncion(funciones, nfunc, peliculas, npelis);
	}
	else if (opcion == 4)
	{
		int newprecio;
		cout << endl
			 << "  1. Configurar el precio de la silla preferencial" << endl;
		cout << "  2. Configurar el precio de silla general" << endl;
		cout << "  3. Configurar el precio de excedente 3D" << endl
			 << endl;
		cout << "> Opcion: " << endl;
		cin >> opcion;
		if (opcion == 1)
		{
			cout << " >> Precio actual de la silla preferencial : $" << preciop << endl
				 << endl;
			cout << "Ingrese el nuevo precio de silla preferencial: ";
			cin >> newprecio;
			preciop = newprecio;
			cout << endl
				 << "Precio configurado correctamente !! " << endl;
		}
		else if (opcion == 2)
		{
			cout << " >> Precio actual de la silla general : $" << preciog << endl
				 << endl;
			cout << "Ingrese el nuevo precio de silla general: ";
			cin >> newprecio;
			preciog = newprecio;
			cout << endl
				 << "Precio configurado correctamente !! " << endl;
		}
		else if (opcion == 3)
		{
			cout << " >> Precio actual del excedente por 3D: $" << excedente3D << endl
				 << endl;
			cout << "Ingrese el nuevo precio del excedente 3D: ";
			cin >> newprecio;
			excedente3D = newprecio;
			cout << endl
				 << "Precio configurado correctamente !! " << endl;
		}
	}
	cout << endl
		 << "**De enter para continuar**";
	getch();
}

int main()
{
	int nsalas = 0, npelis = 0, nfunc = 0, np = 0, opcion, dtr = 0, aux = 0;
	int preciop = 10000, preciog = 6000, excedente3D = 3000;
	string temp = "20160523";
	Sala *salas = new Sala[1000];
	Peli *peliculas = new Peli[1000];
	Funcion *funciones = new Funcion[1000];

	Peli p1;
	p1.nombre = "Deadpool";
	p1.director = "Tim Miller";
	p1.duracion = 123;
	peliculas[npelis++] = p1;

	Peli p2;
	p2.nombre = "Civil War";
	p2.director = "Joe Russo y Anthony Russo";
	p2.duracion = 150;
	peliculas[npelis++] = p2;

	Sala sala1;
	sala1.nfp = 4;
	sala1.nfg = 12;
	sala1.ncol = 15;
	salas[nsalas++] = sala1;

	Sala sala2;
	sala2.nfp = 3;
	sala2.nfg = 10;
	sala2.ncol = 12;
	salas[nsalas++] = sala2;

	Funcion f1;
	f1.idPeli = 0;
	f1.idSala = 0;
	f1.hora = "12:30";
	f1.formato = "3D";
	f1.sillas.nfp = sala1.nfp;
	f1.sillas.nfg = sala1.nfg;
	f1.sillas.ncol = sala1.ncol;
	funciones[nfunc++] = f1;

	Funcion f2;
	f2.idPeli = 1;
	f2.idSala = 1;
	f2.hora = "17:20";
	f2.formato = "2D";
	f2.sillas.nfp = sala2.nfp;
	f2.sillas.nfg = sala2.nfg;
	f2.sillas.ncol = sala2.ncol;
	funciones[nfunc++] = f2;

	do
	{
		cout << "* * * * * * * * * * * * *" << endl;
		cout << "*       MULTIPLEX       *" << endl;
		cout << "*   Por: Sergio Rojas   *" << endl;
		cout << "* * * * * * * * * * * * *" << endl
			 << endl;
		cout << endl
			 << endl
			 << "OPCIONES :" << endl
			 << endl;
		cout << "1. Ventas" << endl;
		cout << "2. Consultas" << endl;
		cout << "3. Configuraciones" << endl;
		cout << "4. Salir" << endl
			 << endl;
		cout << "> Opcion: ";
		cin >> opcion;
		if (opcion == 1)
		{
			vender(opcion, funciones, nfunc, np, dtr, preciop, preciog, peliculas, npelis, excedente3D, aux, temp);
		}
		else if (opcion == 2)
		{
			consultar(opcion, funciones, nfunc, peliculas, npelis, np, dtr);
		}
		else if (opcion == 3)
		{
			configurar(opcion, peliculas, npelis, funciones, nfunc, salas, nsalas, preciop, preciog, excedente3D);
		}

		CLEAR_SCREEN();
	} while (opcion != 4);
	return 0;
}
