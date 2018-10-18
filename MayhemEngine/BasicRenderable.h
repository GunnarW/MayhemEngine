#pragma once
#include "Renderable.h"
class BasicRenderable :
	public Renderable
{
public:
	BasicRenderable();
	~BasicRenderable();

	virtual void Initialize();
};

