#include "WidgetId.h"

int WidgetId::lastId = 0;

std::vector<int> WidgetId::emptyIdHoles;

int WidgetId::generateId()
{
    int tempId;
    if (!emptyIdHoles.empty())
    {
        tempId = emptyIdHoles[0];
        emptyIdHoles.erase( emptyIdHoles.begin() );
        return tempId;
    }
    tempId = lastId;
    lastId++;
    return tempId;
}

void WidgetId::removeId(int widgetId)
{
    emptyIdHoles.push_back(widgetId);
}
