#pragma once
#include <vector>
#include "Rectangle.h"
#include "Punto.h"

class Nodo
{
public:
	int capacidad;
	Nodo* padre;
	std::vector<Point> data_hoja;
	std::vector<Rectangle> data_inter;
	std::vector<Nodo*> hijos;
	Nodo(int tamanho, Nodo* p = NULL);
	~Nodo();
	bool isoverflow();
	bool isleaf();
	bool isroot();
	Nodo* choose_subtree(Point b,Rectangle &bb,int &pos);
};

Nodo::Nodo(int tamanho, Nodo* p)
{
	this->capacidad = tamanho;
	padre = p;
}

Nodo::~Nodo()
{
}

bool Nodo::isroot()
{
	if (padre == NULL) return true;
	return false;
}

bool Nodo::isoverflow()
{
	if (data_hoja.size() > capacidad || data_inter.size() > capacidad)
	{
		return true;
	}
	return false;
}

bool Nodo::isleaf()
{
	if (hijos.size() == 0)
	{
		return true;
	}
	return false;
}


Nodo* Nodo::choose_subtree(Point b,Rectangle &bb,int &pos)
{
	Nodo* aux = NULL;
	float perimetro = 1e9;
	for (int i = 0; i < data_inter.size(); i++)
	{
		if (data_inter[i].contains(b)) 
		{
			pos = i;
			return hijos[i];
		}
		else
		{
			Rectangle value = data_inter[i].reorganizar_rectangle(b);
			float new_perimetro = value.calcular_perimetro(); 
			if (new_perimetro < perimetro)
			{
				pos = i;
				value.pasar_info(bb);
				perimetro = new_perimetro;
				aux = hijos[i];
			}
		}
	}
	return aux;
}
