#include "autorunmanager.h"
#include "/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/SharedFileList.framework/Versions/A/Headers/LSSharedFileList.h"

void AutoRunManager::addAppAsLoginItem()
{
    // Create a reference to the shared file list.
    // We are adding it to the current user only.
    // If we want to add it all users, use
    // kLSSharedFileListGlobalLoginItems instead of
    // kLSSharedFileListSessionLoginItems
//        LSSharedFileListCreate()
    LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
    if (loginItems)
    {
        // This will retrieve the path for the application
        // For example, /Applications/test.app
        CFURLRef bundleUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());

        // Insert an item to the list.
        LSSharedFileListItemRef item = LSSharedFileListInsertItemURL(loginItems, kLSSharedFileListItemLast, NULL, NULL, bundleUrl, NULL, NULL);
        if (item)
            CFRelease(item);
        else
            qDebug("failed to add login item");

        CFRelease(bundleUrl);
        CFRelease(loginItems);
    }
    else
        qDebug("failed to obtain login items");
}

void AutoRunManager::deleteAppFromLoginItem()
{
    // Create a reference to the shared file list.
    LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
    if (loginItems)
    {
        CFURLRef bundleUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());

        // Retrieve the list of Login Items
        UInt32 seedValue;
        CFArrayRef loginItemsArray = LSSharedFileListCopySnapshot(loginItems, &seedValue);

        for (CFIndex i = 0, n = CFArrayGetCount(loginItemsArray); i < n; ++i)
        {
            LSSharedFileListItemRef itemRef = (LSSharedFileListItemRef)CFArrayGetValueAtIndex(loginItemsArray, i);
            // Resolve the item with URL
            CFURLRef url;
            if (LSSharedFileListItemResolve(itemRef, 0, &url, NULL) == noErr)
            {
                bool shouldRemove = CFEqual(bundleUrl, url);
                CFRelease(url);
                if (shouldRemove)
                {
                    LSSharedFileListItemRemove(loginItems, itemRef);
                    break;
                }
            }
        }

        CFRelease(loginItemsArray);
        CFRelease(bundleUrl);
        CFRelease(loginItems);
    }
}
