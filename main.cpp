#include <iostream>

void stackprint(int layer, int stack[10])
{
	std::cout << "----Stack----" << std::endl;

	for (int i = layer - 1; 0 <= i; i--)
	{
		std::cout << stack[i] << std::endl;
	}
}
int main()
{
	/*STACK 만들기
	* 사용자가 1번을 입력시 숫자를 입력받는다 
		숫자를 입력받고 접시를 쌓듯이 저장을한다
	* 사용자가 2번을 입력시 저장된 숫자를 제거한다  
		접시를 꺼내듯이 숫자를 제거해야한다. 즉 가장 최근에 저장한 값을 먼저 제거해야한다
	*/
	
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

				stackprint(layer, &stack[10]);
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