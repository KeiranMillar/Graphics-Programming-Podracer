#include "Vector3.h"
#include <math.h>
#pragma once
class camera
{
private:
	float Roll = 0, Pitch = 0, Yaw = 0, cosR = 0, cosP = 0, cosY = 0, sinR = 0, sinP = 0, sinY = 0;
	Vector3 position, lookAt, forward, up, right;
public:
	camera()
	{
		position.x = 0.0f;
		position.y = 2.0f;
		position.z = 0.0f;
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 0.0f;
		update();
	}
	~camera() 
	{
		
	}


	void camera::update()
	{


		float cosR, cosP, cosY;	//temp values for sin/cos from 
		float sinR, sinP, sinY;
		// Roll, Pitch and Yall are variables stored by the camera
		// handle rotation
		// Only want to calculate these values once, when rotation changes, not every frame. 

		cosY = cosf(Yaw*3.1415f / 180);
		cosP = cosf(Pitch*3.1415f / 180);
		cosR = cosf(Roll*3.1415f / 180);
		sinY = sinf(Yaw*3.1415f / 180);
		sinP = sinf(Pitch*3.1415f / 180);
		sinR = sinf(Roll*3.1415f / 180);

		//This using the parametric equation of a sphere

		// Calculate the three vectors to put into  glu Lookat
		// Look direction,  position and the up vector 
		// This function could also calculate the right vector

		forward.x = sinY * cosP;
		forward.y = sinP;
		forward.z = cosP * -cosY;

		// Look At Point
		// To calculate add Forward Vector to Camera position.

		lookAt = position + forward;

		//Up Vector
		up.x = -cosY * sinR - sinY * sinP * cosR;
		up.y = cosP * cosR;
		up.z = -sinY * sinR - sinP * cosR * -cosY;

		// Side Vector (right)
		// this is a cross product between the forward and up vector. 
		// If you don’t need to calculate this,  don’t do it. 

		right.x = (forward.y * up.z) - (forward.z * up.y);
		right.y = (forward.z * up.x) - (forward.x * up.z);
		right.z = (forward.x * up.y) - (forward.y * up.x);

	};

	void moveForward(float speed)
	{
		//To control speed of movement multiply the forward vector by speed and delta time
		forward.x = forward.x * speed;
		forward.y = forward.y * speed;
		forward.z = forward.z * speed;

		position.x += forward.x;
		position.y += forward.y;
		position.z += forward.z;
		update();
	};

	void moveRight(float speed)
	{
		//To control speed of movement multiply the forward vector by speed and delta time
		right.x = right.x * speed;
		right.y = right.y * speed;
		right.z = right.z * speed;

		position.x += right.x;
		position.y += right.y;
		position.z += right.z;
		update();
	};

	void rotateUp(float direction)
	{
		Pitch += direction;
		update();
	}

	void rotateRight(float direction)
	{
		Yaw += direction;
		update();
	}

	void RotateYaw(float val, float dt, float sens)
	{
		Yaw += val*sens*0.1;
		update();
	}

	void RotatePitch(float val, float dt, float sens)
	{
		Pitch += val*sens*0.1;
		update();
	}
	
	float camera::GetX()
	{
		return position.x;
	};

	float camera::GetY()
	{
		return position.y;
	};

	float camera::GetZ()
	{
		return position.z;
	};

	float camera::GetLookX()
	{
		return lookAt.x;
	};

	float camera::GetLookY()
	{
		return lookAt.y;
	};

	float camera::GetLookZ()
	{
		return lookAt.z;
	};

	float camera::GetUpX()
	{
		return up.x;
	};

	float camera::GetUpY()
	{
		return up.y;
	};

	float camera::GetUpZ()
	{
		return up.z;
	};

	float camera::GetRightX()
	{
		return right.x;
	};

	float camera::GetRightY()
	{
		return right.y;
	};

	float camera::GetRightZ()
	{
		return right.z;
	};

};

