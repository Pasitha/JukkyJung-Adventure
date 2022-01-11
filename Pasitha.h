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
			Button(std::string text, sf::Vector2f size, sf::Texture& buttonTexture, int characterSize = 36, sf::Vector2f position = { 0, 0 }) {
				button.setTexture(&buttonTexture);
				button.setSize(size);
				button.setPosition(position);

				lable.setString(text);
				lable.setFont(ReadexPro);
				lable.setCharacterSize(characterSize);
				lable.setStyle(sf::Text::Bold);
				lable.setFillColor(sf::Color::Black);
				lable.setPosition({ 
					button.getPosition().x + button.getGlobalBounds().width / 2.f - lable.getGlobalBounds().width / 2.f,
					button.getPosition().y + button.getGlobalBounds().height / 2.2f - lable.getGlobalBounds().height / 2.2f 
				});
			}

			Button(std::string text, sf::Vector2f size, std::string path, int characterSize = 36, sf::Vector2f position = { 0, 0 }) {
				sf::Texture buttonTexture = createTexture(path);
				button.setTexture(&buttonTexture);
				button.setSize(size);
				button.setPosition(position);

				lable.setString(text);
				lable.setFont(ReadexPro);
				lable.setCharacterSize(characterSize);
				lable.setStyle(sf::Text::Bold);
				lable.setFillColor(sf::Color::Black);
				lable.setPosition({ 
					button.getPosition().x + button.getGlobalBounds().width / 2.f - lable.getGlobalBounds().width / 2.f,
					button.getPosition().y + button.getGlobalBounds().height / 2.2f - lable.getGlobalBounds().height / 2.2f 
				});
			}

		private:
			sf::RectangleShape button;
			sf::Text lable;
		public:
			// method to draw
			void draw(sf::RenderWindow& window) {
				window.draw(button);
				window.draw(lable);
			}

			// method to set button position
			void setPosition(sf::Vector2f position = { 0, 0 }) {
				button.setPosition(position);
				lable.setPosition({ 
					button.getPosition().x + button.getGlobalBounds().width / 2.f - lable.getGlobalBounds().width / 2.f,
					button.getPosition().y + button.getGlobalBounds().height / 2.2f - lable.getGlobalBounds().height / 2.2f 
				});
			}

			// method used to check mouse is hover the sf::Rectangle
			bool isHover (const sf::RenderWindow& window) {
				float mouseX = sf::Mouse::getPosition(window).x;
				float mouseY = sf::Mouse::getPosition(window).y;

				float btnPosX = button.getPosition().x;
				float btnPosY = button.getPosition().y;

				float btnxPosWidth = btnPosX + button.getLocalBounds().width;
				float btnyPosHeight = btnPosY + button.getLocalBounds().height;

				return mouseX < btnxPosWidth&& mouseX > btnPosX && mouseY < btnyPosHeight&& mouseY > btnPosY;
			};

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

			Sprite(sf::Texture& itexture, float width, float height, sf::Vector2f position = { 0, 0 }) : texture(itexture) {
				sf::Vector2u size = itexture.getSize();

				float scaleX = width / size.x;
				float scaleY = height / size.y;

				sprite.setTexture(texture);
				sprite.setPosition(position);
				sprite.setScale(scaleX, scaleY);
			}

		private:
			sf::Sprite sprite;
			sf::Texture texture;
		public:
			sf::Sprite GetSprite() {
				return sprite;
			}
			
			void setPosition(sf::Vector2f position = { 0,0 }) {
				sprite.setPosition(position);
			}
		};
		
		class Picture {
		public:
			Picture(sf::Texture texture, sf::Vector2f size, sf::Vector2f position) {
				rectangle.setSize(size);
				rectangle.setPosition(position);
				rectangle.setTexture(&texture);
			}
		private:
			sf::RectangleShape rectangle;
		public:
			void draw(sf::RenderWindow& window) {
				window.draw(rectangle);
			}

			void setPosition(sf::Vector2f position) {
				rectangle.setPosition(position);
			}
		};
	}
}
