#include "../include/tlistacom.h"

/*

	TLISTACOM

*/

TListaNodo::TListaNodo() {
	
	TComplejo a;
	this->e = a;

	this->anterior = NULL;
	this->siguiente = NULL;
}

TListaNodo::TListaNodo(const TListaNodo &l) {
	this->e = l.e;
	this->anterior = l.anterior;
	this->siguiente = l.siguiente;
}

TListaNodo::~TListaNodo() {
	TComplejo vacio;
	this->e = vacio;
	//delete this->anterior;
	//delete this->siguiente;
	this->anterior = NULL;
	this->siguiente = NULL;
}

TListaNodo&
TListaNodo::operator=(const TListaNodo &l) {
	
	if(this != &l) {
		this->e = l.e;
		this->anterior = l.anterior;
		this->siguiente = l.siguiente;
	}

	return (*this);
}

/*

	TLISTAPOS

*/

TListaPos::TListaPos() {
	this->pos = NULL;
}

TListaPos::TListaPos(const TListaPos &p) {
	this->pos = p.pos;
}

TListaPos::~TListaPos() {
	this->pos = NULL;
}

TListaPos&
TListaPos::operator=(const TListaPos &p) {
	
	if(this != &p) {
		//ver si TListaPOs p es null??
		this->pos = p.pos;
	}

	return (*this);
}

bool
TListaPos::operator==( TListaPos &p) {
	if(this->pos == p.pos) {
		return true;
	} else return false;
}

bool
TListaPos::operator!=(TListaPos &p) {
	if(this->pos != p.pos) {
		return true;
	} else return false;
}

TListaPos
TListaPos::Anterior() const { 
	TListaPos aux;
	if(this->pos->anterior != NULL) {
		aux.pos = this->pos->anterior;
		return aux;
	} else return aux;
}

TListaPos
TListaPos::Siguiente() const { 
	TListaPos aux;
	if(this->pos->siguiente != NULL) {
		aux.pos = this->pos->siguiente;
		return aux;
	} else return aux;
}

bool
TListaPos::EsVacia() {
	if(this->pos == NULL) return true;
	else return false;
}

/*

	TListaCom

*/

TListaCom::TListaCom() {
	//lista vacia
	this->primero = NULL;
	this->ultimo = NULL;

}

TListaCom::TListaCom(const TListaCom &l) { //copia pofunda

	if(!l.EsVacia()) { // si no es vacía
		//solo tiene un elemento
		if(l.primero->siguiente == NULL && l.ultimo->anterior == NULL) {
			this->primero = new TListaNodo();
			this->ultimo = this->primero;
			this->primero->e = l.primero->e;
		} else {

			TListaPos l1(l.Primera());
			//Añadimos el primer elemento
			this->primero = new TListaNodo();
			this->primero->e = l1.pos->e;
			this->ultimo = this->primero;
			TListaPos p1(this->Primera());

			while(l1.pos->siguiente != NULL) {
				l1 = l1.Siguiente();
				p1.pos->siguiente = new TListaNodo();
				p1.pos->siguiente->anterior = p1.pos;
				p1.pos->siguiente->e = l1.pos->e;
				p1 = p1.Siguiente();
			}
			
			this->ultimo = p1.pos;
			this->ultimo->siguiente = NULL;
			
		}
	} else {
		this->primero = NULL;
		this->ultimo = NULL;
	}

}

TListaCom::~TListaCom() { //destructor profundo
	this->primero = NULL;
	this->ultimo = NULL;
}

TListaCom&
TListaCom::operator=(const TListaCom &l) {

	if(this != &l) {
		this->primero = l.primero;
		this->ultimo = l.ultimo;
	}
	
	return (*this);
}

TListaCom
TListaCom::operator+(const TListaCom &l) {

	TListaCom suma;

	if(this->EsVacia() && l.EsVacia()) return suma;
	else if(!this->EsVacia() && l.EsVacia()) return (*this);
	else if(this->EsVacia() && !l.EsVacia()) return l;
	else {
		
		TListaPos aux;

		aux.pos = this->primero;

		suma.primero = new TListaNodo();
		suma.primero->e = aux.pos->e;
		
		TListaPos taux;
		taux.pos = suma.primero;

		while(aux.pos->siguiente != NULL) {
			aux = aux.Siguiente();
			taux.pos->siguiente = new TListaNodo();
			taux.pos->siguiente->e = aux.pos->e;
			taux.pos->siguiente->anterior = taux.pos;
			taux = taux.Siguiente();
		}

		suma.ultimo = taux.pos;

	}

	return suma;
}

