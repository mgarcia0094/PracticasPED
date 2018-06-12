#ifndef __TVECTORCOM__
#define __TVECTORCOM__

#include "tcomplejo.h"

class TVectorCom {

// Funciones amigas
friend ostream & operator<<(ostream &, const TVectorCom &);

private:
	//tam del vector
	int tamano;
	//puntero TComplejo donde empieza el vector
	TComplejo *c;
	//error
	TComplejo error;

public:
	/*
		Forma canónica de la clase
	*/

	//Constructor por defecto
	TVectorCom();
	//constructor con tamaño
	TVectorCom(int tam);
	//Destructor
	~TVectorCom();
	//constructor copia
	TVectorCom(const TVectorCom&);
	//Sobrecarga Operador Asigncacion
	TVectorCom &operator=(const TVectorCom&);


	//sobrecarga del operador igualdad
	bool operator==(const TVectorCom&) const;

	//sobrecarga del operador desigualdad
	bool operator!=(const TVectorCom&) const;

	// Sobrecarga del operador corchete (parte IZQUIERDA)
	TComplejo &operator[](int);
	// Sobrecarga del operador corchete (parte DERECHA)
	TComplejo operator[](int) const;

	// Tamaño del vector (posiciones TOTALES)
	int Tamano() const { return tamano; }
	// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
	int Ocupadas() const;
	// Devuelve TRUE si existe el TComplejo en el vector
	bool ExisteCom( TComplejo &) const;
	// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
	void MostrarComplejos(double);
	// REDIMENSIONAR el vector de TComplejo
	bool Redimensionar(int);

};

#endif