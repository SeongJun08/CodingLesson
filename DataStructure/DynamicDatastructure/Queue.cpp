#include <iostream>

int main()
{
	const int push = 1;
	const int pop = 2;
	const int shutdown = 3;
	int choose{};
	unsigned int layer = 0;
	int stack[10]{};

	while (true)
	{
		std::cout << "1 : push		2 : pop		3 : Shut down" << std::endl;
		std::cout << " > " << " ";
		std::cin >> choose;

		if (choose == push)
		{
			if (layer < 10)
			{
				int value;
				std::cout << " > value? " << " ";
				std::cin >> value;
				std::cout << std::endl;
				stack[layer++] = value;

				std::cout << "----Stack----" << std::endl;

				for (int i = layer - 1; 0 <= i; i--)
				{
					std::cout << stack[i] << std::endl;
				}
			}
			else
			{
				std::cout << "Stack is full" << std::endl;
			}
			
		}
		else if (choose == pop)
		{
			if (layer > 0)
			{
				std::cout << std::endl;
				std::cout << "pop : " << stack[--layer] << std::endl;
				std::cout << "----Stack----" << std::endl;

				for (int i = layer - 1; 0 <= i; i--)
				{
					std::cout << stack[i] << std::endl;
				}
			}
			else
			{
				std::cout << "Stack is empty" << std::endl;
			}

		}
		else if (choose == shutdown)
		{
			return 0;
		}
		else
		{
			std::cout << "Wrong choice try again" << std::endl;
		}
	}


}
