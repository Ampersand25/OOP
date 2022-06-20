#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using std::string;
using std::vector;
using std::sort;
using std::cout;

class Meniu {
private:
	int pret;

public:
	Meniu() = delete;

	Meniu(int pret) : pret{ pret } {

	}

	int getPret() const noexcept {
		return this->pret;
	}

	virtual string descriere() const noexcept = 0;

	virtual ~Meniu() = default;
};

class MicDejun : public Meniu {
private:
	string denumire;

public:
	MicDejun() = delete;

	MicDejun(int pret, const string& denumire) : Meniu{ pret }, denumire{ denumire } {
		assert((pret == 10 && denumire == "Ochiuri") || (pret == 15 && denumire == "Omleta"));
	}

	string descriere() const noexcept override {
		return  this->denumire;
	}

	~MicDejun() = default;
};

class CuRacoritoare : public Meniu {
private:
	Meniu* meniu;

public:
	CuRacoritoare() = delete;

	CuRacoritoare(Meniu* meniu) : Meniu{ meniu->getPret() + 4 }, meniu{meniu} {

	}

	string descriere() const noexcept override {
		return this->meniu->descriere() + " cu racoritoare";
	}

	~CuRacoritoare() {
		delete meniu;
	}
};

class CuCafea : public Meniu {
private:
	Meniu* meniu;

public:
	CuCafea() = delete;

	CuCafea(Meniu* meniu) : Meniu{ meniu->getPret() + 5 }, meniu{meniu} {

	}

	string descriere() const noexcept override {
		return this->meniu->descriere() + " cu cafea";
	}

	~CuCafea() {
		delete meniu;
	}
};

auto creareMeniu() {
	vector<Meniu*> meniu;

	// 1) un meniu cu Omleta cu racoritoare si cafea
	const auto micDejun1{ new CuCafea{ new CuRacoritoare{ new MicDejun{ 15, "Omleta" } } } };
	meniu.push_back(micDejun1);

	// 2) un meniu cu Ochiuri si cafea
	const auto micDejun2{ new CuCafea{ new MicDejun{ 10, "Ochiuri" } } };
	meniu.push_back(micDejun2);

	// 3) un meniu cu Omleta
	const auto micDejun3{ new MicDejun{ 15, "Omleta" } };
	meniu.push_back(micDejun3);

	return meniu;
}

int main(void)
{
	{
		auto meniu{ creareMeniu() };

		sort(meniu.begin(), meniu.end(), [](const Meniu* meniu1, const Meniu* meniu2) {
			return meniu1->getPret() > meniu2->getPret();
			});

		for (const auto& micDejun : meniu) {
			cout << micDejun->descriere() << ' ' << micDejun->getPret() << '\n';
			delete micDejun;
		}
	}

	return 0;
}