#pragma once
#include "Pagina.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <fstream> 
#include <queue>


using namespace std;

bool ordenar_point_x(Point &a, Point &b)
{
	if(a.x < b.x) return true;
	return false;
}

bool ordenar_point_y(Point &a, Point &b)
{
	if(a.y < b.y) return true;
	return false;
}

bool ordenar_rect_x(Rectangle &a, Rectangle &b)
{
	if(a.x - a.w < b.x - b.x) return true;
	return false;
}

bool ordenar_rect_y(Rectangle &a, Rectangle &b)
{
	if(a.y - a.h < b.y - b.h) return true;
	return false;
}


class RTree
{
public:
	RTree(int cap);
	void insert2(Point p);
	void mostrar();
	void obtener_graphviz();
	vector<Point> range_query(Rectangle a);
	Nodo* root;
	int capacidad;

private:
	void range_query2(Nodo * b,Rectangle a,vector<Point>&c);
	void insert(Point p,Nodo * base);
	void handle_overflow(Nodo * padre);
	void split_leaf(std::vector<Point> a, Nodo *b, Nodo *c,Rectangle &a1,Rectangle &a2);
	void split_internal_nodes(std::vector<Rectangle> a, Nodo *b, Nodo *c,Rectangle &a1,Rectangle &a2);
	void actualizar(Nodo * actual,Nodo *a,Nodo *b,Nodo *c,Rectangle &a1,Rectangle &a2);
	void evaluar_leaf(const std::vector<Point> &a, std::vector<Point> &b,std::vector<Point> &c,Rectangle &ans1,Rectangle &ans2,bool estado = true);
	void evaluar_nodo(const std::vector<Rectangle> &a, std::vector<Rectangle> &b,std::vector<Rectangle> &c,Rectangle &ans1,Rectangle &ans2);
	Rectangle obtener_rec_puntos(std::vector<Point> a,bool estado);
	Rectangle obtener_rec_rect(std::vector<Rectangle> a);
	
};

RTree::RTree(int cap)
{
	this->capacidad = cap;
	root = new Nodo(cap);
}
void RTree::insert2(Point b)
{
	insert(b,root);
}

vector<Point> RTree::range_query(Rectangle a)
{
	vector<Point> valores;
	range_query2(root,a,valores);
	return valores;
}

void RTree::range_query2(Nodo * b,Rectangle a,vector<Point>&c)
{
	if (b->isleaf())
	{
		for (int i = 0; i < b->data_hoja.size(); i++)
		{
			if (a.contains(b->data_hoja[i])) c.push_back(b->data_hoja[i]);
		}		
	}
	else
	{
		for (int i = 0; i < b->data_inter.size(); i++)
		{
			if(a.intersect(b->data_inter[i]))
			{
				range_query2(b->hijos[i],a,c);
			}
		}
		
	}
	
}

void RTree::mostrar()
{
	for (int i = 0; i < root->data_inter.size();i++)
	{
		std::cout << (root->data_inter[i].x)<<" "<<(root->data_inter[i].y)<<" "<<(root->data_inter[i].w)<<" "<<(root->data_inter[i].h)<<std::endl;
	}
	for (int i = 0; i < root->data_hoja.size();i++)
	{
		std::cout << (root->data_hoja[i]).x << " "<<(root->data_hoja[i]).y <<std::endl;
	}
}

