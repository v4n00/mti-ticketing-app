#include "../Headers/Room.h"

unsigned int Room::TOTAL_ROOMS = 0;

Seat** Room::generateRoomOfSeats(unsigned int numberOfSeats) {
	Seat** rez = new Seat * [numberOfSeats];
	for (size_t i = 0; i < numberOfSeats; ++i)
		rez[i] = new Seat();
	return rez;
}

// TODO:
void Room::changeSeatAvailability(unsigned int seatId, SeatAvailability newAvailability) {
	for (size_t i = 0; i < this->numberOfSeats; ++i)
		if (this->seats[i]->getSeatId() == seatId)
			this->seats[i]->setAvailability(newAvailability);
}

// - Getters/Setters
char* Room::getName() {
	return Util::deepCopy(this->name);
}

bool Room::getVIPStatus() {
	return this->isVIP;
}

Seat** Room::getSeats() {
	Seat** rez = new Seat * [numberOfSeats];
	for (size_t i = 0; i < numberOfSeats; ++i)
		rez[i] = new Seat(*(this->seats[i]));
	return rez;
}

unsigned int Room::getNumberOfSeats() {
	return this->numberOfSeats;
}

unsigned int Room::getNumberOfRows() {
	return this->numberOfRows;
}

void Room::setRoomId(unsigned int roomId) {
	if (roomId != 0)
		this->roomId = roomId;
	else throw;
}

void Room::setName(const char* name) {
	if (strlen(name) != 1)
		this->name = Util::deepCopy(name);
	else throw;
}

void Room::setType(const bool isVIP) {
	this->isVIP = isVIP;
}

void Room::setNumberOfSeats(unsigned int numberOfSeats) {
	if (numberOfSeats != 0)
		this->numberOfSeats = numberOfSeats;
	else throw;
}

void Room::setSeats(Seat** seats) {
	if (seats != nullptr) {
		this->seats = new Seat * [numberOfSeats];
		for (size_t i = 0; i < numberOfSeats; ++i)
			this->seats[i] = new Seat(*(seats[i]));
	}
	else throw;
}

void Room::setNumberOfRows(unsigned int numberOfRows) {
	if (numberOfRows < this->numberOfSeats)
		this->numberOfRows = numberOfRows;
	else throw;
}

// - Constructors / Destructors

Room::Room(const Room& anotherRoom) {
	this->setRoomId(anotherRoom.roomId);
	this->setName(anotherRoom.name);
	this->setType(anotherRoom.isVIP);
	this->setNumberOfSeats(anotherRoom.numberOfSeats);
	this->setSeats(anotherRoom.seats);
	this->setNumberOfRows(anotherRoom.numberOfRows);
	TOTAL_ROOMS++;
}

Room::Room(const char* name, bool isVIP, unsigned int n) {
	this->setRoomId(TOTAL_ROOMS);
	this->setName(name);
	this->setType(isVIP);
	this->setNumberOfSeats(n);
	this->seats = Room::generateRoomOfSeats(n);
	TOTAL_ROOMS++;
}

Room::Room(unsigned int roomId, const char* name, bool isVIP, Seat** seats, unsigned int numberOfSeats, unsigned int numberOfRows) {
	this->setRoomId(roomId);
	this->setName(name);
	this->setType(isVIP);
	this->setNumberOfSeats(numberOfSeats);
	this->setSeats(seats);
	this->setNumberOfRows(numberOfRows);
	TOTAL_ROOMS++;
}

Room::Room() {
	this->setRoomId(++TOTAL_ROOMS);
}

Room::~Room() {
	delete[] name;
	for (size_t i = 0; i < this->numberOfSeats; ++i)
		delete seats[i];
	delete[] seats;
}

// cast operator

Room::operator std::string() {
	std::stringstream ss;
	std::string isVIP = this->isVIP ? "VIP" : "not VIP";
	ss << "Room #" << roomId << " named \"" << name << "\"" << " is " << isVIP << ", has "
		<< numberOfRows << " rows and " << numberOfSeats << " seats:" << std::endl;
	for (size_t i = 0; i < numberOfSeats; ++i)
		ss << (std::string) * (this->seats[i]) << std::endl;
	return ss.str();
}

// stream operators

std::ostream& operator << (std::ostream& out, const Room& room) {
	out << "R" << room.roomId << "-" << room.name << "-" << room.isVIP << "-" << room.numberOfRows << "-" << room.numberOfSeats << ":";
	for (size_t i = 0; i < room.numberOfSeats; ++i)
		out << *(room.seats[i]);
	return out;
}

std::istream& operator >> (std::istream& in, Room& room) {
	// inspired from https://stackoverflow.com/questions/22290891/reading-in-file-with-delimiter
	std::string roomId;
	std::string name;
	std::string isVIP;
	std::string numberOfSeats;
	std::string numberOfRows;
	if (std::getline(in, roomId, 'R') &&
		std::getline(in, roomId, '-') &&
		std::getline(in, name, '-') &&
		std::getline(in, isVIP, '-') &&
		std::getline(in, numberOfRows, '-') &&
		std::getline(in, numberOfSeats, ':')) {
			room.setRoomId(std::stoi(roomId));
			/*room.name = new char[name.length() + 1];
			strcpy_s(room.name, name.length() + 1, name.c_str());*/
			room.setName(name.c_str());
			room.setType(std::stoi(isVIP));
			room.setNumberOfSeats(std::stoi(numberOfSeats));
			room.setNumberOfRows(std::stoi(numberOfRows));
	}
	room.seats = new Seat * [room.numberOfSeats];
	for (size_t i = 0; i < room.numberOfSeats; ++i) {
		room.seats[i] = new Seat();
		in >> *(room.seats[i]);
	}
	return in;
}