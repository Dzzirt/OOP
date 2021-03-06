#pragma once
#include <map>
#include "CarExceptions.h"

enum MovementState
{
	STOP,
	FORWARD,
	BACKWARD
};

class CCar
{
public:
	CCar();
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	int GetGear() const;
	int GetSpeed() const;
	bool IsTurnedOn() const;
	MovementState GetDirection() const;
private:
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
	MovementState m_state;
	static std::map<int, std::pair<int, int>> m_speedRanges;
	bool IsGearsSpeedCompatible(int gear1, int gear2);
	bool isGearSupported(int newGear);
	bool IsGearsDirectionCompatible(int gear1, int gear2);
};

