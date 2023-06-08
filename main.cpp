#include <iostream>
#include "raylib.h"

class Ball
{
public:
	float x{};
	float y{};
	float radius{};
	float speedX{};
	float speedY{};

	void draw()
	{
		DrawCircle((int)x, (int)y, radius, YELLOW);
	}
};

class Paddle
{
public:
	float x{};
	float y{};
	float width{};
	float height{};
	float speed{};

	void draw()
	{
		DrawRectangle(x, y - height / 2, width, height, WHITE);
	}

	Rectangle getRect()
	{
		return Rectangle{ x , y - height / 2, width, height };
	}
};

int main()
{
	InitWindow(800, 600, "Pong");  //Creates window
	SetWindowState(FLAG_VSYNC_HINT); //Cuses the FPS to be same as the refresh rate

	Ball ball{};
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5.0f;
	ball.speedX = 400.0f;
	ball.speedY = 400.0f;

	Paddle leftPaddle{};
	leftPaddle.x = 0;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 15.0f;
	leftPaddle.height = 100.0f;
	leftPaddle.speed = 400.0f;

	Paddle rightPaddle{};
	rightPaddle.x = GetScreenWidth() - 15;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 15.0f;
	rightPaddle.height = 100.0f;
	rightPaddle.speed = 400.0f;

	const char* winnerText = nullptr;

	while (!WindowShouldClose())  //Loop keeps running until we close thw window
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		//To prevent the ball from going off the screen
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}
		else if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}


		//Left paddle controll
		if (IsKeyDown(KEY_W) && (leftPaddle.y - leftPaddle.height / 2) >= 0)
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S) && leftPaddle.y + (leftPaddle.height / 2) <= GetScreenHeight())
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		//Right paddle controll
		if (IsKeyDown(KEY_UP) && (rightPaddle.y - rightPaddle.height / 2) >= 0)
		{
			rightPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN) && rightPaddle.y + (rightPaddle.height / 2) <= GetScreenHeight())
		{
			rightPaddle.y += leftPaddle.speed * GetFrameTime();
		}


		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.getRect()))
		{
			if (ball.speedX < 0)
			{
				//ball.x += 1;
				ball.speedX *= -1;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * 500;
			}

		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.getRect()))
		{
			if (ball.speedX > 0)
			{
				//ball.x -= 1;
				ball.speedX *= -1;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * 500;
			}

		}

		//Prints winner
		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		else if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}

		//Onc game is over ppress space tp start again
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			ball.radius = 5.0f;
			ball.speedX = 400.0f;
			ball.speedY = 400.0f;
			winnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);  //changes the background color
		DrawFPS(10, 10);		 //Display FPS

		ball.draw();
		leftPaddle.draw();
		rightPaddle.draw();

		if (winnerText)
		{
			DrawText(winnerText, 150, GetScreenHeight() / 2, 60, RED);
		}
		EndDrawing();

	}
	CloseWindow(); //closes window
}