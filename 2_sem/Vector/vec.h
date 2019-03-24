#include "alloc1.h"

template <typename T, class Allocator = MyAlloc <T> >
class MyVector
{
	public:
		explicit MyVector (const Allocator &alloc) noexcept;
		MyVector (size_type count, const T &value, const Allocator &alloc = Allocator ());
		MyVector (size_type count, const Allocator &alloc = Allocator());
		MyVector (const MyVector &other, const Allocator &alloc);
		MyVector (MyVector &&other, const Allocator &alloc) noexcept;
		~MyVector () noexcept;

		pointer 		begin () noexcept;
		const_pointer 	begin () const noexcept;
		pointer 		end () noexcept;
		const_pointer 	end () const noexcept;
		reference 		at (size_type index);
		const_reference at (size_type index) const;
		reference       operator [] (size_type index);
		const_reference operator [] (size_type index) const
		reference 		front () noexcept;
		const_reference front () const noexcept;
		reference 		back () noexcept;
		const_reference back () noexcept const;
		size_type size () const noexcept;
		size_type max_size () const noexcept;
		size_type capacity () const noexcept;
		bool empty () const noexcept;
		void assign (size_type count, const T &value);
		pointer insert (const_pointer pos, const T &value);
		pointer insert (const_pointer pos, T &&value);
		pointer erase (const_pointer pos);
		pointer erase (const_pointer first, const_iterator last);
		void push_back (const T &value);
		void push_back (T &&value);
		void pop_back ();
		void resize (size_type count);
		void reserve (size_type new_cap);
		void clear () noexcept;
		!!!!MyVector &operator = (const MyVector &other);
		!!!!MyVector &operator = (MyVector &&other);

	private:
		pointer begin_, end_, end_of_storage_;
};

