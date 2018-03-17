#include "stdafx.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager() // do not need extra information
{
}

PowerUpManager::~PowerUpManager() // does not need extra information
{
	for (PowerUp* p : m_pItems)
	{
		delete p;
		p = nullptr;

	}
	m_pItems.clear();
}

PowerUp * PowerUpManager::AddItem(const Point2f & center, PowerUp::Type type)
{
	PowerUp* newPower{ new PowerUp{center, type } };
	m_pItems.push_back(newPower);
//	m_pItems.push_back(new PowerUp{ center, type });
	return newPower;
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* i: m_pItems)
	{
		i->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (PowerUp* i : m_pItems)
	{
		i->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf & rect)
{
	for (unsigned int i{ 0 }; i < m_pItems.size(); i++)
	{
		if (m_pItems[i]->IsOverlapping(rect) == true) // check if the rect is overlapping the given powereUp
		{
			removeItem(i);
			return true;
		}
	}
	return false;
}

void PowerUpManager::removeItem(int index)
{
	//deleting the given item
	delete m_pItems[index];
	m_pItems[index] = nullptr;

	//replacing the nullptr with the index, 
	m_pItems[index] = m_pItems[m_pItems.size() - 1];
	m_pItems.pop_back();

}
