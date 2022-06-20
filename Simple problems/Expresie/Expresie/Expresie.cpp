#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template<typename T>
class Expresie {
private:
	T result;
	vector<T> undoL;

public:
	Expresie() : result{ 0 } {

	}

	Expresie(const T& operand) : result{ operand } {
		
	}

	Expresie& operator+(const T& operand) noexcept {
		this->undoL.push_back(result);
		this->result += operand;
		return *this;
	}

	Expresie& operator-(const T& operand) noexcept {
		this->undoL.push_back(result);
		this->result -= operand;
		return *this;
	}

	T valoare() const noexcept {
		return this->result;
	}

	Expresie& undo() noexcept {
		if (!this->undoL.empty()) {
			this->result = this->undoL.back();
			this->undoL.pop_back();
		}
		return *this;
	}

	~Expresie() = default;
};

void operatii() {
	Expresie<int> exp{ 3 };//construim o expresie,pornim cu operandul 3
	//se extinde expresia in dreapta cu operator (+ sau -) si operand
	exp = exp + 7 + 3;
	exp = exp - 8;
	//tipareste valoarea expresiei (in acest caz:5 rezultat din 3+7+3-8)
	cout << exp.valoare() << "\n";
	exp.undo(); //reface ultima operatie efectuata
	//tipareste valoarea expresiei (in acest caz:13 rezultat din 3+7+3)
	cout << exp.valoare() << "\n";
	exp.undo().undo();
	cout << exp.valoare() << "\n"; //tipareste valoarea expresiei (in acest caz:3)
}

int main() {
	operatii();
	return 0;
}