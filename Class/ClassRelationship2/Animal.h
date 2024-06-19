#pragma once
class Animal
{
protected:
	int mAge;
	int mWeight;

public:
	int GetAge() { return mAge; }
	void SetAge(int age) { mAge = age; }
	int GetWeight() const { return mWeight; }
	void SetWeight(int weight) { mWeight = weight; }

	void Sound();
};

