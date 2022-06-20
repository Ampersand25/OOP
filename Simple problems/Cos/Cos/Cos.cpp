#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;

template<typename T>
class Cos {
private:
	vector<T> produse;
	vector<vector<T>> undoL;

public:
	Cos() = default;

	Cos& operator+(const T& produs) noexcept {
		this->undoL.push_back(this->produse);
		this->produse.push_back(produs);
		
		return *this;
	}
	
	void tipareste(ostream& out) const noexcept {
		if (this->produse.empty()) {
			out << "[!]Cosul este gol!\n";
			return;
		}

		for (const auto& produs : this->produse)
			out << produs << ' ';
		out << endl;
	}

	Cos& undo() noexcept {
		if (this->undoL.size()) {
			this->produse = this->undoL.back();
			this->undoL.pop_back();
		}

		return *this;
	}

	~Cos() = default;
};

void cumparaturi() {
	Cos<string> cos;//creaza un cos de cumparaturi
	cos = cos + "Mere"; //adauga Mere in cos
	cos.undo();//elimina Mere din cos
	cos + "Mere"; //adauga Mere in cos
	cos = cos + "Paine" + "Lapte";//adauga Paine si Lapte in cos
	cos.undo().undo();//elimina ultimele doua produse adaugate

	cos.tipareste(cout);//tipareste elementele din cos (Mere)
}

int main() {
	cumparaturi();
	return 0;
}