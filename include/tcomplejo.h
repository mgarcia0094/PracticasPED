#ifndef __TCOMPLEJO__
#define __TCOMPLEJO__

#include <iostream>

using namespace std;

class TComplejo {

	/*
		FUNCIONES AMIGAS
	*/
	//Sobrecarga del operador salida
	friend ostream &operator<< (ostream &, const TComplejo &);

	//sobrecarga para suma de double con complejos
	friend TComplejo operator+ (double,TComplejo&);
	friend TComplejo operator- (double, TComplejo&);
	friend TComplejo operator* (double, TComplejo&);

	public:

		/*
		*	FORMA CANÓNICA DE LA CLASE
		*/
		//Constructor a partir de la PARTE REAL e IMAGINARIA
		TComplejo(double re = 0, double im = 0) { this->re=re; this->im=im;}
		//Constructor copia
		TComplejo (const TComplejo& c) {	this->re = c.re; this->im = c.im;}
		//Destructor
		~TComplejo() { this->re=0; this->im=0;}

		//Sobrecarga del operador asignación
		TComplejo& operator= (const TComplejo&);

		/*
		*	MÉTODOS
		*/

		//Sobrecarga de operadores aritméticos
		//suma
		TComplejo operator+ (const TComplejo&) const;
		TComplejo operator- (const TComplejo&) const;
		TComplejo operator* (const TComplejo&) const;
		TComplejo operator+ (double d);
		TComplejo operator- (double d);
		TComplejo operator* (double d);

		//otros operadores
		bool operator== (const TComplejo&); //igualdad de num complejos
		bool operator!= (const TComplejo&); //desigualdad de num complejos

		//devuelve los valores de la clase
		double Re() const { return this->re;} 
		double Im() const { return this->im;}

		//Modifica PARTE REAL
		void Re(double re) { this->re = re;}
		//Modifica PARTE IMAGINARIA
		void Im(double im) { this->im = im;}

		double Arg(void); //Calcula el argumento (en radianes)
		double Mod(void); //Calcula el módulo

	private:
		double re; //Parte real
		double im; //Parte imaginaria



};

#endif
