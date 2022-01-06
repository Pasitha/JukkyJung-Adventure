#pragma once
#include "common.h"

namespace pasitha {
	namespace sfml {
		sf::Font ReadexPro;
		
		// Function used to create sf::Texture
		sf::Texture createTexture(std::string path) {
			sf::Texture texture;
			if (!texture.loadFromFile(path))
				std::cerr << "Can't loadFile at: " << path << "\n";
			return texture;
		}
		
		class Button {
		public:
			Button(std::string text, sf::Vector2f size, sf::Texture& buttonTexture, int characterSize = 36) {
				button.setTexture(&buttonTexture);
				button.setSize(size);

				lable.setString(text);
				lable.setFont(ReadexPro);
				lable.setCharacterSize(characterSize);
				lable.setStyle(sf::Text::Bold);
				lable.setFillColor(sf::Color::Black);
				lable.setPosition({ button.getPosition().x + button.getGlobalBounds().width / 2.f - lable.getGlobalBounds().width / 2.f, button.getPosition().y + button.getGlobalBounds().height / 2.2f - lable.getGlobalBounds().height / 2.2f });
			}

		private:
			sf::RectangleShape button;
			sf::Text lable;
		public:
			void draw(sf::RenderWindow& window) {
				window.draw(button);
				window.draw(lable);
			}
		};

		class Sprite {
		public:
			Sprite(std::string path, float width, float height, sf::Vector2f position = { 0, 0 }) {
				if (!texture.loadFromFile(path))
					std::cerr << "can't load texture from " << path << "\n";

				sf::Vector2u size = texture.getSize();

				float scaleX = width / size.x;
				float scaleY = height / size.y;

				sprite.setTexture(texture);
				sprite.setPosition(position);
				sprite.setScale(scaleX, scaleY);
			}

			Sprite(sf::Texture texture, sf::Vector2f position = { 0, 0 }) {
				sprite.setTexture(texture);
				sprite.setPosition(position);
			}

		private:
			sf::Sprite sprite;
			sf::Texture texture;
		public:
			sf::Sprite GetSprite() {
				return sprite;
			}
		};
	}
}
