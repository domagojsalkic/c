#include <iostream>
#include <string>

class animal {
public:
	virtual unsigned num_Leggs() const = 0;
	virtual std::string species_Name() const = 0;
	virtual ~animal() = 0;
};

animal::~animal() {};

class bird : public animal {
protected:
	unsigned leggs;
	std::string species;
public:
	bird(int i, std::string s) : leggs(i), species(s) {};
//	unsigned num_Leggs() const { return this->leggs; };
//	std::string species_Name() const { return this->species; };
//	~bird() { std::cout << "bird deleted." << std::endl;};
};

class owl : public bird {
public:
	owl() : bird(2, "owl") {};
	unsigned num_Leggs() const { return this->leggs; };
	std::string species_Name() const { return this->species; };
	~owl() { std::cout << "owl deleted." << std::endl; };
};


class sparrow : public bird {
public:
	sparrow() : bird(2, "sparrow") {};
	unsigned num_Leggs() const { return this->leggs; } ;
	std::string species_Name() const { return this->species; };
	~sparrow() { std::cout << "sparrow deleted." << std::endl; };
};

class insect : public animal {
protected:
	unsigned leggs;
	std::string species;
public:
	insect(int i, std::string s) : leggs(i), species(s) {};
//	unsigned num_Leggs() const { return this->leggs; };
//	std::string species_Name() const { return this->species; };
//	~insect() { std::cout << "insect deleted." << std::endl;};
};

class grasshopper : public insect {
public:
	grasshopper() : insect(6, "grasshopper") {};
	unsigned num_Leggs() const { return this->leggs; };
	std::string species_Name() const { return this->species; };
	~grasshopper() { std::cout << "grasshopper deleted."<<std::endl;};
};
class cockroach : public insect {
public:
	cockroach() : insect(6, "cockroach") {};
	unsigned num_Leggs()const { return this->leggs; };
	std::string species_Name() const { return this->species; };
	~cockroach() { std::cout << "cockroach deleted." << std::endl;};
};

class spider : public animal {
protected:
	unsigned leggs;
	std::string species;	
public:
	spider(int i, std::string s) : leggs(i), species(s){};
//	unsigned num_Leggs()const { return leggs; };
//	std::string species_Name() const { return species; };
//	~spider() { std::cout << "spider deleted."<<std::endl; };
};
class hobo : public spider {
public:
	hobo() : spider(8, "hobo") {};
	unsigned num_Leggs() const { return this->leggs; };
	std::string species_Name() const { return this->species; };
	~hobo() { std::cout << "hobo deleted." << std::endl; };
};

class tarantula : public spider {
public:
	tarantula() : spider(8, "tarantula") {};
	unsigned num_Leggs() const { return this->leggs; };
	std::string species_Name() const { return this->species; };
	~tarantula() { std::cout << "tarantula deleted." << std::endl; };
};
animal* animal_factory(int i) {
	animal* temp;
	if (i == 1)
		temp = new cockroach;
	else if (i == 2)
		temp = new tarantula;
	else if (i == 3)
		temp = new sparrow;
	/*else if (i == 4)
		temp = new grasshopper;
	else if (i == 5)
		temp = new hobo;
	else if (i == 6)
		temp = new owl;*/
	else
		temp = nullptr;

	return temp;
}


class legg_counter {
	unsigned sumLeggs;
public:
	legg_counter() : sumLeggs(0) {};
	void count_Leggs(animal *animal) { this->sumLeggs += animal->num_Leggs(); };
	void ispis() const { std::cout << sumLeggs << std::endl; };
	~legg_counter() { std::cout << "legg_counter deleted." << std::endl; };
};


int main() {
	int n;
	animal *pa = nullptr;
	legg_counter leggs;
	while (std::cin >> n) {
		pa = animal_factory(n);
		if (pa == nullptr)
			break;
		leggs.count_Leggs(pa);
	}
	/*for (int i = 0; i < 3; i++) {
		std::cin >> n;
		pa[i] = animal_factory(n);
		leggs.count_Leggs(pa[i]);
	}
	for (int i = 0; i < 3; i++) {
		std::cout << pa[i]->species_Name() << std::endl;
	}*/
	leggs.ispis();

	delete pa; pa = nullptr;

	return 0;
}