template <typename T>
MyVector <T>::MyVector (const Allocator &alloc) noexcept : Allocator (alloc),
begin_ (nullptr), end_ (nullptr), end_of_storage_ (nullptr)
{}
template <typename T>
MyVector <T>::MyVector MyVector (size_type count, const T &value, const Allocator &alloc = Allocator ()) :
Allocator (alloc), begin_ (allocate (count)), end_ (begin_ + count), end_of_storage_ (end_)
{
	std::uninitialized_fill_n <pointer, size_type>(begin_, count, value);
}
template <typename T>
MyVector <T>::MyVector MyVector (size_type count, const Allocator &alloc = Allocator ()) :
Allocator (alloc), begin_ (allocate (count)), end_ (begin_ + count), end_of_storage_ (end_)
{}
template <typename T>
MyVector <T>::MyVector <T>::MyVector (const MyVector &other, const Allocator &alloc) : Allocator (alloc),
begin_ (allocate (other.size ())), end_ (begin_ + other.size ()), end_of_storage_(end_)
{
	memcpy (begin_, other.begin_, other.size () * sizeof (pointer));
}
template <typename T>
MyVector <T>::MyVector (MyVector &&other, const Allocator &alloc) noexcept : Allocator (alloc),
begin_ (other.begin_), end_ (other.end_), end_of_storage_ (other.end_of_storage_)
{
	other.begin_ = nullptr;
	other.end_ = nullptr;
	other.end_of_storage_ = nullptr;
}
template <typename T>
MyVector <T>::~MyVector () noexcept
{
	dealocate (begin_, capacity ())
}
template <typename T>
pointer MyVector <T>::begin () noexcept {return begin_;}
template <typename T>
const_pointer MyVector <T>::begin () const noexcept {return begin_;}
template <typename T>
pointer MyVector <T>::end () noexcept {return end_;}
template <typename T>
const_pointer MyVector <T>::end () const noexcept {return end_;}
template <typename T>
reference MyVector <T>::at (size_type index)
{
	if (index >= size ())
		throw std::out_of_range ("Access to element in vector after end\n");
	return begin_[index];
}
template <typename T>
const_reference MyVector <T>::at (size_type index) const
{
	if (index >= size ())
		throw std::out_of_range ("Access to element in vector after end\n");
	return begin_[index];
}
template <typename T>
reference MyVector <T>::operator [] (size_type index) {return begin_[index];}
template <typename T>
const_reference MyVector <T>::operator [] (size_type index) {return begin_[index];}
template <typename T>
reference MyVector <T>::front () noexcept {return begin_;}
template <typename T>
const_reference MyVector <T>::front () const noexcept {return begin_;}
template <typename T>
reference MyVector <T>::back () noexcept {return end_ - 1;}
template <typename T>
const_reference MyVector <T>::back () const noexcept {return end_ - 1;}
template <typename T>
size_type MyVector <T>::size () const noexcept { return end_ - begin_; }
template <typename T>
size_type MyVector <T>::max_size () const noexcept { return Allocator::max_size (); }
template <typename T>
size_type MyVector <T>::capacity() const noexcept { return end_of_storage_ - begin_; }
template <typename T>
bool MyVector <T>::empty () const noexcept { return begin_ == end_; }
template <typename T>
void MyVector::assign (size_type count, const T &value)
{
	if (count > capacity ())
	{
		pointer new_storage = allocate (count);
		deallocate (begin_);
		begin_ = new_storage;
		end_of_storage_ = begin_ + count;
	}
	end_ = begin_ + count;
	std::uninitialized_fill_n <pointer, size_type> (begin_, count, value);
}
template <typename T>
pointer MyVector::insert (const_pointer pos, const T &value)
{
	if (end_ == end_of_storage_)
	{
		size_type index = pos - begin_;
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, index * sizeof (value_type));
		memcpy (new_storage + index + 1, _begin + index, (size () - index) * sizeof(value_type));
		deallocate (begin_);
		end_ = new_storage + size () + 1;
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
		pos = begin_ + index;
	}
	else
	{
		memmove (const_cast <pointer> (pos) + 1, pos, (end_ - pos) * sizeof (value_type));
		_end++;
	}
	*const_cast <pointer> (pos) = value;
	return const_cast <pointer> (pos);
}
template <typename T>
pointer MyVector <T>::insert (const_pointer pos, T &&value)
{
	if (end_ == end_of_storage_)
	{
		size_type index = pos - begin_;
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, index * sizeof (value_type));
		memcpy (new_storage + index + 1, _begin + index, (size () - index) * sizeof(value_type));
		deallocate (begin_);
		end_ = new_storage + size () + 1;
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
		pos = begin_ + index;
	}
	else
	{
		memmove (const_cast <pointer> (pos) + 1, pos, (end_ - pos) * sizeof (value_type));
		_end++;
	}
	*const_cast <pointer> (pos) = std::move (value);
	return const_cast <pointer> (pos);
}
template <typename T>
pointer MyVector <T>::erase (const_pointer pos)
{
	end_--;
	memmove (const_cast <pointer> (pos), pos + 1, (end_ - pos) * sizeof (value_type));
	return const_cast <pointer> (pos);
}
template <typename T>
pointer MyVector <T>::erase (const_pointer first, const_pointer last)
{
	size_type count = last - first;
	_end -= count;
	memmove (const_cast <pointer> (first), first + count, (end_ - first) * sizeof (value_type));
	return const_cast <pointer> (first);
}
template <typename T>
void MyVector <T>::push_back (const T &value)
{
	if (end_ == end_of_storage_)
	{
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, size () * sizeof (value_type));
		dealocate (begin_);
		end_ = new_storage + size ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
	}
	*end_ = value;
	end_++;
}
template <typename T>
void MyVector <T>::push_back (T &&value)
{
	if (end_ == end_of_storage_)
	{
		pointer new_storage = allocate (size () + 1);
		memcpy (new_storage, begin_, size () * sizeof (value_type));
		dealocate (begin_);
		end_ = new_storage + size ();
		begin_ = new_storage;
		end_of_storage_ = begin_ + size () + 1;
	}
	*end_ = std::move (value);
	end_++;
}
template <typename T>
void MyVector <T>::pop_back ()
{
	end_--;
}
template <typename T>
void MyVector <T>::resize (size_type count)
{
	if (capacity () < count)
	{
		size_type new_size = size () + count;
		pointer new_storage = allocate (new_size);
		memcpy (new_storage, begin_, size() * sizeof(value_type));
		deallocate (begin_);
		begin_ = new_storage;
		end_of_storage_ = begin_ + new_size;
	}
	end_ = begin_ + count;
}
template <typename T>
void MyVector <T>::reserve (size_type new_cap)
{
	if (capacity () < new_cap)
	{
		const size_t cur_size = size ();
		pointer new_storage = allocate (new_cap);
		memcpy (new_storage, begin_, cur_size * sizeof (value_type));
		deallocate (begin_);
		begin_ = new_storage;
		end_ = new_storage + cur_size;
		end_of_storage_ = begin_ + new_cap;
	}
}
template <typename T>
void MyVector <T>::clear () noexcept
{
	end_ = begin_;
}