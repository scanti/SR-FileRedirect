SR-FileRedirect
===============

A mod file redirector for Saints Row the Third and Saints Row IV


*** What does it do? ***

This utility allows you to specify the directory in which you place any mod files for SRIV instead of using the default program directory. This means modders can test out stuff without having to move stuff in and out of the Saints Row directory. Please note this is very much in the beta stage. It works by modifying the game's import address table and hooking CreateFileA and GetFileAttributesA. I don't know if Steam's CEG protection will crash the game after a certain duration (however it doesn't seem to).

You can set 2 levels of redirection. The first level is the base level. This is for the mods you wish to share between profiles. The second level adds to and it a file already exists in the base directory overwrites your mods files.

*** How to compile? ***

The source is written for Visual Studio 2005. If you have a newer version you'll have to convert the project to your version. Different versions of Visual Studio have their own little quirks so you may need to tweak the code to get it to work.

It will normally compile for SRIV. To compile for SRTT add a define called SRTT. 

*** How does it work? ***

In Steam go into the Saints Row properties. Select Set Launch Options.... 

In the command box type the parameters you wish to set.

Any directories are relative to the program directory or you can use an absolute path. If the directory has spaces in it surround it with double quotes.

i.e.

-loose:"my loose files"

-loose:c:\test

*** Parameters you can set ***

-loosebase:<path of the base directory file>

This sets the base directory for your mods. You can set it to -loosebase: if you wish to use the vanilla directory for the base i.e. the Saints Row root directory.

-loose:<path of the loose mod files directory>

This will set the directory for the second level of redirection. The game will look in this directory first. If the file doesn't exist then it will look in the base directory. Finally if the file is a vpp_pc file and it doesn't exist in the base folder it will look in the game's vanilla  packfiles\pc\cache\ folder.

If you set the -loose directory but not the -loosebase directory, the game will use the -loose directory as the -loosebase directory.

-looselist:<file path of the mod file directory list file>

This will allow you to use a simple text file to tell the game which directories to look for mod files in. The text file is just a list of directories, with each directory on it's own line. The first directory in the list has the highest priority, with the priority decreasing as it goes down the list. If you wish to include the vanilla directory in the search then type a single period "." for the directory and it will search the default Saints Row directory.

Using -looselist will override the -loose and -loosebase settings. However it will be overidden when using the -vanilla parameter.

If the file you specify doesn't exist or is blank then the game will act as if you used the -vanilla parameter.

-vanilla

This will stop the game from loading any mod files including any in the vanilla game directory. Basically it will start the game completely unmodded.
{It won't work with any vpp_pc files that have been altered in the vanilla game's directory).

Adding this parameter will override all other parameters.

*** How to install? ***

1). In the Saints Row program directory rename steam_api.dll to steam_old.dll
2). Copy the steam_api.dll into the Saints Row program directory.

To uninstall just Verify the integrity of the game cache and steam will overwrite the modified steam_api.dll.

If the game updates it will overwrite the steam_api.dll and disable the utility. However it should be version agnostic so you hopefully should just be able to reinstall after an update and it will work again.

To update an installation just overwrite the old steam_api.dll file with the new steam_api.dll file.

*** Known problems ***

If the redirected directory is on a drive that doesn't exist the game runs really slowly.

*** Change log ***

Version 3.0

	Added directory caching and the abilty to search mod directories from a text file. (-looselist)

Version 2.0

    Added 2 levels of redirection. (-loose and -loosebase)
	Added support for vpp_pc files.
	Added the -vanilla parameter.
	Started on plug-in file support by adding hooks for WinMain and the when the game quits.
	Added support for Saints Row the Third.
	
Version 1.0

	The initial release.
