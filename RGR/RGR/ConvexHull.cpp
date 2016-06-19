#include "stdafx.h"
#include "ConvexHull.h"
#include <boost/iterator/counting_iterator.hpp>

using namespace std;
using namespace sf;
namespace
{
	const int SIZE_DOT = 10;
}
CConvexHull::CConvexHull(std::ifstream & in)
	:m_inputPoints(ReadInputData(in))
{
	m_positionsPoints = vector<size_t>(boost::make_counting_iterator(0), boost::make_counting_iterator((int)m_inputPoints.size()));
	for (Vector2i point : m_inputPoints)
	{
		
		CircleShape dot(SIZE_DOT);
		dot.setOrigin((int)SIZE_DOT / 2, (int)SIZE_DOT / 2);
		dot.setPosition(point.x, point.y);
		dot.setFillColor(Color::Cyan);
		m_dots.push_back(dot);
	}
}



int CConvexHull::Rotate(sf::Vector2i const & A, sf::Vector2i const & B, sf::Vector2i const & C) const
{
	return Sgn((B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x));
}

std::vector<sf::Vector2i> CConvexHull::ReadInputData(std::ifstream & in)
{
	vector<sf::Vector2i> points;
	int pointsCount;
	string inputStr;
	in >> pointsCount;
	while (pointsCount-- > 0)
	{
		int x, y;
		in >> x >> y;
		points.push_back({ x, y });
	}
	return points;
}

void CConvexHull::FindMinPoint()
{
	cout << "step 1" << endl;
	for (size_t it = 1; it < m_inputPoints.size(); it++)
	{
		if (m_inputPoints[it].x < m_inputPoints[m_positionsPoints[0]].x)
		{
			swap(m_positionsPoints[0], m_positionsPoints[it]);
		}
		else if ((m_inputPoints[it].x == m_inputPoints[m_positionsPoints[0]].x) && (m_inputPoints[it].y < m_inputPoints[m_positionsPoints[0]].y))
		{
			swap(m_positionsPoints[0], m_positionsPoints[it]);
		}
	}
}

void CConvexHull::SortPoint()
{
	size_t base = m_positionsPoints[0];
	sort(begin(m_positionsPoints) + 1, end(m_positionsPoints), [&](auto & last, auto & next) {
		return (Rotate(m_inputPoints[base], m_inputPoints[last], m_inputPoints[next]) > 0);
	});
}

void CConvexHull::RemovingInternalPoints()
{
	cout << "i came to push elemeny in m_result" << endl;
	m_result.push_back(m_positionsPoints[0]);
	m_result.push_back(m_positionsPoints[1]);
	for (size_t i = 2; i < m_inputPoints.size(); i++)
	{
		while ((Rotate(m_inputPoints[m_result[m_result.size() - 2]], m_inputPoints[m_result[m_result.size() - 1]], m_inputPoints[m_positionsPoints[i]]) < 0) && (m_result.size() - 2 >= 0))
		{
			m_result.pop_back();
		}
		m_result.push_back(m_positionsPoints[i]);
	}
}

void CConvexHull::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	if (m_step == STEP::NONE)
	{
		for (auto dot : m_dots)
		{
			target.draw(dot, states);
		}
	}
	if (m_step == STEP::FIRST)
	{
		for (auto dot : m_dots)
		{
			target.draw(dot, states);
		}
	}
}

std::vector<sf::Vector2i> CConvexHull::GetResult() const
{
	std::vector<sf::Vector2i> result;
	for (auto numb : m_result)
	{
		result.push_back(m_inputPoints[numb]);
	}
	return result;
}

std::vector<sf::Vector2i> CConvexHull::GetInputPoints() const
{
	return m_inputPoints;
}

void CConvexHull::Update()
{
	//TODO:: timer!!!!

	// step 1 - draw all point on the screen
	switch (m_step)
	{
	case STEP::NONE:
		m_step = STEP::FIRST;
		break;
	case STEP::FIRST:
		FindMinPoint();
		m_dots[0].setFillColor(Color::Red);
		m_step = STEP::SECOND;
		break;

	}
}
void CConvexHull::GrahamScan()
{
	for (size_t it = 1; it < m_inputPoints.size(); it++)
	{
		if (m_inputPoints[it].x < m_inputPoints[m_positionsPoints[0]].x)
		{
			swap(m_positionsPoints[0], m_positionsPoints[it]);
		}
		else if ((m_inputPoints[it].x == m_inputPoints[m_positionsPoints[0]].x) && (m_inputPoints[it].y < m_inputPoints[m_positionsPoints[0]].y))
		{
			swap(m_positionsPoints[0], m_positionsPoints[it]);
		}
	}
	size_t base = m_positionsPoints[0];
	sort(begin(m_positionsPoints) + 1, end(m_positionsPoints), [&](auto & last, auto & next) {

		return (Rotate(m_inputPoints[base], m_inputPoints[last], m_inputPoints[next]) > 0);
	});
	m_result.push_back(m_positionsPoints[0]);
	m_result.push_back(m_positionsPoints[1]);
	for (size_t i = 2; i < m_inputPoints.size(); i++)
	{
		while ((Rotate(m_inputPoints[m_result[m_result.size() - 2]], m_inputPoints[m_result[m_result.size() - 1]], m_inputPoints[m_positionsPoints[i]]) < 0) && (m_result.size() - 2 >= 0))
		{
			m_result.pop_back();
		}
		m_result.push_back(m_positionsPoints[i]);
	}
}