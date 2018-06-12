#include "tcomplejo.h"

#ifndef __TLISTANODO__
#define __TLISTANODO__

class TListaNodo {
	friend class TListaCom;
	friend class TListaPos;
	private:
		TComplejo e;
		TListaNodo *anterior;
		TListaNodo *siguiente;
	public:
		TListaNodo();
		TListaNodo( const TListaNodo&);
		~TListaNodo();
		TListaNodo &operator=(const TListaNodo&);
};

#endif

#ifndef __TLISTAPOS__
#define __TLISTAPOS__

class TListaPos {
	friend ostream &operator<<(ostream&, TListaPos&);
	friend class TListaCom; //para copia
	private:
		TListaNodo *pos;
	public:
		TListaPos();
		TListaPos(const TListaPos&);
		~TListaPos();
		TListaPos& operator=(const TListaPos&);

		bool operator==(TListaPos&);
		bool operator!=(TListaPos&);

		TListaPos Anterior() const;
		TListaPos Siguiente() const;
		bool EsVacia();

};

#endif

#ifndef __TLISTACOM__
#define __TLISTACOM__

class TListaCom {
	friend ostream &operator<<(ostream&,const TListaCom&);
	private:
		TListaNodo *primero;
		TListaNodo *ultimo;
	public:

		TListaCom();
		TListaCom(const TListaCom&);
		~TListaCom();
		TListaCom& operator=(const TListaCom&);

		bool operator==( const TListaCom&);
		bool operator!=(const TListaCom&);
		TListaCom operator+(const TListaCom&);
		TListaCom operator-(const TListaCom&);

		bool EsVacia() const;
		bool InsCabeza(TComplejo&);
		bool InsertarI(TComplejo&, const TListaPos&);
		bool InsertarD(TComplejo&, const TListaPos&);
		bool Borrar(TComplejo&);
		bool BorrarTodos(TComplejo&);
		bool Borrar(TListaPos&);
		TComplejo Obtener(const TListaPos&) const;
		bool Buscar(const TComplejo&) const;
		int Longitud() const;
		TListaPos Primera() const;
		TListaPos Ultima() const;
		TListaCom ordenarLista(const TListaCom&);
};

#endif