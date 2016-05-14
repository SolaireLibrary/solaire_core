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
	//public:
		typedef T Type;
	private:
		uint8_t mImplementation[interfaces::MAX_INTERFACES_ITERATOR_SIZE];
		bool mCreated;
	private:
		inline interfaces::iterator<T>* get_iterator_ptr() {
			return reinterpret_cast<interfaces::iterator<T>*>(mImplementation);
		}

		inline const interfaces::iterator<T>* get_iterator_ptr() const {
			return reinterpret_cast<const interfaces::iterator<T>*>(mImplementation);
		}

	    inline interfaces::iterator<T>& get_iterator() {
			runtime_assert(mCreated, "Iterator implementation is null");
			return *get_iterator_ptr();
	    }

		inline const interfaces::iterator<T>& get_iterator() const {
			runtime_assert(mCreated, "Iterator implementation is null");
			return *get_iterator_ptr();
	    }
	public:

		iterator() :
			mCreated(false)
		{}

		iterator(iterator<T>&& aOther) :
			mCreated(false)
		{
			if(aOther.mCreated) {
				aOther.get_iterator().copy(get_iterator_ptr());
				mCreated = true;
			}
		}

		iterator(const iterator<T>& aOther) :
			mCreated(false)
		{
			if(aOther.mCreated) {
				aOther.get_iterator().copy(get_iterator_ptr());
				mCreated = true;
			}
		}

		iterator(const interfaces::iterator<T>& aiterator) :
            mCreated(true)
        {
            aiterator.copy(get_iterator_ptr());
        }

		~iterator() {
			if(mCreated) get_iterator().~iterator();
		}

		inline iterator<T>& operator=(iterator<T>&& aOther) {
			if(mCreated) get_iterator().~iterator();
			if(aOther.mCreated) aOther.get_iterator().copy(get_iterator_ptr());
			return *this;
		}

		inline iterator<T>& operator=(const iterator<T>& aOther) {
			if(mCreated) get_iterator().~iterator();
			if(aOther.mCreated) aOther.get_iterator().copy(get_iterator_ptr());
			return *this;
		}

		inline operator iterator<const T>() const {
			iterator<T> tmp = *this;
			return *reinterpret_cast<iterator<const T>*>(&tmp);
		}

		// Comparison

		inline bool operator==(const iterator<T>& aOther) const {
			return get_iterator().get_offset() == aOther.get_iterator().get_offset();
		}

		inline bool operator!=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() != aOther.get_iterator().get_offset();
		}

		inline bool operator<(const iterator<T>& aOther) const {
			return get_iterator().get_offset() < aOther.get_iterator().get_offset();
		}

		inline bool operator>(const iterator<T>& aOther) const {
			return get_iterator().get_offset() > aOther.get_iterator().get_offset();
		}

		inline bool operator<=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() <= aOther.get_iterator().get_offset();
		}

		inline bool operator>=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() >= aOther.get_iterator().get_offset();
		}

		// Dereference

		inline T& operator*() {
			return *const_cast<T*>(get_iterator().dereference());
		}

		inline const T& operator*() const {
			return *get_iterator().dereference();
		}

		inline T* operator->() {
			return const_cast<T*>(get_iterator().dereference());
		}

		inline const T* operator->() const {
			return get_iterator().dereference();
		}

		inline T& operator[](const uint32_t aIndex) {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return const_cast<T&>(tmp.get_iterator().dereference());
		}

		inline const T& operator[](const uint32_t aIndex) const {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return tmp.get_iterator().dereference();
		}

		// Increment

		inline iterator<T>& operator++() {
			get_iterator().increment(1);
			return *this;
		}

		inline iterator<T> operator++(int) {
			iterator<T> tmp(*this);
			get_iterator().increment(1);
			return tmp;
		}

		inline iterator<T>& operator+=(const uint32_t aOffset) {
			get_iterator().increment(aOffset);
			return *this;
		}

		inline iterator<T> operator+(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.get_iterator().increment(aOffset);
			return tmp;
		}

		// Decrement

		inline iterator<T>& operator--() {
			get_iterator().decrement(1);
			return *this;
		}

		inline iterator<T> operator--(int) {
			iterator<T> tmp(*this);
			get_iterator().decrement(1);
			return tmp;
		}

		inline iterator<T>& operator-=(const uint32_t aOffset) {
			get_iterator().decrement(aOffset);
			return *this;
		}

		inline iterator<T> operator-(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.get_iterator().decrement(aOffset);
			return tmp;
		}

		inline int32_t operator-(const iterator<T>& aOther) const {
			return get_iterator().get_offset() - aOther.get_iterator().get_offset();
		}
	};
}

#endif