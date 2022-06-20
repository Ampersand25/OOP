#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class Examen {
private:
	string tip;
	string ora;

public:
	Examen() = delete;

	Examen(const string& tip, const string& ora) : tip{ tip }, ora{ ora } {

	}

	string getDescriere() const noexcept {
		return this->tip + ' ' + this->ora;
	}

	~Examen() = default;
};

template<typename T>
class ToDo {
private:
	vector<T> toDoList;

public:
	ToDo() = default;

	ToDo& operator<<(const T& toDoItem) noexcept {
		this->toDoList.push_back(toDoItem);
		return *this;
	}

	void printToDoList(ostream& out) noexcept {
		if (this->toDoList.empty()) {
			out << "[X]Nu exista niciun item in lista ToDo!\n";
			return;
		}
		
		for (const auto& toDoItem : this->toDoList)
			out << toDoItem.getDescriere() << '\n';
	}

	~ToDo() = default;
};

void todolist() {
	ToDo<Examen> todo;
	Examen oop{ "oop scris","8:00" };
	todo << oop << Examen{ "oop practic", "11:00" }; //Adauga 2 examene la todo
	std::cout << oop.getDescriere(); //tipareste la consola: oop scris ora 8:00
	//itereaza elementele adaugate si tipareste la consola lista de activitati
	//in acest caz tipareste: De facut:oop scris ora 8:00;oop practic ora 11:00
	todo.printToDoList(std::cout);
}

int main() {
	todolist();
	return 0;
}