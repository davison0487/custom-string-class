// String.cpp

#include "String.hpp"

using namespace ECE141;

/* ----- ECE141::BufferManger -----*/
BufferManager::BufferManager(size_t presize) {
	buffer = new char[presize]();
	bufSize = presize;
};

BufferManager::BufferManager(const	BufferManager& newBuf) {
	this->buffer = new char[newBuf.bufSize]();
	this->bufSize = newBuf.bufSize;
	this->append(newBuf.buffer);
};

BufferManager& BufferManager::operator=(const BufferManager& newBuf) {
	delete[] this->buffer;
	this->buffer = new char[newBuf.bufSize]();
	this->bufSize = newBuf.bufSize;
	this->append(newBuf.buffer);

	return *this;
};

BufferManager::~BufferManager() {
	delete[] buffer;
};

void BufferManager::resize(size_t newSize) {
	char* temp = new char[newSize + 16]();

	for (size_t i = 0; i < std::strlen(buffer); ++i)
		temp[i] = buffer[i];

	delete[] buffer;
	buffer = temp;
	temp = nullptr;
	bufSize = newSize + 16;
}

void BufferManager::append(const char* aBuf) {
	size_t oldSize = std::strlen(this->buffer);

	if (std::strlen(this->buffer) + std::strlen(aBuf) + 1 > this->bufSize)
		this->resize(std::strlen(this->buffer) + std::strlen(aBuf) + 1);

	for (size_t i = 0; i < std::strlen(aBuf); ++i)
		this->buffer[i + oldSize] = aBuf[i];
};

void BufferManager::append(const char ch) {
	if (std::strlen(buffer) + 2 > bufSize)
		resize(std::strlen(buffer) + 2);
	buffer[std::strlen(buffer)] = ch;
};

void BufferManager::edit(size_t pos, const char newChar) {
	buffer[pos] = newChar;
};

void BufferManager::remove(size_t pos, size_t len) {
	size_t oldSize = std::strlen(this->buffer);

	for (size_t i = pos; i < oldSize - len; ++i)
		buffer[i] = buffer[i + len];

	for (size_t i = oldSize - len; i < bufSize; ++i)
		buffer[i] = 0;

	resize(std::strlen(buffer));
};

void BufferManager::show() {
	std::cout << "string: \t" << this->buffer << std::endl;
	std::cout << "string length: \t" << std::strlen(buffer) << std::endl;
	std::cout << "bufSize: \t" << bufSize << std::endl;
}

/* ----- ECE141::String -----*/
String::String(const String& aString, size_t aPresize) {
	if (aPresize == 0)
		BufferManager();
	else {
		BufferManager(aPresize);
		this->append(aString.buffer);
	}
};

String::String(const char* aBuffer, size_t aPresize) {
	if (aPresize == 0)
		BufferManager();
	else {
		BufferManager(aPresize);
		append(aBuffer);
	}
};

String::~String() {
	//delete[] buffer;
};

String& String::operator=(const String& aCopy) {
	delete[] this->buffer;
	this->bufSize = aCopy.bufSize;
	this->buffer = new char[this->bufSize]();
	this->append(aCopy.buffer);
	return *this;
};

String& String::operator=(const char* aBuffer) {
	delete[] this->buffer;
	this->bufSize = std::strlen(aBuffer)+16;
	this->buffer = new char[this->bufSize]();
	this->append(aBuffer);
	return *this;
};

size_t String::size() const {
	return std::strlen(buffer);
};

char& String::operator[](int pos) {
	return buffer[pos];
};

String  String::operator+(const String& aString) {
	String res(buffer);
	res.append(aString.buffer);
	return res;
};

String  String::operator+(const char* aBuffer) {
	String res(buffer);
	res.append(aBuffer);
	return res;
};

String& String::operator+=(const String& aString) {
	this->append(aString.buffer);
	return *this;
};

String& String::operator+=(const char* aBuffer) {
	this->append(aBuffer);
	return *this;
};

String& String::insert(size_t anIndex, const String& aString, size_t aMaxCopyLen) {
	char* suffix = new char[this->bufSize]();
	for (size_t i = anIndex; i < std::strlen(this->buffer); ++i) {
		suffix[i - anIndex] = this->buffer[i];
		this->buffer[i] = 0;
	}

	char* inString = new char[std::strlen(aString.buffer)+1]();
	if (aMaxCopyLen == 0)
		aMaxCopyLen = std::strlen(aString.buffer);
	for (size_t i = 0; i < aMaxCopyLen; ++i)
		inString[i] = aString.buffer[i];

	this->append(inString);
	this->append(suffix);
	return *this;
};