void RTree::obtener_graphviz()
{
	ofstream texto1("datos.dot");
	texto1.close();
	
	fstream texto("datos.dot");
	texto << "digraph g {"<<endl;
	texto << "node [shape = record,height=.1];"<<endl;
	queue<Nodo *>values;
	queue<int>padres;
	queue<int>cantidad;
	values.push(root);
	string nombre = "e";
	int estado = 0;
	int node = 0;
	int helper = 0;
	while(!values.empty())
	{
		bool avanzar = !padres.empty();
		
		Nodo *aux = values.front();
		values.pop();
		if(aux->isleaf())
		{
			texto << "node"+to_string(node++)+"[label = "+'"';
			for (int i = 0; i < aux->data_hoja.size(); i++)
			{
				texto << "<f"+to_string(i)+"> |("+to_string(int(aux->data_hoja[i].x))+","+to_string(int(aux->data_hoja[i].y))+")|";
			}
			texto<<'"' <<"];"<<endl;	
			if(avanzar)
			{
				if (helper == cantidad.front()) 
				{
					padres.pop();
					cantidad.pop();
					helper = 0;
				}
				texto << '"' <<"node"<<padres.front()<<'"'<<":f"<<to_string(helper++) << "-> "<<'"'<<"node"<<node-1<<'"'<<endl;
			}
		}
		else
		{
			texto << "node"+to_string(node++)+"[label = "+'"';
			for (int i = 0; i < aux->data_inter.size(); i++)
			{
				texto << "<f"+to_string(i)+"> |"+nombre+to_string(estado++)+"|";
				values.push(aux->hijos[i]);
				
			}
			texto<<'"' <<"];"<<endl;
			if(avanzar)
			{
				if (helper == cantidad.front()) 
				{
					padres.pop();
					cantidad.pop();
					helper = 0;
				}
				texto << '"'<<"node"<<padres.front()<<'"'<<":f"<<to_string(helper++) << "-> " <<'"' << "node"<<node-1<<'"'<<endl;
			}
			padres.push(node-1);
			cantidad.push(aux->data_inter.size());
			
		}
			
	}
		
	texto << "}"<<endl;
	texto.close();
}

void RTree::insert(Point b,Nodo * base)
{
	if (base->isleaf())
	{
		for (int i = 0; i < base->data_hoja.size(); i++)
		{
			if (base->data_hoja[i].esigual(b)) return;
		}
		
		base->data_hoja.push_back(b);
		if (base->isoverflow())
		{
			handle_overflow(base);
		}
	}
	else
	{
		Rectangle solucion(0,0,0,0);
		int pos;
		Nodo* selec = base->choose_subtree(b,solucion,pos);
		selec->padre = base;
		insert(b,selec);
		cout << "Checkeando" << endl;
		
		if(! (base->data_inter[pos].contains(b)))
		{
			solucion.pasar_info((selec-> padre)->data_inter[pos]);
		}
			
		
		
	}
}
Rectangle RTree::obtener_rec_puntos(std::vector<Point> a,bool estado)
{
	Rectangle answer(0,0,0,0);
	if (estado)
	{
		//cout << (a[a.size()-1].x - a[0].x) << endl;
		answer.w = (a[a.size()-1].x - a[0].x)/float(2.0);
		answer.x = a[a.size()-1].x - answer.w;
		sort(a.begin(),a.end(),ordenar_point_y);
		answer.h = (a[a.size()-1].y - a[0].y)/float(2.0);
		answer.y = a[a.size()-1].y - answer.h;
	}
	else
	{
		answer.h = (a[a.size()-1].y - a[0].y)/float(2.0);
		answer.y = a[a.size()-1].y - answer.h;
		sort(a.begin(),a.end(),ordenar_point_x);
		answer.w = (a[a.size()-1].x - a[0].x)/float(2.0);
		answer.x = a[a.size()-1].x - answer.w;
	}
	answer.checkear();
	return answer;
	
}

Rectangle RTree::obtener_rec_rect(std::vector<Rectangle> a)
{
	Rectangle answer(0,0,0,0);
	float x_min,x_max,y_min,y_max;
	x_min= y_min =1e9;
	x_max = y_max = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if(a[i].x - a[i].w < x_min)
		{
			x_min = a[i].x - a[i].w;
		} 
		if(a[i].x + a[i].w > x_max)
		{
			x_max = a[i].x + a[i].w;
		} 
		if(a[i].y + a[i].h > y_max)
		{
			y_max = a[i].y + a[i].h;
		} 
		if(a[i].y - a[i].h < y_min)
		{
			y_min = a[i].y - a[i].h;
		} 
	}
	/*
	cout << "-----------------------------"<<endl;
	cout << x_max<<" "<<x_min<<endl;
	cout << y_max<<" "<<y_min<<endl;
	cout << "-----------------------------"<<endl;*/
	answer.w = (x_max - x_min)/float(2.0);
	answer.x = (x_max - answer.w);
	answer.h = (y_max - y_min)/float(2.0);
	answer.y = (y_max - answer.h);

	return answer;
}

