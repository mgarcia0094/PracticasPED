#include "tabbcom.h"

/*
	TNodoABB
*/

TNodoABB::TNodoABB() {
	TComplejo c;
	TABBCom aux;
	this->item = c;
	this->iz = aux;
	this->de = aux;
}

TNodoABB::TNodoABB(const TNodoABB &n) {
	this->item = n.item;
	TABBCom d(n.de);
	TABBCom i(n.iz);
	this->de = d;
	this->iz = i;
}

TNodoABB&
TNodoABB::operator=(TNodoABB &n) {
	if(&de != NULL) de.~TABBCom();
	if(&iz != NULL) iz.~TABBCom();
	
	TABBCom i(n.iz);
	TABBCom d(n.de);
	
	this->item = n.item;
	this->iz = i;
	this->de = d;
	cout << this->iz.nodo << endl;
	cout << this->de.nodo << endl;
	return (*this);
}

TNodoABB::~TNodoABB() {
	TComplejo c;
	this->item = c;
	this->de.~TABBCom();
	this->iz.~TABBCom();
}

/*
	TABBCom
*/

void
TABBCom::InordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		this->nodo->iz.InordenAux(v, n);
		v[n] = this->nodo->item;
		n += 1;
		this->nodo->de.InordenAux(v, n);
	}
}

void
TABBCom::PreordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		v[n] = this->nodo->item;
		n += 1;
		this->nodo->iz.PreordenAux(v, n);
		this->nodo->de.PreordenAux(v, n);
	}
}

void
TABBCom::PostordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		this->nodo->iz.PostordenAux(v, n);
		this->nodo->de.PostordenAux(v, n);
		v[n] = this->nodo->item;
		n += 1;
	}
}

TABBCom::TABBCom() {
	this->nodo = NULL;
}

TABBCom::TABBCom(const TABBCom &c) {
	if(c.nodo != NULL) {
		this->nodo = new TNodoABB(*c.nodo);
	} else {
		this->nodo = NULL;
	}
}

TABBCom::~TABBCom() {
	//liberar memoria con delete[]
	if(this->nodo != NULL) {
		//delete this->nodo;
		this->nodo = NULL;
	}
}

TABBCom&
TABBCom::operator=(const TABBCom &c){
	if(c.nodo != NULL) {
		if(this->nodo != NULL) (*this).~TABBCom();
		this->nodo = new TNodoABB(*c.nodo);
	} else this->nodo = NULL;
	return (*this);
}

bool
TABBCom::operator==(const TABBCom &c) {
	if(this->Nodos() == c.Nodos()) {
		TVectorCom v = this->Preorden();
		TVectorCom p = c.Preorden();
		bool aux = false;
		for(int x = 1; x <= this->Nodos(); x++) {
			aux = false;
			for(int y = 1; y <= c.Nodos(); y++) {
				if(v[x] == p[y]) aux = true;
			}
			if(!aux) return false; //no se ha encontrado
		}
		return true;
	} else return false;
}

bool 
TABBCom::EsVacio() const {
	if(this->nodo == NULL) return true;
	else return false;
}


