#ifndef SOLAIRE_ITERATOR_HPP
#define SOLAIRE_ITERATOR_HPP

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


#include "solaire/core/interfaces/iterator.hpp"

namespace solaire {

	//! \todo Call destructor on interfaces::iterator

	template<class T>
	class iterator {
	public:
		typedef T Type;
	private:
		uint8_t mImplementation[interfaces::MAX_INTERFACES_ITERATOR_SIZE];
		bool mCreated;
	private:
	    SOLAIRE_FORCE_INLINE interfaces::iterator<T>& getiterator() {
			if(! mCreated) throw std::runtime_error("P12218319::iterator::getiterator : Cannot dereference null interfaces::iterator");
			return *reinterpret_cast<interfaces::iterator<T>*>(mImplementation);
	    }

	    SOLAIRE_FORCE_INLINE const interfaces::iterator<T>& getiterator() const {
			if(! mCreated) throw std::runtime_error("P12218319::iterator::getiterator : Cannot dereference null interfaces::iterator");
			return *reinterpret_cast<const interfaces::iterator<T>*>(mImplementation);
	    }

		inline const T* dereference() const {
			const T* const tmp = getiterator().dereference();
			if(tmp == nullptr) throw std::runtime_error("P12218319::iterator::dereference : Out of bounds");
			return tmp;
		}

		inline void increment(const uint32_t aOffset) throw() {
			if(mCreated) {
				getiterator().increment(aOffset);
			}else {
				int32_t& offset = *reinterpret_cast<int32_t*>(mImplementation);
				offset += aOffset;
			}
		}

		inline void decrement(const uint32_t aOffset) throw() {
			if(mCreated) {
				getiterator().decrement(aOffset);
			}else {
				int32_t& offset = *reinterpret_cast<int32_t*>(mImplementation);
				offset -= aOffset;
			}
		}

		inline void copy(interfaces::iterator<T>* const aPointer) const {
			if(! mCreated) throw std::runtime_error("P12218319::iterator::copy : Cannot copy null interfaces::iterator");
			return getiterator().copy(aPointer);
		}

		inline int32_t get_offset() const {
			if(mCreated) {
				return getiterator().get_offset();
			}else {
				return *reinterpret_cast<const int32_t*>(mImplementation);
			}
		}
	public:

		iterator() :
			mCreated(false)
		{
			*reinterpret_cast<int32_t*>(mImplementation) = 0;
		}

		iterator(iterator<T>&& aOther) :
			mCreated(false)
		{
			if(aOther.mCreated) {
				aOther.copy(&getiterator());
				mCreated = true;
			}else {
				*reinterpret_cast<int32_t*>(mImplementation) = *reinterpret_cast<const int32_t*>(aOther.mImplementation);
				mCreated = false;
			}
		}

		iterator(const iterator<T>& aOther) :
			mCreated(false)
		{
			if(aOther.mCreated) {
				aOther.copy(&getiterator());
				mCreated = true;
			}else {
				*reinterpret_cast<int32_t*>(mImplementation) = *reinterpret_cast<const int32_t*>(aOther.mImplementation);
				mCreated = false;
			}
		}

		iterator(const interfaces::iterator<T>& aiterator) :
            mCreated(true)
        {
            aiterator.copy(&getiterator());
        }

		~iterator() {
			if(mCreated) getiterator().~interfaces::iterator();
		}

		inline iterator<T>& operator=(iterator<T>&& aOther) {
			interfaces::iterator<T>* const iterator = reinterpret_cast<interfaces::iterator<T>*>(mImplementation);
			if(mCreated) iterator->~interfaces::iterator();
			if(aOther.mCreated) {
				aOther.copy(iterator);
				mCreated = true;
			}else {
				*reinterpret_cast<int32_t*>(mImplementation) = *reinterpret_cast<const int32_t*>(aOther.mImplementation);
				mCreated = false;
			}
			return *this;
		}

		inline iterator<T>& operator=(const iterator<T>& aOther) {
			interfaces::iterator<T>* const iterator = reinterpret_cast<interfaces::iterator<T>*>(mImplementation);
			if(mCreated) iterator->~interfaces::iterator();
			if(aOther.mCreated) {
				aOther.copy(iterator);
				mCreated = true;
			}else {
				*reinterpret_cast<int32_t*>(mImplementation) = *reinterpret_cast<const int32_t*>(aOther.mImplementation);
				mCreated = false;
			}
			return *this;
		}

		/*template<typename ENABLE = typename std::enable_if<! std::is_same<T, const T>::value>::type>
		operator iterator<const T>() const{
			iterator<T> tmp = *this;
			return *reinterpret_cast<iterator<const T>*>(&tmp);
		}*/

		// Comparison

		inline bool operator==(const iterator<T>& aOther) const {
			return get_offset() == aOther.get_offset();
		}

		inline bool operator!=(const iterator<T>& aOther) const {
			return get_offset() != aOther.get_offset();
		}

		inline bool operator<(const iterator<T>& aOther) const {
			return get_offset() < aOther.get_offset();
		}

		inline bool operator>(const iterator<T>& aOther) const {
			return get_offset() > aOther.get_offset();
		}

		inline bool operator<=(const iterator<T>& aOther) const {
			return get_offset() <= aOther.get_offset();
		}

		inline bool operator>=(const iterator<T>& aOther) const {
			return get_offset() >= aOther.get_offset();
		}

		// Dereference

		inline T& operator*() {
			return *const_cast<T*>(dereference());
		}

		inline const T& operator*() const {
			return *dereference();
		}

		inline T* operator->() {
			return const_cast<T*>(dereference());
		}

		inline const T* operator->() const {
			return dereference();
		}

		inline T& operator[](const uint32_t aIndex) {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return const_cast<T&>(tmp.dereference());
		}

		inline const T& operator[](const uint32_t aIndex) const {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return tmp.dereference();
		}

		// Increment

		inline iterator<T>& operator++() {
			increment(1);
			return *this;
		}

		inline iterator<T> operator++(int) {
			iterator<T> tmp(*this);
			increment(1);
			return tmp;
		}

		inline iterator<T>& operator+=(const uint32_t aOffset) {
			increment(aOffset);
			return *this;
		}

		inline iterator<T> operator+(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.increment(aOffset);
			return tmp;
		}

		// Decrement

		inline iterator<T>& operator--() {
			decrement(1);
			return *this;
		}

		inline iterator<T> operator--(int) {
			iterator<T> tmp(*this);
			decrement(1);
			return tmp;
		}

		inline iterator<T>& operator-=(const uint32_t aOffset) {
			decrement(aOffset);
			return *this;
		}

		inline iterator<T> operator-(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.decrement(aOffset);
			return tmp;
		}

		inline int32_t operator-(const iterator<T>& aOther) const {
			return get_offset() - aOther.get_offset();
		}
	};
}

#endif