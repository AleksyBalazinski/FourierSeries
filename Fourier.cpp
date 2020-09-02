#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
const double pi = 3.14159265;
const double dx = 0.001;
const int iterations = 2 * pi / dx;

double F(double x) //parabola
{
	return x * x;
}

double a_k(int k, double (*func)(double x))
{
	double sum = 0;
	if (k >= 1)
	{
		for (int i = 0; i <= iterations; i++)
		{
			sum += (*func)(-pi + dx * i) * cos(k * (-pi + dx * i)) * dx;
		}
		return (sum / pi);
	}
	if (k == 0)
	{
		for (int i = 0; i <= iterations; i++)
		{
			sum += (*func)(-pi + dx * i) * dx;
		}
		return (sum / (2 * pi));
	}
	else return -1;
}

double b_k(int k, double (*func)(double x))
{
	double sum = 0;
	if (k >= 1)
	{
		for (int i = 0; i <= iterations; i++)
		{
			sum += (*func)(-pi + dx * i) * sin(k * (-pi + dx * i)) * dx;
		}
		return sum;
	}
	else return -1;
}
double Fourier(double x_px, int n, double (*func)(double x))
{
	double y = 0;
	// a_k
	for (int i = 0; i <= n; i++)
	{
		y += a_k(i, func) * cos(i * (x_px / 50 - 8));
	}
	// b_k
	for (int i = 1; i <= n; i++)
	{
		y += b_k(i, func) * sin(i * (x_px / 50 - 8));
	}
	return y;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Graph");
	sf::VertexArray curve(sf::PrimitiveType::LineStrip, 80);
	//Axes
	sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
	xAxis[0].position = sf::Vector2f(0, 400);
	xAxis[1].position = sf::Vector2f(800, 400);
	sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
	yAxis[0].position = sf::Vector2f(400, 0);
	yAxis[1].position = sf::Vector2f(400, 800);

	int gen = 0;
	for (double x_px = 0; x_px < 800; x_px += 10)
	{

		curve.append(sf::Vertex(sf::Vector2f(x_px, -50*Fourier(x_px, gen, &F)+400))); //You can replace F with any function you like 
	}

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed) window.close();
			
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Space)
				{
					gen++;
					curve.clear();
					for (double x_px = 0; x_px < 800; x_px += 10)
					{
						
						curve.append(sf::Vertex(sf::Vector2f(x_px, -50 * Fourier(x_px, gen, &F) + 400))); //You can replace F with any function you like 
					}
				}
			}
		}
		window.clear();
		window.draw(curve);
		window.draw(xAxis);
		window.draw(yAxis);
		window.display();
	}
}
