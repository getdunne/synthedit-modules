# SynthEdit .vcxproj template
The Visual Studio project template file included with SynthEdit 1.3 is not ideal, as it generates project files for VS2010 not 2017, and the post-build event copies SEM files to locations other than where I want them.

Substitute the enclosed *XX_TEMPLATE_XX.vcxproj* file under e.g. *C:\Program Files\SynthEdit 1.3\template* to get nicer *.vcxproj* files for your SEMs.

## Limitation on module name capitalization
SynthEdit 1.3's "Build Code Skeleton" function, which uses this template, doesn't appear to be able to handle more than one initial capital letter in module names. "MultiiPartName" will thus become "Multipartname". Choose your names accordingly.
