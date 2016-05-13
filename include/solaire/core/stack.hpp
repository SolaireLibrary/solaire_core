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
	public:
		virtual SOLAIRE_INTERFACE_CALL ~stack() {

		}

		virtual interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_stack() throw() = 0;
		virtual const interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_const_stack() const throw() = 0;

		inline T& push_back(const T& avalue_) {
			if(! get_stack().push_back(avalue_)) throw std::runtime_error("P12218319::stack::push_back : Failed to push item");
			return container<T>::back();
		}

		inline T pop_back() {
			T tmp = container<T>::back();
			if(! get_stack().pop_back()) throw std::runtime_error("P12218319::stack::pop_back : Failed to pop item");
			return tmp;
		}

		inline void push_back(const container<T>& aOther) {
			const iterator<const T> end = aOther.end();
			for(iterator<const T> i = aOther.begin(); i != end; ++i) push_back(*i);
		}

		inline void clear() throw() {
		    get_stack().clear();
		}

		// Inherited from container
		interfaces::container<T>& SOLAIRE_INTERFACE_CALL get_container() throw() override {
		    return get_stack();
		}

		const interfaces::container<T>& SOLAIRE_INTERFACE_CALL get_const_container() const throw() override {
		    return get_stack();
		}
	};

	template<class T, class CONTAINER>
	class value_stack : public stack<T> {
	private:
		CONTAINER mContainer;
	public:
		template<class ...PARAMS>
		value_stack(PARAMS... aParams) :
			mContainer(aParams...)
		{}

		virtual SOLAIRE_INTERFACE_CALL ~value_stack() {

		}

		// inherited from stack
		interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_stack() throw() override {
			return mContainer;
		}

		const interfaces::stack<T>& SOLAIRE_INTERFACE_CALL get_const_stack() const throw() override {
			return mContainer;
		}
	};
}

#endif