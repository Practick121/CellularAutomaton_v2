#include "Camera.h"

Camera::Camera(){}

Camera::Camera(sf::RenderWindow* iw1, sf::Rect<float> rect1, sf::Rect<float> viewport1)
{
	iw = iw1;
	zoom = 1;
	orig_rect = rect = rect1;
	if (viewport1 == sf::Rect<float>{0, 0, 0, 0})
		orig_viewport = viewport = { rect.left / (float)Config::windowSize.x, rect.top / (float)Config::windowSize.y,\
					rect.width / (float)Config::windowSize.x, rect.height / (float)Config::windowSize.y };
	else
		orig_viewport = viewport = viewport1;
	view.setCenter({ rect.left + rect.width / 2, rect.top + rect.height / 2 });
	view.setSize(rect.getSize());
	view.setViewport(viewport);
}

void Camera::setCamera()
{
	iw->setView(view);
}

void Camera::addZoom(float a)
{
	sf::Vector2f mouse_pos = get_mouse_pos(iw);
	sf::Vector2f mouse_pos_adapt = iw->mapPixelToCoords({ (int)mouse_pos.x, (int)mouse_pos.y }, view);
	sf::Vector2f center_now = mouse_pos_adapt + (view.getCenter() - mouse_pos_adapt) * a;
	zoom *= a;
	//rect = { {center_now - sf::Vector2f(0.5 * rect.width, 0.5 * rect.height) }, rect.getSize()* a};
	rect.width *= a;
	rect.height *= a;
	rect.left = center_now.x - rect.width / 2;
	rect.top = center_now.y - rect.height / 2;
	view.zoom(a);
	view.setCenter(center_now);
}


void Camera::reset()
{
	zoom = 1;
	viewport = orig_viewport;
	rect = orig_rect;
	view.setCenter({ rect.left + rect.width / 2, rect.top + rect.height / 2 });
	view.setSize(rect.getSize());
	view.setViewport(viewport);
	mouse_last_pos = { -1e9, -1e9 };
}

void Camera::move(sf::Vector2f d)
{
	rect = { rect.getPosition() + d, rect.getSize()};
	view.setCenter({ rect.left + rect.width / 2, rect.top + rect.height / 2 });
}

void Camera::setActive(bool cond)
{
	if (cond == true && scrollactive == false) {
		//mouse_last_pos = iw->mapPixelToCoords({ (int)get_mouse_pos(iw).x, (int)get_mouse_pos(iw).y }, view);
		mouse_last_pos = get_mouse_pos(iw);
	}
	scrollactive = cond;
}

void Camera::check()
{
	//std::cout << "zoom: " << zoom << std::endl;
	if (scrollactive) {
		//sf::Vector2f movevector = (iw->mapPixelToCoords({ (int)get_mouse_pos(iw).x, (int)get_mouse_pos(iw).y}, view) - mouse_last_pos);
		sf::Vector2f movevector = (get_mouse_pos(iw) - mouse_last_pos) * zoom;
		//mouse_last_pos = iw->mapPixelToCoords({ (int)get_mouse_pos(iw).x, (int)get_mouse_pos(iw).y}, view);
		mouse_last_pos = get_mouse_pos(iw);
		move(-movevector);
	}
}
