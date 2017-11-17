#include <vector>

using namespace std;

class PageMap
{
  private:
    Page* page;
    vector<uint8_t> pageTreeIndex;
  public:
    PageMap(Page* page);
    bool MoveUpTree();
    bool MoveDownTree(uint8_t colIndex = 0);
    bool MoveToPreviousPage();
    bool MoveToNextPage();
    uint8_t GetColIndex();
    uint8_t GetRowIndex();   
    void RenderPage();    
    Page* GetPage(uint8_t pageOffset = 0); 
};
