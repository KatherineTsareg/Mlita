#pragma once
#include "stdafx.h"

class CConvexHull : public sf::Drawable
{
public:
	CConvexHull(std::ifstream & in);
	~CConvexHull() = default;
	void GrahamScan();
	void Update();
	void draw(sf::RenderTarget & render, sf::RenderStates states) const override;
	std::vector<sf::Vector2i> GetResult()const;
	std::vector<sf::Vector2i> GetInputPoints()const;
private:
	void FindMinPoint();
	void CConvexHull::SortPoint();
	void RemovingInternalPoints();
	std::vector<sf::Vector2i> ReadInputData(std::ifstream & in);
	int Rotate(sf::Vector2i const& A, sf::Vector2i const& B, sf::Vector2i const& C)const;
	
	const std::vector<sf::Vector2i> m_inputPoints;
	std::vector<size_t> m_positionsPoints;
	std::vector<size_t> m_result;
	std::vector<sf::CircleShape> m_dots;
	//std::vector<sf::Vertex[2]> m_lines;
	const enum STEP {NONE, FIRST, SECOND, THIRD};
	STEP m_step = STEP::NONE;
};


template <typename T>
int Sgn(T const& numb)
{
	return (numb > 0 ? 1 : (numb < 0 ? -1 : 0));
}