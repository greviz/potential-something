#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

const int	WINDOW_WIDTH = 600,
WINDOW_HEIGHT = 800;

const float PADDLE_VELOCITY = 4.0f;
const float BALL_VELOCITY = -1;

using namespace std;

struct Rectangle
{
	sf::RectangleShape shape;

	float X()		{ return shape.getPosition().x; }
	float Y()		{ return shape.getPosition().y; }
	float Left()	{ return X() - shape.getSize().x / 2.f; }
	float Right()	{ return X() + shape.getSize().x / 2.f; }
	float Top()		{ return Y() - shape.getSize().y / 2.f; }
	float Bottom()	{ return Y() + shape.getSize().y / 2.f; }

	
};

struct Paddle : public Rectangle
{
	sf::Vector2f velocity;

	Paddle(float mX, float mY, float mHeight, float mWidth, sf::Color mColor = sf::Color::Red)
	{
		shape.setPosition(mX, mY);
		shape.setSize(sf::Vector2f(mHeight, mWidth)); // POMYSL JAK TO NAPISAC "LEPIEJ"?
		shape.setFillColor(mColor);
	}

	void Update()
	{
		shape.move(velocity);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && WINDOW_WIDTH > Right())
		{
			velocity.x = PADDLE_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && Left() > 0)
		{
			velocity.x = -PADDLE_VELOCITY;
		}
		else
		{
			velocity.x = 0;
		}
	}
};
struct Circle
{
	sf::CircleShape shape;


	float X() { return shape.getPosition().x; }
	float Y() { return shape.getPosition().y; }
	float Left() { return X() - shape.getRadius(); }
	float Right() { return X() + shape.getRadius(); }
	float Top() { return Y() - shape.getRadius(); }
	float Bottom() { return Y() + shape.getRadius(); }
};

struct Ball : public Circle
{
	sf::Vector2f velocity{ BALL_VELOCITY, BALL_VELOCITY };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(10);
		shape.setFillColor(sf::Color::Yellow);
	}
	void Update()
	{
		shape.move(velocity);
		if (Left() == 0)
		{
			if (velocity.x == -1 && velocity.y == -1)
			{
				velocity.x = 1;
				velocity.y = -1;

			}
			else
			{
				velocity.x = 1;
				velocity.y = 1;
			}
		}

		if (Top() == 0)
		{
			if (velocity.x == 1 && velocity.y == -1)
			{
				velocity.x = 1;
				velocity.y = 1;
			}
			else
			{
				velocity.x = -1;
				velocity.y = 1;
			}
		}

		if (Right() == WINDOW_WIDTH)
		{
			if (velocity.x == 1 && velocity.y == 1)
			{
				velocity.x = -1;
				velocity.y = 1;
			}
			else
			{
				velocity.x = -1;
				velocity.y = -1;
			}
		}
		if (Bottom() == 0)
		{
			
		}
	}
};
void chceckCollision(Ball& ball, Paddle& pad)
{
	if (ball.shape.getPosition().x <= pad.Right() && ball.shape.getPosition().x >= pad.Left())
	{
		if (ball.Bottom() == pad.Top())
		{
			if (ball.velocity.x == 1 && ball.velocity.y == 1)
			{
				ball.velocity.x = 1;
				ball.velocity.y = -1;
			}
			else
			{
				ball.velocity.x = -1;
				ball.velocity.y = -1;
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "#Paddle & Ball", sf::Style::Titlebar | sf::Style::Close);

	// Init game object 
	Paddle paddle(WINDOW_WIDTH / 2, 700, 150, 50);
	Ball ball(500, WINDOW_HEIGHT /2 );
	paddle.shape.setOrigin(75,0);
	srand(time(NULL));
	clock_t time;
	time = clock();

	// PETLA GRY
	while (true)
	{
		
		if ((clock()-time) > CLOCKS_PER_SEC/256)
		{
			window.clear(sf::Color::Black);

			//EVENT
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					break;
			}

			// UPDATE
			{
				chceckCollision(ball, paddle);
				paddle.Update();
				chceckCollision(ball, paddle);
				ball.Update();
				chceckCollision(ball, paddle);
			}
			// SHOW
			{
				window.draw(paddle.shape);
				window.draw(ball.shape);
			}

			window.display();
			time = clock();
		}
	}

	return 0;
}