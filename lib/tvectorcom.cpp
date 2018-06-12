#include "../include/tvectorcom.h"

using namespace std;

//constructor vacío
TVectorCom::TVectorCom() {
	this->tamano = 0;
	this->c = NULL;
}

//sobrecarga asignacion
TVectorCom&
TVectorCom::operator= (const TVectorCom &t)  {
  	
  	(*this).~TVectorCom(); //llamamos al destructor
	
	this->tamano = t.Tamano();
	
	if(t.Tamano() <= 0) {
		this->tamano = 0;
		this->c = NULL;
	} else this->c = new TComplejo[t.Tamano()];

	//copiamos uno a uno los elementos del vector
	for(int x=0; x < this->tamano ; x++) {
		this->c[x] = t.c[x];
	}

	return (*this);
}

//constructor con un tamaño
TVectorCom::TVectorCom(int tam) {
	if(tam <= 0) {
		this->tamano = 0;
		this->c = NULL;
	} else {
		 this->c = new TComplejo[tam];
		 this->tamano = tam;
	}

	//rellenamos el vector con TComplejo vacíos
	for(int x=0; x < tam; x++) {
		TComplejo d;
		c[x] = d;
	}
}

//destructor
TVectorCom::~TVectorCom() {
	//tamaño 0
	this->tamano = 0;
	delete[] this->c;
	this->c = NULL;
}

//vector copia
TVectorCom::TVectorCom(const TVectorCom &t) {
	
	(*this).~TVectorCom(); //llamamos al destructor
	
	this->tamano = t.Tamano();
	

	if(t.Tamano() <= 0) {
		this->tamano = 0;
		this->c = NULL;
	} else this->c = new TComplejo[this->tamano];

	//rellenamos el vector con TComplejo vacíos
	
	for(int x=0; x < this->tamano; x++) {
		TComplejo d;
		c[x] = d;
	}

	//copiamos uno a uno los elementos del vector
	for(int x=0; x < this->tamano ; x++) {
		this->c[x] = t.c[x];
	}
}

//igualdad
bool
TVectorCom::operator==(const TVectorCom &v) const {
	
	if(this->tamano == v.Tamano()) { //mismo tamaño
		for(int x=0; x < this->tamano; x++) {
			if(this->c[x] != v.c[x]) return false;
		}
	} else return false;

	return true;
}

//desigualdad
bool
TVectorCom::operator!=(const TVectorCom &v) const {
	
	if(this->tamano == v.Tamano()) { //mismo tamaño
		for(int x=0; x < this->tamano; x++) {
			if(this->c[x] != v.c[x]) return true;
		}
	} else return true;

	return false;
}


//parte izquierda
TComplejo&
TVectorCom::operator[] (int valor) {
	if((valor <= this->tamano) && (valor >= 1)) {
		return c[valor-1];
	} else return this->error;
}

//parte derecha
TComplejo
TVectorCom::operator[] (int valor) const {
	if((valor <= this->tamano) && (valor >= 1)) {
		TComplejo d(c[valor-1]);
		return d;
	} else return this->error;
}

//casillas ocupadas
int
TVectorCom::Ocupadas() const {
	int ocupadas=0;
	for(int x=0; x < this->tamano;x++) {
		if(this->c[x] != this->error) ocupadas++;
	}
	return ocupadas;
}

//si está el complejo
bool
TVectorCom::ExisteCom( TComplejo &com) const {
	for(int x=0; x < this->tamano;x++) {
		if(com == this->c[x]) return true;
	}

	return false;
}

void
TVectorCom::MostrarComplejos(double com) {
	cout << "[";
	for(int x=0;x < tamano;x++) {
		if(com <= this->c[x].Re()) cout << c[x] << ", "; //hay que mirar la coma
	}
	cout << "]" << endl;
}

//completarlo
bool
TVectorCom::Redimensionar(int tamNuevo) {
	if(tamNuevo > 0 || tamNuevo != this->tamano) {
		if(tamNuevo > tamano) { //si tam más grande
			
			TComplejo *n = new TComplejo[tamNuevo];
			
			for(int x = 0;x < tamNuevo; x++) {
				if(x < tamano) { //si es mas peueño que el tamaño antiguo
					//copia los elementos del vector viejo
					TComplejo aux(c[x]);
					n[x] = aux;
				} else { //crea nuevos
					TComplejo aux;
					n[x] = aux;
				} 
			}

			//asignamos el nuevo tamaño y el vector
			this->tamano = tamNuevo;
			//borramos el vector
			delete[] c;
			this->c = n;
			return true;
		} else { // si tam es más pequeño
			for(int x=0;x<tamano;x++) {
				if(x >= tamNuevo) delete[] c; //FALLA
			}
			this->tamano = tamNuevo;
			return true;
		}
	} else return false;

}

//imprimir salida
ostream &operator<< (ostream &os, const TVectorCom &t) {
	os << "[";
	for(int x=0;x<t.Tamano();x++) {
		os << "(" << (x+1) << ")" << " " << t.c[x];
		if(x != (t.Tamano() - 1)) os << ", ";
	}
	os << "]";
  return os;
}