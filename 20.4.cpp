#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

int main()
{	
	std::srand (std::time(nullptr));
	std::string qwery;
	int banknotes[5] = { 100, 200, 500, 1000, 5000 };
	int money[1000];
	int withdrow_amount;
	std::cout << "input + for refill or - for withdrow\n";
	std::cin >> qwery;
	std::ifstream input("cash.txt", std::ios::binary);
	if (input.is_open())
	{
		input.read((char*)money, sizeof(money));
		input.close();
	} else {
		std::cerr << "something wrong with file";
		return 0;
	}
	if (qwery == "+")
	{
		for (int i = 0; i < 1000; i++)
		{
			money[i] = banknotes[std::rand() % 5];
		}
		std::ofstream output("cash.txt", std::ios::binary);
		output.write((char*)money, sizeof(money));
		return 1;
	}
	else if (qwery == "-")
	{
		std::cout << "Amount: ";
		int amount;
		std::cin >> amount;
		if ((amount % 100) != 0)
		{
			std::cerr << "Invalid amount" << amount << std::endl;
			return 2;
		}
		withdrow_amount = amount;
		for (int i = 0; i >= 0; --i)
		{
			int banknote = banknotes[i];
			for (int j = 0; j < 1000; ++j) {
				if (money[j] == banknote) {
					if (withdrow_amount >= banknote) {
						money[j] = 0;
						withdrow_amount -= banknote;
						if (withdrow_amount == 0) {
							std::cout << "Amount taken: " << amount << std::endl;
							std::ofstream output("cash.txt", std::ios::binary);
							output.write((char*)money, sizeof(money));
							return 0;
						}
					}
				}
			}
		}
		std::cerr << "not enogh banknotes";
	}
}