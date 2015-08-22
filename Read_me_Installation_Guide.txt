Installation Guide:
1. Install Git.
2. In the git command prompt, navigate to the folder you want to download the project in. For instance:
cd D:/Test<Enter>
3. Type:
git init<Enter>
4. Type (if you are using Visual Studio 2013 or later version) (566MB download):
git remote add origin https://github.com/uzunov-dimitar/TeamRocketGame.git<Enter>
or if are using Visual Studio 2015 or later you can alternatively use (571MB download):
git remote add origin https://github.com/AdamPayne/TeamRocketGame.git<Enter>
5. Type:
git fetch origin master<Enter>
git merge FETCH_HEAD<Enter>
6. Navigate to '<the chosen folder/root>/MyGame/SpaceGame' and open the solution 'SpaceGame.sln'.
7. Open the properties for the project(Project> SpaceGame Properties...) and apply the following fixes to match your chosen root folder:
7.1 From the left:
Configuration Properties-> C/C++-> General-> Additional Include Directories:
	<absolute root directory>\MyGame\SpaceGame\SpaceGame\common\include
	<absolute root directory>\MyGame\SpaceGame\SpaceGame\tools\editor_tileless
	<absolute root directory>\MyGame\SpaceGame\SpaceGame\irrKlang\include
7.2 Again from left:
Configuration Properties-> Linker-> General-> Additional Library Directories:
	<absolute root directory>\MyGame\SpaceGame\SpaceGame\bin\win
	<absolute root directory>\MyGame\SpaceGame\SpaceGame\irrKlang\lib\Win32-visualStudio
8. Compile.

How to incorporate irrKlang in your C++ Visual Studio project:
1. Download the 32-bit version of irrKlang unless your project is 64-bit.
2. Unpack 'irrKlang-<version>/' in <folder by your choice/root> (referred from now on as <absolute root directory>). 
3. Open the properties of the project and apply the following changes:
3.1 Add in:
Configuration Properties-> C/C++-> General-> Additional Include Directories:
	<absolute root directory>\include
3.2 Add in:
Configuration Properties-> Linker-> General-> Additional Library Directories:
	<absolute root directory>\lib\Win32-visualStudio
3.3 Add in:
Configuration Properties-> Linker-> Input-> Additional Dependencies:
	<other dependencies>;irrKlang.lib
4. Copy/Paste irrklang.dll from 
'<absolute root directory>/bin/win32-visualStudio'
into your Debug/Release directory as well as the directory containing your project file.