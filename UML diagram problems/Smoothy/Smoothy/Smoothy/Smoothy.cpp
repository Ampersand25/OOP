#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::sort;
using std::cout;
using std::endl;

class Smoothy {
private:
	int pret;

public:
	Smoothy() = delete;

	Smoothy(int pret) : pret{ pret } {

	}

	int getPret() const noexcept {
		return this->pret;
	}

	virtual string descriere() const noexcept = 0;

	virtual ~Smoothy() = default;
};

class BasicSmoothy : public Smoothy {
private:
	string nume;

public:
	BasicSmoothy() = delete;

	BasicSmoothy(int pret, const string& nume) : Smoothy{ pret }, nume{ nume } {

	}

	string descriere() const noexcept override {
		return this->nume;
	}

	~BasicSmoothy() = default;
};

class DecoratorSmoothy : public Smoothy {
private:
	Smoothy* smoothy;

public:
	DecoratorSmoothy() = delete;

	DecoratorSmoothy(Smoothy* smoothy) : Smoothy{ smoothy->getPret() }, smoothy{smoothy} {

	}

	DecoratorSmoothy(int pret, Smoothy* smoothy) : Smoothy{ pret }, smoothy{ smoothy } {

	}

	virtual string descriere() const noexcept override {
		return this->smoothy->descriere();
	}

	virtual ~DecoratorSmoothy() {
		delete smoothy;
	}
};

class SmoothyCuFrisca : public DecoratorSmoothy {
public:
	SmoothyCuFrisca() = delete;

	SmoothyCuFrisca(Smoothy* smoothy) : DecoratorSmoothy{ smoothy->getPret() + 2, smoothy} {

	}

	string descriere() const noexcept override {
		return DecoratorSmoothy::descriere() + " cu frisca";
	}

	~SmoothyCuFrisca() = default;
};

class SmoothyCuUmbreluta : public DecoratorSmoothy {
public:
	SmoothyCuUmbreluta() = delete;

	SmoothyCuUmbreluta(Smoothy* smoothy) : DecoratorSmoothy{ smoothy->getPret() + 3, smoothy } {

	}

	string descriere() const noexcept override {
		return DecoratorSmoothy::descriere() + " cu umbreluta";
	}

	~SmoothyCuUmbreluta() = default;
};

vector<Smoothy*> getSmoothyList() {
	vector<Smoothy*> smoothyList;

	// 1) un smoothy de kivi cu frisca si umbreluta
	const auto smoothy_1{ new SmoothyCuUmbreluta{ new SmoothyCuFrisca{ new BasicSmoothy{ 10, "kivi" } } } };
	smoothyList.push_back(smoothy_1);

	// 2) un smoothy de capsuni cu frisca
	const auto smoothy_2{ new SmoothyCuFrisca{ new BasicSmoothy{ 10, "capsuni" } } };
	smoothyList.push_back(smoothy_2);

	// 3) un smoothy simplu de kivi
	const auto smoothy_3{ new BasicSmoothy{10, "kivi" } };
	smoothyList.push_back(smoothy_3);

	return smoothyList;
}

int main(void)
{
	{
		auto smoothyList{ getSmoothyList() };

		sort(smoothyList.begin(), smoothyList.end(), [](Smoothy* smoothy_1, Smoothy* smoothy_2) {
			return smoothy_1->descriere() < smoothy_2->descriere();
			});

		for (const auto& smoothy : smoothyList) {
			cout << smoothy->descriere() << ' ' << smoothy->getPret() << endl;
			delete smoothy;
		}
	}

	_CrtDumpMemoryLeaks();

	return 0;
}