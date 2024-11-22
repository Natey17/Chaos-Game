// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	Text infoText;
	Font textFont;
	textFont.loadFromFile("fonts/arial.ttf");
	infoText.setFont(textFont);
	infoText.setString("Pick Your Points");
	infoText.setCharacterSize(75);
	infoText.setFillColor(Color::White);
	FloatRect textBounds = infoText.getLocalBounds();
	infoText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	infoText.setPosition(1920 / 2.0f, 75);

	srand(time(NULL));
	vector<Vector2f> baseVertices;
	vector<Vector2f> chaosPoints;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event userInput;
		while (window.pollEvent(userInput))
		{
			if (userInput.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (userInput.type == sf::Event::MouseButtonPressed)
			{
				if (userInput.mouseButton.button == sf::Mouse::Left)
				{

					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << userInput.mouseButton.x << std::endl;
					std::cout << "mouse y: " << userInput.mouseButton.y << std::endl;

					if (baseVertices.size() < 3)
					{
						baseVertices.push_back(Vector2f(userInput.mouseButton.x, userInput.mouseButton.y));
						if (baseVertices.size() == 3)
						{
							infoText.setString("Choose Start Point");
							FloatRect textBounds = infoText.getLocalBounds();
							infoText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
							infoText.setPosition(1920 / 2.0f, 75);
						}
					}
					else if (chaosPoints.size() == 0)
					{
						chaosPoints.push_back(Vector2f(userInput.mouseButton.x, userInput.mouseButton.y));
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (chaosPoints.size() > 0)
		{
			for (int i = 0; i < 10; i++)
			{
				int randomVertex = rand() % 3;
				float midX = (baseVertices[randomVertex].x + chaosPoints.back().x) * 0.5;
				float midY = (baseVertices[randomVertex].y + chaosPoints.back().y) * 0.5;
				chaosPoints.push_back(Vector2f(midX, midY));
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		if (baseVertices.size() < 3 || chaosPoints.size() == 0)
		{
			window.draw(infoText);
		}

		for (int i = 0; i < baseVertices.size(); i++)
		{
			RectangleShape baseMarker(Vector2f(10, 10));
			baseMarker.setPosition(Vector2f(baseVertices[i].x, baseVertices[i].y));
			baseMarker.setFillColor(Color::Blue);
			window.draw(baseMarker);
		}

		for (int i = 0; i < chaosPoints.size(); i++)
		{
			RectangleShape chaosMarker(Vector2f(5, 5));
			chaosMarker.setPosition(Vector2f(chaosPoints[i].x, chaosPoints[i].y));
			chaosMarker.setFillColor(Color::Red);
			window.draw(chaosMarker);
		}
		window.display();
	}
}
