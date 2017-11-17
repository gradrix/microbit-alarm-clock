#include <stack>
#include <string>
#include "MicroBit.h"
#include "Clock.h"
#include "Page.h"
#include "PageMap.h"

MicroBit mb;

const int CHECK_PRESSES_AFTER = 600;
bool refreshScreen = false;
bool doNotLoopMessage = false;
unsigned int firstPress = 0;
uint8_t aPressCount = 0;
uint8_t bPressCount = 0;
Clock* mbClock = NULL;
PageMap* pageMap = NULL;

void showMessage(string message)
{
  if (refreshScreen)
  {
    char *cstr = new char[message.length() + 1];
    strcpy(cstr, message.c_str());
    ManagedString retManagedString(cstr);
    delete [] cstr;
    while(mb.display.scrollAsync(retManagedString) == MICROBIT_BUSY) {
    }
    refreshScreen = false;
  }
}

void navigate(int aPresses, int bPresses)
{
  doNotLoopMessage = false;
  mb.display.clear();
  
  if (aPresses == 1)
    pageMap->MoveToPreviousPage();  
  else if (bPresses == 1)
    pageMap->MoveToNextPage();
  else if (aPresses > 1)
    pageMap->MoveUpTree();
  else if (bPresses > 1)
    pageMap->MoveDownTree();
  
  //pageMap->RenderPage();

  aPressCount = 0;
  bPressCount = 0;
  firstPress = 0;
}

//Initiates key press
void initiatePress()
{
  if (mb.buttonA.isPressed())
  {
    bPressCount = 0;
    aPressCount++;
    if (firstPress == 0)
      firstPress = mb.systemTime();
  }
  else if(mb.buttonB.isPressed())
  {
    aPressCount = 0;
    bPressCount++;
    if (firstPress == 0)
      firstPress = mb.systemTime();
  }

  if (firstPress > 0)
  {
    if (aPressCount > 0 && mb.systemTime() - firstPress > CHECK_PRESSES_AFTER)
    {
      refreshScreen = true;
      navigate(aPressCount, 0);
    }
    else if (bPressCount > 0 && mb.systemTime() - firstPress > CHECK_PRESSES_AFTER)
    {
      refreshScreen = true;
      navigate(0, bPressCount);
    }
  }
}

void rootMenu(uint8_t pageColIndex)
{
  switch(pageColIndex)
  {
    case 0:
      doNotLoopMessage = true;
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
  showMessage(to_string(signed(pg)));
}

int main()
{
  mb.init();
  mbClock = new Clock();
  
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

  while(1)
  {
    initiatePress();

    mbClock->Tick(mb.systemTime());
    pageMap->RenderPage();
    mb.sleep(120);
  }
  delete mbClock;
  delete page;
  delete pageMap;
  
  release_fiber();
};
