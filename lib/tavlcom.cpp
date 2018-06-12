#include "../include/tavlcom.h"

/*
	TNodoABB
*/

TNodoAVL::TNodoAVL() {
	TComplejo c;
	TAVLCom aux;
	this->fe = 0;
	this->item = c;
	this->iz = aux;
	this->de = aux;
}

TNodoAVL::TNodoAVL(const TNodoAVL &n) {
	this->item = n.item;
	this->fe = n.fe;
	TAVLCom d(n.de);
	TAVLCom i(n.iz);
	this->de = d;
	this->iz = i;
}

TNodoAVL&
TNodoAVL::operator=(TNodoAVL &n) {

	if(&de != NULL) de.~TAVLCom();
	if(&iz != NULL) iz.~TAVLCom();
	
	TAVLCom i(n.iz);
	TAVLCom d(n.de);
	
	this->item = n.item;
	this->fe = n.fe;
	this->iz = i;
	this->de = d;

	
	return (*this);
}

TNodoAVL::~TNodoAVL() {
	TComplejo c;
	this->item = c;
	this->fe = 0;
	this->de.~TAVLCom();
	this->iz.~TAVLCom();
}

/*
	TAVLCom
*/

void
TAVLCom::InordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		this->nodo->iz.InordenAux(v, n);
		v[n] = this->nodo->item;
		n += 1;
		this->nodo->de.InordenAux(v, n);
	}
}

void
TAVLCom::PreordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		v[n] = this->nodo->item;
		n += 1;
		this->nodo->iz.PreordenAux(v, n);
		this->nodo->de.PreordenAux(v, n);
	}
}

void
TAVLCom::PostordenAux(TVectorCom &v, int &n) const {
	if(this->nodo != NULL) {
		this->nodo->iz.PostordenAux(v, n);
		this->nodo->de.PostordenAux(v, n);
		v[n] = this->nodo->item;
		n += 1;
	}
}

TAVLCom::TAVLCom() {
	this->nodo = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &a) {
	if(!a.EsVacio()){  // si el arbol no es vacio
		TNodoAVL *aux=new TNodoAVL;
		if(!aux) cerr<<"Error con la memoria"<<endl;
		else{
			aux->fe=a.nodo->fe;
			aux->item=a.nodo->item;
			nodo=aux;
			nodo->iz=a.nodo->iz;
			nodo->de=a.nodo->de;
		}
	} else nodo=NULL;
}

TAVLCom::~TAVLCom() {
	//liberar memoria con delete[]
	if(nodo!=NULL){
		delete nodo;
		nodo=NULL;
	}
}

TAVLCom&
TAVLCom::operator=(const TAVLCom &a){
	if(*this!=a){         // Comprobamos autoasignacion
		if(!a.EsVacio()){  // si el arbol a copiar no es vacio
			if(!EsVacio()){ //si el arbol que invoca no es vacio liberamos toda la memoria
				delete nodo;
				nodo=NULL;
			}
			TNodoAVL *aux=new TNodoAVL;
			if(!aux) cerr<<"Error TAVLCom operator="<<endl;
			else{
				aux->fe=a.nodo->fe;
				aux->item=a.nodo->item;
				nodo=aux;
				nodo->iz=a.nodo->iz;
				nodo->de=a.nodo->de;
			}
		}
		else{
			if(!EsVacio()){
				delete nodo;
				nodo=NULL;
			}
		}
	}
	return *this;
}

