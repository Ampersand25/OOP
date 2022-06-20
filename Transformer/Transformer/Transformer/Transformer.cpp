#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;
using std::sort;
using std::cout;
using std::endl;

class Transformer {
public:
	Transformer() = default;

	virtual void transform(vector<int>& nrs) const noexcept = 0;

	virtual ~Transformer() = default;
};

class Adder : public Transformer {
private:
	int cat;

public:
	Adder() = delete;

	Adder(int cat) : cat{ cat } {

	}

	virtual void transform(vector<int>& nrs) const noexcept override {
		for (auto& nr : nrs)
			nr += this->cat;
	}

	virtual ~Adder() = default;
};

class Swapper : public Transformer {
public:
	Swapper() = default;

	void transform(vector<int>& nrs) const noexcept override {
		for (auto i{ 1 }; i < nrs.size(); i += 2)
			swap(nrs.at(i - 1), nrs.at(i));
	}

	~Swapper() = default;
};

class Nuller : public Adder {
public:
	Nuller() = delete;

	Nuller(int cat) : Adder{ cat } {

	}

	void transform(vector<int>& nrs) const noexcept override {
		Adder::transform(nrs);

		for (auto& nr : nrs)
			if (nr > 10)
				nr = 0;
	}

	~Nuller() = default;
};

class Composite : public Transformer {
private:
	Transformer* transformer_1;
	Transformer* transformer_2;

public:
	Composite() = delete;

	Composite(Transformer* transformer_1, Transformer* transformer_2) : transformer_1{ transformer_1 }, transformer_2{ transformer_2 } {

	}

	void transform(vector<int>& nrs) const noexcept override {
		transformer_1->transform(nrs);
		transformer_2->transform(nrs);
	}

	~Composite() {
		delete transformer_1;
		delete transformer_2;
	}
};

class Numbers {
private:
	Transformer* transformer;
	vector<int> nrs;

public:
	Numbers() = delete;

	Numbers(Transformer* transformer) : transformer{ transformer } {

	}

	void add(int nr) noexcept {
		this->nrs.push_back(nr);
	}

	vector<int> transform() noexcept {
		sort(this->nrs.begin(), this->nrs.end(), [](int a, int b) {
			return a > b;
			});

		this->transformer->transform(this->nrs);

		return this->nrs;
	}

	Transformer* getTransformer() const noexcept {
		return this->transformer;
	}

	~Numbers() = default;
};

Numbers creareNumbers1() {
	Numbers numbers{ new Composite{ new Nuller{ 9 }, new Swapper } };

	return numbers;
}

Numbers creareNumbers2() {
	Numbers numbers{ new Composite{ new Nuller{ 9 }, new Composite{ new Swapper{}, new Adder{ 3 } } } };

	return numbers;
}

int main(void)
{
	{
		auto numbers_1{ creareNumbers1() };
		auto numbers_2{ creareNumbers2() };

		numbers_1.add(-8);
		numbers_1.add(3);
		numbers_1.add(-11);
		numbers_1.add(4);
		numbers_1.add(1);

		numbers_2.add(0);
		numbers_2.add(-5);
		numbers_2.add(4);
		numbers_2.add(-12);
		numbers_2.add(-7);

		const auto nrs_1{ numbers_1.transform() };
		const auto nrs_2{ numbers_2.transform() };

		for (const auto& nr : nrs_1)
			cout << nr << ' ';

		cout << endl;

		for (const auto& nr : nrs_2)
			cout << nr << ' ';

		delete numbers_1.getTransformer();
		delete numbers_2.getTransformer();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}
