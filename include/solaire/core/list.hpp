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
	public:
		virtual SOLAIRE_INTERFACE_CALL ~list() {

		}

		virtual interfaces::list<T>& SOLAIRE_INTERFACE_CALL get_list() throw() = 0;
		virtual const interfaces::list<T>& SOLAIRE_INTERFACE_CALL get_list() const throw() = 0;

		inline T& insert_before(const uint32_t aIndex, const T& avalue_) {
			if(! get_list().insert(aIndex, avalue_)) throw std::runtime_error("P12218319::stack::insert_before : Failed to insert item");
			return container<T>::operator[](aIndex);
		}

		inline T& insert_after(const uint32_t aIndex, const T& avalue_) {
			return insert_before(aIndex + 1, avalue_);
		}

		inline T erase(const uint32_t aIndex) {
			T tmp = container<T>::operator[](aIndex);
			if(! get_list().erase(aIndex)) throw std::runtime_error("P12218319::list::erase : Failed to erase item");
			return tmp;
		}

		// Inherited from deque
		interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_deque() throw() override {
		    return get_list();
		}

		const interfaces::deque<T>& SOLAIRE_INTERFACE_CALL get_const_deque() const throw() override {
		    return get_list();
		}
	};

	template<class T, class CONTAINER>
	class value_list : public list<T> {
	private:
		CONTAINER mContainer;
	public:
		template<class ...PARAMS>
		value_list(PARAMS... aParams) :
			mContainer(aParams...)
		{}

		virtual SOLAIRE_INTERFACE_CALL ~value_list() {

		}

		// inherited from deque
		interfaces::list<T>& SOLAIRE_INTERFACE_CALL get_list() throw() override {
			return mContainer;
		}

		const interfaces::list<T>& SOLAIRE_INTERFACE_CALL get_const_list() const throw() override {
			return mContainer;
		}
	};
}

#endif