bool
TAVLCom::operator==(const TAVLCom &c) {
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
TAVLCom::operator!=(const TAVLCom &c) {
	return !((*this)==c);
}

bool 
TAVLCom::EsVacio() const {
	if(this->nodo == NULL) return true;
	else return false;
}

bool 
TAVLCom::esMenor(TComplejo a, TComplejo b) {
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

bool 
TAVLCom::Insertar(TComplejo &d) {
	
	TAVLCom a,c,e,g;
	TComplejo aux,nulo;

	if(d==nulo) return false;    // Si el numero a insertar es nulo (no hace nada)
	else{
		if(EsVacio()){                      // Si el nodo esta vacio se coloca el elemento
			nodo=new TNodoAVL;
			if(!nodo) cerr<<"Error al crear la memoria en TAVLCom::Insertar(const TComplejo &)"<<endl;
			else{
				nodo->item=d;
				return true;
			}
		}
		else{                     
			if(Buscar(d)) return false; // si el elemento ya existe no hace nada
			else{               
				if(!esMenor(d,nodo->item)){           
					if (nodo->de.Insertar(d)){     
						nodo->fe=nodo->de.Altura()-nodo->iz.Altura();  // se actualiza el factor de equilibrio
						if(nodo->fe>1){   // si el fe es mayor que uno hay que hacer alguna rotacion
							if(nodo->de.nodo->fe==1){ 
								a=nodo->iz;
								c=nodo->de.nodo->iz;
								e=nodo->de.nodo->de;
								aux=nodo->item;
								nodo->item=nodo->de.nodo->item;
								if(nodo->iz.EsVacio())
									nodo->iz.Insertar(aux);
								else
									nodo->iz.nodo->item=aux;
								nodo->de=e;
								nodo->iz.nodo->iz=a;
								nodo->iz.nodo->de=c;

								nodo->iz.nodo->fe=nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
								nodo->fe=nodo->de.Altura()-nodo->iz.Altura();

							}
							if(nodo->de.nodo->fe==-1){ 
								a=nodo->iz;
								c=nodo->de.nodo->iz.nodo->iz;
								e=nodo->de.nodo->iz.nodo->de;
								g=nodo->de.nodo->de;
								aux=nodo->item;
								nodo->item=nodo->de.nodo->iz.nodo->item;
								if(nodo->iz.EsVacio())
									nodo->iz.Insertar(aux);
								else
									nodo->iz.nodo->item=aux;
								nodo->iz.nodo->iz=a;
								nodo->iz.nodo->de=c;
								nodo->de.nodo->iz=e;
								nodo->de.nodo->de=g;
								nodo->iz.nodo->fe=nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
								nodo->de.nodo->fe=nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
								nodo->fe=nodo->de.Altura()-nodo->iz.Altura();
							}
						}
						return true;
					}
					else return false;
				}
				else {
				    // sabemos que va a la izquierda (es menor)
					if (nodo->iz.Insertar(d)){     //llamada recursiva
						nodo->fe=nodo->de.Altura()-nodo->iz.Altura();  // se actualiza el factor de equilibrio
						if (nodo->fe<-1){ // hay que hacer alguna rotacion

							if(nodo->iz.nodo->fe==-1){ 

								a=nodo->iz.nodo->iz;
								c=nodo->iz.nodo->de;
								e=nodo->de;
								aux=nodo->item;
								nodo->item=nodo->iz.nodo->item;

								if(nodo->de.EsVacio())
									nodo->de.Insertar(aux);
								else
									nodo->de.nodo->item=aux;
								
								nodo->iz=a;
								nodo->de.nodo->iz=c;
								nodo->de.nodo->de=e;
								nodo->de.nodo->fe=nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
								nodo->fe=nodo->de.Altura()-nodo->iz.Altura();
							}
							if(nodo->iz.nodo->fe==1){  //rotacion ID
								
								a=nodo->iz.nodo->iz;
								c=nodo->iz.nodo->de.nodo->iz;
								e=nodo->iz.nodo->de.nodo->de;
								g=nodo->de;
								aux=nodo->item;
								nodo->item=nodo->iz.nodo->de.nodo->item;
								
								if(nodo->de.EsVacio())
									nodo->de.Insertar(aux);
								else
									nodo->de.nodo->item=aux;
								
								nodo->iz.nodo->iz=a;
								nodo->iz.nodo->de=c;
								nodo->de.nodo->iz=e;
								nodo->de.nodo->de=g;
								nodo->iz.nodo->fe=nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
								nodo->de.nodo->fe=nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
								nodo->fe=nodo->de.Altura()-nodo->iz.Altura();
							}
						}
						return true;
					}
					else return false;
				}
			}
		}
	}
}

bool
TAVLCom::Borrar(TComplejo &d) {
	bool res;
	TAVLCom a,c,e,g;
	TNodoAVL *aux;
	TComplejo num_aux,nulo;
	if(!Buscar(d)) return false;
	else {
		if(EsVacio()) return false;
		else { //si el arbol no esta vacio
			if(nodo->item==d){ //si hemos encontrado el numero
				if(nodo->de.nodo == NULL && nodo->iz.nodo == NULL){ //si es un nodo hoja (LO QUITAMOS)
					delete nodo;
					nodo = NULL;
					return true;
				}
				else{ //si no es un nodo hoja (SUSTITUIMOS POR EL MAYOR DE LA IZQUIERDA
					if(!nodo->iz.EsVacio()){ //si tiene hijo izquierdo
						aux = nodo->iz.nodo;
						while (!aux->de.EsVacio()){ //mientras que no lleguemos al mayor del subarbol izquierdo	
							aux = aux->de.nodo;
						}
						num_aux = nodo->item;
						nodo->item = aux->item;
						aux->item = num_aux;
						res = nodo->iz.Borrar(d); //llamada recursiva
					}
					else{ //si no tiene hijo hizquierdo al ser avl solo tendra un hijo derecho
						aux = nodo->de.nodo;
						num_aux = nodo->item;
						nodo->item = aux->item;
						aux->item = num_aux;
						res = nodo->de.Borrar(d); //llamada recursiva
					}
				}
			} else { //si no hemos encontrado el numero (SEGUIMOS BUSCANDO DONDE CORRESPONDA)
				if(esMenor(d,nodo->item)) res = nodo->de.Borrar(d);
				else res = nodo->iz.Borrar(d);
			}
			
			if(res == true) { //si hemos quitado algun nodo del arbol (ACTUALIZAR FE Y COMPROBAR REESTRUCTURACIONES)
				nodo->fe = nodo->de.Altura() - nodo->iz.Altura();
				if((nodo->fe==2 && nodo->de.nodo->fe==0)||(nodo->fe==2 && nodo->de.nodo->fe==1)){ // ROTACION DD
					a = nodo->iz;
					c = nodo->de.nodo->iz;
					e = nodo->de.nodo->de;
					num_aux = nodo->item;
					nodo->item = nodo->de.nodo->item;
					if(nodo->iz.EsVacio())
						nodo->iz.Insertar(num_aux);
					else
						nodo->iz.nodo->item = num_aux;
					nodo->de = e;
					nodo->iz.nodo->iz = a;
					nodo->iz.nodo->de = c;
					nodo->iz.nodo->fe = nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
					nodo->fe = nodo->de.Altura()-nodo->iz.Altura();
				}
				if(nodo->fe==2 && nodo->de.nodo->fe==-1){ // ROTACION DI
					a = nodo->iz;
					c = nodo->de.nodo->iz.nodo->iz;
					e = nodo->de.nodo->iz.nodo->de;
					g = nodo->de.nodo->de;
					num_aux = nodo->item;
					nodo->item = nodo->de.nodo->iz.nodo->item;
					if(nodo->iz.EsVacio())
						nodo->iz.Insertar(num_aux);
					else
						nodo->iz.nodo->item = num_aux;
					nodo->iz.nodo->iz = a;
					nodo->iz.nodo->de = c;
					nodo->de.nodo->iz = e;
					nodo->de.nodo->de = g;
					nodo->iz.nodo->fe = nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
					nodo->de.nodo->fe = nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
					nodo->fe = nodo->de.Altura()-nodo->iz.Altura();
				}
				if((nodo->fe==-2 && nodo->iz.nodo->fe==0)||(nodo->fe==-2 && nodo->iz.nodo->fe==-1)){ // ROTACION II
					a = nodo->iz.nodo->iz;
					c = nodo->iz.nodo->de;
					e = nodo->de;
					num_aux = nodo->item;
					nodo->item = nodo->iz.nodo->item;
					if(nodo->de.EsVacio())
						nodo->de.Insertar(num_aux);
					else
						nodo->de.nodo->item = num_aux;
					nodo->iz = a;
					nodo->de.nodo->iz = c;
					nodo->de.nodo->de = e;
					nodo->de.nodo->fe = nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
					nodo->fe = nodo->de.Altura()-nodo->iz.Altura();
				}
				if(nodo->fe==-2 && nodo->iz.nodo->fe==1){ // ROTACION ID
					a = nodo->iz.nodo->iz;
					c = nodo->iz.nodo->de.nodo->iz;
					e = nodo->iz.nodo->de.nodo->de;
					g = nodo->de;
					num_aux = nodo->item;
					nodo->item = nodo->iz.nodo->de.nodo->item;
					if(nodo->de.EsVacio())
						nodo->de.Insertar(num_aux);
					else
						nodo->de.nodo->item = num_aux;
					nodo->iz.nodo->iz = a;
					nodo->iz.nodo->de = c;
					nodo->de.nodo->iz = e;
					nodo->de.nodo->de = g;
					nodo->iz.nodo->fe = nodo->iz.nodo->de.Altura()-nodo->iz.nodo->iz.Altura();
					nodo->de.nodo->fe = nodo->de.nodo->de.Altura()-nodo->de.nodo->iz.Altura();
					nodo->fe = nodo->de.Altura()-nodo->iz.Altura();
				}
			}
			return res;
		}
	}
}

bool
TAVLCom::Buscar(TComplejo &d) {
	if(EsVacio()) return false;
	else{
		if(d==nodo->item) return true;
		else{
			if(esMenor(d, nodo->item)) return(nodo->iz.Buscar(d));
			else return(nodo->de.Buscar(d));
		}
	}
}

TComplejo
TAVLCom::Raiz() {
	TComplejo aux;
	if(this->EsVacio()) return aux;
	else {
		return this->nodo->item;
	}
}

int
TAVLCom::Nodos() const {
	if(!EsVacio()) {
		return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
	} else return 0;
}

int 
TAVLCom::NodosHoja() {
	if(EsVacio()) return 0;
	else{
		if((nodo->iz.EsVacio()) && (nodo->de.EsVacio())) return 1;
		else return (nodo->iz.NodosHoja()+nodo->de.NodosHoja());
	}
}

int
TAVLCom::Altura() {
	int aD, aR;
	if (EsVacio()) return 0;
	else{
	    aD=1+nodo->de.Altura();
	    aR=1+nodo->iz.Altura();
	    if(aD>aR) return aD;
	    else return aR;
	}
}

TVectorCom
TAVLCom::Inorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->InordenAux(v, posicion);
	return v;
}

TVectorCom
TAVLCom::Preorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->PreordenAux(v, posicion);
	return v;
}

