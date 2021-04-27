#ifndef WIDGETID_H
#define WIDGETID_H

#include <vector>

class WidgetId
{
    private:
        static int lastId;
        static std::vector<int> emptyIdHoles;
    public:
        static int generateId();
        static void removeId(int widgetId);
};

#endif
