#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Figure.h"


class Picture
{
private:
	std::vector<std::shared_ptr<Figure>> current_figures{};
	std::vector<std::shared_ptr<Figure>> deleted_figures {};
	std::string file_name {};

public:
	Picture() = default;
	
	~Picture();

	PointT m_prevPos{ 0,0 };

	Picture(std::vector<std::shared_ptr<Figure>>& vec, std::string& file_name);

	//Возвращает указатель на добавленную фигуру
	std::shared_ptr<Figure> AddFigure(Figure&);

	std::shared_ptr<Figure> AddFigure(std::shared_ptr<Figure>);

	bool DeleteFigure();

	//Возвращает текущую выделенную фигуру
	//Если фигура не найдена возвращает nullptr
	std::shared_ptr<Figure> GetFigure() const;

	//Возвращает фигуру в которую попадает точка
	std::shared_ptr<Figure> GetFigure(PointT) const;	

	std::string FileName() const { return file_name; }

	void SetFileName(std::string&);

	void Save() const;

	void Load();

	bool Undo();

	bool Redo();

	void Clear();

	//Меняет флаг выделения на false у фигур, если находит такую, то возращает true.
	bool ZeroTouch();	
	
	size_t Size() { return current_figures.size(); }

	void  GetFigures(std::vector<std::shared_ptr<Figure>>& figures) const;

	friend std::pair<int, int> GetPictureSize(const Picture&);
};

