#ifndef SOLAIRE_STACK_HPP
#define SOLAIRE_STACK_HPP

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

#include "solaire/core/container.hpp"

namespace solaire {
	template<class T>
	class stack : public container<T> {
	protected:
		virtual bool SOLAIRE_INTERFACE_CALL _push_back(T&&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _pop_back() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _clear() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _reserve(const uint32_t) throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~stack() {

		}

		inline void push_back(T&& aValue) {
			runtime_assert(_push_back(std::move(aValue)), "P12218319::stack::push_back : Failed to push item");
		}

		inline void push_back(const T& aValue) {
			T tmp = aValue;
			runtime_assert(_push_back(std::move(tmp)), "P12218319::stack::push_back : Failed to push item");
		}

		inline T pop_back() {
			T tmp = container<T>::back();
			runtime_assert(_pop_back(), "P12218319::stack::pop_back : Failed to pop item");
			return tmp;
		}

		inline void push_back(const container<T>& aOther) {
			if(&aOther == this) throw std::runtime_error("P12218319::stack::push_back : Cannot push self");
			const uint32_t s = size();
			reserve(s + aOther.size());
			single_for<const container<T>&>(aOther, 0, s, [this](const T& aValue)->void {
				push_back(aValue);
			});
		}

		inline void clear(){
			runtime_assert(_clear(), "P12218319::stack::clear : Failed to clear");
		}

		inline void reserve(const uint32_t aSize) {
			runtime_assert(_reserve(aSize), "P12218319::stack::reserve : Failed to reserve");
		}

		stack<T>& operator=(container<T>&& aOther) {
			clear();
			push_back(aOther);
			return *this;
		}

		stack& operator=(const container<T>& aOther) {
			clear();
			push_back(aOther);
			return *this;
		}
	};
}

#endif