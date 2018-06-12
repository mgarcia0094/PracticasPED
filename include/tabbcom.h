#ifndef TABBCOM
#define TABBCOM

#include <iostream>
#include <queue>
#include "tvectorcom.h"

using namespace std;

class TNodoABB;

class TABBCom {
	friend ostream &operator << (ostream &, const TABBCom &);
	friend TNodoABB;
private:
	TNodoABB *nodo;
	void InordenAux(TVectorCom &, int &) const;
	void PreordenAux(TVectorCom &, int &) const;
	void PostordenAux(TVectorCom &, int &) const;
	int NodosRec(const TABBCom &) const;
	int NodosHojasRec(const TABBCom &) const;
	int AlturaRec(TABBCom &);
	bool BuscarRec(TABBCom &, TComplejo &);
	void InsertarRec(TABBCom &, TComplejo &);
	TABBCom EncontrarArbol(TABBCom &, TComplejo &);
	TComplejo EliminarNodoMax(TABBCom &);
	void SustituirNumero(TABBCom &, TComplejo &, TComplejo );
	void RecorrerNiveles(TABBCom, queue<TABBCom*> &, TVectorCom &) const;
	void EliminarConexion(TABBCom &, TComplejo &);
	void BorrarComplejo(TABBCom &, TComplejo &);
	TComplejo BuscarMayor(TABBCom&);
	void BorrarRec(TComplejo &);
	bool esMenor(TComplejo,TComplejo);
public:
	TABBCom();
	TABBCom(const TABBCom &);
	~TABBCom();
	TABBCom &operator=(const TABBCom &);
	bool operator ==(const TABBCom &);
	bool EsVacio() const;
	bool Insertar(TComplejo &);
	bool Borrar(TComplejo &);
	bool Buscar(TComplejo &);
	TComplejo Raiz();
	int Altura();
	int Nodos() const;
	int NodosHoja() const;
	TVectorCom Inorden() const;
	TVectorCom Preorden() const;
	TVectorCom Postorden() const;
	TVectorCom Niveles() const;
};

class TNodoABB {
	friend TABBCom;
private:
	TComplejo item;
	TABBCom iz, de;
public:
	TNodoABB();
	TNodoABB(const TNodoABB &);
	~TNodoABB();
	TNodoABB &operator=(TNodoABB &);
};

#endif