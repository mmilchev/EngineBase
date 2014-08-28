#ifndef STL_EXT_H
#define STL_EXT_H

#include <assert.h>
#include <cstddef>

// watch_ptr is a smart pointer that automatically becomes NULL when it's pointee is deleted
//Source: https://github.com/manylegged/outlaws-core/blob/master/stl_ext.h#L268

struct Watchable;

struct watch_ptr_base {

	watch_ptr_base() : ptr(nullptr), next(nullptr), prev(nullptr) {}

	const Watchable* ptr;
	watch_ptr_base*  next;
	watch_ptr_base*  prev;
};

struct Watchable {

	mutable watch_ptr_base watch_list;

	void nullReferencesTo()
	{
		for (watch_ptr_base* watcher = watch_list.next; watcher != nullptr; watcher = watcher->next)
		{
			watcher->ptr = nullptr;
			if (watcher->prev)
				watcher->prev->next = nullptr;
			watcher->prev = nullptr;
		}
	}

	void onQueueForDelete()
	{
		nullReferencesTo();
	}

	~Watchable()
	{
		nullReferencesTo();
	}
};

// smart pointer that automatically becomes NULL when it's pointee is deleted
template <typename T>
class watch_ptr : public watch_ptr_base {

	void unlink()
	{
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
		next = nullptr;
		prev = nullptr;

		ptr = nullptr;
	}

	void link(const Watchable* p)
	{
		ptr = p;
		assert(prev == nullptr);
		assert(next == nullptr);
		if (p != nullptr)
		{
			prev = &p->watch_list;
			next = p->watch_list.next;
			if (p->watch_list.next)
				p->watch_list.next->prev = this;
			p->watch_list.next = this;
		}
	}

public:
	~watch_ptr()
	{
		unlink();
	}

	// default construct to null
	watch_ptr() { }

	watch_ptr(nullptr_t) { }

	explicit watch_ptr(T *t) { link(t); }
	watch_ptr(const watch_ptr &t) { link(t.ptr); }
	template <typename U>
	watch_ptr(const watch_ptr<U> &t) { link(t.ptr); }

	watch_ptr& operator=(T* t)
	{
		unlink();
		link(t);
		return *this;
	}

	watch_ptr& operator=(const watch_ptr& other)
	{
		unlink();
		link(other.ptr);
		return *this;
	}

	// it's a smart pointer
	T& operator*()  const { return *get(); }
	T* operator->() const { return get(); }
	bool operator==(const watch_ptr &o) const { return ptr == o.ptr; }
	bool operator!=(const watch_ptr &o) const { return !(ptr == o.ptr); }
	bool operator<(const watch_ptr &o)  const { return ptr < o.ptr; }
	explicit operator bool()            const { return ptr != nullptr; }

	T*  get() const { return (T*)ptr; }
};

template <typename T>
watch_ptr<T> make_watch_compare(const T* v)
{
	watch_ptr<T> p;
	p.ptr = v;
	return p;
}

template <typename T>
watch_ptr<T> make_watch(T* v)
{
	watch_ptr<T> p(v);
	return p;
}

#endif