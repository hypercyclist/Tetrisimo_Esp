#ifndef WIDGETID_H
#define WIDGETID_H

#include <vector>

// This class used for generating ID to every widget. If widget was removed
// empty hole in list of ID marked as empty. Empty holes firstly will be replaced
// by new widgets.
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
