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
	public:
		virtual SOLAIRE_INTERFACE_CALL ~deque() {

		}

		virtual interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_deque() throw() = 0;
		virtual const interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_const_deque() const throw() = 0;

		inline T& push_front(const T& avalue_) {
			if(! get_deque().push_front(avalue_)) throw std::runtime_error("P12218319::deque::push_front : Failed to push item");
			return container<T>::front();
		}

		inline T pop_front() {
			T tmp = container<T>::front();
			if(! get_deque().pop_front()) throw std::runtime_error("P12218319::deque::pop_front : Failed to pop item");
			return tmp;
		}

		inline void push_front(const container<T>& aOther) {
			const iterator<const T> end = aOther.end();
			for(iterator<const T> i = aOther.begin(); i != end; ++i) push_front(*i);
		}

		// Inherited from stack
		interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_stack() throw() override {
		    return get_deque();
		}

		const interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_const_stack() const throw() override {
		    return get_deque();
		}
	};

	template<class T, class CONTAINER>
	class value_deque : public deque<T> {
	private:
		CONTAINER mContainer;
	public:
		template<class ...PARAMS>
		value_deque(PARAMS... aParams) :
			mContainer(aParams...)
		{}

		virtual SOLAIRE_INTERFACE_CALL ~value_deque() {

		}

		// inherited from deque
		interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_deque() throw() override {
			return mContainer;
		}

		const interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_const_deque() const throw() override {
			return mContainer;
		}
	};
}

#endif