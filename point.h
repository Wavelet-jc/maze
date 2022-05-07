#pragma once
typedef struct Point {
	int x;	// ÐÐ
	int y;	// ÁÐ
}Point;

void MoveRight(Point* p)
{
	p->y++;
}

void MoveLeft(Point* p)
{
	p->y--;
}

void MoveUp(Point* p)
{
	p->x++;
}

void MoveDown(Point* p)
{
	p->x--;
}

void CopyPoint(const Point* p, Point* pCopyer) 
{
	pCopyer->x = p->x;
	pCopyer->y = p->y;
}