TVectorCom
TAVLCom::Postorden() const {
	int posicion = 1;
	TVectorCom v(Nodos());
	this->PostordenAux(v, posicion);
	return v;
}

bool
TAVLCom::encontradoTrayecto(const TComplejo &d, TNodoAVL*& p) {

	while(p != NULL) {
		if(p->item == d) return true;
		return encontradoTrayecto(d,p->iz.nodo) + encontradoTrayecto(d,p->de.nodo);
	}

	return false;

}

bool
TAVLCom::examen(TListaCom& l) {
	TListaCom aux = l.ordenarLista(l);
	TListaPos p = aux.Primera();
	TNodoAVL* avl_puntero_arbol = this->nodo;

	while(!p.EsVacia()) {
		if(!encontradoTrayecto(aux.Obtener(p),avl_puntero_arbol)) return false;
		p = p.Siguiente();
	}

	return true;
}



//FUNCIONES FRIENDS
ostream &operator<< (ostream &os, const TAVLCom &arb) {
	TVectorCom v = arb.Inorden();
	os << v;
 	return os;
}

// TABBCOMPLEJOO


//Pruebas

//Busca y devuelve pos de memoria
/*

TNodoABB*
TABBCom::Busca2(const TComplejo &com){
	bool encontrado=false;
	TNodoABB * this_nodo = NULL;
	if(nodo != NULL){
		if(nodo->item == com){
			 encontrado=true;
			 this_nodo = this->nodo;
		}
		else{
			this_nodo = nodo->iz.Busca2(com);
			if(this_nodo == NULL){
				this_nodo = nodo->de.Busca2(com);
			}
		}
	}
	return this_nodo;
}

TListaCom
TABBCom::Camino(const TListaCom &lista){
	TListaCom lista_Aux;
	TListaPos recorredor;
	recorredor = lista.Primera();
	TNodoABB *apuntador = NULL;
	bool camino = false;
	if(!EsVacio()){
		if(!lista.EsVacia()){
			TVectorCom v1;
			v1 = Preorden();
			for(int i = v1.Tamano(); i>0 ;i--){
				lista_Aux.InsCabeza(v1[i]);
			}
			apuntador = Busca2(recorredor.pos->e);
			if(apuntador != NULL){
				camino = true;
				recorredor = recorredor.Siguiente();
				while(!recorredor.EsVacia() && camino){
					if(apuntador->de.nodo->item == recorredor.pos->e){
						apuntador = apuntador->de.nodo;
					}
					else if(apuntador->iz.nodo->item == recorredor.pos->e){
						apuntador = apuntador->iz.nodo;
					}
					else{
						camino = false;
					}
					recorredor = recorredor.Siguiente();
				}
				if(camino == true){
					for(TListaPos i = lista.Primera(); !i.EsVacia();i = i.Siguiente()){
						lista_Aux.Borrar(i.pos->e);
					}
				}
			}
			else{

			}
		}
	}
	return lista_Aux;
}
*/



