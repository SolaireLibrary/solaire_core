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

#include "solaire/core/iterator.hpp"

namespace solaire {
	SOLAIRE_EXPORT_CLASS generic_container{
	public:
		virtual SOLAIRE_INTERFACE_CALL ~generic_container() {

		}

		virtual bool SOLAIRE_INTERFACE_CALL is_contiguous() const throw() = 0;
		virtual uint32_t SOLAIRE_INTERFACE_CALL size() const throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL can_invalidate() const throw() = 0;

		inline bool empty() const throw() {
			return size() == 0;
		}
	};


	template<class T>
	SOLAIRE_EXPORT_CLASS container : public generic_container{
	protected:
		virtual T* SOLAIRE_INTERFACE_CALL get(const uint32_t) throw() = 0;
		virtual solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_begin_iterator() throw() = 0;
		virtual solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_end_iterator() throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~container() {

		}

		inline iterator<T> begin() throw() {
			return get_begin_iterator();
		}

		inline iterator<const T> begin() const throw() {
			return get_begin_iterator();
		}

		inline iterator<T> end() throw() {
			return get_end_iterator();
		}

		inline iterator<const T> end() const throw() {
			return get_end_iterator();
		}

		T& operator[](const uint32_t aIndex) {
			T* const tmp = get(aIndex);
			if(tmp == nullptr) throw std::runtime_error("P12218319::container::operator[] : Failed to get item");
			return *tmp;
		}

		const T& operator[](const uint32_t aIndex) const {
			T* const tmp = const_cast<container<T>*>(this)->get(aIndex);
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

		template<class CONTAINER, const bool DIRECT = false>
		CONTAINER sub_set(const uint32_t aBegin, const uint32_t aItems) const {
			CONTAINER tmp;
			if(DIRECT) {
				if(is_contiguous()) {
					const T* const ptr = &operator[](0);
					if(tmp.is_contiguous()) {
						T* const ptr2 = &tmp[0];
						for(uint32_t i = aBegin; i < aBegin + aItems; ++i) ptr2[i] = ptr[i];
					}else {
						for (uint32_t i = aBegin; i < aBegin + aItems; ++i) tmp[i] = ptr[i];
					}
				}else {
					if(tmp.is_contiguous()) {
						T* const ptr2 = &tmp[0];
						for(uint32_t i = aBegin; i < aBegin + aItems; ++i) ptr2[i] = operator[](i);
					}else {
						for(uint32_t i = aBegin; i < aBegin + aItems; ++i) tmp[i] = operator[](i);
					}
				}
			}else {
				if(is_contiguous()) {
					const T* const ptr = &operator[](0);
					for(uint32_t i = aBegin; i < aBegin + aItems; ++i) tmp.push_back(ptr[i]);
				}else {
					for(uint32_t i = aBegin; i < aBegin + aItems; ++i) tmp.push_back(operator[](i));
				}
			}
		
			
			return tmp;
		}
	};
}

#endif