#ifndef SOLAIRE_LIST_HPP
#define SOLAIRE_LIST_HPP

//Copyright 2016 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "solaire/core/deque.hpp"

namespace solaire {
	template<class T>
	class list : public deque<T> {
	protected:
		virtual bool SOLAIRE_INTERFACE_CALL _insert(const uint32_t, const T&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _erase(const uint32_t) throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~list() {

		}

		inline T& insert_before(const uint32_t aIndex, const T& aValue) {
			runtime_assert(_insert(aIndex, aValue), "P12218319::stack::insert_before : Failed to insert item");
			return container<T>::operator[](aIndex);
		}

		inline T& insert_after(const uint32_t aIndex, const T& aValue) {
			return insert_before(aIndex + 1, aValue);
		}

		inline T erase(const uint32_t aIndex) {
			T tmp = container<T>::operator[](aIndex);
			runtime_assert(_erase(aIndex), "P12218319::list::erase : Failed to erase item");
			return tmp;
		}
	};
}

#endif