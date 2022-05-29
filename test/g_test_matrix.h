
#pragma once
#include <tuple>
#include <map>

template<typename T, T default_value>
class Matrix_Test {
	using storage = std::map<std::tuple<std::size_t, std::size_t>, T>;

	class Element {
	public:
		Element(storage& data, std::size_t row, std::size_t col) :
			_data(data), _row(row), _col(col) {};
		operator T() {
			if (_data.count({ _row, _col })) {
				return _data[{_row, _col}];
			}
			else {
				return default_value;
			}
		}
		operator const T() const {
			if (_data.count({ _row, _col })) {
				return _data[{_row, _col}];
			}
			else {
				return default_value;
			}
		}
		Element& operator=(T element) {
			if (element != default_value)
				_data[{_row, _col}] = element;
			else
				_data.erase({ _row,_col });
			return *this;
		};
	private:
		std::size_t _row, _col;
		storage& _data;
	};

	class Row {
	public:
		Row(storage& data, std::size_t row) : _data(data), _row(row) {};
		Element operator[](std::size_t columnindex) {
			return Element(_data, _row, columnindex);
		};
	private:
		std::size_t _row;
		storage& _data;
	};

public:
	class iterator : public std::iterator<std::forward_iterator_tag, T> {
	public:
		iterator(typename storage::iterator iter)
			: it(iter) {};
		bool operator==(iterator& rhs) {
			return it == rhs.it;
		}
		bool operator!=(iterator& rhs) {
			return it != rhs.it;
		}
		iterator& operator--() {
			--it;
			return *this;
		}
		iterator& operator++() {
			++it;
			return *this;
		}
		std::tuple<std::size_t, std::size_t, T> operator*() {
			return {
				std::get<0>(it->first),
				std::get<1>(it->first),
				it->second };
		}
	protected:
		typename storage::iterator it;
	};

	std::size_t size() {
		return _data.size();
	};
	Row operator[](std::size_t index) {
		return Row(_data, index);
	};
	Matrix_Test::iterator begin() {
		return _data.begin();
	};
	Matrix_Test::iterator end() {
		return _data.end();
	};
private:
	storage _data;
};
