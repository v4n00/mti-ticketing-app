#pragma once
#include <string>

class Entity {
protected:
	unsigned int id = 0;
	char* name = nullptr;

	void setId(unsigned int id);
	void setName(const char* name);
public:
	int getId() const;
	char* getName() const;

	virtual explicit operator std::string() = 0;

	template<typename T>
	static T* deepCopy(const T* arr, unsigned int size);
};