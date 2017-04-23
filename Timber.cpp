#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;

int main() {

	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!!");

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	Texture beeTexture;
	beeTexture.loadFromFile("graphics/bee.png");

	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture cloudTexture;
	cloudTexture.loadFromFile("graphics/cloud.png");

	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	spriteCloud1.setTexture(cloudTexture);
	spriteCloud2.setTexture(cloudTexture);
	spriteCloud3.setTexture(cloudTexture);

	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Clock clock;
	Event event;
	bool isPaused = true;
	int score = 0;

	Text messageText;
	Text scoreText;
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRec = messageText.getLocalBounds();
	messageText.setOrigin(textRec.left + textRec.width / 2.0f,
			textRec.top + textRec.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// Main Game Loop - execute FP/S
	while (window.isOpen()) {
		// Have the window listen for events - either user events or system events
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed
					|| Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				isPaused = false;
			}
		}

		if (!isPaused) {
			Time dt = clock.restart();

			// Play with the Bee Sprite
			if (!beeActive) {
				srand((int) time(0));
				beeSpeed = (rand() % 200) + 200;

				srand((int) time(0) * 10);
				float height = (rand() % 500) + 500;

				beeSprite.setPosition(2000, height);
				beeActive = true;
			} else {
				beeSprite.setPosition(
						beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()),
						beeSprite.getPosition().y);

				if (beeSprite.getPosition().x < -100) {
					beeActive = false;
				}
			}

			// Play with the Cloud Sprite
			if (!cloud1Active) {
				srand((int) time(0) * 10);
				cloud1Speed = (rand() % 200);

				srand((int) time(0) * 10);
				float height = (rand() & 150);

				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			} else {
				spriteCloud1.setPosition(
						spriteCloud1.getPosition().x
								+ (cloud1Speed * dt.asSeconds()),
						spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}

			if (!cloud2Active) {
				srand((int) time(0) * 20);
				cloud2Speed = (rand() % 200);

				srand((int) time(0) * 20);
				float height = (rand() % 300) + 150;
				spriteCloud2.setPosition(-200, height);

				cloud2Active = true;
			} else {
				spriteCloud2.setPosition(
						spriteCloud2.getPosition().x
								+ (cloud2Speed * dt.asSeconds()),
						spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x > 1920) {
					beeActive = false;
				}
			}

			if (!cloud3Active) {
				srand((int) time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int) time(0) * 30);
				float height = (rand() % 450) - 150;

				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			} else {
				spriteCloud3.setPosition(
						spriteCloud3.getPosition().x
								+ (cloud3Speed * dt.asSeconds()),
						spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

		} // End main if

		window.clear();

		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(beeSprite);
		window.draw(scoreText);
		if (isPaused) {
			window.draw(messageText);
		}

		window.display();
	}

	return 0;
}