void RTree::evaluar_nodo(const std::vector<Rectangle> &a, std::vector<Rectangle> &b,std::vector<Rectangle> &c,Rectangle &ans1,Rectangle &ans2)
{
	int valor_min = int(0.4 * root->capacidad);
	float perimetro_minimo = ans1.calcular_perimetro()+ans2.calcular_perimetro() ==0? 1e9 : ans1.calcular_perimetro()+ans2.calcular_perimetro(); 

	std::vector<Rectangle>a1;
	std::vector<Rectangle>a2;

	for (int i = valor_min; i < a.size()-valor_min; i++)
	{
		
		a1.assign(a.begin(),a.begin()+i);
		a2.assign(a.begin()+i,a.end());
		Rectangle prueba = obtener_rec_rect(a1);
		Rectangle prueba1 = obtener_rec_rect(a2);

		float p_prueba = prueba.calcular_perimetro();
		float p_prueba1 = prueba1.calcular_perimetro();
		if (p_prueba + p_prueba1 < perimetro_minimo)
		{
	
			perimetro_minimo = p_prueba + p_prueba1;
			prueba.pasar_info(ans1);
			prueba1.pasar_info(ans2);
			b = a1;
			c = a2;
			
		}

	}
}

void RTree::evaluar_leaf(const std::vector<Point> &a, std::vector<Point> &b,std::vector<Point> &c,Rectangle &ans1,Rectangle &ans2,bool estado)
{
	int valor_min = int(0.4 * root->capacidad);
	float perimetro_minimo = ans1.calcular_perimetro()+ans2.calcular_perimetro() ==0? 1e9 : ans1.calcular_perimetro()+ans2.calcular_perimetro(); 

	std::vector<Point>a1;
	std::vector<Point>a2;

	for (int i = valor_min; i < a.size()-valor_min; i++)
	{
		
		a1.assign(a.begin(),a.begin()+i);
		a2.assign(a.begin()+i,a.end());
		Rectangle prueba = obtener_rec_puntos(a1,estado);
		Rectangle prueba1 = obtener_rec_puntos(a2,estado);

		float p_prueba = prueba.calcular_perimetro();
		float p_prueba1 = prueba1.calcular_perimetro();
		if (p_prueba + p_prueba1 < perimetro_minimo)
		{
	
			perimetro_minimo = p_prueba + p_prueba1;
			prueba.pasar_info(ans1);
			prueba1.pasar_info(ans2);
			b = a1;
			c = a2;
			
		}

	}
	
}

void RTree::split_leaf(std::vector<Point> a, Nodo *best1, Nodo *best2,Rectangle &ans1,Rectangle &ans2)
{
	sort(a.begin(),a.end(),ordenar_point_x);
	evaluar_leaf(a,best1->data_hoja,best2->data_hoja,ans1,ans2);
	sort(a.begin(),a.end(),ordenar_point_y);
	evaluar_leaf(a,best1->data_hoja,best2->data_hoja,ans1,ans2,false);
}

void RTree::split_internal_nodes(std::vector<Rectangle> a, Nodo *best1, Nodo *best2,Rectangle &a1,Rectangle &a2)
{
	sort(a.begin(),a.end(),ordenar_rect_x);
	evaluar_nodo(a,best1->data_inter,best2->data_inter,a1,a2);
	reverse(a.begin(),a.end());
	evaluar_nodo(a,best1->data_inter,best2->data_inter,a1,a2);
	sort(a.begin(),a.end(),ordenar_rect_y);
	evaluar_nodo(a,best1->data_inter,best2->data_inter,a1,a2);
	reverse(a.begin(),a.end());
	evaluar_nodo(a,best1->data_inter,best2->data_inter,a1,a2);

}

