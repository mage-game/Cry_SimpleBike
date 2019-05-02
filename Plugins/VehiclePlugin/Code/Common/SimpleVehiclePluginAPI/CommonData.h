#pragma once

struct BikeTransfrom
{
	float posX = 0.0f;
	float posY = 0.0f;
	float posZ = 0.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	BikeTransfrom& operator =(const BikeTransfrom& pkg)
	{
		posX = pkg.posX;
		posY = pkg.posY;
		posZ = pkg.posZ;
		rotX = pkg.rotX;
		rotY = pkg.rotY;
		rotZ = pkg.rotZ;

		return *this;
	}
};

struct BikeAnimation
{
	float frontWheel = 0.0f;
	float rearWheel = 0.0f;
	float steer = 0.5f;
	float pedal = 0.0f;
	float bodyRoll = 0.5f;

	BikeAnimation& operator = (const BikeAnimation& pkg)
	{
		frontWheel = pkg.frontWheel;
		rearWheel = pkg.rearWheel;
		steer = pkg.steer;
		pedal = pkg.pedal;
		bodyRoll = pkg.bodyRoll;

		return *this;
	}
};
