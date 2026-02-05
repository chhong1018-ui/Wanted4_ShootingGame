#pragma once

#include "Math/Vector.h"

class ICanPlayerMove
{
public:
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& newPosition
	) = 0;
};