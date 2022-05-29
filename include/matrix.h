#pragma once
#include <tuple>
#include <map>

/**
 * @brief класс Matrix 2-мерная разреженная матрица 
 * 
 * @tparam T - тип элементов по умолчанию в матрице 
 * @tparam default_value- значение элементов по умолчанию в матрице 
 */
template<typename T, T default_value>
class Matrix {
	using storage = std::map<std::tuple<std::size_t, std::size_t>, T>;
	/**
 	* @brief Класс Element отдельный элемент в матрице
 	* 
 	*/
	class Element {
	public:/**
	 * @brief Конструктор класса Element
	 * 
	 * @param data - значение элемента
	 * @param row индекс строки
	 * @param col индекс столбца
	 */
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
	/**
 	 * @brief Конструктор класса Row для размещения Element
	 * 
	 * @param data - значение элемента
	 * @param row индекс строки
	 */ 

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
/**
 * @brief Класс ононаправленного итератора для обхода значений в матрице
 * 
 */
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
		/**
		 * @brief Оператор декремента.
		 * 
		 * @return iterator& итератор для обращения к пердыдущему элементу
		 */
		iterator& operator--() {
			--it;
			return *this;
		}
		/**
		 * @brief Оператор инкремента.
		 * 
		 * @return iterator& итератор  для обращения к следующему элементу
		 */
		iterator& operator++() {
			++it;
			return *this;
		}
		/**
		 * @brief получение элемента tuple, на который указывает итератор 
		 */
		std::tuple<std::size_t, std::size_t, T> operator*() {
			return {
				std::get<0>(it->first),
				std::get<1>(it->first),
				it->second };
		}
	protected:
		typename storage::iterator it;
	};
	/**
	 * @brief Возращает количество элементов в матрице/размер матрицы.
	 */
	std::size_t size() {
		return _data.size();
	};
	Row operator[](std::size_t index) {
		return Row(_data, index);
	};
	/**
	 * @brief Извлекает итератор для первого элемента в указанной матрице.
	 */
	Matrix::iterator begin() {
		return _data.begin();
	};
	/**
	 * @brief Извлекает итератор для крайнего элемента в указанной матрице.
	 */
	
	Matrix::iterator end() {
		return _data.end();
	};
private:
	storage _data;
};