TListaCom
TListaCom::operator-(const TListaCom &l) { //completar
	
	TListaCom resta;

	if(this->EsVacia() && l.EsVacia()) return resta;
	else if(!this->EsVacia() && l.EsVacia()) return (*this);
	else if(this->EsVacia() && !l.EsVacia()) return l;
	else {
		
		TListaPos aux, rest;
		bool primero = true;
		aux.pos = this->primero;
		
		do {
			
			if(!l.Buscar(aux.pos->e)) {
				if(primero) {
					resta.primero = new TListaNodo();
					rest.pos = resta.primero;
					rest.pos->e = aux.pos->e;
					primero = false;
				} else {
					TListaPos p;
					p.pos = rest.pos;
					rest = rest.Siguiente();
					p.pos->e = aux.pos->e;
					p.pos->siguiente = rest.pos;
					rest.pos->anterior = p.pos;
				}
			}
			aux = aux.Siguiente();
		} while(aux.pos != this->ultimo);
		
		resta.ultimo = rest.pos;

	}

	return resta;
}

bool 
TListaCom::operator==( const TListaCom &l) {
	if(this->Longitud() == l.Longitud()) {
		TListaPos p1,p2;
		p1 = this->Primera();
		p2 = l.Primera();
		while(!p1.EsVacia()) {
			if(p1.pos->e != p2.pos->e) return false;
			p1 = p1.Siguiente();
			p2 = p2.Siguiente();
		}
		return true;
	} else return false;
}

bool 
TListaCom::operator!=(const TListaCom &l){
	
	if(this->Longitud() == l.Longitud()) {
		TListaPos p1,p2;
		p1 = this->Primera();
		p2 = l.Primera();
		while(!p1.EsVacia()) {
			if(p1.pos->e != p2.pos->e) return true;
			p1 = p1.Siguiente();
			p2 = p2.Siguiente();
		}
		return false;
	} else return true;
}

bool
TListaCom::EsVacia() const{
	if(this->primero == NULL || this->ultimo == NULL) return true;
	else return false;
}

bool
TListaCom::InsCabeza(TComplejo &c) {
	TListaNodo *p = new TListaNodo();
	if(&p != NULL) { //se puede reservar memoria dinamica
		if(this->EsVacia()) {
			this->primero = p;
			this->primero->e = c;
			this->ultimo = this->primero;
		} else {
			TListaPos aux(this->Primera());
			this->primero = new TListaNodo();
			this->primero->e = c;
			this->primero->siguiente = aux.pos;
			aux.pos->anterior = this->primero;
		}
		return true;
	} else return false;
}

bool
TListaCom::InsertarI(TComplejo &c, const TListaPos &l) {
	if(l.pos != NULL) {
		if(l.pos->anterior == NULL) {
			//si es el primero
			this->primero = new TListaNodo();
			this->primero->e = c;
			this->primero->siguiente = l.pos;
			l.pos->anterior = this->primero;
		} else {
			TListaPos aux;
			aux.pos = l.pos->anterior;
			aux.pos->siguiente = new TListaNodo();
			aux.pos->siguiente->e = c;
			aux.pos->siguiente->anterior = aux.pos;
			l.pos->anterior = aux.pos->siguiente;
			aux.pos->siguiente->siguiente = l.pos;
		}
		return true;
	} else return false;
}

bool
TListaCom::InsertarD(TComplejo &c, const TListaPos &l) {
	if(l.pos != NULL) {
		if(l.pos->siguiente == NULL) {
			//si es el primero
			this->ultimo = new TListaNodo();
			this->ultimo->e = c;
			this->ultimo->anterior = l.pos;
			l.pos->siguiente = this->ultimo;
		} else {
			TListaPos aux;
			aux.pos = l.pos->siguiente;
			aux.pos->anterior = new TListaNodo();
			aux.pos->anterior->e = c;
			aux.pos->anterior->siguiente = aux.pos;
			l.pos->siguiente = aux.pos->anterior;
			aux.pos->anterior->anterior = l.pos;
		}
		return true;
	} else return false;
}


