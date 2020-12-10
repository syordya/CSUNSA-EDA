#include <SFML/Graphics.hpp>
#include "RTree.h"


using namespace sf;
int main()
{
	RenderWindow window(VideoMode(900,700), "RTree-demo");
	
	RTree prueba(3);

	vector<Point> testeador;

	/*prueba.insert2(Point(400,500));
	
	prueba.insert2(Point(600,300));
	prueba.insert2(Point(640,500));
	prueba.insert2(Point(230,150));
	prueba.mostrar();
	prueba.insert2(Point(150,200));
	prueba.mostrar();
	testeador.push_back(Point(400,500));
	testeador.push_back(Point(600,300));
	testeador.push_back(Point(640,500));
	testeador.push_back(Point(230,150));
	testeador.push_back(Point(150,200));
	vector<CircleShape> pp1;
	for(int i= 0; i < testeador.size();i++)
	{
		CircleShape shape(5.f);
		shape.setFillColor(sf::Color::Black);
		shape.setPosition(testeador[i].x,testeador[i].y);
		pp1.push_back(shape);
	}
	
	prueba.obtener_graphviz();
	cout << "---------------------------"<<endl;
	
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (int i = 0; i < pp1.size(); i++)
		{
			window.draw(pp1[i]);
		}
		
		window.display();
		
	}
*/
	/*prueba.insert2(Point(13,7));
	prueba.mostrar();
	prueba.insert2(Point(15,9));
	prueba.insert2(Point(13,9));
	
	prueba.insert2(Point(17,8));
	prueba.insert2(Point(16,1));
	prueba.mostrar();*/
	
	
	
	vector<CircleShape> pp;
	vector<RectangleShape> pp1;
	sf::RectangleShape consulta(sf::Vector2f(100,100));
	consulta.setOutlineThickness(5);
	consulta.setOutlineColor (sf::Color::Blue);
	consulta.setPosition(300,300);
	
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if(Mouse::isButtonPressed(sf::Mouse::Right))
		{
			window.close();
		}
		if(Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i ss = sf::Mouse::getPosition();
			CircleShape shape(5.f);
			shape.setFillColor(sf::Color::Black);
			shape.setPosition(ss.x,ss.y);
			bool pasa = 1;
			for (int i = 0; i < pp.size(); i++)
			{
				sf::Vector2f val = pp[i].getPosition();
				if(int(val.x) == ss.x || int(val.y) == ss.y)
				{
					pasa = 0;
					break;
				}
			}
			if(pasa)
			{
				pp.push_back(shape);
				prueba.insert2(Point(float(ss.x),float(ss.y)));
				vector<Point> answer_consulta = prueba.range_query(Rectangle(350,350,50,50));
				cout << "PUNTOS DENTRO: "<<answer_consulta.size()<<endl;
			}
			
				
			
		}
		pp1.clear();
		queue<Nodo *>values;
		values.push(prueba.root);
		while(!values.empty())
		{
			Nodo *aux = values.front();
			values.pop();
			if(aux->isleaf())
			{
				
			}
			else
			{
				for (int i = 0; i < aux->data_inter.size(); i++)
				{

					sf::RectangleShape rectangulo(sf::Vector2f(aux->data_inter[i].w*2,aux->data_inter[i].h*2));
					rectangulo.setOutlineThickness(5);
					rectangulo.setOutlineColor (sf::Color::Red);
					rectangulo.setPosition(aux->data_inter[i].x-aux->data_inter[i].w,aux->data_inter[i].y-aux->data_inter[i].h);
					pp1.push_back(rectangulo);
					values.push(aux->hijos[i]);
				}
				
			}
			
		}
		window.draw(consulta);

		for (int i = 0; i < pp1.size(); i++)
		{
			window.draw(pp1[i]);
		}
		for (int i = 0; i < pp.size(); i++)
		{
			window.draw(pp[i]);
		}
		
		window.display();
		
	}
	//prueba.obtener_graphviz();

	return 0;
}