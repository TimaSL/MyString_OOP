#include <iostream>
#include <string>

class MyString {
public:
	MyString() {
		str_ = nullptr;
		len_ = 0;
		capacity_ = 0;
	}

	MyString(const char* other) : len_(strlen_my(other)) {
		if (len_ == 0)
			capacity_ = 0;
		else
		capacity_ = len_ + 1;
		ToNewString(other);
	}

	MyString(std::string other) {
		len_ = std::size(other);
		ToNewString(other.c_str());
	}

	MyString(const char* other, int count) {
		len_ = count;
		ToNewString(other);
	}

	MyString(int count, char symb) {
		MyString();
		append(count, symb);
	}

	MyString(const MyString& other) {
		len_ = other.len_;
		ToNewString(other.str_);
	}

	~MyString() {
		delete[] str_;
	}

	MyString operator +(const MyString& other) {
		return plus(other.str_);
	}

	MyString& operator +=(const MyString& other) {
		return append(other.str_);
	}

	MyString& operator +=(const char* other) {
		return append(other);
	}

	MyString operator =(const MyString other) {
		clear();
		append(other.str_);
		return *this;
	}

	MyString& operator =(const char* other) {
		clear();
		append(other);
		return *this;
	}

	MyString& operator =(const char symb) {
		clear();
		append(&symb);
		return *this;
	}

	MyString operator [](int index) {
		MyString result;
		result.str_ = new char[2];
		result.len_ = 1;
		result.str_[0] = str_[index];
		result.str_[1] = '\0';
		return result;
	}

	bool operator >(const MyString& right) { return compare(right) > 0; }
	
	bool operator <(const MyString& right) { return compare(right) < 0; }

	bool operator >=(const MyString& right) { return compare(right) >= 0; }

	bool operator <=(const MyString& right) { return compare(right) <= 0; }

	bool operator ==(const MyString& right) { return compare(right) == 0;}

	bool operator !=(const MyString& right) { return compare(right) != 0;}

	char* c_str() { return str_;}
	
	char* data() { return str_;}

	int length() { return size();}

	int size() {
		if (str_ == nullptr)
			return 0;
		else
		int len = 0;
		while (str_[len_] != '\0') ++len_;
		return len_;
	}

	bool empty(){
		if (len_ == 0) return 1;
		return 0;
	}

	int capacity() {
		return capacity_;
	}

	MyString& shrink_to_fit() {
		int len = strlen_my(this->str_);
		char* str = new char[len + 1];
		for (int i = 0; i < len; ++i) {
			str[i] = this->str_[i];
		}
		str[len] = '\0';
		delete[] this->str_;
		this->str_ = new char[len + 1];
		for (int i = 0; i < len; ++i) {
			this->str_[i] = str[i];
		}
		this->str_[len] = '\0';
		this->len_ = len;
		delete[] str;
		return *this;
	}

	MyString& erase(int index, int count) {
		if (index > len_) return *this;

		if (index + count >= len_) {
			this->str_[index] = '\0';
			return *this;
		}
		int j = index;
		for (int i = index + count; this->str_[i] != '\0'; ++j, ++i) {
			this->str_[j] = this->str_[i];
		}
		this->str_[j] = '\0';	
		return *this;
	}

	MyString& clear() {
		if(str_!=NULL)
		if (strcmp(str_, "\0")) delete[] str_;
		str_ = new char[capacity_];
		str_[0] = 0x00;
		len_ = 0;
		return *this;
	}

	MyString& insert(int index, int count, char symb) {
		char* str_tmp = new char[count+1];
		for (int i = 0; i < count; ++i)
		{
			str_tmp[i] = symb;
		}
		return insert_my(index, str_tmp, count);
	}

	MyString& insert(int index, const char* other) {
		int lenstr = strlen_my(other);
		return insert_my(index, other, lenstr);
	}

	MyString& insert(int index, const char* other, int count) {
		int lenstr = strlen_my(other);
		if (count > lenstr) count = lenstr;
		return insert_my(index, other, count);
	}

	MyString& insert(int index, std::string other) {	
		return insert_my(index, other.c_str(), other.length());
	}

	MyString& insert(int index, std::string other, int count) {
		int lenstr = std::size(other);
		if (count > lenstr) count = lenstr;
		return insert_my(index, other.c_str(), count);
	}

	MyString& append(int count, char symb) {
		char* str = new char[count + 1];
		int i;
		for (i = 0; i < count; ++i)
			str[i] = symb;
		str[i] = '\0';

		return append_my(str,0,count);
	}

	MyString& append(const char* other) {
		return append_my(other, 0, strlen_my(other));
	}

	MyString& append(const char* other, int index, int count) {
		int lenstr = strlen_my(other);
		if (index > lenstr) return *this;
		if (index + count > lenstr) count = lenstr - index;
		return append_my(other, index, count);
	}

	MyString& append(std::string other) {
		return append_my(other.c_str(), 0, strlen_my(other.c_str()));
	}

	MyString& append(std::string other, int index, int count) {
		int lenstr = std::size(other);
		if (index > lenstr) return *this;
		if (index + count > lenstr) count = lenstr - index;
		return append_my(other.c_str(), index, count);
	}