String& String::insert(size_t anIndex, const char* aString, size_t aMaxCopyLen) {
	char* newstr = new char[this->bufSize + strlen(aString) + 16]();

	for (size_t i = 0; i < anIndex; ++i)
		newstr[i] = this->buffer[i];

	if (aMaxCopyLen == 0)
		aMaxCopyLen = std::strlen(aString);
	for (size_t i = anIndex; i < anIndex + aMaxCopyLen; ++i)
		newstr[i] = aString[i - anIndex];

	for (size_t i = anIndex + aMaxCopyLen; i < std::strlen(this->buffer) + aMaxCopyLen; ++i)
		newstr[i] = this->buffer[i - aMaxCopyLen];

	delete[] this->buffer;
	this->buffer = newstr;
	newstr = nullptr;
	this->bufSize = this->bufSize + std::strlen(aString) + 16;
	return *this;
};

String& String::replace(size_t anIndex, size_t aMaxCopyLen, const String& aSubString) {
	if (aMaxCopyLen == 0)
		this->insert(anIndex, aSubString, 0);
	else {
		this->erase(anIndex, aMaxCopyLen);
		this->insert(anIndex, aSubString, 0);
	}

	return *this;
};

String& String::replace(size_t anIndex, size_t aMaxCopyLen, const char* aSubString) {
	if (aMaxCopyLen == 0)
		this->insert(anIndex, aSubString,0);
	else {
		this->erase(anIndex, aMaxCopyLen);
		this->insert(anIndex, aSubString, 0);
	}

	return *this;
};

String& String::erase(size_t anIndex, size_t aCount) {
	this->remove(anIndex, aCount);
	return *this;
};

int String::compare(const String& aString) const {
	size_t maxlen = std::min(std::strlen(this->buffer), std::strlen(aString.buffer));

	for (size_t i = 0; i < maxlen; ++i) {
		if (this->buffer[i] < aString.buffer[i])
			return -1;
		else if (this->buffer[i] > aString.buffer[i])
			return 1;
	}
	return 0;
};

bool String::operator==(const String& aString) const {
	if (std::strlen(this->buffer) != std::strlen(aString.buffer))
		return false;
	for (size_t i = 0; i < std::strlen(this->buffer); ++i) {
		if (this->buffer[i] != aString.buffer[i])
			return false;
	}
	return true;
};

bool String::operator==(const char* aBuffer) const {
	if (std::strlen(this->buffer) != std::strlen(buffer))
		return false;
	for (size_t i = 0; i < std::strlen(this->buffer); ++i) {
		if (this->buffer[i] != buffer[i])
			return false;
	}
	return true;
};

bool String::operator<(const String& aString) const {
	size_t maxlen = std::min(std::strlen(this->buffer), std::strlen(aString.buffer));

	for (size_t i = 0; i < maxlen; ++i) {
		if (this->buffer[i] < aString.buffer[i])
			return true;
	}
	return false;
};

bool String::operator<(const char* aBuffer) const {
	size_t maxlen = std::min(std::strlen(this->buffer), std::strlen(aBuffer));

	for (size_t i = 0; i < maxlen; ++i) {
		if (this->buffer[i] < aBuffer[i])
			return true;
	}
	return false;
};

int String::find(const String& aSubString, size_t anOffset) const {
	size_t i = 0, pos = anOffset;
	std::queue<int> q;

	while (pos < std::strlen(this->buffer)) {
		if (i != 0 && this->buffer[pos] == aSubString.buffer[0])
			q.push(pos);

		if (this->buffer[pos] == aSubString.buffer[i]) {
			++pos;
			++i;
			if (i == std::strlen(aSubString.buffer))
				return pos - i;
		}
		else {
			i = 0;
			if (!q.empty()) {
				pos = q.front();
				q.pop();
			}
			else
				++pos;
		}
	}

	return -1;
};

std::ostream& ECE141::operator<< (std::ostream& out, const String& aStr) {
	for (size_t i = 0; i < std::strlen(aStr.buffer); ++i)
		out << aStr.buffer[i];
	return out;
};

std::istream& ECE141::operator>> (std::istream& in, String& aString) {
	while (in) {
		char cur = in.get();
		aString.append(cur);
	}
	return in;
};
