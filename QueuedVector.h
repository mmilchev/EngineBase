#ifndef QUEUED_VECTOR_H
#define QUEUED_VECTOR_H

#include <vector>
#include <queue>
#include <memory>

//This vector is useful when you need to change things inside it while itterating over the elements
//Adding and removing elements are done reparately - the itterating vector is not changed immediately
//No memory deallocation happens automatically
template<class VecType>
class QueuedVector
{
public:
	QueuedVector();

	void Add(VecType type);
	void Remove(VecType type);
	void RemoveAt(int index);

	void RemoveAddedInstance(VecType target);

	void ProcessQueued();

	void Clear();

	template<class PredTpye>
	void Sort(PredTpye pred);

	int Size() const;

	std::vector<VecType> const& GetRawData() const;

	VecType operator[] (const int nIndex);
	const VecType& operator[] (const int nIndex) const;
private:
	//These are just queues. Not allocating/deleting anything
	std::vector<VecType> m_AddQueue;
	std::vector<VecType> m_RemoveQueue;

	//Data is not deleted if it's a pointer
	std::vector<VecType> m_VectorData;
};

template<class VecType>
void QueuedVector<VecType>::RemoveAddedInstance(VecType target)
{
	auto found = std::find_if(m_AddQueue.begin(), m_AddQueue.end(),
		[target](const VecType& item) { return item == target; });
	if (found != m_AddQueue.end())
		m_AddQueue.erase(found);
}

template <class VecType>
QueuedVector<VecType>::QueuedVector()
{
}

template <class VecType>
template <class PredTpye>
void QueuedVector<VecType>::Sort(PredTpye pred)
{
	std::sort(m_VectorData.begin(), m_VectorData.end(), pred);
}

template <class VecType>
void QueuedVector<VecType>::Add(VecType type)
{
	m_AddQueue.push_back(type);
}

template <class VecType>
void QueuedVector<VecType>::Remove(VecType type)
{
	m_RemoveQueue.push_back(type);
}

template <class VecType>
void QueuedVector<VecType>::RemoveAt(int index)
{
	Remove(this[index]);
}

template <class VecType>
void QueuedVector<VecType>::ProcessQueued()
{
	for (auto& item : m_AddQueue)
	{
		m_VectorData.push_back(item);
	}
	m_AddQueue.clear();

	for (auto& target : m_RemoveQueue)
	{
		auto found = std::find_if(m_VectorData.begin(), m_VectorData.end(),
			[target](const VecType& item) { return item == target; });
		if (found != m_VectorData.end())
			m_VectorData.erase(found);
	}

	m_RemoveQueue.clear();
}

template <class VecType>
void QueuedVector<VecType>::Clear()
{
	m_VectorData.clear();
}

template <class VecType>
int QueuedVector<VecType>::Size() const
{
	return m_VectorData.size();
}

template <class VecType>
std::vector<VecType> const& QueuedVector<VecType>::GetRawData() const
{
	return m_VectorData;
}

template <class VecType>
VecType QueuedVector<VecType>::operator[](int const nIndex)
{
	return m_VectorData[nIndex];
}

template <class VecType>
VecType const& QueuedVector<VecType>::operator[](int const nIndex) const
{
	return m_VectorData[nIndex];
}
#endif