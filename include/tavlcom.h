#ifndef TABBCOM
#define TABBCOM

#include <iostream>
#include <queue>
#include "tvectorcom.h"
#include "tlistacom.h"

using namespace std;

class TNodoAVL;

class TAVLCom {
	friend ostream &operator << (ostream &, const TAVLCom &);
	friend TNodoAVL;
private:
	TNodoAVL *nodo;
	void InordenAux(TVectorCom &, int &) const;
	void PreordenAux(TVectorCom &, int &) const;
	void PostordenAux(TVectorCom &, int &) const;
	bool esMenor(TComplejo,TComplejo);
	bool encontradoTrayecto(const TComplejo &, TNodoAVL*&);
public:
	//canónicas
	TAVLCom();
	TAVLCom(const TAVLCom &);
	~TAVLCom();
	TAVLCom &operator=(const TAVLCom &);
	//
	bool operator ==(const TAVLCom &);
	bool operator !=(const TAVLCom &);
	bool EsVacio() const;

	bool Insertar(TComplejo &);
	bool Buscar(TComplejo &);
	bool Borrar(TComplejo &);

	int Altura();
	int Nodos() const;
	int NodosHoja();

	TVectorCom Inorden() const;
	TVectorCom Preorden() const;
	TVectorCom Postorden() const;

	TComplejo Raiz();
	bool examen(TListaCom&);
};

class TNodoAVL {
	friend TAVLCom;
private:
	TComplejo item;
	TAVLCom iz, de;
	int fe;
public:
	TNodoAVL();
	TNodoAVL(const TNodoAVL &);
	~TNodoAVL();
	TNodoAVL &operator=(TNodoAVL &);
};

#endif