//TAVLCOMPLEJO

//Devuelve posicion de memoria com

/*
TNodoAVL*
TAVLCom::Busca2(const TComplejo &com){
	bool encontrado=false;
	TNodoABB * this_nodo = NULL;
	if(raiz != NULL){
		if(raiz->item == com){
			 encontrado=true;
			 this_nodo = this->raiz;
		}
		else{
			this_nodo = raiz->iz.Busca2(com);
			if(this_nodo == NULL){
				this_nodo = raiz->de.Busca2(com);
			}
		}
	}
	return this_nodo;
}

//Recorre arbol y devuelve dependiendo

void
TAVLCom::BuscaEnAVL(TComplejo &com, int &valor){
	if(!EsVacio()){
		if(raiz->iz.raiz->item == com){
			valor = 1;
		}
		else if(raiz->de.raiz->item == com){
			valor = 2;
		}
		else{
			raiz->iz.Buscar(com);
			raiz->de.Buscar(com);
		}
	}
}

*/
//Recorrer arbol y lista a la vez

/*
int *
TAVLCom::BuscaAVL(TListaCom &lista){
	if(lista.EsVacia()){
		return NULL;
	}
	else{
		int valor = 0;
		int contador = 0;
		int longitud = lista.Longitud();
		int *v = new int[longitud] ;
		for (int i =0; i<longitud; i++){
			v[i] = 0;
		}
		if(EsVacio()){
		}
		else{
			for(TListaPos i = lista.Primera(); !i.EsVacia(); i= i.Siguiente()){
				if(raiz->item == i.pos->e){
					v[contador] = 3;
				}
				else{
					BuscaEnAVL(i.pos->e,valor);
					v[contador] = valor;
				}
				valor = 0;
				contador ++;
			}
		}
		return v;
	}
}

*/
//FIN