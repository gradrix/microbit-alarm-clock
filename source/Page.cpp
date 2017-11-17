#include "Page.h" 

Page::Page()
{
  this->pageRenderFunc = nullptr;
};
void Page::AddRenderFunction(pageFunc pageRenderFunc)
{
  this->pageRenderFunc = pageRenderFunc;
};
void Page::AddChildPages(uint8_t pageAmount)
{
  for (uint8_t i = 0; i < pageAmount; i++)
  {
      Page newPage;
      this->pages.push_back(newPage); 
  }
};
uint8_t Page::GetChildPageSize()
{
  return this->pages.size();   
};
Page* Page::GetChildPage(uint8_t index)
{
  if ((this->GetChildPageSize() - 1) < index)
      return nullptr;
  return &this->pages.at(index);   
};
void Page::RenderPage(uint8_t colIndex)
{
  if (this->pageRenderFunc)
    this->pageRenderFunc(colIndex);
};
