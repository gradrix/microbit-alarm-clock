#include <stack>
#include <string>
#include <iostream>
#include "Clock.h"
#include "Page.h"
#include "PageMap.h"

using namespace std;

const int CHECK_PRESSES_AFTER = 600;
int8_t firstPress = 0;
int8_t aPressCount = 0;
int8_t bPressCount = 0;
Clock* mbClock = NULL;
PageMap* pageMap = NULL;

void showMessage(string message)
{
  cout << message << endl;
}

void navigate(int aPresses, int bPresses)
{
  if (aPresses == 1)
    pageMap->MoveToPreviousPage();  
  else if (bPresses == 1)
    pageMap->MoveToNextPage();
  else if (aPresses > 1)
    pageMap->MoveUpTree();
  else if (bPresses > 1)
    pageMap->MoveDownTree();
    
  
  pageMap->RenderPage();

  aPressCount = 0;
  bPressCount = 0;
  firstPress = 0;
}

void rootMenu(uint8_t pageColIndex)
{
  switch(pageColIndex)
  {
    case 0:
      showMessage(".");
      break;
    case 1:
      showMessage(mbClock->Show());
      break;
    case 2:
      showMessage("0000-00-00");
  }
}

void clockMenu(uint8_t pageColIndex)
{
  switch(pageColIndex)
  {
    case 0:
      showMessage("Hour");
      break;
    case 1:
      showMessage("Minute");
      break;
    case 2:
      showMessage("Second");
      break;
  }
}

void dateMenu(uint8_t pageColIndex)
{
  switch(pageColIndex)
  {
    case 0:
      showMessage("Year");
      break;
    case 1:
      showMessage("Month");
      break;
    case 2:
      showMessage("Day");
      break;
  }
}

void dummy(uint8_t pg)
{
  showMessage("Shite");
}

int main()
{
  //Root page
  Page* page = new Page();
  page->AddRenderFunction(rootMenu);
  page->AddChildPages(3);

  //2nd level
  page->GetChildPage(1)->AddRenderFunction(clockMenu);
  page->GetChildPage(1)->AddChildPages(3);
  page->GetChildPage(2)->AddRenderFunction(dateMenu);
  page->GetChildPage(2)->AddChildPages(3);
  
  //3rd level
  page->GetChildPage(1)->GetChildPage(0)->AddChildPages(1);
  page->GetChildPage(1)->GetChildPage(0)->AddRenderFunction(dummy);
  page->GetChildPage(1)->GetChildPage(1)->AddChildPages(1);
  page->GetChildPage(1)->GetChildPage(1)->AddRenderFunction(dummy);
  page->GetChildPage(1)->GetChildPage(2)->AddChildPages(1);
  page->GetChildPage(1)->GetChildPage(2)->AddRenderFunction(dummy);
  page->GetChildPage(2)->GetChildPage(0)->AddChildPages(1);
  page->GetChildPage(2)->GetChildPage(0)->AddRenderFunction(dummy);
  page->GetChildPage(2)->GetChildPage(1)->AddChildPages(1);
  page->GetChildPage(2)->GetChildPage(1)->AddRenderFunction(dummy);
  page->GetChildPage(2)->GetChildPage(2)->AddChildPages(1);
  page->GetChildPage(2)->GetChildPage(2)->AddRenderFunction(dummy);
  
  pageMap = new PageMap(page);
  mbClock = new Clock();
 // Page* pg = pageMap->GetPage();
  
  
  navigate(0, 1);
  navigate(0, 2);
  navigate(0, 2);
  navigate(0, 2);
  navigate(2, 0);
  navigate(1, 0);
  navigate(2, 0);
    navigate(0, 2);
};
