#include <iostream>
#include <iomanip>

class money {
	int kn;
	int lp;
public:
	money(int kn=0, int lp=0) : kn(kn), lp(lp) {}
	money& operator+=(const money& novac);
	money& operator-=(const money& novac);
	int isNegativ() { return this->kn < 0 ? 1 : 0; }
	friend std::ostream& operator<<(std::ostream& os, const money& novac);
	friend std::istream& operator>>(std::istream& is, money& novac);
};

money& money::operator+=(const money& novac) {
	int ukLipe = this->kn < 0 ? ((this->kn * 100) - this->lp) : ((this->kn * 100) + this->lp);
	int lipe = (novac.kn * 100) + novac.lp;

	this->kn = (ukLipe + lipe) / 100;
	this->lp = (ukLipe + lipe) % 100;

	return *this;
}

money& money::operator-=(const money& novac) {
	int ukLipe = this->kn < 0 ? ((this->kn * 100) - this->lp) : ((this->kn * 100) + this->lp);
	int lipe = (novac.kn * 100) - novac.lp;

	this->kn = ukLipe < 0 ? ((ukLipe + lipe) / 100) : ((ukLipe + lipe) / 100);
	this->lp = ukLipe < 0 ? (ukLipe + lipe) % 100 * (-1) : ukLipe == 0 ? ((ukLipe + lipe) % 100) * (-1) : ((ukLipe + lipe) % 100);

	return *this;
}

std::ostream& operator<<(std::ostream& os,const money& novac) {
	return (novac.lp ? (os << novac.kn << " kn, " << std::setw(2) << std::setfill('0') << novac.lp << " lp" ) : (os << novac.kn << " kn"));
}

std::istream& operator>>(std::istream& is, money& novac) {
	char prefix;
	is >> prefix >> novac.kn >> novac.lp;
	if (prefix == '-') {
		novac.kn = novac.kn * (-1);
	}
	return is;
}

int main() {
	money racun,uk;
	while (std::cin >> racun) {
		if (racun.isNegativ())
			uk -= racun;
		else
			uk += racun;
	}
	std::cout << uk;
}