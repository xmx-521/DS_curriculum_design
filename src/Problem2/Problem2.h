#include "../../lib/List/List.h"

template <typename T>
List<T> Intersect_list(const List<T> &list_1, const List<T> &list_2)
{
    List<T> new_list;
    LinkNode<T> *p1 = list_1.GetBegin();
    LinkNode<T> *p2 = list_2.GetBegin();
    while (p1 != list_1.GetEnd() && p2 != list_2.GetEnd())
    {
        if (p1->GetData() < p2->GetData())
        {
            p1 = p1->Next();
        }
        else if (p1->GetData() == p2->GetData())
        {
            new_list.PushBack(p1->GetData());
            p1 = p1->Next();
            p2 = p2->Next();
        }
        else
        {
            p2 = p2->Next();
        }
    }
    return new_list;
}