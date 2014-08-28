#ifndef QUEUED_VECTOR_PTR_H
#define QUEUED_VECTOR_PTR_H

#include <vector>
#include <queue>
#include <memory>

//This vector is useful when you need to change things inside it while itterating over the elements
//Adding and removing elements are done reparately - the itterating vector is not changed immediately
template<class VecType>
class QueuedVectorPtr
{
public:
	QueuedVectorPtr();

	void Add(VecType* type);
	void Remove(VecType* type);
	void RemoveAt(int index);

	void AddQueued();
	void RemoveQueued();

	int Size() const;

	VecType* operator[] (const int nIndex);
private:
	//These are just queues. Not allocating/deleting anything
	std::queue<VecType*> m_AddQueue;
	std::queue<VecType*> m_RemoveQueue;

	//The stored data. Deallocates automatically
	std::vector<std::unique_ptr<VecType>> m_VectorData;
};

template<class VecType>
QueuedVectorPtr<VecType>::QueuedVectorPtr()
{
}

template <class VecType>
void QueuedVectorPtr<VecType>::Add(VecType* type)
{
	m_AddQueue.push(type);
}

template <class VecType>
void QueuedVectorPtr<VecType>::Remove(VecType* type)
{
	m_RemoveQueue.push(type);
}

template <class VecType>
void QueuedVectorPtr<VecType>::RemoveAt(int index)
{
	Remove(this[index]);
}

template <class VecType>
void QueuedVectorPtr<VecType>::AddQueued()
{
	while (!m_AddQueue.empty())
	{
		m_VectorData.push_back(std::unique_ptr<VecType>(m_AddQueue.front()));
		m_AddQueue.pop();
	}
}

template <class VecType>
void QueuedVectorPtr<VecType>::RemoveQueued()
{
	while (!m_RemoveQueue.empty())
	{
		auto target = m_RemoveQueue.front();
		auto found = std::find_if(m_VectorData.begin(), m_VectorData.end(), 
			[target](const std::unique_ptr<VecType>& item) { return item.get() == target; });
		if (found != m_VectorData.end())
			m_VectorData.erase(found);
		m_RemoveQueue.pop();
	}
}

template <class VecType>
int QueuedVectorPtr<VecType>::Size() const
{
	return m_VectorData.size();
}

template <class VecType>
VecType* QueuedVectorPtr<VecType>::operator[](int const nIndex)
{
	return m_VectorData[nIndex].get();
}
#endif