#pragma once
#include "Config.h"
#include "functions.h"
#include <iostream>
#include <SFML//Graphics.hpp>

class Camera {
public:
	sf::View view;
	bool scrollactive = false;
	Camera();
	Camera(sf::RenderWindow* iw1, sf::Rect<float> rect1, sf::Rect<float> viewport={0, 0, 0, 0});
	void setCamera();
	void addZoom(float a);
	void reset();
	void move(sf::Vector2f d);
	void setActive(bool cond);
	void check();
private:
	sf::Vector2f mouse_last_pos = { -1e9, -1e9 };
	float zoom;
	sf::Rect<float> rect, orig_rect, viewport, orig_viewport;
	sf::RenderWindow* iw;
};