//borra el primer elemento que coincida con el TComplejo
bool
TListaCom::Borrar(TComplejo &c) {
	if(this->primero != NULL) {
		TListaPos p(this->Primera());
		while(p.pos != NULL) {
			if(p.pos->e == c) {
				p.Anterior().pos->siguiente = p.Siguiente().pos;
				p.Siguiente().pos->anterior = p.Anterior().pos;

				delete p.pos;
				return true;
			}
		}
		return true; //se devuelve true?
	} else return false;
}

//borra todas las ocurrencias de TCOMplejo
bool
TListaCom::BorrarTodos(TComplejo &c) {
	if(this->primero != NULL) { //está bien?
		TListaPos p(this->Primera());
		while(p.pos != NULL) {
			if(c == p.pos->e) {
				TListaPos a, b;
				if(p.pos->anterior != NULL) {
					a = p.Anterior();
					a.pos->siguiente = p.pos->siguiente;
				} else {
					this->primero = p.pos->siguiente;
				}
				if(p.pos->siguiente != NULL) {
					b = p.Siguiente();
					b.pos->anterior = p.pos->anterior;
				} else {
					this->ultimo = p.pos->anterior;
				}
			}
			p = p.Siguiente();
		}
		return true;
	} else return false;
}

bool
TListaCom::Borrar(TListaPos &l) {
	if(l.pos != NULL) {
		TListaPos ant, post;

		//funcionaria con el primer elemento y el ultimo?
		ant = l.Anterior();
		post = l.Siguiente();

		//los unimos
		ant.pos->siguiente = post.pos;
		post.pos->anterior = ant.pos;

		//borramos el del medio
		delete l.pos;
	} else return false;
}

TComplejo
TListaCom::Obtener(const TListaPos &pos) const{
	TComplejo c(pos.pos->e);
	return c;
}

bool
TListaCom::Buscar(const TComplejo &t) const{
	TListaPos r;
	r.pos = this->primero;
	if(r.pos != NULL) {
		while(r.pos != NULL) {
			if(r.pos->e == t) return true;
			r.pos = r.pos->siguiente;
		}
		return false;
	} else return false;
}


int
TListaCom::Longitud() const{
	TListaPos p,vacia;
	p.pos = this->primero;
	int contador = 0;
	while(p.pos != NULL) {
		contador++;
		if(p.Siguiente() == vacia) p.pos = NULL;
		else p.pos = p.pos->siguiente; 
	}
	return contador;
}

TListaPos
TListaCom::Primera() const{
	TListaPos aux;
	if(this->primero == NULL) return aux; //devolvera un pos vacio
	else {
		aux.pos = this->primero;
		return aux;
	}
}

TListaPos
TListaCom::Ultima() const{
	TListaPos aux;
	if(this->ultimo == NULL) return aux; //devolvera un pos vacio
	else {
		aux.pos = this->ultimo;
		return aux;
	}
}

bool
esMenor(TComplejo a, TComplejo b) {
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

TListaCom
TListaCom::ordenarLista(const TListaCom& l) {
	TListaCom aux(l);
	TListaPos p = aux.Primera();
	while(p.pos != NULL) {
		TListaPos auxInteriorP = aux.Primera();
		while(auxInteriorP.pos != NULL) {
			if(esMenor(p.pos->e,auxInteriorP.pos->e)){
				//cout << "Es menor " << auxInteriorP.pos->e << " que " << auxComplejo << endl;
				TComplejo b = auxInteriorP.pos->e;
				auxInteriorP.pos->e = p.pos->e;
				p.pos->e = b;
			} 
			auxInteriorP = auxInteriorP.Siguiente();
		}
		p = p.Siguiente();
		
	}
	return aux;
}

ostream &operator<<(ostream &os, const TListaCom &l){
	TListaPos p = l.Primera();

	os << "{";
	while(!p.EsVacia()) {
		TComplejo c = l.Obtener(p);
		os << c;
		p = p.Siguiente();
		if(!p.EsVacia()) os << ",";
	}

	os << "}";
	return os;
}