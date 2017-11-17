#include <vector>
#include <stdint.h>

using namespace std;
typedef void (* pageFunc)(uint8_t colIndex);

class Page
{
  private:
    vector<Page> pages;
    pageFunc pageRenderFunc;
  public:
    Page();
    void AddRenderFunction(pageFunc pageRenderFunc);
    void AddChildPages(uint8_t pageAmount);
    void RenderPage(uint8_t colIndex);
    uint8_t GetChildPageSize();
    Page* GetChildPage(uint8_t index);
};
