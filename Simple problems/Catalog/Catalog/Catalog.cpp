#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::exception;

template<typename T>
class IteratorCatalog;

template<typename T>
class Catalog {
	friend class IteratorCatalog<T>;

private:
	string curs;
	vector<T> note;

public:
	Catalog() = delete;

	Catalog(const string& curs) : curs{ curs } {

	}

	Catalog& operator+(const T& nota) noexcept {
		this->note.push_back(nota);
		return *this;
	}

	IteratorCatalog<T> begin() noexcept {
		return IteratorCatalog<T>(*this);
	}

	IteratorCatalog<T> end() noexcept {
		return IteratorCatalog<T>(*this, this->note.size());
	}

	~Catalog() = default;
};

template<typename T>
class IteratorCatalog {
	friend class Catalog<T>;

private:
	Catalog<T>& catalog;
	int pos;

public:
	IteratorCatalog() = delete;

	IteratorCatalog(Catalog<T>& catalog) : catalog{ catalog }, pos{ 0 } {

	}

	IteratorCatalog(Catalog<T>& catalog, int pos) : catalog{ catalog }, pos{ pos } {

	}

	bool operator==(const IteratorCatalog& ot) const noexcept {
		return this->pos == ot.pos;
	}

	bool operator!=(const IteratorCatalog& ot) const noexcept {
		return this->pos != ot.pos;
	}

	IteratorCatalog& operator++() noexcept {
		++this->pos;
		return *this;
	}

	T operator*() const {
		if (this->pos < 0 || this->pos >= this->catalog.note.size())
			throw exception("[!]Index out of bounds!");
		
		return this->catalog.note.at(this->pos);
	}

	~IteratorCatalog() = default;
};

void catalog() {
	Catalog<int> cat{ "OOP" };//creaza catalog cu note intregi
	cat + 10; //adauga o nota in catalog
	cat = cat + 8 + 6;
	int sum = 0;
	for (auto n : cat) { sum += n; } //itereaza notele din catalog
	std::cout << "Suma note:" << sum << "\n";
}

int main() {
	catalog();
	return 0;
}