void RTree::actualizar(Nodo * actual, Nodo * father, Nodo *first, Nodo *Second,Rectangle &a1,Rectangle &a2)
{
	int pos;
	if (actual->isleaf())
	{		
		for (int i = 0; i < father->data_inter.size(); i++)
		{
			if (father->data_inter[i].contains(actual->data_hoja[0]))
			{
				bool estado = 1;
				for (int j = 1; j < actual->data_hoja.size()-1; j++)
				{
					if (!(father->data_inter[i].contains(actual->data_hoja[j])))
					{
						estado = 0;
						break;
					}
				}
				if(estado)
				{
					pos = i;
				}
				
			}
		}

		father->data_inter.insert(father->data_inter.begin()+pos,a2);
		father->data_inter.insert(father->data_inter.begin()+pos,a1);
		Nodo * aux = father->hijos[pos]; 
		father->hijos.insert(father->hijos.begin()+pos,Second);
		father->hijos.insert(father->hijos.begin()+pos,first);
		Second->padre = father;
		first->padre = father;
		father->data_inter.erase(father->data_inter.begin()+pos+2);
		father->hijos.erase(father->hijos.begin()+pos+2);
		
	}
	else
	{
		for (int i = 0; i < father->data_inter.size(); i++)
		{
			if (father->data_inter[i].contains_rectangle(actual->data_inter[0]))
			{
				bool estado = 1;
				for (int j = 1; j < actual->data_inter.size(); j++)
				{
					if (!(father->data_inter[i].contains_rectangle(actual->data_inter[j])))
					{
						estado = 0;
						break;
					}
				}
				if(estado)
				{
					pos = i;
				}
				
			}
		}
		father->data_inter.insert(father->data_inter.begin()+pos,a2);
		father->data_inter.insert(father->data_inter.begin()+pos,a1);
		Nodo * aux = father->hijos[pos]; 
		father->hijos.insert(father->hijos.begin()+pos,Second);
		father->hijos.insert(father->hijos.begin()+pos,first);
		Second->padre = father;
		first->padre = father;
		for (int i = 0; i < first->data_inter.size(); i++)
		{
			for (int j = 0; j < aux->data_inter.size(); j++)
			{
				if(first->data_inter[i].esigual(aux->data_inter[j]))
				{
					first->hijos[i] = aux->hijos[j];
					aux->hijos[j] = NULL;
					break;
				}
			}
			
		}
		for (int i = 0; i < Second->data_inter.size(); i++)
		{
			for (int j = 0; j < aux->data_inter.size(); j++)
			{
				if(Second->data_inter[i].esigual(aux->data_inter[j]))
				{
					Second->hijos[i] = aux->hijos[j];
					aux->hijos[j] = NULL;
					break;
				}
			}
		}
		
		
		father->data_inter.erase(father->data_inter.begin()+pos+2);
		father->hijos.erase(father->hijos.begin()+pos+2);
		//delete aux;
	}


	
} 

void RTree::handle_overflow(Nodo * u)
{
	Nodo *best1 = new Nodo(u->capacidad);
	Nodo *best2 = new Nodo(u->capacidad);
	Rectangle ans(0,0,0,0);
	Rectangle ans1(0,0,0,0);
	if (u -> isleaf())
	{
		split_leaf(u->data_hoja,best1,best2,ans,ans1);
	}
	else
	{
		split_internal_nodes(u->data_inter,best1,best2,ans,ans1);
	}

	if (u -> isroot())
	{
		Nodo * new_root = new Nodo(u->capacidad);
		new_root->data_inter.push_back(ans);
		new_root->data_inter.push_back(ans1);
		new_root->hijos.push_back(best1);
		best1->padre = new_root;
		new_root->hijos.push_back(best2);
		best2->padre = new_root;
		
		
		if (u->hijos.size()!=0)
		{
			for (int i = 0; i < best1->data_inter.size(); i++)
			{
				cout << best1->data_inter[i].x<<endl;
				for (int j = 0; j < u->data_inter.size(); j++)
				{

					if(best1->data_inter[i].esigual(u->data_inter[j]))
					{
	
						best1->hijos.insert(best1->hijos.begin()+i,u->hijos[j]);
	
						break;
					}
				}
				
			}

			for (int i = 0; i < best2->data_inter.size(); i++)
			{
				for (int j = 0; j < u->data_inter.size(); j++)
				{
					if(best2->data_inter[i].esigual(u->data_inter[j]))
					{
						best2->hijos.insert(best2->hijos.begin()+i,u->hijos[j]);
						break;
					}
				}
			}
		}
		Nodo * aux = root;
		root = new_root;
		delete aux;
		
		
	}
	else
	{
		Nodo * padre_u = u -> padre;
		actualizar(u,padre_u, best1,best2,ans,ans1);
		if (padre_u->isoverflow())
		{
			handle_overflow(padre_u);
			
		}
	}
	
}