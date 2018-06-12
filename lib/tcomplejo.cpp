#include "../include/tcomplejo.h"
#include <math.h> //for sqrt, pow

//sobrecarga asignacion
TComplejo&
TComplejo::operator= (const TComplejo& t) {
  if(this != &t) {
    (*this).~TComplejo();
    this->Re(t.Re());
    this->Im(t.Im());
  }
  return (*this);
}

//Sobrecarga de operadores aritmético suma
TComplejo
TComplejo::operator+ (const TComplejo& t) const {
  TComplejo aux;
  aux.Re(this->Re() + t.Re());
  aux.Im(this->Im() + t.Im());
  return aux;
}

//Sobrecarga de operadores aritmético resta
TComplejo
TComplejo::operator- (const TComplejo& t) const{
  TComplejo aux;
  aux.Re(this->Re() - t.Re());
  aux.Im(this->Im() - t.Im());
  return aux;
}

//Sobrecarga de operadores aritmético producto
//Formula: (a + bi) · (c + di) = (ac − bd) + (ad + bc)i
TComplejo
TComplejo::operator* (const TComplejo& t) const{
  TComplejo aux;
  aux.Re((this->Re()*t.Re()) - (this->Im()*t.Im()));
  aux.Im((this->Re()*t.Im()) - (this->Im()*t.Re()));
  return aux;
}

//Sobrecarga de operadores aritmético suma double
TComplejo
TComplejo::operator+ (double d) {
  TComplejo c(d);
  return ((*this)+c);
}

//Sobrecarga de operadores aritmético resta double
TComplejo
TComplejo::operator- (double d) {
  TComplejo c(d);

  return (*this)-c;
}

//Sobrecarga de operadores aritmético mult double
TComplejo
TComplejo::operator* (double d) {
  TComplejo c(d);
  return ((*this)*c);
}

//igualdad de num complejos
bool 
TComplejo::operator== (const TComplejo& t) {
  return (this->Re() == t.Re() && this->Im()==t.Im());
}

 //desigualdad de num complejos
bool 
TComplejo::operator!= (const TComplejo& t) {
  return !(this->Re() == t.Re() && this->Im()==t.Im());
}

//Calcula el argumento (en radianes)
double 
TComplejo::Arg(void) {
 return atan2(this->Im(),this->Re());
}

//Calcula el módulo  
double 
TComplejo::Mod(void) {
  //por tema de decimales no se pone directamente en el return
 double a = sqrt(pow(this->Re(),2) + pow(this->Im(),2));
 return a;
}

//FUNCIONES FRIENDS
ostream &operator<< (ostream &os, const TComplejo &t) {
  os << "(" << t.Re() << " " << t.Im() << ")";
  return os;
}

//sobrecarga para suma de double con complejos
TComplejo operator+ (double d,TComplejo& t) {
  TComplejo aux(d);
  return aux+t;
}

//sobrecarga para resta de double con complejos
TComplejo operator- (double d, TComplejo& t) {
  TComplejo aux(d);
  return aux-t;
}

//sobrecarga para producto de double con complejos
TComplejo operator* (double d, TComplejo& t) {
  TComplejo aux(d);
  return aux*t;
}
