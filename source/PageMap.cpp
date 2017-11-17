#include "Page.h" 
#include "PageMap.h" 

PageMap::PageMap(Page* page)
{
    this->page = page;
    this->pageTreeIndex.push_back(0);
};
bool PageMap::MoveUpTree()
{
    if (this->pageTreeIndex.empty())
        return false;
    this->pageTreeIndex.pop_back();
    return true;
};
bool PageMap::MoveDownTree(uint8_t colIndex/* = 0 */)
{
    this->pageTreeIndex.push_back(colIndex);
    if (this->GetPage())
        return true;
    
    this->pageTreeIndex.pop_back();
    return false;  
};
bool PageMap::MoveToPreviousPage()
{            
    if (this->pageTreeIndex.empty()) return false;
    
    if (this->GetColIndex() == 0) {
      this->pageTreeIndex.at(this->pageTreeIndex.size() - 1) = this->GetPage(1)->GetChildPageSize() - 1;
      return true;
    }
    this->pageTreeIndex.at(this->pageTreeIndex.size() - 1) = this->pageTreeIndex.back() - 1; 
    return false;  
};
bool PageMap::MoveToNextPage()
{
    if (this->pageTreeIndex.empty()) return false;
  
    this->pageTreeIndex.at(this->pageTreeIndex.size() - 1) = this->pageTreeIndex.back() + 1; 
    if (this->GetPage())
        return true;        
    this->pageTreeIndex.at(this->pageTreeIndex.size() - 1) = 0;
    return false;  
};
uint8_t PageMap::GetColIndex()
{
    if (this->pageTreeIndex.empty()) return 0;
    return this->pageTreeIndex.back();
};
uint8_t PageMap::GetRowIndex()
{
    if (this->pageTreeIndex.empty()) return 0;
    return this->pageTreeIndex.size() - 1;
};
void PageMap::RenderPage() 
{
    uint8_t colIndx = this->GetColIndex();
    this->MoveUpTree();
    Page* page = this->GetPage();
    this->MoveDownTree(colIndx);
    if (page)
      page->RenderPage(colIndx);
};
Page* PageMap::GetPage(uint8_t pageOffset) 
{
    Page* pageIterator = this->page;
    for (uint8_t i = 0; i < this->pageTreeIndex.size() - pageOffset; i++)
    {
        Page* currentPage = pageIterator->GetChildPage(pageTreeIndex.at(i));
        if (currentPage) 
            pageIterator = currentPage;
        else
            return nullptr;
    }
    return pageIterator;
};
