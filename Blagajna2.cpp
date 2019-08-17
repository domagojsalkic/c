#include <iostream>
#include <iomanip>

class money {
	int kn;
	int lp;
public:
	money(int kn = 0, int lp = 0) : kn(kn), lp(lp) {}
	money& operator+=(const money& novac);
	money& operator-=(const money& novac);
	friend std::ostream& operator<<(std::ostream& os, const money& novac);
	friend std::istream& operator>>(std::istream& is, money& novac);
};

money& money::operator+=(const money& novac) {
	this->lp += novac.lp;
	this->kn += novac.kn;
	if (this->lp >= 100) {
		this->lp -= 100;
		++(this->kn);
	}

	return *this;
}

money& money::operator-=(const money& novac) {
	this->lp -= novac.lp;
	this->kn -= novac.kn;
	if (this->lp < 0) {
		--this->kn;
		this->lp += 100;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const money& novac) {
	os << novac.kn << " kn";
	if (novac.lp)
		os << ", " << std::setw(2) << std::setfill('0') << novac.lp << " lp";
	return os;
}

std::istream& operator>>(std::istream& is, money& novac) {
	is >> novac.kn >> novac.lp;
	return is;
}

int main() {
	money racun, uk;
	char c;
	while (std::cin >> c >> racun) {
		if (c == '-')
			uk -= racun;
		else
			uk += racun;
	}
	std::cout << uk;
}