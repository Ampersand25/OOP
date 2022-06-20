#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::exception;

template<typename T>
class IteratorGeanta;

template<typename T>
class Geanta {
	friend class IteratorGeanta<T>;

private:
	T proprietar;
	vector<T> continut;

public:
	Geanta() = delete;

	Geanta(const T& proprietar) : proprietar{ proprietar } {

	}

	Geanta& operator+(const T& item) noexcept {
		this->continut.push_back(item);
		return *this;
	}

	IteratorGeanta<T> begin() noexcept {
		return IteratorGeanta<T>(*this);
	}

	IteratorGeanta<T> end() noexcept {
		return IteratorGeanta<T>(*this, this->continut.size());
	}

	~Geanta() = default;
};

template<typename T>
class IteratorGeanta {
	friend class Geanta<T>;

private:
	Geanta<T>& geanta;
	int pos;

public:
	IteratorGeanta() = delete;

	IteratorGeanta(Geanta<T>& geanta) : geanta{ geanta }, pos{ 0 } {

	}

	IteratorGeanta(Geanta<T>& geanta, int pos) : geanta{ geanta }, pos{ pos } {

	}

	T operator*() const {
		if(this->pos >= 0 && this->pos < this->geanta.continut.size())
			return this->geanta.continut.at(this->pos);
		throw exception("[!]Index out of range!");
	}

	IteratorGeanta<T> operator++() noexcept {
		++this->pos;
		return *this;
	}

	bool operator==(const IteratorGeanta<T> ot) const noexcept {
		return this->pos == ot.pos;
	}

	bool operator!=(const IteratorGeanta<T> ot) const noexcept {
		return this->pos != ot.pos;
	}

	~IteratorGeanta() = default;
};

void calatorie() {
	Geanta<string> ganta{ "Ion" };//creaza geanta pentru Ion
	ganta = ganta + string{ "haine" }; //adauga obiect in ganta
	ganta + string{ "pahar" };
	for (auto o : ganta) {//itereaza obiectele din geanta
		cout << o << "\n";
	}
}

int main() {
	calatorie();
	return 0;
}