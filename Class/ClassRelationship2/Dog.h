#pragma once
#include "Animal.h"
class Dog :
	public Animal
{
public:
	enum Breed
	{
		HUSKY,
		RETERIEVER,
		CHIHUAHUA
	};

public:
	void Roll();
	void SetBreed(Breed breed);
	Breed GetBReed() const;

private:
	Breed mBreed;

};

