SR-FileRedirect
===============

A mod file redirector for Saints Row the Third and Saints Row IV


*** What does it do? ***

This utility allows you to specify the directory in which you place any mod files for SRIV instead of using the default program directory. This means modders can test out stuff without having to move stuff in and out of the Saints Row directory. Please note this is very much in the beta stage. It works by modifying the game's import address table and hooking CreateFileA and GetFileAttributesA. I don't know if Steam's CEG protection will crash the game after a certain duration (however it doesn't seem to).

*** How to compile? ***

The source is written for Visual Studio 2005. If you have a newer version you'll have to convert the project to your version. Different versions of Visual Studio have their own little quirks so you may need to tweak the code to get it to work.

It will normally compile for SRIV. To compile for SRTT add a define called SRTT. 

*** How does it work? ***

In Steam go into the Saints Row IV or Saints Row the Third properties. Select Set Launch Options.... 

In the command box type -loose:<directory your of your mod files>

The directory is relative to the program directory or you can use an absolute path. If the directory has spaces in it surround it with double quotes.

i.e.

-loose:"my loose files"

-loose:c:\test

*** How to install? ***

1). In the Saints Row program directory rename steam_api.dll to steam_old.dll
2). Copy the steam_api.dll into the Saints Row program directory.

To uninstall just Verify the integrity of the game cache and steam will overwrite the modified steam_api.dll.

If the game updates it will overwrite the steam_api.dll and disable the utility. However it should be version agnostic so you hopefully should just be able to reinstall after an update and it will work again.

*** Known problems ***

If the redirected directory is on a drive that doesn't exist the game runs really slowly.
