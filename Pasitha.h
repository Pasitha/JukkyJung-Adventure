#pragma once
#include "common.h"

namespace pasitha {
	namespace sfml {
		class Button {
		public:
			Button() {

			}
		private:
			sf::RectangleShape button;
		public:

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