	MyString& replace(int index, int count, const char* other) {

		return replace_my(index, count, other);
	}

	MyString& replace(int index, int count, std::string other) {
		return replace_my(index, count, other.c_str());
	}

	MyString substr(int index) {
		if (index > len_) index = len_;
		if (index < 0) return *this;	
		MyString result;

		result.str_ = new char[len_ - index+1];
		result.capacity_ = len_ - index+1;
		
		strncpy_my(result.str_,this->str_+index,len_-index);
		result.len_ = len_ - index;
		return result;
	}

	MyString substr(int index, int count) {
		MyString newStr;
		if (index > len_) index = len_;
		if (index < 0) return *this;
		if (count > len_ - index) count = len_ - index;
		if (count < 0) return *this;
		MyString result;

		result.str_ = new char[count];
		result.capacity_ = count+ 1;

		strncpy_my(result.str_, this->str_ + index, count);
		result.len_ = count;
		return result;

	}

	int find(const char* other) {
		return find_my(other, 0);
	}

	int find(const char* other, int index) {
		return find_my(other, index);
	}

	int find(std::string other) {
		return find_my(other.c_str(), 0);
	}

	int find(std::string other, int index) {
		return find_my(other.c_str(), index);
	}

private:
	char* str_;
	int len_;
	int capacity_;
	friend std::ostream& operator <<(std::ostream& out, const MyString& str);
	friend std::istream& operator >>(std::istream& in, MyString& str);

	int strlen_my(const char* other) {
		const char* s;

		for (s = other; *s; ++s)
			;
		return (s - other);
	}

	int compare(const MyString& str2) {
		if (this == &str2) return 0;
		unsigned i = 0;
		while (str_[i] && str_[i] == str2.str_[i]) ++i;
		return str_[i] - str2.str_[i];
	}

	void strncpy_my(char dest[], const char source[], int count) {
		int i = 0;
		while (i<count)
		{
			dest[i] = source[i];
			if (dest[i] == '\0')
			{
				break;
			}
			++i;
		}
		dest[i] = '\0';
	}

	void capacityCheck(int valueLen) {
		
		if ((valueLen > capacity_-1)&&(valueLen!=0))
			capacity_ = valueLen+1;
	}

	void ToNewString(const char* other) {
		this->str_ = new char[len_ + 1];
		for (int i = 0; i < len_; i++) {
			this->str_[i] = other[i];
		}
		this->str_[len_] = '\0';
		capacityCheck(len_);
	}

	MyString plus(const char* other) {
		MyString newStr;
		newStr.append(this->str_);
		newStr.append(other);
		return newStr;
	}

	MyString& insert_my(int index, const char* other, int count) {
		int len_sum = len_ + count;
		char* newStr = new char[len_sum + 1];
		for (int i = 0, k = 0; k < len_sum; ++i, ++k) {
			if (i == index) {
				int j = i;
				for (int h = 0; h < count; ++j, ++h) {
					newStr[j] = other[h];
				}
				k = j - 1;
				--i;
				index = -100;
			}
			else {
				newStr[k] = this->str_[i];
			}
		}
		this->clear();
		len_ = len_sum;
		this->str_ = new char[len_ + 1];
		for (int i = 0; i < len_; ++i) {
			this->str_[i] = newStr[i];
		}
		this->str_[len_] = '\0';
		delete[] newStr;
		capacityCheck(len_);
		return *this;
	}

	MyString& append_my(const char* other, int index, int count) {
		return insert(this->len_, other, count);
	}

	MyString& replace_my(int index, int count, const char* other) {
		int len = strlen_my(other);
		if (index > this->len_) return *this;
		if (count > this->len_ - index) count = this->len_ - index;
		if (count < 0) count = 0;
		int lenstr = this->len_ - count + len;
		char* newStr = new char[lenstr];
		for (int i = 0; i < index; ++i) {
			newStr[i] = this->str_[i];
		}
		for (int i = index, j = 0; i < len + index; ++i, ++j) {
			newStr[i] = other[j];
		}
		for (int i = index + len, j = index + count; i < lenstr; ++i, ++j) {
			newStr[i] = this->str_[j];
		}
		delete[] this->str_;
		this->str_ = new char[lenstr + 1];
		for (int i = 0; i < lenstr; ++i) {
			this->str_[i] = newStr[i];
		}
		this->str_[lenstr] = '\0';
		delete[] newStr;
		capacityCheck(lenstr);
		return *this;
	}

	int find_my(const char* other, int index) {
		if (index > this->len_ || index < 0) return -1;
		int len = strlen_my(other);
		for (int i = index; i < this->len_; ++i) {
			int j = 0;
			for (int k = i; j < len; ++j, ++k) {
				if (other[j] != this->str_[k]) break;
				if (j == len - 1) return i;
			}
		}
		return -1;
	}
};

std::ostream& operator <<(std::ostream& out, const MyString& other) {
	if (other.str_ != 0) out << other.str_;
	return out;
}

std::istream& operator >> (std::istream& in, MyString& a)
{
	std::string s;
	in >> s;
	a.append(s);
	return in;
}
