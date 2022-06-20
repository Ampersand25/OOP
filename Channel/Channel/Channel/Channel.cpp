#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

class Channel {
public:
	Channel() = default;

	virtual void send(const string& msg) const = 0;

	virtual ~Channel() = default;
};

class Telefon : public Channel {
private:
	int nrTel;

public:
	Telefon() = delete;

	Telefon(int nrTel) : nrTel{ nrTel } {
		srand(time(NULL)); // srand(time(0));
	}

	virtual void send(const string& msg) const override {
		cout << "dial: " << this->nrTel << endl;

		if (rand() % 10 < 5)
			throw exception("[!]Linia este ocupata!");
	}

	virtual ~Telefon() = default;
};

class Fax : public Telefon {
public:
	Fax() = delete;

	Fax(int nrTel) : Telefon{ nrTel } {

	}

	void send(const string& msg) const override {
		Telefon::send(msg);
		cout << "sending fax\n";
	}

	~Fax() = default;
};

class SMS : public Telefon {
public:
	SMS() = delete;

	SMS(int nrTel) : Telefon{ nrTel } {

	}

	void send(const string& msg) const override {
		Telefon::send(msg);
		cout << "sending sms\n";
	}

	~SMS() = default;
};

class Failover : public Channel {
private:
	Channel* channel_1;
	Channel* channel_2;

public:
	Failover() = delete;

	Failover(Channel* channel_1, Channel* channel_2) : channel_1{ channel_1 }, channel_2{ channel_2 } {

	}

	void send(const string& msg) const override {
		try {
			this->channel_1->send(msg);
		}
		catch (const exception& ex) {
			cerr << ex.what() << endl;
			this->channel_2->send(msg);
		}
	}

	~Failover() {
		delete this->channel_1;
		delete this->channel_2;
	}
};

class Contact {
private:
	Channel* channel_1;
	Channel* channel_2;
	Channel* channel_3;

public:
	Contact() = delete;

	Contact(Channel* channel_1, Channel* channel_2, Channel* channel_3) : channel_1{ channel_1 }, channel_2{ channel_2 }, channel_3{ channel_3 } {

	}

	void sendAlarm(const string& msg) const noexcept {
		auto run{ true };

		while (run) {
			try {
				this->channel_1->send(msg);
				run = false;
			}
			catch (const exception& ex) {
				try {
					cerr << ex.what() << endl;
					this->channel_2->send(msg);
					run = false;
				}
				catch (const exception& ex) {
					try {
						cerr << ex.what() << endl;
						this->channel_3->send(msg);
						run = false;
					}
					catch (const exception& ex) {
						cerr << ex.what() << endl;
					}
				}
			}
		}
	}

	Channel* getChannel1() const noexcept {
		return this->channel_1;
	}

	Channel* getChannel2() const noexcept {
		return this->channel_2;
	}

	Channel* getChannel3() const noexcept {
		return this->channel_3;
	}

	~Contact() = default;
};

Contact creareContact() {
	Channel* telefon{ new Telefon{ 123 } };
	Channel* faxSMS{ new Failover{ new Fax{ 45 }, new SMS{ 678 } } };
	Channel* telefonFaxSMS{ new Failover{ new Telefon{ 9 }, new Failover{ new Fax{ 12345 }, new SMS{6789} } } };

	Contact contact{ telefon, faxSMS, telefonFaxSMS };

	return contact;
}

int main(void)
{
	{
		const auto contact{ creareContact() };

		contact.sendAlarm("Hello, ");
		contact.sendAlarm("World");
		contact.sendAlarm("!");

		auto channel_1{ contact.getChannel1() };
		auto channel_2{ contact.getChannel2() };
		auto channel_3{ contact.getChannel3() };

		delete channel_1;
		delete channel_2;
		delete channel_3;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}