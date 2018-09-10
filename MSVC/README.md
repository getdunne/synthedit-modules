# MSVC folder
This is where you will find the Visual Studio 2017 solution file ``modules.sln``. Open this in [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/vs/) to compile the SEMs.

You will also find pre-compiled versions of all the SEMs in the *modules32* and *modules64* folders.

## Setting up Visual Studio Community Edition
Microsoft has been kind enough to make the latest (2017) version of their *Visual Studio* IDE available free. Go to the [main Visual Studio page](https://visualstudio.microsoft.com/vs/), click on "Download Visual Studio", and select the "Community" option.

The default installation of Visual Studio Community Edition is not sufficient to build this code. When you run the installer, you'll see a list of "workloads" on the left. Make sure to check the checkbox for *Desktop development with C++*. On the right, you'll see a more compact list of individual features headed "Installation details". Check the box for *Visual C++ MFC for x86 and x64*.
