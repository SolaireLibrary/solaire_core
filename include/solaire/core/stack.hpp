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
		virtual bool SOLAIRE_INTERFACE_CALL _push_back(const T&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _pop_back() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL _clear() throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~stack() {

		}

		virtual bool SOLAIRE_INTERFACE_CALL can_invalidate() const throw() = 0;

		inline T& push_back(const T& avalue_) {
			runtime_assert(_push_back(avalue_), "P12218319::stack::push_back : Failed to push item");
			return container<T>::back();
		}

		inline T pop_back() {
			T tmp = container<T>::back();
			runtime_assert(_pop_back(), "P12218319::stack::pop_back : Failed to pop item");
			return tmp;
		}

		inline void push_back(const container<T>& aOther) {
			const iterator<const T> end = aOther.end();
			for(iterator<const T> i = aOther.begin(); i != end; ++i) push_back(*i);
		}

		inline void clear() throw() {
			runtime_assert(_clear(), "P12218319::stack::clear : Failed to clear");
		}
	};
}

#endif