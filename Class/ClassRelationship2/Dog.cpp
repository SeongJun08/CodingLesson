#include <iostream>
#include "Dog.h"

void Dog::Roll()
{
	std::cout << "Rolling..." << std::endl;
}

void Dog::SetBreed(Breed breed)
{
	mBreed = breed;
}

Dog::Breed Dog::GetBReed() const
{
	return Breed();
}
