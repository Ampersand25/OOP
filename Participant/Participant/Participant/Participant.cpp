#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::copy_if;
using std::back_inserter;

class Participant {
public:
	Participant() = default;

	virtual void tipareste(ostream& out) const noexcept = 0;

	virtual bool eVoluntar() const noexcept {
		return true;
	}

	virtual ~Participant() = default;
};

class Angajat : public Participant {
private:
	Participant* participant;

public:
	Angajat() = delete;

	Angajat(Participant* participant) : Participant{}, participant{ participant } {

	}

	void tipareste(ostream& out) const noexcept override {
		this->participant->tipareste(out);
		out << " angajat";
	}

	bool eVoluntar() const noexcept override {
		return false;
	}

	~Angajat() {
		delete participant;
	}
};

class Personal : public Participant {
private:
	string nume;

public:
	Personal() = delete;

	Personal(const string& nume) : Participant{}, nume{ nume } {

	}

	virtual void tipareste(ostream& out) const noexcept override {
		out << this->nume;
	}

	virtual ~Personal() = default;
};

class Administrator : public Personal {
public:
	Administrator() = delete;

	Administrator(const string& nume) : Personal{ nume } {

	}

	void tipareste(ostream& out) const noexcept override {
		Personal::tipareste(out);
		out << " Administrator";
	}

	~Administrator() = default;
};

class Director : public Personal {
public:
	Director() = delete;

	Director(const string& nume) : Personal{ nume } {

	}

	void tipareste(ostream& out) const noexcept override {
		Personal::tipareste(out);
		out << " Director";
	}

	~Director() = default;
};

class ONG {
private:
	vector<Participant*> participanti;

public:
	ONG() = default;

	void add(Participant* participant) noexcept {
		this->participanti.push_back(participant);
	}

	vector<Participant*> getAll(bool voluntari) const noexcept {
		vector<Participant*> all;

		copy_if(this->participanti.begin(), this->participanti.end(), back_inserter(all), [&voluntari](Participant* participant) {
			return participant->eVoluntar() == voluntari;
			});
		
		return all;
	}

	~ONG() = default;
};

ONG creareONG() {
	ONG ong;

	// 1) un administrator voluntar
	Participant* administratorVoluntar{ new Administrator{ "Vasile" } };
	ong.add(administratorVoluntar);

	// 2) un administrator angajat
	Participant* administratorAngajat{ new Angajat{ new Administrator{ "Ion" } } };
	ong.add(administratorAngajat);

	// 3) un director voluntar
	Participant* directorVoluntar{ new Director{ "Tudor" } };
	ong.add(directorVoluntar);

	// 4) un director angajat
	Participant* directorAngajat{ new Angajat{ new Director{ "Mircea" } } };
	ong.add(directorAngajat);

	return ong;
}

int main(void)
{
	{
		const auto ong{ creareONG() };

		cout << "Angajati:\n";
		const auto angajati{ ong.getAll(false) };
		for (const auto& angajat : angajati) {
			angajat->tipareste(cout);
			cout << endl;
		}

		cout << "\nVoluntari:\n";
		const auto voluntari{ ong.getAll(true) };
		for (const auto& voluntar : voluntari) {
			voluntar->tipareste(cout);
			cout << endl;
		}

		for (const auto& angajat : angajati)
			delete angajat;

		for (const auto& voluntar : voluntari)
			delete voluntar;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}