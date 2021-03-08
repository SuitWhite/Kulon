#include "Classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1200, 1000), "Kulon"); 
    SomeParticle particle[100];
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
    window.setMouseCursor(cursor);

	Clock clock; 
    int nmbpartcls=0;
	float nmbcharg=-1;
	while (window.isOpen())
	{
		double time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();  
		time = time / 800; 
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close(); 
		}
		sf::Vector2i position = sf::Mouse::getPosition();
		if (Keyboard::isKeyPressed(Keyboard::P)) nmbcharg+=1;
		if (Keyboard::isKeyPressed(Keyboard::M)) nmbcharg-=1;
        if (event.type == sf::Event::MouseButtonPressed)
        {
			particle[nmbpartcls]= *(new SomeParticle(position.x, position.y , 1.6*nmbcharg));
            nmbpartcls++;
			if (nmbpartcls>=100) nmbpartcls=0;
        }
		for (int i=0; i<nmbpartcls; i++){
            for (int k=0; k<nmbpartcls; k++){
				if (i!=k){
					double dobcharg=particle[i].GetCharge()*particle[k].GetCharge();
					double kvdis=particle[i].DistanceToAnother(particle[k])*particle[i].DistanceToAnother(particle[k]);
					if (particle[i].GetCoorX()<=particle[k].GetCoorX() && particle[i].GetCoorY()>=particle[k].GetCoorY() && particle[i].GetCharge()!=0 && particle[k].GetCharge()!=0) // situation 2
					{
						particle[i].dy+=1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*sin(particle[i].AngleToAnother(particle[k]));
						std::cout << "dy=" << particle[i].dy << " dis=" << particle[i].DistanceToAnother(particle[k]) << " chrg=" << dobcharg << " kvdis=" << kvdis << " weight=" << particle[i].GetWeight() << " sin=" << sin(particle[i].AngleToAnother(particle[k]))	<<std::endl;
						particle[i].dx+=-1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*cos(particle[i].AngleToAnother(particle[k]));
						std::cout << "dx=" << particle[i].dx << std::endl;
					}
					else if (particle[i].GetCoorX()<=particle[k].GetCoorX() && particle[i].GetCoorY()<=particle[k].GetCoorY() && particle[i].GetCharge()!=0 && particle[k].GetCharge()!=0) // situation 1
					{
						particle[i].dy+=-1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*sin(particle[i].AngleToAnother(particle[k]));
						std::cout << "dy=" << particle[i].dy << " dis=" << particle[i].DistanceToAnother(particle[k]) << " chrg=" << dobcharg << " kvdis=" << kvdis << " weight=" << particle[i].GetWeight() << " sin=" << sin(particle[i].AngleToAnother(particle[k]))	<<std::endl;
						particle[i].dx+=-1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*cos(particle[i].AngleToAnother(particle[k]));
						std::cout << "dx=" << particle[i].dx << std::endl;
					}
					else if (particle[i].GetCoorX()>=particle[k].GetCoorX() && particle[i].GetCoorY()>=particle[k].GetCoorY() && particle[i].GetCharge()!=0 && particle[k].GetCharge()!=0) // situation 4
					{
						particle[i].dy+=1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*sin(particle[i].AngleToAnother(particle[k]));
						std::cout << "dy=" << particle[i].dy << " dis=" << particle[i].DistanceToAnother(particle[k]) << " chrg=" << dobcharg << " kvdis=" << kvdis << " weight=" << particle[i].GetWeight() << " sin=" << sin(particle[i].AngleToAnother(particle[k]))	<<std::endl;
						particle[i].dx+=1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*cos(particle[i].AngleToAnother(particle[k]));
						std::cout << "dx=" << particle[i].dx << std::endl;
					}
					else if (particle[i].GetCoorX()>=particle[k].GetCoorX() && particle[i].GetCoorY()<=particle[k].GetCoorY() && particle[i].GetCharge()!=0 && particle[k].GetCharge()!=0) // sutiation 3
					{
						particle[i].dy+=-1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*sin(particle[i].AngleToAnother(particle[k]));
						std::cout << "dy=" << particle[i].dy << " dis=" << particle[i].DistanceToAnother(particle[k]) << " chrg=" << dobcharg << " kvdis=" << kvdis << " weight=" << particle[i].GetWeight() << " sin=" << sin(particle[i].AngleToAnother(particle[k]))	<<std::endl;
						particle[i].dx+=1*((particle[i].GetCharge()*particle[k].GetCharge())/kvdis)*cos(particle[i].AngleToAnother(particle[k]));
						std::cout << "dx=" << particle[i].dx << std::endl;
					}
				}
			}
        }
		window.clear(Color::White); 
        for (int i=0; i<nmbpartcls; i++){
			particle[i].update(time);
            window.draw(particle[i].circle);
        }
		window.display(); // выводим на дисплей
	}
	return 0;
}
