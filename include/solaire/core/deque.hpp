#ifndef SOLAIRE_DEQUE_HPP
#define SOLAIRE_DEQUE_HPP

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

#include "solaire/core/stack.hpp"

namespace solaire {
	template<class T>
	class deque : public stack<T> {
	protected:
		virtual bool SOLAIRE_INTERFACE_CALL _push_front(T&&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _pop_front() throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~deque() {

		}

		inline void push_front(T&& aValue) {
			runtime_assert(_push_front(std::move(aValue)), "P12218319::deque::push_front : Failed to push item");
		}

		inline void push_front(const T& aValue) {
			T tmp = aValue;
			runtime_assert(_push_front(std::move(tmp)), "P12218319::deque::push_front : Failed to push item");
		}

		inline T pop_front() {
			T tmp = container<T>::front();
			runtime_assert(_pop_front(), "P12218319::deque::pop_front : Failed to pop item");
			return tmp;
		}

		inline void push_front(const container<T>& aOther) {
			if (&aOther == this) throw std::runtime_error("P12218319::deque::push_front : Cannot push self");
			const uint32_t s = size();
			reserve(s + aOther.size());
			single_for<const container<T>&>(aOther, 0, s, [this](const T& aValue)->void {
				push_front(aValue);
			});
		}
	};
}

#endif