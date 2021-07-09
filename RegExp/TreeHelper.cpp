#include "pch.h"
#include "TreeHelper.h"

HTREEITEM TreeHelper::FindChild(HTREEITEM item, PCWSTR name) const {
    item = _tv.GetChildItem(item);
    while (item) {
        CString text;
        _tv.GetItemText(item, text);
        if (text == name)
            return item;
        item = _tv.GetNextSiblingItem(item);
    }
    return nullptr;
}

HTREEITEM TreeHelper::FindItem(HTREEITEM hParent, PCWSTR path) {
    int start = 0;
    CString spath(path);
    if (spath[0] == L'\\') {
        // skip first
        spath = spath.Mid(spath.Find(L'\\', 1));
    }
    HTREEITEM hItem = nullptr;
    while (hParent) {
        auto name = spath.Tokenize(L"\\", start);
        if (name.IsEmpty())
            break;
        _tv.Expand(hParent, TVE_EXPAND);
        hItem = FindChild(hParent, name);
        if (!hItem)
            break;
        hParent = hItem;
    }
    return hItem;
}