bool 
TABBCom::esMenor(TComplejo a, TComplejo b) {
	if(a.Mod() < b.Mod()) return true;
	else if(a.Mod() == b.Mod()) {
		if(a.Re() < b.Re()) {
			return true;
		} else if(a.Re() == b.Re()) {
			if(a.Im() < b.Im()) return true;
			else return false;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void
TABBCom::InsertarRec(TABBCom &arb, TComplejo &n) {
	
	if(esMenor(n,arb.Raiz())) {
		if(arb.nodo->iz.nodo == NULL) {
			arb.nodo->iz.nodo = new TNodoABB();
			arb.nodo->iz.nodo->item = n;
		} else {
			InsertarRec(arb.nodo->iz, n);
		}
	} else {
		if(arb.nodo->de.nodo == NULL) {
			arb.nodo->de.nodo = new TNodoABB();
			arb.nodo->de.nodo->item = n;
		} else {
			InsertarRec(arb.nodo->de, n);
		}
	}
}

bool 
TABBCom::Insertar(TComplejo &num) {

	if(this->EsVacio()) {
		this->nodo = new TNodoABB();
		this->nodo->item = num;
		return true;
	} else {
		if(!this->Buscar(num)) {
			InsertarRec(*this, num);
			return true;
		} else return false;
	}
}

TABBCom
TABBCom::EncontrarArbol(TABBCom &arb, TComplejo &n) {
	if(arb.nodo->item == n) {
		return arb.nodo->iz;
	} else {
		if(arb.nodo->iz.nodo != NULL) return EncontrarArbol(arb.nodo->iz, n);
		if(arb.nodo->de.nodo != NULL) return EncontrarArbol(arb.nodo->de, n);
	}
}

void
TABBCom::EliminarConexion(TABBCom &arb, TComplejo &c) {
	
	if(arb.nodo->de.nodo != NULL) {
		if(arb.nodo->de.nodo->item == c) {
			arb.nodo->de.nodo = NULL;
		}
	}

	if(arb.nodo->iz.nodo != NULL) {
		if(arb.nodo->iz.nodo->item == c) {
			arb.nodo->iz.nodo = NULL;
		}
	}

	if(arb.nodo->de.nodo != NULL) EliminarConexion(arb.nodo->de, c);
	if(arb.nodo->iz.nodo != NULL) EliminarConexion(arb.nodo->iz, c);
}

TComplejo
TABBCom::EliminarNodoMax(TABBCom &arb) {
	if(arb.nodo->de.nodo == NULL) {
		TComplejo c(arb.nodo->item);
		return c;
	} else {
		return EliminarNodoMax(arb.nodo->de);
	}
}

void
TABBCom::SustituirNumero(TABBCom &arb, TComplejo &n, TComplejo max) {
	if(arb.nodo->item == n) {
		arb.nodo->item = max;
	} else {
		if(arb.nodo->iz.nodo != NULL) SustituirNumero(arb.nodo->iz,n,max);
		if(arb.nodo->de.nodo != NULL) SustituirNumero(arb.nodo->de,n,max);
	}
}

void
TABBCom::BorrarComplejo(TABBCom &arb, TComplejo &num) {
	
	if(arb.nodo->item == num) {
		arb.nodo = NULL;
	} else {
		if(this->nodo->iz.nodo != NULL) arb.nodo->iz.BorrarComplejo(this->nodo->iz,num);
		if(this->nodo->de.nodo != NULL) arb.nodo->de.BorrarComplejo(this->nodo->de,num);
	}
}	

TComplejo
TABBCom::BuscarMayor(TABBCom &a) {

	if(a.nodo->de.nodo == NULL && a.nodo->iz.nodo == NULL) return a.nodo->item;
	else if(a.nodo->de.nodo == NULL) {
		TComplejo max = BuscarMayor(a.nodo->iz);
		if(esMenor(a.nodo->item,max)) return max;
		else return a.nodo->item;
	} else if(a.nodo->iz.nodo == NULL ) {
		TComplejo max = BuscarMayor(a.nodo->de);
		if(esMenor(a.nodo->item,max)) return max;
		else return a.nodo->item;
	} else {
		TComplejo maxD = BuscarMayor(a.nodo->de);
		TComplejo maxI = BuscarMayor(a.nodo->iz);
		
		if(esMenor(maxD,a.nodo->item) && esMenor(maxI,a.nodo->item)) return a.nodo->item;
		else if(esMenor(a.nodo->item, maxD)&& esMenor(maxI,maxD)) return maxD;
		else return maxI;

	}
}

void
TABBCom::BorrarRec(TComplejo &n) {
	if(this->nodo->item == n) {
		//es el primer nodo
		if(this->nodo->iz.nodo != NULL) {
			TComplejo max = BuscarMayor(this->nodo->iz);
			BorrarComplejo((*this), max);
			this->nodo->item = max;
		} else if(this->nodo->de.nodo != NULL) {
			TComplejo max = BuscarMayor(this->nodo->de);
			BorrarComplejo((*this), max);
			this->nodo->item = max;
		} else {
			this->nodo = NULL;
		}

	} else {
		if(this->nodo->de.nodo != NULL) this->nodo->de.BorrarRec(n);
		if(this->nodo->iz.nodo != NULL) this->nodo->iz.BorrarRec(n);
	}
}

bool
TABBCom::Borrar(TComplejo &n) {

	if(Buscar(n)) {
		BorrarRec(n);
		return true;
	} else {
		return false;
	}
}

bool
TABBCom::BuscarRec(TABBCom &arb, TComplejo &n) {
	if(arb.nodo != NULL) {
		if(arb.nodo->item == n) {
			return true;
		}
		
		bool i = BuscarRec(arb.nodo->iz, n);
		bool d = BuscarRec(arb.nodo->de, n);

		if(i || d) {
			return true;
		} else return false;

	} else return false;
}

bool
TABBCom::Buscar(TComplejo &n) {
	if(BuscarRec(*this, n)) return true;
	else return false;
}

TComplejo
TABBCom::Raiz() {
	TComplejo aux;
	if(this->EsVacio()) return aux;
	else {
		return this->nodo->item;
	}
}

int 
TABBCom::NodosRec(const TABBCom &arb) const {
	if(arb.nodo != NULL) {
		return 1 + NodosRec(arb.nodo->iz) + NodosRec(arb.nodo->de);
	} else return 0;
}

int
TABBCom::Nodos() const {
	if(this->EsVacio()) return 0;
	else {
		return NodosRec(*this);
	}
}

int 
TABBCom::NodosHojasRec(const TABBCom &arb) const {
	if(arb.nodo != NULL) {
		if(arb.nodo->iz.nodo == NULL && arb.nodo->de.nodo == NULL) {
			return 1;
		} else {
			NodosHojasRec(arb.nodo->iz);
			NodosHojasRec(arb.nodo->de);
			return 0;
		}
	} else return 0;
}

int 
TABBCom::NodosHoja() const{
	if(this->EsVacio()) return 0;
	else {
		return NodosHojasRec(*this);
	}
}

int MayoriaAux(int a, int b) {
	if(a < b) return b;
	else return a;
}

int 
TABBCom::AlturaRec(TABBCom &c) {
	if(c.nodo != NULL) return 1 + MayoriaAux(AlturaRec(c.nodo->de), AlturaRec(c.nodo->iz));
	else return 0;
}

int
TABBCom::Altura() {
	if(this->EsVacio()) return 1;
	else {
		return AlturaRec(*this);
	}
}

TVectorCom
TABBCom::Inorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->InordenAux(v, posicion);
	return v;
}

TVectorCom
TABBCom::Preorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->PreordenAux(v, posicion);
	return v;
}

TVectorCom
TABBCom::Postorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->PostordenAux(v, posicion);
	return v;
}

void
TABBCom::RecorrerNiveles(TABBCom arbol, queue<TABBCom*> &q, TVectorCom &v) const {
	TABBCom* aux;
	int n = 1;

	if(&arbol!=NULL) {
		q.push(&arbol);
		while(!q.empty()) {
			aux = q.front();
			v[n] = aux->nodo->item;
			n++;
			q.pop();
			if(aux->nodo->iz.nodo != NULL) q.push(&aux->nodo->iz);
			if(aux->nodo->de.nodo != NULL) q.push(&aux->nodo->de);
		}
	}
}

TVectorCom 
TABBCom::Niveles() const {
	TVectorCom v(Nodos());
	queue<TABBCom*> q;
	this->RecorrerNiveles(*this, q, v);
	return v;
}

//FUNCIONES FRIENDS
ostream &operator<< (ostream &os, const TABBCom &arb) {
	TVectorCom v = arb.Niveles();
	os << v;
 	return os;
}