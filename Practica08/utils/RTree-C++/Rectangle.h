#pragma once
#include "Punto.h"

class Rectangle
{
public:
	float x;
	float y;
	float w;
	float h;
	Rectangle(float x,float y,float w,float h);
	bool contains(const Point& a);
	bool intersect(const Rectangle& a);
	float calcular_perimetro();
	Rectangle reorganizar_rectangle(Point b);
	~Rectangle();
	void pasar_info(Rectangle &b);
	void checkear();
	bool esigual(Rectangle a);
	bool contains_rectangle(const Rectangle& a);


};

void Rectangle::pasar_info(Rectangle &b)
{
	b.x = x;
	b.y = y;
	b.w = w;
	b.h = h;
}

bool Rectangle::esigual(Rectangle a)
{
	if (a.x == x && a.y==y && a.w == w && a.h == h) return true;
	return false;
}

bool Rectangle::contains_rectangle(const Rectangle& a)
{
	if (a.x - a.w < x - w) return false;
	if (a.x + a.w > x + w) return false;
	if (a.y - a.h < y - h) return false;
	if (a.y + a.h > y + h) return false;
	return true;

}

void Rectangle::checkear()
{
	if (w == 0)
	{
		w += 0.2;
	}
	if(h == 0)
	{
		h += 0.2;
	}
}

Rectangle::Rectangle(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rectangle::~Rectangle()
{
}

bool Rectangle::contains(const Point& a)
{
	if (x + w >= a.x && x - w <= a.x && y + h >= a.y && y - h <= a.y) return true;
	return false;
}

bool Rectangle::intersect(const Rectangle& rango)
{
	if (rango.x - rango.w < x + w || rango.y + rango.h > y - h || rango.y - rango.h < y + h || rango.x + rango.w > x - w)
	{
		return true;
	}
	return false;
}

float Rectangle::calcular_perimetro()
{
	return 4.0 * w + 4.0 * h;
}

Rectangle Rectangle::reorganizar_rectangle(Point b)
{
	float largo = 2.0 * w;
	float distancia_largo;
	if (b.x < x - w)
	{
		distancia_largo = b.x - (x-w);
		largo += ((x - w)-b.x);
	}
	else if (b.x > x + w)
	{
		distancia_largo = b.x - (x+w);
		largo += ((b.x - x+w));
	}


	float ancho = 2.0 * h;
	float distancia_ancho;
	if (b.y < y - h)
	{
		distancia_ancho = b.y - (y-h);
		ancho += ((y - h) - b.y);
	}
	else if (b.y > y + h)
	{
		distancia_ancho = b.y - (y-h);
		ancho += ((b.y - y+h));
	}
	return Rectangle(x + (distancia_largo/2), y + (distancia_ancho/2),largo / 2, ancho / 2);
}
