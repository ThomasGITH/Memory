#include<iostream>
#include<SFML\Graphics.hpp>
#include <vector>

std::vector<std::string> texLocList = { "images/10C.png","images/2C.png","images/3C.png","images/4C.png","images/5C.png", "images/6C.png","images/7C.png","images/8C.png","images/9C.png", "images/AC.png", "images/JC.png", "images/KC.png", "images/QC.png",
"images/10D.png","images/2D.png","images/3D.png","images/4D.png","images/5D.png", "images/6D.png","images/7D.png","images/8D.png","images/9D.png", "images/AD.png", "images/JD.png", "images/KD.png", "images/QD.png",
"images/10H.png","images/2H.png","images/3H.png","images/4H.png","images/5H.png", "images/6H.png","images/7H.png","images/8H.png","images/9H.png", "images/AH.png", "images/JH.png", "images/KH.png", "images/QH.png",
"images/10S.png","images/2S.png","images/3S.png","images/4S.png","images/5S.png", "images/6S.png","images/7S.png","images/8S.png","images/9S.png", "images/AS.png", "images/JS.png", "images/KS.png", "images/QS.png"};

std::vector<sf::Texture> textureList;
std::vector<sf::Sprite> spriteList;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Thomas Memory Game", sf::Style::Fullscreen);

//SHUFFLES TEXTURES
std::vector<sf::Texture> shuffle(std::vector<sf::Texture> array, int len)
{
	for (unsigned int i = 0; i < len; i++)
	{
		int randomIndex = std::rand() % len;
		sf::Texture temp = array[i];
		array[i] = array[randomIndex];
		array[randomIndex] = temp;
	}
	return array;
}

//CHECK IF MOUSE HOVERS OVER SPRITE
bool checkBounds(sf::Sprite sprite)
{
	if ((sf::Mouse::getPosition(window).x > sprite.getGlobalBounds().left) &&
		(sf::Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width)) &&
		(sf::Mouse::getPosition(window).y > sprite.getGlobalBounds().top) &&
		(sf::Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)))
	{
		return true;
	}
	return false;
}

int main()
{
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(60);

	srand(time(NULL));

	//CREATE, LOAD AND PUSH TEXTURES
	for (size_t i = 0; i < texLocList.size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(i < texLocList.size()? texLocList[i] : texLocList[i - texLocList.size()]);
		textureList.push_back(texture);
	}

	//SHUFFLE TEXTURE ARRAY
	textureList = shuffle(textureList, textureList.size());

	sf::Texture back;
	back.loadFromFile("images/red_back.png");
	sf::Sprite sample(back);

	//CREATE SPRITES WITH TEXTURES
	for (size_t i = 0; i < texLocList.size() * 2; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(i < 52 ? textureList[i] : textureList[i - texLocList.size()]);
		sprite.scale(0.1025, 0.1025f);
		spriteList.push_back(sprite);
	}

	int x = 0, y = 0, counter = 0, remember = 0;

	//POSITION SPRITES
	for (size_t i = 0; i < 7; i++)
	{
		y += 1;
		spriteList[counter].setPosition(x, y * 120);
		sf::Vector2f verticalPos = spriteList[counter].getPosition();
		remember = verticalPos.y;
		for (size_t i = 0; i < 16; i++)
		{
			if (counter < spriteList.size())
			{
				x += 1;
				spriteList[counter].setPosition(x * 100, remember);
				counter += 1;
			}
		}
		x = 0;
	}

	int firstCard = NULL, secondCard = NULL;
	bool FirstLook = true;

	sf::Clock clock; // starts the clock
	sf::Time elapsed = clock.getElapsedTime();

	//MAIN(GAME) LOOP
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//CLICK TO START GUESSING/PLAYING
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && FirstLook)
			{
				for (size_t i = 0; i < spriteList.size(); i++)
				{
					spriteList[i].setTexture(back);
				}
				FirstLook = false;
			}

			//CARD PRESS
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (size_t i = 0; i < spriteList.size(); i++)
				{
					if (checkBounds(spriteList[i]) && spriteList[i].getTexture() == sample.getTexture())
					{
						std::cout << i << std::endl;
						std::cout << spriteList[i].getTexture() << std::endl;
						spriteList[i].setTexture(i < 52? textureList[i] : textureList[i - texLocList.size()]);

						if (firstCard == NULL) { firstCard = i; }
						else if ((firstCard != NULL) && (firstCard != i))
						{
							secondCard = i;
							if (spriteList[firstCard].getTexture() == spriteList[secondCard].getTexture())
							{
								firstCard = NULL; secondCard = NULL;
							}
							else {
									spriteList[firstCard].setTexture(back);
									spriteList[secondCard].setTexture(back);
									firstCard = NULL; secondCard = NULL;
								}
							}
						}
					}
				}


			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(0, 102, 0));
		
		for (size_t i = 0; i < spriteList.size(); i++)
		{
			window.draw(spriteList[i]);
		}		window.display();
	}
	return 0;
}
