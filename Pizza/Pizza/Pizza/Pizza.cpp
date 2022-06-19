#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::exception;
using std::sort;
using std::cout;

class Pizza {
private:
	int pret;

public:
	Pizza() = delete;

	Pizza(int pret) : pret{ pret } {

	}

	int getPret() const noexcept {
		return this->pret;
	}

	virtual string descriere() const noexcept = 0;

	virtual ~Pizza() = default;
};

class BasicPizza : public Pizza {
private:
	string denumire;

public:
	BasicPizza() = delete;

	BasicPizza(int pret, const string& denumire) : Pizza{ pret }, denumire { denumire } {
		if ((pret != 15 || denumire != "Salami") && (pret != 20 || denumire != "Diavola")) {
			throw exception("[X]Pizza does not exist!");
		}
	}

	string descriere() const noexcept override {
		return this->denumire;
	}

	~BasicPizza() = default;
};

class PizzaCuPeperoni : public Pizza {
private:
	Pizza* pizza;

public:
	PizzaCuPeperoni() = delete;

	PizzaCuPeperoni(Pizza* pizza) : Pizza{ pizza->getPret() + 2 }, pizza{pizza} {

	}

	string descriere() const noexcept override {
		return this->pizza->descriere() + " cu peperoni";
	}

	~PizzaCuPeperoni() {
		delete pizza;
	}
};

class PizzaCuCiuperci : public Pizza {
private:
	Pizza* pizza;

public:
	PizzaCuCiuperci() = delete;

	PizzaCuCiuperci(Pizza* pizza) : Pizza{ pizza->getPret() + 3 }, pizza{ pizza } {

	}

	string descriere() const noexcept override {
		return this->pizza->descriere() + " cu ciuperci";
	}

	~PizzaCuCiuperci() {
		delete pizza;
	}
};

vector<Pizza*> creareComanda() {
	vector<Pizza*> comanda;

#define pb push_back

	// 1) o pizza "Salami" cu ciuperci
	Pizza* pizza_1{ new PizzaCuCiuperci{ new BasicPizza{ 15, "Salami" } } };
	comanda.pb(pizza_1);

	// 2) o pizza "Salami" simpla
	Pizza* pizza_2{ new BasicPizza{ 15, "Salami" } };
	comanda.pb(pizza_2);

	// 3) o pizza "Diavola" cu peperoni si ciuperci
	Pizza* pizza_3{ new PizzaCuCiuperci{ new PizzaCuPeperoni{ new BasicPizza{ 20, "Diavola" } } } };
	comanda.pb(pizza_3);

#undef pb

	return comanda;
}

int main(void)
{
	{
		auto comanda{ creareComanda() };

		sort(comanda.begin(), comanda.end(), [](const Pizza* pizza_1, const Pizza* pizza_2) {
			return pizza_1->getPret() > pizza_2->getPret();
			});

		for (const auto pizza : comanda) {
			cout << pizza->descriere() << ' ' << pizza->getPret() << '\n';
		}

		for (const auto& pizza : comanda) {
			delete pizza;
		}
	}

	return 0;
}