#ifndef SOLAIRE_CONTAINER_HPP
#define SOLAIRE_CONTAINER_HPP

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

#include "solaire/core/interfaces/container.hpp"

namespace solaire {
	template<class T>
	SOLAIRE_EXPORT_CLASS container {
	public:
		virtual interfaces::container<T>& SOLAIRE_INTERFACE_CALL get_container() throw() = 0;
		virtual const interfaces::container<T>& SOLAIRE_INTERFACE_CALL get_const_container() const throw() = 0;

		virtual SOLAIRE_INTERFACE_CALL ~container() {

		}

		inline bool empty() const throw() {
			return get_const_container().size() == 0;
		}

		inline uint32_t size() const throw() {
			return get_const_container().size();
		}

		inline bool is_contiguous() const throw() {
			return get_const_container().is_contiguous();
		}

		inline iterator<T> begin() throw() {
			return get_container().get_begin_iterator();
		}

		inline iterator<const T> begin() const throw() {
			return const_cast<interfaces::container<T>&>(get_const_container()).get_begin_iterator();
		}

		inline iterator<T> end() throw() {
			return get_container().get_end_iterator();
		}

		inline iterator<const T> end() const throw() {
			return const_cast<interfaces::container<T>&>(get_const_container()).get_end_iterator();
		}

		T& operator[](const uint32_t aIndex) {
			T* const tmp = get_container().get(aIndex);
			if(tmp == nullptr) throw std::runtime_error("P12218319::container::operator[] : Failed to get item");
			return *tmp;
		}

		const T& operator[](const uint32_t aIndex) const {
			T* const tmp = const_cast<interfaces::container<T>&>(get_const_container()).get(aIndex);
			if(tmp == nullptr) throw std::runtime_error("P12218319::container::operator[] : Failed to get item");
			return *tmp;
		}

		inline T& front() {
			return operator[](0);
		}

		inline const T& front() const {
			return operator[](0);
		}

		inline T& back() {
			return operator[](size() - 1);
		}

		inline const T& back() const {
			return operator[](size() - 1);
		}

		inline bool operator==(const container<T>& aOther) const throw() {
			if(size() != aOther.size()) return false;
			const iterator<const T> end = end();
			iterator<const T> j = aOther.begin();
			for(iterator<const T> i = begin(); i != end; ++i, ++j) {
				if(*i != *j) return false;
			}
			return true;
		}

		inline bool operator!=(const container<T>& aOther) const throw() {
			return ! operator==(aOther);
		}

		template<class F>
		inline iterator<T> find_first(const F aFunctor) {
			return find_next<F>(begin(), aFunctor);
		}

		template<class F>
		iterator<T> find_next(iterator<T> aIndex, const F aFunctor) {
			const iterator<T> end = end();
			for(aIndex; aIndex != end; ++aIndex) if(aFunctor(*aIndex)) return aIndex;
			return end;
		}

		template<class F>
		iterator<T> find_last(const F aFunctor) {
			const iterator<T> end = end();
			iterator<T> i = find_first<F>(aFunctor);
			iterator<T> j = i;
			while(i != end) {
				j = i;
				i = find_next<F>(aFunctor);
			}
			return j;
		}

		template<class F>
		inline iterator<const T> find_first(const F aFunctor) const {
			return find_next<F>(begin(), aFunctor);
		}

		template<class F>
		iterator<const T> find_next(iterator<const T> aIndex, const F aFunctor) const {
			const iterator<const T> end = end();
			for(aIndex; aIndex != end; ++aIndex) if(aFunctor(*aIndex)) return aIndex;
			return end;
		}

		template<class F>
		iterator<const T> find_last(const F aFunctor) const {
			const iterator<const T> end = end();
			iterator<const T> i = find_first<F>(aFunctor);
			iterator<const T> j = i;
			while(i != end) {
				j = i;
				i = find_next<F>(aFunctor);
			}
			return j;
		}
	};

	template<class CONTAINER>
	class value_container : public container<typename CONTAINER::type> {
	private:
		CONTAINER mContainer;
	public:
		template<class ...PARAMS>
		value_container(PARAMS... aParams) :
			mContainer(aParams...)
		{}

		virtual SOLAIRE_INTERFACE_CALL ~value_container() {

		}

		// inherited from container
		interfaces::container<typename CONTAINER::type>& SOLAIRE_INTERFACE_CALL get_container() throw() override {
			return mContainer;
		}

		const interfaces::container<typename CONTAINER::type>& SOLAIRE_INTERFACE_CALL get_const_container() const throw() override {
			return mContainer;
		}
	};
}

#endif