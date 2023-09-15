#include "Picture.h"

Picture::Picture(std::vector<std::shared_ptr<Figure>>& vec, std::string& file_name)
	: current_figures(vec)
	, file_name(file_name)
{}

Picture::~Picture()
{

}

std::shared_ptr<Figure> Picture::AddFigure(Figure& f)
{
	auto ptr = std::shared_ptr<Figure>(&f);
	current_figures.push_back(ptr);
	return ptr;
}

std::shared_ptr<Figure> Picture::AddFigure(std::shared_ptr<Figure> ptr)
{
	current_figures.push_back(ptr);
	return ptr;
}

bool Picture::DeleteFigure()
{
	for (int i = 0; i < current_figures.size(); ++i)
	{
		if (current_figures[i]->GetTouch())
		{
			deleted_figures.push_back(current_figures[i]);
			current_figures.erase(current_figures.begin() + i);
			return true;
		}
	}	
	return false;
}

std::shared_ptr<Figure> Picture::GetFigure(PointT p) const
{
	for (auto& f : current_figures)
	{
		if (f->IsBelongs(p))
		{
			return f;
		}
	}
	return nullptr;
}

std::shared_ptr<Figure> Picture::GetFigure() const
{
	for (auto& f : current_figures)
	{
		if (f->GetTouch())
		{
			return f;
		}
	}
	return nullptr;
}

void Picture::SetFileName(std::string& name)
{
	file_name = name;
}

void Picture::Save() const
{

}

void Picture::Load()
{

}

bool Picture::Undo()
{
	return 0;
}

bool Picture::Redo()
{
	return 0;
}

void Picture::Clear()
{
	deleted_figures.insert(deleted_figures.end(), current_figures.begin(), current_figures.end());
	current_figures.clear();
}


void Picture::GetFigures(std::vector<std::shared_ptr<Figure>>& figures) const
{
	for (const auto& f : current_figures)
	{
		figures.push_back(f);
	}

}

bool Picture::ZeroTouch()
{
	for (auto& i : current_figures)
	{
		if (i->GetTouch())
		{
			i->SetTouch(false);
			return true;
		}
		
	}
	return false;

}

std::pair<int, int> GetPictureSize(const Picture& p)
{
	std::pair<int, int> max {};

	for (auto& f : p.current_figures)
	{
		if (max.first < f->GetMaxXY().first)
		{
			max.first = f->GetMaxXY().first;
		}
		if (max.second < f->GetMaxXY().second)
		{
			max.second = f->GetMaxXY().second;
		}
		
	}
	return max;
}
