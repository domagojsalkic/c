#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

typedef std::vector<int>::const_iterator Iter;

bool isOdd(int broj) { return broj % 2 == 1; };
bool comp(int a, int b) {
	if (!isOdd(a) && isOdd(b))
		return true;
	if (isOdd(a) && !isOdd(b))
		return false;
	return a < b;
}
bool veciOd(int broj) { return broj >= 100; };
void print(const int& n) { std::cout << n << " "; };
bool potencija(int n) {
	return (n > 0 && ((n & (n - 1)) == 0));
}

int main() {
	std::vector<int> b;
	Iter it;
	int broj;
	while (true) {
		std::cin >> broj;
		if (std::cin.fail())
			break;
		b.push_back(broj);
	}
	if (!b.empty()) {
		std::cout << *(std::min_element(b.begin(), b.end())) << std::endl;
		it = std::find_if(b.begin(), b.end(), isOdd);
		if (it != b.end())
			std::cout << *it << std::endl;
		std::cout << std::count_if(b.begin(), b.end(), isOdd) << std::endl;
		b.erase(remove_if(b.begin(), b.end(), veciOd), b.end());
		std::replace_if(b.begin(), b.end(), potencija, 2);
		std::sort(b.begin(), b.end(), comp);
		std::for_each(b.begin(), b.end(), print);
	}
	else {
		std::cout << 0;
	}
}